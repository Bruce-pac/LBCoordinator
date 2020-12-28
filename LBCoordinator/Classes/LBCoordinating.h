//
//  Coordinator.h
//  MainProject-MultiPod
//
//  Created by gxy on 2019/10/28.
//  Copyright © 2019 Bruce. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
/*
 协调器抽象协议，表示有能力处理一个业务流程。

 *** 不要直接实现这个协议，请继承LBBaseCoordinator或它的子类。
 */
@protocol LBCoordinating <NSObject>
@property (nonatomic, copy, readonly) NSString *identifier;
@property (nonatomic, strong, nullable) id<LBCoordinating> parentCoordinator;
@property (nonatomic, copy, readonly) NSArray<id<LBCoordinating>> *childCoordinators;
/// 开启业务流程
- (void)startWithOptions:(nullable NSDictionary *)options;
/// 结束业务流程，做一些清理操作
- (void)stopWithCompletion:(void (^)(void))completion;

- (void)startChildCoordinator:(id<LBCoordinating>)child;
- (void)stopChildCoordinator:(id<LBCoordinating>)child;
- (void)addChildCoordinator:(id<LBCoordinating>)child;

- (void)activate;
@end

NS_ASSUME_NONNULL_END
