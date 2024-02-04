import * as React from 'react';

import { Root } from './navigators/Root';
import { Clvm, Program } from 'react-native-clvm';

export default function App() {
  React.useEffect(() => {
    const program = Program.fromAssemble('(* (f 1) (f 1))');
    const r = program.run(Clvm.assemble('(10)'));
    console.log(Clvm.toInt(r.value));
    // const bytes = fromHex('ff1dff02ffff1effff0bff02ff05808080');
    // const hex = toHex(bytes);
    // console.log(hex);
    // const program = Program.fromHex('ff1dff02ffff1effff0bff02ff05808080');
    // const sexp = program.getSExp();
    // const test = Clvm.assemble('((70 80) ((91 92 93 94 95) 100) (110 120))');
    // console.log(test.getNodeType());
  }, []);

  return <Root />;
}
