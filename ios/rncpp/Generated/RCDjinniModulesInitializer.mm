#import "RCDjinniModulesInitializer.h"
#import "RVReactDjinni.h"

#import "RCDemoModule.h"

@interface RCDjinniModulesInitializer ()

@property (readonly) NSURL *url;
@property NSArray<id<RCTBridgeModule>> *modules;

@end

@implementation RCDjinniModulesInitializer

- (instancetype)initWithURL:(NSURL *)url {
  if (self = [super init]) {
    _url = url;
    _modules = nil;
  }
  return self;
}

- (NSURL *)sourceURLForBridge:(RCTBridge *)bridge {
  return self.url;
}

- (NSArray<id<RCTBridgeModule>> *)extraModulesForBridge:(RCTBridge *)bridge {
  if (self.modules == nil) {
    self.modules = @[[RCDemoModule create:[RVReactDjinni createReactBridge:bridge]]];
  }
  return self.modules;
}

@end
