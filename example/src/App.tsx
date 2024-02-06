import * as React from 'react';

import { Root } from './navigators/Root';
import { Clvm, Program } from 'react-native-clvm';

export default function App() {
  React.useEffect(() => {
    const program = Program.fromAssemble('(* (f 1) (f 1))');
    // const x = Clvm.assemble('(10)');
    // // console.log(x.isAtom(), x.isPair());
    // const val = program.run(x).value;
    // console.log(val.toInt(), val.toBytes());
    // const r = program.run(Clvm.assemble('(10)'));
    // console.log(program, Clvm.toInt(r.value));
    // const bytes = fromHex('ff1dff02ffff1effff0bff02ff05808080');
    // const hex = toHex(bytes);
    // console.log(hex);
    // const program = Program.fromHex('ff1dff02ffff1effff0bff02ff05808080');
    // const sexp = program.getSExp();
    // const test = Clvm.assemble('((70 80) ((91 92 93 94 95) 100) (110 120))');
    // console.log(test.getNodeType());
    const prog = Program.fromAssemble('1');
    const r = prog.run(Clvm.assemble('("this" "is the" "environment")'));
    const iter = r.value.toIter();
    console.log(iter.nextStr());
    console.log(iter.nextStr());
    console.log(iter.nextStr());
    console.log(iter.hasNext());
    // console.log(iter);
    // console.log(r.value.first().toString());
  }, []);

  return <Root />;
}
