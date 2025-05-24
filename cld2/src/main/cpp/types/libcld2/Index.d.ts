export const detectSync: (text: string, options?: object) => object;
export const detectAsync: (text: string, options?: object) => Promise<object>;
export const getDetectedLanguages: () => Array<string>;
export const getLanguages: () => object;
export const getEncodings: () => Array<string>;