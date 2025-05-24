#include "cld2_constants.h"
#include "napi/native_api.h"
#include "cld2.h"
#include "napi_utils.h"

struct CLDInput {
    std::string bytes;
    std::string languageHint;
    std::string encodingHint;
    std::string tldHint;
    std::string httpHint;
    int numBytes;
    bool isPlainText;
    bool bestEffort;
};

struct CLDOutput {
    CLD2::Language language3[3];
    int percent3[3];
    double normalized_score3[3];
    CLD2::ResultChunkVector resultChunkVector;
    int textBytesFound;
    bool isReliable;
};

struct CLDCallback {
    napi_async_work asyncWork = nullptr;
    napi_deferred deferred = nullptr;
    napi_ref callback = nullptr;
    CLDInput *input = nullptr;
    CLDOutput *output = nullptr;
    
    ~CLDCallback() {
        if (input != nullptr) {
            delete input;
            input = nullptr;
        }
        if (output != nullptr) {
            delete output;
            output = nullptr;
        }
    }
};

static CLDInput* UnpackInputFromJSArgs(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2] = {nullptr};
    NAPI_CALL(napi_get_cb_info(env, info, &argc, args, nullptr, nullptr));
    
    std::string inputText = NValueToString(env, args[0]);
    napi_value optionsNapiValue = args[1];
    
    CLDInput* input = new CLDInput();
    
    input->bytes = inputText.c_str();
    input->numBytes = input->bytes.length();
    
    if (!IsNValueUndefined(env, optionsNapiValue)) {
        // isHTML
        napi_value isHTMLNapiValue;
        napi_get_named_property(env, optionsNapiValue, "isHTML", &isHTMLNapiValue);
        bool isHTML = NValueToBool(env, isHTMLNapiValue);
        input->isPlainText = isHTML;
        
        // languageHint
        napi_value languageHintNapiValue;
        napi_get_named_property(env, optionsNapiValue, "languageHint", &languageHintNapiValue);
        std::string languageHint = NValueToString(env, languageHintNapiValue, true);
        input->languageHint = languageHint;
        
        // encodingHint
        napi_value encodingHintNapiValue;
        napi_get_named_property(env, optionsNapiValue, "encodingHint", &encodingHintNapiValue);
        std::string encodingHint = NValueToString(env, encodingHintNapiValue, true);
        input->encodingHint = encodingHint;
        
        // tldHint
        napi_value tldHintNapiValue;
        napi_get_named_property(env, optionsNapiValue, "tldHint", &tldHintNapiValue);
        std::string tldHint = NValueToString(env, tldHintNapiValue, true);
        input->tldHint = tldHint;
        
        // httpHint
        napi_value httpHintNapiValue;
        napi_get_named_property(env, optionsNapiValue, "httpHint", &httpHintNapiValue);
        std::string httpHint = NValueToString(env, httpHintNapiValue, true);
        input->httpHint = httpHint;
        
        // bestEffort
        napi_value bestEffortNapiValue;
        napi_get_named_property(env, optionsNapiValue, "bestEffort", &bestEffortNapiValue);
        bool bestEffort = NValueToBool(env, bestEffortNapiValue);
        input->bestEffort = bestEffort;
    }
    
    return input;
}

static napi_value UnpackOutputToJS(napi_env env, const CLDOutput* output) {
    napi_value languages = nullptr;
    napi_create_array(env, &languages);
    int languageIdx = 0;
    for (size_t resultIdx = 0; resultIdx < 3; resultIdx++) {
        CLD2::Language lang = output->language3[resultIdx];

        if (lang == CLD2::UNKNOWN_LANGUAGE) {
            continue;
        }
        
        napi_value item;
        napi_create_object(env, &item);
        napi_set_named_property(env, item, "name", StringToNValue(env, std::string(ohos_cld2::Constants::getInstance().getLanguageName(lang))));
        napi_set_named_property(env, item, "code", StringToNValue(env, std::string(ohos_cld2::Constants::getInstance().getLanguageCode(lang))));
        napi_set_named_property(env, item, "percent", Int32ToNValue(env, output->percent3[resultIdx]));
        napi_set_named_property(env, item, "score", DoubleToNValue(env, output->normalized_score3[resultIdx]));

        napi_set_element(env, languages, languageIdx++, item);
    }

    int chunkIdx = 0;
    napi_value chunks = nullptr;
    napi_create_array(env, &chunks);
    for (size_t resultIdx = 0; resultIdx < output->resultChunkVector.size(); resultIdx++) {
        CLD2::ResultChunk chunk = output->resultChunkVector.at(resultIdx);
        CLD2::Language lang = static_cast<CLD2::Language>(chunk.lang1);
        
        if (lang == CLD2::UNKNOWN_LANGUAGE) {
            continue;
        }
        
        napi_value item;
        napi_create_object(env, &item);
        napi_set_named_property(env, item, "name", StringToNValue(env, std::string(ohos_cld2::Constants::getInstance().getLanguageName(lang))));
        napi_set_named_property(env, item, "code", StringToNValue(env, std::string(ohos_cld2::Constants::getInstance().getLanguageCode(lang))));
        napi_set_named_property(env, item, "offset", Int32ToNValue(env, chunk.offset));
        napi_set_named_property(env, item, "bytes", Int32ToNValue(env, chunk.bytes));
        napi_set_element(env, chunks, chunkIdx++, item);
    }
    
    napi_value results;
    napi_create_object(env, &results);
    napi_set_named_property(env, results, "reliable", BoolToNValue(env, output->isReliable));
    napi_set_named_property(env, results, "textBytes", Int32ToNValue(env, output->textBytesFound));
    napi_set_named_property(env, results, "languages", languages);
    napi_set_named_property(env, results, "chunks", chunks);
    return results;
}

