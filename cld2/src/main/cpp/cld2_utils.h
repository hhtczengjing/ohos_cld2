//
// Created on 2025/5/18.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef OHOS_CLD2_CLD2_UTILS_H
#define OHOS_CLD2_CLD2_UTILS_H

#include "cld2.h"

namespace ohos_cld2 {

struct CldLanguage {
    const char *name;
    const char *code;

	CldLanguage(const char *name, const char *code) : name(name), code(code) {}
};

struct CldDetected {
    const char *name;

	CldDetected(const char *name) : name(name) {}
};

struct CldEncoding {
    const char *name;
    CLD2::Encoding encoding;

	CldEncoding(const char *name, CLD2::Encoding encoding) : name(name), encoding(encoding) {}
};

class Constants {
public:
    static Constants& getInstance() {
        static Constants instance;
        return instance;
    }
    
    std::vector<CldLanguage>* getLanguages();
    std::vector<CldDetected>* getDetected();
    std::vector<CldEncoding>* getEncodings();
    
    CLD2::Language getLanguageFromName(const char* name);
    int getEncodingFromName(const char* name);
    const char* getLanguageName(CLD2::Language lang);
    const char* getLanguageCode(CLD2::Language lang);
    
private:
    std::vector<CldLanguage> *languages;
    std::vector<CldDetected> *detected;
    std::vector<CldEncoding> *encodings;

    Constants();
    Constants(Constants const&);
    void operator=(Constants const&);

    void init();
    void initLanguages();
    void initDetected();
    void initEncodings();
};

}

#endif //OHOS_CLD2_CLD2_UTILS_H
