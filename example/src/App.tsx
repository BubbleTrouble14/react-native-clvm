import * as React from 'react';

import { Root } from './navigators/Root';
import { Clvm, Program } from 'react-native-clvm';
import { fromHex, toHex } from 'react-native-bls-signatures';

export default function App() {
  React.useEffect(() => {
    const bytes = fromHex('ff1dff02ffff1effff0bff02ff05808080');
    const hex = toHex(bytes);
    console.log(hex);
    const program = Program.fromHex('ff1dff02ffff1effff0bff02ff05808080');
    const sexp = program.getSExp();
    const test = Clvm.assemble('(f (f (r 1)))');
    console.log(sexp.getNodeType());
  }, []);

  return <Root />;
}
