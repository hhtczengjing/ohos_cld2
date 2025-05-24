export interface Language {
  readonly name: string;
  readonly code: string;
  readonly percent: number;
  readonly score: number;
}

export interface Chunk {
  readonly name: string;
  readonly code: string;
  readonly offset: number;
  readonly bytes: number;
}

export interface Options {
  isHTML?: boolean;
  languageHint?: string;
  encodingHint?: string;
  tldHint?: string;
  httpHint?: string;
  bestEffort?: boolean;
}

export interface DetectLanguage {
  readonly reliable: boolean;
  readonly textBytes: number;
  readonly languages: Language[];
  readonly chunks: Chunk[];
}

export interface DetectContext {
  readonly detectedLanguages: string[];
  readonly languages: Record<string, string>;
  readonly encodings: string[];
}