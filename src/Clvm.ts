import type { Clvm as ClvmApi } from './types/Clvm';

/**
 * Declares the BlsApi as an available object in the global scope
 */
declare global {
  var ClvmApi: ClvmApi;
}

export const Clvm = ClvmApi;
