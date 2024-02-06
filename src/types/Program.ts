import { fromHex } from 'react-native-bls-signatures';
// import type { ClvmObject } from './ClvmObject';
import type { SExp } from './SExp';

export interface ProgramOutput {
  value: SExp;
  cost: bigint;
}

export interface IBaseProgram {
  getTreeHash(): Uint8Array;
  getSExp(): SExp;
  serialize(): Uint8Array;
  run(args: SExp): ProgramOutput;
  curry(args: SExp): Program;
}

export type JsiProgram = Pick<
  IBaseProgram,
  'getTreeHash' | 'getSExp' | 'serialize' | 'run' | 'curry'
>;

export interface IProgram extends IBaseProgram {
  fromBytes(bytes: Uint8Array): Program;
  fromHex(hex: string): Program;
  fromAssemble(str: string): Program;
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

  serialize(): Uint8Array {
    const func = this.getFunctionFromCache('serialize');
    return func.bind(this)();
  }

  run(args: SExp): ProgramOutput {
    const func = this.getFunctionFromCache('run');
    return func.bind(this)(args);
  }

  curry(args: SExp): Program {
    const func = this.getFunctionFromCache('curry');
    return func.bind(this)(args);
  }

  static fromBytes(bytes: Uint8Array): Program {
    return global.ClvmApi.Program.fromBytes(bytes);
  }

  static fromHex(hex: string): Program {
    return global.ClvmApi.Program.fromBytes(fromHex(hex));
  }

  static fromAssemble(str: string): Program {
    return global.ClvmApi.Program.fromAssemble(str);
  }
}
