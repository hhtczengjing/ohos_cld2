#include "cld2_utils.h"
#include "napi/native_api.h"
#include "cld2.h"
#include "napi_utils.h"

struct CLDOutput {
    CLD2::Language language3[3];
    int percent3[3];
    double normalized_score3[3];
    CLD2::ResultChunkVector resultChunkVector;
    int textBytesFound;
    bool isReliable;
};

napi_value UnpackOutputToJS(napi_env env, napi_callback_info info, std::unique_ptr<CLDOutput> output) {
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

static napi_value Detect(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1] = {nullptr};
    NAPI_CALL(napi_get_cb_info(env, info, &argc, args, nullptr, nullptr));
    
    std::string inputText = NValueToString(env, args[0]);
    
    CLD2::CLDHints hints;
    hints.tld_hint = 0;
    hints.content_language_hint = 0;
    hints.language_hint = CLD2::UNKNOWN_LANGUAGE;
    hints.encoding_hint = CLD2::UNKNOWN_ENCODING;
    
    int flags = 0;
    
    std::unique_ptr<CLDOutput> output(new CLDOutput);
    
    CLD2::ExtDetectLanguageSummary(
      inputText.c_str(),
      inputText.length(),
      true,
      &hints,
      flags,
      output->language3,
      output->percent3,
      output->normalized_score3,
      &output->resultChunkVector,
      &output->textBytesFound,
      &output->isReliable
    );

    return UnpackOutputToJS(env, info,std::move(output));
}

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        { "detect", nullptr, Detect, nullptr, nullptr, nullptr, napi_default, nullptr }
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
