import type { TurboModule } from 'react-native';
import { TurboModuleRegistry } from 'react-native';

export interface Spec extends TurboModule {
  install(): boolean;
}

const ClvmInstaller = TurboModuleRegistry.getEnforcing<Spec>('Clvm');

console.log('Loading react-native-clvm...');

if (global.ClvmApi === undefined || global.ClvmApi == null) {
  if (ClvmInstaller == null || typeof ClvmInstaller.install !== 'function') {
    console.error(
      'Native Clvm Module cannot be found! Make sure you correctly ' +
        'installed native dependencies and rebuilt your app.'
    );
  } else {
    // Install the module
    const result = ClvmInstaller.install();
    if (result !== true) {
      console.error(
        `Native Clvm Module failed to correctly install JSI Bindings! Result: ${result}`
      );
    } else {
      console.log('Clvm loaded successfully');
    }
  }
} else {
  console.log('react-native-clvm installed.');
}
