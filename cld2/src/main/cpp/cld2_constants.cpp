//
// Created on 2025/5/18.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "cld2_constants.h"
#include <string>
#include <vector>

namespace CLD2 {
  extern const int kNameToLanguageSize;
  extern const CharIntPair kNameToLanguage[];
}

namespace ohos_cld2 {

Constants::Constants() {
    init();
}

std::vector<CldLanguage>* Constants::getLanguages() {
    return languages;
}

std::vector<CldDetected>* Constants::getDetected() {
    return detected;
}

std::vector<CldEncoding>* Constants::getEncodings() {
    return encodings;
}

CLD2::Language Constants::getLanguageFromName(const char* name) {
    return CLD2::GetLanguageFromName(name);
}

int Constants::getEncodingFromName(const char* name) {
    std::vector<CldEncoding>* encodings = Constants::getInstance().getEncodings();
    for(std::vector<CldEncoding>::size_type i = 0; i < encodings->size(); i++) {
      CldEncoding encoding = encodings->at(i);
      if (!strcasecmp(encoding.name, name)) {
        return encoding.encoding;
      }
    }

    return CLD2::UNKNOWN_ENCODING;
}

const char* Constants::getLanguageName(CLD2::Language lang) {
    return CLD2::LanguageName(lang);
}

const char* Constants::getLanguageCode(CLD2::Language lang) {
    return CLD2::LanguageCode(lang);
}

void Constants::init() {
    initLanguages();
    initDetected();
    initEncodings();
}

void Constants::initLanguages() {
    languages = new std::vector<CldLanguage>();
    
    for(int i = 0; i < CLD2::kNameToLanguageSize; i++) {
      const char *name = CLD2::kNameToLanguage[i].s;
      if (!strcmp(name, "Unknown")) {
        continue;
      }

      CLD2::Language lang = CLD2::GetLanguageFromName(name);
      if (lang == CLD2::UNKNOWN_LANGUAGE) {
        continue;
      }

      languages->insert(languages->end(), CldLanguage(LanguageName(lang), LanguageCode(lang)));
    }
}

void Constants::initDetected() {
    detected = new std::vector<CldDetected>();
    
    detected->insert(detected->end(), CldDetected("ABKHAZIAN"));
    detected->insert(detected->end(), CldDetected("AFAR"));
    detected->insert(detected->end(), CldDetected("AFRIKAANS"));
    detected->insert(detected->end(), CldDetected("AKAN"));
    detected->insert(detected->end(), CldDetected("ALBANIAN"));
    detected->insert(detected->end(), CldDetected("AMHARIC"));
    detected->insert(detected->end(), CldDetected("ARABIC"));
    detected->insert(detected->end(), CldDetected("ARMENIAN"));
    detected->insert(detected->end(), CldDetected("ASSAMESE"));
    detected->insert(detected->end(), CldDetected("AYMARA"));
    detected->insert(detected->end(), CldDetected("AZERBAIJANI"));
    detected->insert(detected->end(), CldDetected("BASHKIR"));
    detected->insert(detected->end(), CldDetected("BASQUE"));
    detected->insert(detected->end(), CldDetected("BELARUSIAN"));
    detected->insert(detected->end(), CldDetected("BENGALI"));
    detected->insert(detected->end(), CldDetected("BIHARI"));
    detected->insert(detected->end(), CldDetected("BISLAMA"));
    detected->insert(detected->end(), CldDetected("BOSNIAN"));
    detected->insert(detected->end(), CldDetected("BRETON"));
    detected->insert(detected->end(), CldDetected("BULGARIAN"));
    detected->insert(detected->end(), CldDetected("BURMESE"));
    detected->insert(detected->end(), CldDetected("CATALAN"));
    detected->insert(detected->end(), CldDetected("CEBUANO"));
    detected->insert(detected->end(), CldDetected("CHEROKEE"));
    detected->insert(detected->end(), CldDetected("CORSICAN"));
    detected->insert(detected->end(), CldDetected("CROATIAN"));
    detected->insert(detected->end(), CldDetected("CZECH"));
    detected->insert(detected->end(), CldDetected("Chinese"));
    detected->insert(detected->end(), CldDetected("ChineseT"));
    detected->insert(detected->end(), CldDetected("DANISH"));
    detected->insert(detected->end(), CldDetected("DHIVEHI"));
    detected->insert(detected->end(), CldDetected("DUTCH"));
    detected->insert(detected->end(), CldDetected("DZONGKHA"));
    detected->insert(detected->end(), CldDetected("ENGLISH"));
    detected->insert(detected->end(), CldDetected("ESPERANTO"));
    detected->insert(detected->end(), CldDetected("ESTONIAN"));
    detected->insert(detected->end(), CldDetected("FAROESE"));
    detected->insert(detected->end(), CldDetected("FIJIAN"));
    detected->insert(detected->end(), CldDetected("FINNISH"));
    detected->insert(detected->end(), CldDetected("FRENCH"));
    detected->insert(detected->end(), CldDetected("FRISIAN"));
    detected->insert(detected->end(), CldDetected("GALICIAN"));
    detected->insert(detected->end(), CldDetected("GANDA"));
    detected->insert(detected->end(), CldDetected("GEORGIAN"));
    detected->insert(detected->end(), CldDetected("GERMAN"));
    detected->insert(detected->end(), CldDetected("GREEK"));
    detected->insert(detected->end(), CldDetected("GREENLANDIC"));
    detected->insert(detected->end(), CldDetected("GUARANI"));
    detected->insert(detected->end(), CldDetected("GUJARATI"));
    detected->insert(detected->end(), CldDetected("HAITIAN_CREOLE"));
    detected->insert(detected->end(), CldDetected("HAUSA"));
    detected->insert(detected->end(), CldDetected("HAWAIIAN"));
    detected->insert(detected->end(), CldDetected("HEBREW"));
    detected->insert(detected->end(), CldDetected("HINDI"));
    detected->insert(detected->end(), CldDetected("HMONG"));
    detected->insert(detected->end(), CldDetected("HUNGARIAN"));
    detected->insert(detected->end(), CldDetected("ICELANDIC"));
    detected->insert(detected->end(), CldDetected("IGBO"));
    detected->insert(detected->end(), CldDetected("INDONESIAN"));
    detected->insert(detected->end(), CldDetected("INTERLINGUA"));
    detected->insert(detected->end(), CldDetected("INTERLINGUE"));
    detected->insert(detected->end(), CldDetected("INUKTITUT"));
    detected->insert(detected->end(), CldDetected("INUPIAK"));
    detected->insert(detected->end(), CldDetected("IRISH"));
    detected->insert(detected->end(), CldDetected("ITALIAN"));
    detected->insert(detected->end(), CldDetected("JAVANESE"));
    detected->insert(detected->end(), CldDetected("Japanese"));
    detected->insert(detected->end(), CldDetected("KANNADA"));
    detected->insert(detected->end(), CldDetected("KASHMIRI"));
    detected->insert(detected->end(), CldDetected("KAZAKH"));
    detected->insert(detected->end(), CldDetected("KHASI"));
    detected->insert(detected->end(), CldDetected("KHMER"));
    detected->insert(detected->end(), CldDetected("KINYARWANDA"));
    detected->insert(detected->end(), CldDetected("KURDISH"));
    detected->insert(detected->end(), CldDetected("KYRGYZ"));
    detected->insert(detected->end(), CldDetected("Korean"));
    detected->insert(detected->end(), CldDetected("LAOTHIAN"));
    detected->insert(detected->end(), CldDetected("LATIN"));
    detected->insert(detected->end(), CldDetected("LATVIAN"));
    detected->insert(detected->end(), CldDetected("LIMBU"));
    detected->insert(detected->end(), CldDetected("LINGALA"));
    detected->insert(detected->end(), CldDetected("LITHUANIAN"));
    detected->insert(detected->end(), CldDetected("LUXEMBOURGISH"));
    detected->insert(detected->end(), CldDetected("MACEDONIAN"));
    detected->insert(detected->end(), CldDetected("MALAGASY"));
    detected->insert(detected->end(), CldDetected("MALAY"));
    detected->insert(detected->end(), CldDetected("MALAYALAM"));
    detected->insert(detected->end(), CldDetected("MALTESE"));
    detected->insert(detected->end(), CldDetected("MANX"));
    detected->insert(detected->end(), CldDetected("MAORI"));
    detected->insert(detected->end(), CldDetected("MARATHI"));
    detected->insert(detected->end(), CldDetected("MAURITIAN_CREOLE"));
    detected->insert(detected->end(), CldDetected("MONGOLIAN"));
    detected->insert(detected->end(), CldDetected("NAURU"));
    detected->insert(detected->end(), CldDetected("NDEBELE"));
    detected->insert(detected->end(), CldDetected("NEPALI"));
    detected->insert(detected->end(), CldDetected("NORWEGIAN"));
    detected->insert(detected->end(), CldDetected("NORWEGIAN_N"));
    detected->insert(detected->end(), CldDetected("NYANJA"));
    detected->insert(detected->end(), CldDetected("OCCITAN"));
    detected->insert(detected->end(), CldDetected("ORIYA"));
    detected->insert(detected->end(), CldDetected("OROMO"));
    detected->insert(detected->end(), CldDetected("PASHTO"));
    detected->insert(detected->end(), CldDetected("PEDI"));
    detected->insert(detected->end(), CldDetected("PERSIAN"));
    detected->insert(detected->end(), CldDetected("POLISH"));
    detected->insert(detected->end(), CldDetected("PORTUGUESE"));
    detected->insert(detected->end(), CldDetected("PUNJABI"));
    detected->insert(detected->end(), CldDetected("QUECHUA"));
    detected->insert(detected->end(), CldDetected("RHAETO_ROMANCE"));
    detected->insert(detected->end(), CldDetected("ROMANIAN"));
    detected->insert(detected->end(), CldDetected("RUNDI"));
    detected->insert(detected->end(), CldDetected("RUSSIAN"));
    detected->insert(detected->end(), CldDetected("SAMOAN"));
    detected->insert(detected->end(), CldDetected("SANGO"));
    detected->insert(detected->end(), CldDetected("SANSKRIT"));
    detected->insert(detected->end(), CldDetected("SCOTS"));
    detected->insert(detected->end(), CldDetected("SCOTS_GAELIC"));
    detected->insert(detected->end(), CldDetected("SERBIAN"));
    detected->insert(detected->end(), CldDetected("SESELWA"));
    detected->insert(detected->end(), CldDetected("SESOTHO"));
    detected->insert(detected->end(), CldDetected("SHONA"));
    detected->insert(detected->end(), CldDetected("SINDHI"));
    detected->insert(detected->end(), CldDetected("SINHALESE"));
    detected->insert(detected->end(), CldDetected("SISWANT"));
    detected->insert(detected->end(), CldDetected("SLOVAK"));
    detected->insert(detected->end(), CldDetected("SLOVENIAN"));
    detected->insert(detected->end(), CldDetected("SOMALI"));
    detected->insert(detected->end(), CldDetected("SPANISH"));
    detected->insert(detected->end(), CldDetected("SUNDANESE"));
    detected->insert(detected->end(), CldDetected("SWAHILI"));
    detected->insert(detected->end(), CldDetected("SWEDISH"));
    detected->insert(detected->end(), CldDetected("SYRIAC"));
    detected->insert(detected->end(), CldDetected("TAGALOG"));
    detected->insert(detected->end(), CldDetected("TAJIK"));
    detected->insert(detected->end(), CldDetected("TAMIL"));
    detected->insert(detected->end(), CldDetected("TATAR"));
    detected->insert(detected->end(), CldDetected("TELUGU"));
    detected->insert(detected->end(), CldDetected("THAI"));
    detected->insert(detected->end(), CldDetected("TIBETAN"));
    detected->insert(detected->end(), CldDetected("TIGRINYA"));
    detected->insert(detected->end(), CldDetected("TONGA"));
    detected->insert(detected->end(), CldDetected("TSONGA"));
    detected->insert(detected->end(), CldDetected("TSWANA"));
    detected->insert(detected->end(), CldDetected("TURKISH"));
    detected->insert(detected->end(), CldDetected("TURKMEN"));
    detected->insert(detected->end(), CldDetected("UIGHUR"));
    detected->insert(detected->end(), CldDetected("UKRAINIAN"));
    detected->insert(detected->end(), CldDetected("URDU"));
    detected->insert(detected->end(), CldDetected("UZBEK"));
    detected->insert(detected->end(), CldDetected("VENDA"));
    detected->insert(detected->end(), CldDetected("VIETNAMESE"));
    detected->insert(detected->end(), CldDetected("VOLAPUK"));
    detected->insert(detected->end(), CldDetected("WARAY_PHILIPPINES"));
    detected->insert(detected->end(), CldDetected("WELSH"));
    detected->insert(detected->end(), CldDetected("WOLOF"));
    detected->insert(detected->end(), CldDetected("XHOSA"));
    detected->insert(detected->end(), CldDetected("X_Buginese"));
    detected->insert(detected->end(), CldDetected("X_Gothic"));
    detected->insert(detected->end(), CldDetected("X_KLINGON"));
    detected->insert(detected->end(), CldDetected("X_PIG_LATIN"));
    detected->insert(detected->end(), CldDetected("YIDDISH"));
    detected->insert(detected->end(), CldDetected("YORUBA"));
    detected->insert(detected->end(), CldDetected("ZHUANG"));
    detected->insert(detected->end(), CldDetected("ZULU"));
}

void Constants::initEncodings() {
    encodings = new std::vector<CldEncoding>();
    
    encodings->insert(encodings->end(), CldEncoding("ISO_8859_1", CLD2::ISO_8859_1));
    encodings->insert(encodings->end(), CldEncoding("ISO_8859_2", CLD2::ISO_8859_2));
    encodings->insert(encodings->end(), CldEncoding("ISO_8859_3", CLD2::ISO_8859_3));
    encodings->insert(encodings->end(), CldEncoding("ISO_8859_4", CLD2::ISO_8859_4));
    encodings->insert(encodings->end(), CldEncoding("ISO_8859_5", CLD2::ISO_8859_5));
    encodings->insert(encodings->end(), CldEncoding("ISO_8859_6", CLD2::ISO_8859_6));
    encodings->insert(encodings->end(), CldEncoding("ISO_8859_7", CLD2::ISO_8859_7));
    encodings->insert(encodings->end(), CldEncoding("ISO_8859_8", CLD2::ISO_8859_8));
    encodings->insert(encodings->end(), CldEncoding("ISO_8859_9", CLD2::ISO_8859_9));
    encodings->insert(encodings->end(), CldEncoding("ISO_8859_10", CLD2::ISO_8859_10));
    encodings->insert(encodings->end(), CldEncoding("JAPANESE_EUC_JP", CLD2::JAPANESE_EUC_JP));
    encodings->insert(encodings->end(), CldEncoding("JAPANESE_SHIFT_JIS", CLD2::JAPANESE_SHIFT_JIS));
    encodings->insert(encodings->end(), CldEncoding("JAPANESE_JIS", CLD2::JAPANESE_JIS));
    encodings->insert(encodings->end(), CldEncoding("CHINESE_BIG5", CLD2::CHINESE_BIG5));
    encodings->insert(encodings->end(), CldEncoding("CHINESE_GB", CLD2::CHINESE_GB));
    encodings->insert(encodings->end(), CldEncoding("CHINESE_EUC_CN", CLD2::CHINESE_EUC_CN));
    encodings->insert(encodings->end(), CldEncoding("KOREAN_EUC_KR", CLD2::KOREAN_EUC_KR));
    encodings->insert(encodings->end(), CldEncoding("UNICODE_UNUSED", CLD2::UNICODE_UNUSED));
    encodings->insert(encodings->end(), CldEncoding("CHINESE_EUC_DEC", CLD2::CHINESE_EUC_DEC));
    encodings->insert(encodings->end(), CldEncoding("CHINESE_CNS", CLD2::CHINESE_CNS));
    encodings->insert(encodings->end(), CldEncoding("CHINESE_BIG5_CP950", CLD2::CHINESE_BIG5_CP950));
    encodings->insert(encodings->end(), CldEncoding("JAPANESE_CP932", CLD2::JAPANESE_CP932));
    encodings->insert(encodings->end(), CldEncoding("UTF8", CLD2::UTF8));
    encodings->insert(encodings->end(), CldEncoding("ASCII_7BIT", CLD2::ASCII_7BIT));
    encodings->insert(encodings->end(), CldEncoding("RUSSIAN_KOI8_R", CLD2::RUSSIAN_KOI8_R));
    encodings->insert(encodings->end(), CldEncoding("RUSSIAN_CP1251", CLD2::RUSSIAN_CP1251));
    encodings->insert(encodings->end(), CldEncoding("MSFT_CP1252", CLD2::MSFT_CP1252));
    encodings->insert(encodings->end(), CldEncoding("RUSSIAN_KOI8_RU", CLD2::RUSSIAN_KOI8_RU));
    encodings->insert(encodings->end(), CldEncoding("MSFT_CP1250", CLD2::MSFT_CP1250));
    encodings->insert(encodings->end(), CldEncoding("ISO_8859_15", CLD2::ISO_8859_15));
    encodings->insert(encodings->end(), CldEncoding("MSFT_CP1254", CLD2::MSFT_CP1254));
    encodings->insert(encodings->end(), CldEncoding("MSFT_CP1257", CLD2::MSFT_CP1257));
    encodings->insert(encodings->end(), CldEncoding("ISO_8859_11", CLD2::ISO_8859_11));
    encodings->insert(encodings->end(), CldEncoding("MSFT_CP874", CLD2::MSFT_CP874));
    encodings->insert(encodings->end(), CldEncoding("MSFT_CP1256", CLD2::MSFT_CP1256));
    encodings->insert(encodings->end(), CldEncoding("MSFT_CP1255", CLD2::MSFT_CP1255));
    encodings->insert(encodings->end(), CldEncoding("ISO_8859_8_I", CLD2::ISO_8859_8_I));
    encodings->insert(encodings->end(), CldEncoding("HEBREW_VISUAL", CLD2::HEBREW_VISUAL));
    encodings->insert(encodings->end(), CldEncoding("CZECH_CP852", CLD2::CZECH_CP852));
    encodings->insert(encodings->end(), CldEncoding("CZECH_CSN_369103", CLD2::CZECH_CSN_369103));
    encodings->insert(encodings->end(), CldEncoding("MSFT_CP1253", CLD2::MSFT_CP1253));
    encodings->insert(encodings->end(), CldEncoding("RUSSIAN_CP866", CLD2::RUSSIAN_CP866));
    encodings->insert(encodings->end(), CldEncoding("ISO_8859_13", CLD2::ISO_8859_13));
    encodings->insert(encodings->end(), CldEncoding("ISO_2022_KR", CLD2::ISO_2022_KR));
    encodings->insert(encodings->end(), CldEncoding("GBK", CLD2::GBK));
    encodings->insert(encodings->end(), CldEncoding("GB18030", CLD2::GB18030));
    encodings->insert(encodings->end(), CldEncoding("BIG5_HKSCS", CLD2::BIG5_HKSCS));
    encodings->insert(encodings->end(), CldEncoding("ISO_2022_CN", CLD2::ISO_2022_CN));
    encodings->insert(encodings->end(), CldEncoding("TSCII", CLD2::TSCII));
    encodings->insert(encodings->end(), CldEncoding("TAMIL_MONO", CLD2::TAMIL_MONO));
    encodings->insert(encodings->end(), CldEncoding("TAMIL_BI", CLD2::TAMIL_BI));
    encodings->insert(encodings->end(), CldEncoding("JAGRAN", CLD2::JAGRAN));
    encodings->insert(encodings->end(), CldEncoding("MACINTOSH_ROMAN", CLD2::MACINTOSH_ROMAN));
    encodings->insert(encodings->end(), CldEncoding("UTF7", CLD2::UTF7));
    encodings->insert(encodings->end(), CldEncoding("BHASKAR", CLD2::BHASKAR));
    encodings->insert(encodings->end(), CldEncoding("HTCHANAKYA", CLD2::HTCHANAKYA));
    encodings->insert(encodings->end(), CldEncoding("UTF16BE", CLD2::UTF16BE));
    encodings->insert(encodings->end(), CldEncoding("UTF16LE", CLD2::UTF16LE));
    encodings->insert(encodings->end(), CldEncoding("UTF32BE", CLD2::UTF32BE));
    encodings->insert(encodings->end(), CldEncoding("UTF32LE", CLD2::UTF32LE));
    encodings->insert(encodings->end(), CldEncoding("BINARYENC", CLD2::BINARYENC));
    encodings->insert(encodings->end(), CldEncoding("HZ_GB_2312", CLD2::HZ_GB_2312));
    encodings->insert(encodings->end(), CldEncoding("UTF8UTF8", CLD2::UTF8UTF8));
    encodings->insert(encodings->end(), CldEncoding("TAM_ELANGO", CLD2::TAM_ELANGO));
    encodings->insert(encodings->end(), CldEncoding("TAM_LTTMBARANI", CLD2::TAM_LTTMBARANI));
    encodings->insert(encodings->end(), CldEncoding("TAM_SHREE", CLD2::TAM_SHREE));
    encodings->insert(encodings->end(), CldEncoding("TAM_TBOOMIS", CLD2::TAM_TBOOMIS));
    encodings->insert(encodings->end(), CldEncoding("TAM_TMNEWS", CLD2::TAM_TMNEWS));
    encodings->insert(encodings->end(), CldEncoding("TAM_WEBTAMIL", CLD2::TAM_WEBTAMIL));
    encodings->insert(encodings->end(), CldEncoding("KDDI_SHIFT_JIS", CLD2::KDDI_SHIFT_JIS));
    encodings->insert(encodings->end(), CldEncoding("DOCOMO_SHIFT_JIS", CLD2::DOCOMO_SHIFT_JIS));
    encodings->insert(encodings->end(), CldEncoding("SOFTBANK_SHIFT_JIS", CLD2::SOFTBANK_SHIFT_JIS));
    encodings->insert(encodings->end(), CldEncoding("KDDI_ISO_2022_JP", CLD2::KDDI_ISO_2022_JP));
    encodings->insert(encodings->end(), CldEncoding("SOFTBANK_ISO_2022_JP", CLD2::SOFTBANK_ISO_2022_JP));
}

}