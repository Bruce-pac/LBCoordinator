//
//  LBFeatureModuleManager.h
//  LBCoordinator
//
//  Created by gxy on 2020/11/29.
//

#import <Foundation/Foundation.h>
#import <LBCoordinator/LBFeatureModule.h>

NS_ASSUME_NONNULL_BEGIN

@interface LBFeatureModuleManager : NSObject

+ (instancetype)sharedManager;

- (void)storeModule:(id<LBFeatureModule>)module;
- (void)releaseModule:(id<LBFeatureModule>)module;

- (_Nullable id<LBFeatureModule>)fetchModuleWithId:(NSString *)moduleId;

/// 根据类型内部构造对象存储，只适合new、init构造方法，不适合自定义构造方法
/// 适合从配置文件反射类型后调用
/// @param moduleClass 组件类型
- (void)storeModuleWithClass:(Class<LBFeatureModule>)moduleClass;


@end

NS_ASSUME_NONNULL_END
