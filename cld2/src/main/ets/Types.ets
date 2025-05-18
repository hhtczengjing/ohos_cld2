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
  readonly isHTML?: boolean;
  readonly languageHint?: string;
  readonly encodingHint?: string;
  readonly tldHint?: string;
  readonly httpHint?: string;
  readonly bestEffort?: boolean;
}

export interface DetectLanguage {
  readonly reliable: boolean;
  readonly textBytes: number;
  readonly languages: Language[];
  readonly chunks: Chunk[];
}