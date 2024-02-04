enum NodeType {
  None = 'None',
  Atom_Bytes = 'Atom_Bytes',
  Atom_Str = 'Atom_Str',
  Atom_Int = 'Atom_Int',
  Atom_G1Element = 'Atom_G1Element',
  List = 'List',
  Tuple = 'Tuple',
}

export interface ClvmObject {
  getNodeType(): NodeType;
  isFalse(): boolean;
  equalsTo(): boolean;
}

export interface ClvmObjectAtom extends ClvmObject {
  getBytes(): Uint8Array;
  isNeg(): boolean;
  asString(): string;
  asLong(): number;
  asInt(): number;
  asG1Element(): Uint8Array;
}

export interface ClvmObjectPair extends ClvmObject {
  getFirstNode(): ClvmObject;
  getRestNode(): ClvmObject;
  setResNode(node: ClvmObject): void;
}
