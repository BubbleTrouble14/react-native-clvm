import { fromHex } from 'react-native-bls-signatures';
import type { SExp } from './SExp';

export interface IBaseProgram {
  getTreeHash(): Uint8Array;
  getSExp(): SExp;
}

export type JsiProgram = Pick<IBaseProgram, 'getTreeHash' | 'getSExp'>;

export interface IProgram extends IBaseProgram {
  fromBytes(bytes: Uint8Array): Program;
}

export class Program implements IBaseProgram {
  private functionCache: Partial<JsiProgram>;

  constructor() {
    this.functionCache = {};
  }

  private getFunctionFromCache<T extends keyof JsiProgram>(
    functionName: T
  ): JsiProgram[T] {
    if (this.functionCache[functionName] == null) {
      this.functionCache[functionName] = global.ClvmApi.Program[functionName];
    }
    return this.functionCache[functionName] as JsiProgram[T];
  }

  getTreeHash(): Uint8Array {
    const func = this.getFunctionFromCache('getTreeHash');
    return func.bind(this)();
  }

  getSExp(): SExp {
    const func = this.getFunctionFromCache('getSExp');
    return func.bind(this)();
  }

  static fromBytes(bytes: Uint8Array): Program {
    return global.ClvmApi.Program.fromBytes(bytes);
  }

  static fromHex(hex: string): Program {
    return global.ClvmApi.Program.fromBytes(fromHex(hex));
  }
}
