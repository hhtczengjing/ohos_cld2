import { detectAsync, detectSync } from "libcld2.so";
import { DetectLanguage, Options } from "./Types";

export class CLD {

  public static detect(text: string, options?: Options): DetectLanguage {
    return detectSync(text, options) as DetectLanguage;
  }

  public static detectAsync(text: string, options?: Options): Promise<DetectLanguage> {
    return detectAsync(text, options) as Promise<DetectLanguage>;
  }
}