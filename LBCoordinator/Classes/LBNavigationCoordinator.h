//
//  LBNavigationCoordinator.h
//  Tendaisy
//
//  Created by Bruce on 2019/12/3.
//  Copyright © 2019 Bruce. All rights reserved.
//

#import <LBCoordinator/LBBaseCoordinator.h>

NS_ASSUME_NONNULL_BEGIN

@interface LBNavigationCoordinator : LBBaseCoordinator<UINavigationControllerDelegate>
@property (nonatomic, strong, readonly) __kindof UINavigationController *rootVC;
/// 入口视图控制器
@property (nonatomic, strong) __kindof UIViewController *entranceVC;
// 此导航流管理的控制器们
@property (nonatomic, strong, readonly) NSArray<__kindof UIViewController *> *managedVCs;

- (instancetype)initWithRootVC:(__kindof UINavigationController *)rootVC;
- (instancetype)init NS_UNAVAILABLE;

#pragma mark - Convenience, Don't Override!

- (void)presentViewController:(UIViewController *)viewController
                     animated: (BOOL)flag
                   completion:(void (^ _Nullable)(void))completion;
- (void)dismissViewControllerAnimated: (BOOL)flag
                           completion: (void (^ _Nullable)(void))completion;

/// 请使用以下方法，不要直接调用UINavigationController相关方法
- (void)pushViewController:(UIViewController *)viewController animated:(BOOL)animated NS_SWIFT_NAME(pushViewController(_:animated:));
- (nullable UIViewController *)popViewControllerAnimated:(BOOL)animated;
- (nullable NSArray<__kindof UIViewController *> *)popToViewController:(UIViewController *)viewController animated:(BOOL)animated;
- (nullable NSArray<__kindof UIViewController *> *)popToRootViewControllerAnimated:(BOOL)animated;

#pragma mark - Override

/// pop完成后的回调，子类可以重写
/// @param toViewController pop完成后显示的控制器
/// @param fromViewController 被pop的控制器
- (void)didPopTransitionToViewController:(UIViewController *)toViewController
                      fromViewController:(UIViewController *)fromViewController;
@end

NS_ASSUME_NONNULL_END