static CLDOutput* DetectLanguage(const CLDInput* input) {
    CLD2::CLDHints hints;
    hints.tld_hint = 0;
    hints.content_language_hint = 0;
    hints.language_hint = CLD2::UNKNOWN_LANGUAGE;
    hints.encoding_hint = CLD2::UNKNOWN_ENCODING;
    
    if (input->languageHint.length() > 0) {
        hints.language_hint = ohos_cld2::Constants::getInstance().getLanguageFromName(input->languageHint.c_str());
    }
    
    if (input->encodingHint.length() > 0) {
        hints.encoding_hint = ohos_cld2::Constants::getInstance().getEncodingFromName(input->encodingHint.c_str());
    }
    
    if (input->tldHint.length() > 0) {
        hints.tld_hint = input->tldHint.c_str();
    }
    
    if (input->httpHint.length() > 0) {
        hints.content_language_hint = input->httpHint.c_str();
    }
    
    int flags = 0;
    if (input->bestEffort) {
        flags |= CLD2::kCLDFlagBestEffort;
    }
    
    CLDOutput *output = new CLDOutput();
    CLD2::ExtDetectLanguageSummary(
      input->bytes.c_str(),
      input->numBytes,
      input->isPlainText,
      &hints,
      flags,
      output->language3,
      output->percent3,
      output->normalized_score3,
      &output->resultChunkVector,
      &output->textBytesFound,
      &output->isReliable
    );
    return output;
}

static napi_value DetectSync(napi_env env, napi_callback_info info) {
    auto input = UnpackInputFromJSArgs(env, info);
    auto output = DetectLanguage(input);
    auto result = UnpackOutputToJS(env,output);
    delete input;
    delete output;
    return result;
}

static napi_value DetectAsync(napi_env env, napi_callback_info info) {
    auto input = UnpackInputFromJSArgs(env, info);
    
    napi_value promise = nullptr;
    napi_deferred deferred = nullptr;
    napi_create_promise(env, &deferred, &promise);
    
    auto callbackData = new CLDCallback();
    callbackData->deferred = deferred;
    callbackData->input = input;
    
    napi_value resourceName = nullptr;
    napi_create_string_utf8(env, "AsyncCallback", NAPI_AUTO_LENGTH, &resourceName);
    
    // 创建异步任务
    napi_create_async_work(env, nullptr, resourceName, [](napi_env env, void *data){
        CLDCallback *callbackData = reinterpret_cast<CLDCallback *>(data);
        auto output = DetectLanguage(callbackData->input);
        callbackData->output = output;
    }, [](napi_env env, napi_status status, void *data){
        CLDCallback *callbackData = reinterpret_cast<CLDCallback *>(data);
        auto output = callbackData->output;
        if (output != nullptr) {
            auto result = UnpackOutputToJS(env,output);
            napi_resolve_deferred(env, callbackData->deferred, result);
        } else {
            napi_reject_deferred(env, callbackData->deferred, nullptr);
        }
        napi_delete_async_work(env, callbackData->asyncWork);
        delete callbackData;
    }, callbackData, &callbackData->asyncWork);
    // 将异步任务加入队列
    napi_queue_async_work(env, callbackData->asyncWork);
    return promise;
}

static napi_value DetectedLanguages(napi_env env, napi_callback_info info) {
    auto rawDetected = ohos_cld2::Constants::getInstance().getDetected();
    std::vector<std::string> languages;
    for (size_t i = 0; i < rawDetected->size(); i++) {
        auto rawLanguage = rawDetected->at(i);
        languages.push_back(rawLanguage.name);
    }
    return StringArrayToNValue(env, languages);
}

static napi_value Languages(napi_env env, napi_callback_info info) {
    napi_value languages;
    napi_create_object(env, &languages);
    auto rawLanguages = ohos_cld2::Constants::getInstance().getLanguages();
    for (size_t i = 0; i < rawLanguages->size(); i++) {
        auto rawLanguage = rawLanguages->at(i);
        napi_set_named_property(env, languages, rawLanguage.name, StringToNValue(env, rawLanguage.code));
    }
    return languages;
}

static napi_value Encodings(napi_env env, napi_callback_info info) {
    auto rawEncodings = ohos_cld2::Constants::getInstance().getEncodings();
    auto numEncodings = rawEncodings->size();
    std::vector<std::string> encodings;
    for (size_t i = 0; i < numEncodings; i++) {
        auto rawEncoding = rawEncodings->at(i);
        encodings.push_back(rawEncoding.name);
    }
    return StringArrayToNValue(env, encodings);
}

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        { "detectSync", nullptr, DetectSync, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "detectAsync", nullptr, DetectAsync, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getDetectedLanguages", nullptr, DetectedLanguages, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getLanguages", nullptr, Languages, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getEncodings", nullptr, Encodings, nullptr, nullptr, nullptr, napi_default, nullptr }
    };
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}
EXTERN_C_END

static napi_module demoModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "cld2",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void RegisterCld2Module(void)
{
    napi_module_register(&demoModule);
}
