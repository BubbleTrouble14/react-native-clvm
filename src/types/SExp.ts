import type { ClvmObject } from './ClvmObject';

enum NodeType {
  None = 'None',
  Atom_Bytes = 'Atom_Bytes',
  Atom_Str = 'Atom_Str',
  Atom_Int = 'Atom_Int',
  Atom_G1Element = 'Atom_G1Element',
  List = 'List',
  Tuple = 'Tuple',
}

type Pair = {
  first: SExp;
  rest: SExp;
};

// export interface ClvmObject {
//   getNodeType(): NodeType;
//   isFalse(): boolean;
//   equalsTo(): boolean;
// }

// export interface ClvmObjectAtom extends ClvmObject {
//   getBytes(): Uint8Array;
//   isNeg(): boolean;
//   asString(): string;
//   asLong(): number;
//   asInt(): number;
//   asG1Element(): Uint8Array;
// }

// export interface ClvmObjectPair extends ClvmObject {
//   getFirstNode(): ClvmObject;
//   getRestNode(): ClvmObject;
//   setResNode(node: ClvmObject): void;
// }

export interface ClvmIterator {
  next(): ClvmObject | undefined;
  hasNext(): boolean;
  nextInt(): { value: number; numBytes: number } | undefined;
  nextStr(): string | undefined;
  nextBytes(): Uint8Array | undefined;
}

export interface SExp {
  getNodeType(): NodeType;
  isFalse(): boolean;
  equalsTo(): boolean;
  isAtom(): boolean;
  isPair(): boolean;
  isNull(): boolean;
  toBytes(): Uint8Array;
  toInt(): number;
  toString(): string;
  first(): SExp;
  rest(): SExp;
  toPair(): Pair;
  toIter(): ClvmIterator;
}
