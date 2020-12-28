//
//  LBFeatureModule.h
//  LBCoordinator
//
//  Created by gxy on 2020/11/26.
//

#import <Foundation/Foundation.h>

@class LBBaseCoordinator;
@protocol LBFeatureModule;

NS_ASSUME_NONNULL_BEGIN

@protocol LBFeatureModuleDelegate <NSObject>
@optional
- (void)featureModule:(id<LBFeatureModule>)module
didFinishLaunchingWithOptions:(NSDictionary *)options;

- (void)featureModuleWillTerminate:(id<LBFeatureModule>)module;
@end

@protocol LBApplicationContext


@end

/*
 抽象业务组件，表示该业务pod模块的外观类（或者叫service类）暴露对外服务，同时也支持URL远程。
 建议一个业务pod库尽量只暴露这一个文件。
 外部获取模块外观类，需要通过LBFeatureModuleManager来获取，不能直接构造。

 可以在现有的XMService_XXX类上实现此协议，已提供的方法也不需要任何修改。
 */
@protocol LBFeatureModule

@property (nonatomic, copy, readonly) NSString *uniqueId;

@property (nonatomic, strong, readonly) __kindof LBBaseCoordinator *rootCoordinator;

@property (nonatomic, weak) id<LBFeatureModuleDelegate> delegate;

/*
 可以在options里指定此模块支持的各种各样的启动参数，比如转场方式、业务字段、跳转某个内部页面的标记
 */
- (void)launchWithOptions:(nullable NSDictionary *)options;

@optional

@property (nonatomic, assign) BOOL active;
@property (nonatomic, weak, nullable) id<LBApplicationContext> appContext;

// 此业务流程的根控制器
@property (nonatomic, strong, readonly) __kindof UIViewController *rootVC;

/*
 注入一些依赖对象，可以用来在不同的App程序中替换不同的基础依赖库实现，比方说老项目使用AFN，新项目使用Alamofire，但是某个业务库需要通用，不可能重写，假如直接依赖AFN，那么在新项目中就会有两个网络库增加包大小。具体看demo中使用。
 */
- (void)injectDependencies:(NSDictionary *)dependencies;

@end

NS_ASSUME_NONNULL_END
