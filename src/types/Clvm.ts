import type { IProgram } from './Program';
import type { ISExp } from './SExp';

export interface Clvm {
  calculateNumber(clvmProgram: string): number;
  Program: IProgram;
  SExp: ISExp;
  assemble: (sexp: string) => ISExp;
}
