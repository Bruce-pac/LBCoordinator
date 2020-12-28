//
//  LBBaseCoordinator.h
//  Tendaisy
//
//  Created by Bruce on 2019/12/3.
//  Copyright © 2019 Bruce. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LBCoordinating.h"
#import "UIResponder+LBCoordinating.h"

NS_ASSUME_NONNULL_BEGIN
/*
 @abstract class.
 一般只需要重写 -startWithOptions: 方法。
 */
@interface LBBaseCoordinator : UIResponder<LBCoordinating>

@property (nonatomic, copy, readonly) NSString *identifier;
@property (nonatomic, strong, nullable) __kindof LBBaseCoordinator *parentCoordinator;

/*
 ** 此子类coordinator业务流结束的回调
 需要由此子类coordinator主动调用，可在此回调里进行一些内存管理操作，比如stopChildCoordinator，以及一些额外的操作
 */
@property (nonatomic, copy, nullable) void (^didCompleted)(__kindof LBBaseCoordinator *coordinator);

- (void)start;

- (void)startChildCoordinator:(id<LBCoordinating>)child;
- (void)stopChildCoordinator:(id<LBCoordinating>)child;
- (void)addChildCoordinator:(id<LBCoordinating>)child;

///    Coordinator can be in memory, but it‘s not currently displaying anything.
///    For example, parentCoordinator started some other Coordinator which then took over root VC to display its VCs,
///    but did not stop this one.
///
///    Parent Coordinator can then re-activate this one, in which case it should take-over the
///    the ownership of the root VC.
///
///    Note: if you override this method, you should call `super`
///
///    By default, it sets itself as `parentCoordinator` for its `rootViewController`.
- (void)activate;
@end

NS_ASSUME_NONNULL_END
