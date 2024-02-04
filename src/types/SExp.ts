export interface IBaseSExp {
  getNodeType(): string;
}

export type JsiSExp = Pick<IBaseSExp, 'getNodeType'>;

export interface ISExp extends IBaseSExp {
  // fromBytes(bytes: Uint8Array): SExp;
}

export class SExp implements IBaseSExp {
  private functionCache: Partial<JsiSExp>;

  constructor() {
    this.functionCache = {};
  }

  private getFunctionFromCache<T extends keyof JsiSExp>(
    functionName: T
  ): JsiSExp[T] {
    if (this.functionCache[functionName] == null) {
      this.functionCache[functionName] = global.ClvmApi.SExp[functionName];
    }
    return this.functionCache[functionName] as JsiSExp[T];
  }

  getNodeType(): string {
    const func = this.getFunctionFromCache('getNodeType');
    return func.bind(this)();
  }
}
