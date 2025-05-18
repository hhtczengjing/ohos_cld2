import { detect } from "libcld2.so";
import { DetectLanguage } from "./Types";

export class CLD {

  public static detect(text: string): DetectLanguage {
    return detect(text) as DetectLanguage
  }
}