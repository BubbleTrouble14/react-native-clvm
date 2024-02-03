#ifdef __cplusplus
#import "JsiClvmApi.h"
#endif

#ifdef RCT_NEW_ARCH_ENABLED
#import "RNClvmSpec.h"

@interface Clvm : NSObject <NativeClvmSpec>
#else
#import <React/RCTBridgeModule.h>

@interface Clvm : NSObject <RCTBridgeModule>
#endif

@end
