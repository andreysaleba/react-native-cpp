#import <Foundation/Foundation.h>

#import <React/RCTBridgeDelegate.h>

@interface RCDjinniModulesInitializer : NSObject<RCTBridgeDelegate>

- (instancetype)initWithURL:(NSURL *)url;

@end
