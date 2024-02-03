import * as React from 'react';

import { Root } from './navigators/Root';
import { Clvm } from 'react-native-clvm';

export default function App() {
  React.useEffect(() => {
    console.log(Clvm.calculateNumber('(f (q . (80 90 100)))'));
  }, []);

  return <Root />;
}
