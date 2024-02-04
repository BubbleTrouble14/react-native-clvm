import type { ClvmObject } from './ClvmObject';
import type { IProgram } from './Program';

export interface Clvm {
  calculateNumber(clvmProgram: string): number;
  Program: IProgram;
  // SExp: ISExp;
  assemble: (sexp: string) => ClvmObject;
  toInt(val: ClvmObject): number;
}
