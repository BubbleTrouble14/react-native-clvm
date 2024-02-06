import type { ClvmObject } from './ClvmObject';
import type { IProgram } from './Program';
import type { SExp } from './SExp';

export interface Clvm {
  calculateNumber(clvmProgram: string): number;
  Program: IProgram;
  SExp: SExp;
  assemble: (str: string) => SExp;
  toInt(val: ClvmObject): number;
  sExpFromStream: (stream: Uint8Array) => ClvmObject;
}
