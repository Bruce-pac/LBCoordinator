//
//  LBFeatureModuleManager.m
//  LBCoordinator
//
//  Created by gxy on 2020/11/29.
//

#import "LBFeatureModuleManager.h"

@interface LBFeatureModuleManager ()
@property (nonatomic, strong) NSMutableDictionary<NSString *, id<LBFeatureModule>> *moduleMap;
@end

@implementation LBFeatureModuleManager
static LBFeatureModuleManager *_instance;

+ (instancetype)allocWithZone:(struct _NSZone *)zone {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _instance = [super allocWithZone:zone];
    });
    return _instance;
}

+ (instancetype)sharedManager {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _instance = [LBFeatureModuleManager new];
    });
    return _instance;
}

- (instancetype)init {
    self = [super init];
    if (self) {
        _moduleMap = [NSMutableDictionary dictionary];
    }
    return self;
}

- (void)storeModule:(id<LBFeatureModule>)module{
    [_moduleMap setObject:module forKey:module.uniqueId];
}

- (void)releaseModule:(id<LBFeatureModule>)module {
    [_moduleMap removeObjectForKey:module.uniqueId];
}

- (id<LBFeatureModule>)fetchModuleWithId:(NSString *)moduleId {
    id module = [_moduleMap objectForKey:moduleId];
    if (module) {
        return module;
    }
    Class clazz = NSClassFromString(moduleId);
    if (!clazz) {
        return nil;
    }
    module = [[clazz alloc] init];
    if (![module conformsToProtocol:@protocol(LBFeatureModule)]) {
        // 断言
        return nil;
    }
    [self storeModule:module];
    return module;
}
@end
