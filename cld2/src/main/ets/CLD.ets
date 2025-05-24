import { detectAsync, detectSync, getDetectedLanguages, getEncodings, getLanguages } from "libcld2.so";
import { DetectContext, DetectLanguage, Options } from "./Types";

export class CLD {

  public static detect(text: string, options?: Options): DetectLanguage {
    return detectSync(text, options) as DetectLanguage;
  }

  public static detectAsync(text: string, options?: Options): Promise<DetectLanguage> {
    return detectAsync(text, options) as Promise<DetectLanguage>;
  }

  public static getContext(): DetectContext {
    return {
      detectedLanguages: getDetectedLanguages(),
      languages: getLanguages() as Record<string, string>,
      encodings: getEncodings()
    } as DetectContext;
  }
}