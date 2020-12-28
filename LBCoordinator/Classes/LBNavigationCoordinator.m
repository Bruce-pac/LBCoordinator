//
//  LBNavigationCoordinator.m
//  Tendaisy
//
//  Created by Bruce on 2019/12/3.
//  Copyright © 2019 Bruce. All rights reserved.
//

#import "LBNavigationCoordinator.h"
#import "UIViewController+LBCoordinator.h"

@interface LBNavigationCoordinator ()
/*
 此导航流管理的控制器，是rootVC的viewControllers的子集，因为此导航流可能和其他导航流共用一个UINavigationController
 */
@property (nonatomic, strong) NSMutableArray<UIViewController *> *managedViewControllers;
@property (nonatomic, strong, readwrite) __kindof UINavigationController *rootVC;
@end

@implementation LBNavigationCoordinator

- (instancetype)initWithRootVC:(__kindof UINavigationController *)rootVC {
    self = [super init];
    if (self) {
        _rootVC = rootVC;
        _managedViewControllers = [NSMutableArray array];
    }
    return self;
}

- (void)startWithOptions:(NSDictionary *)options{
    [self activate];
}

- (void)stopWithCompletion:(void (^)(void))completion {
    NSMutableArray *curVCs = self.rootVC.viewControllers.mutableCopy;
    [curVCs removeObjectsInArray:self.managedViewControllers];
    [self.rootVC setViewControllers:curVCs animated:YES];
    [self.managedViewControllers removeAllObjects];
    [super stopWithCompletion:completion];
}

- (void)activate {
    self.rootVC.lb_coordinator = self;
    self.rootVC.delegate = self;
}

#pragma mark - Convenience

- (void)presentViewController:(UIViewController *)viewControllerToPresent animated: (BOOL)flag completion:(void (^ _Nullable)(void))completion{
    viewControllerToPresent.lb_coordinator = self;
    [self.rootVC presentViewController:viewControllerToPresent animated:flag completion:completion];
}

- (void)dismissViewControllerAnimated: (BOOL)flag completion: (void (^ _Nullable)(void))completion{
    [self.rootVC dismissViewControllerAnimated:flag completion:completion];
}

- (void)pushViewController:(UIViewController *)viewController animated:(BOOL)animated{
    [self.managedViewControllers addObject:viewController];
    viewController.lb_coordinator = self;
    [self.rootVC pushViewController:viewController animated:animated];
}

- (UIViewController *)popViewControllerAnimated:(BOOL)animated{
    if (self.managedViewControllers.count < 2) {
        return nil;
    }
    [self.managedViewControllers removeLastObject];
    return [self.rootVC popViewControllerAnimated:animated];
}

- (NSArray<__kindof UIViewController *> *)popToViewController:(UIViewController *)viewController animated:(BOOL)animated{
    NSUInteger idx = [self.managedViewControllers indexOfObject:viewController];
    if (idx == NSNotFound) {
        return nil;
    }
    NSUInteger len = self.managedViewControllers.count - 1 - idx;
    if (len <= 0) {
        return nil;
    }
    [self.managedViewControllers removeObjectsInRange:NSMakeRange(idx + 1, len)];
    return [self.rootVC popToViewController:viewController animated:animated];
}

- (NSArray<__kindof UIViewController *> *)popToRootViewControllerAnimated:(BOOL)animated{
    if (self.managedViewControllers.count <= 1) {
        return nil;
    }
    UIViewController *root = self.managedViewControllers.firstObject;
    return [self popToViewController:root animated:animated];
}

#pragma mark - UINavigationControllerDelegate

- (void)navigationController:(UINavigationController *)navigationController willShowViewController:(UIViewController *)viewController animated:(BOOL)animated{

}

- (void)navigationController:(UINavigationController *)navigationController didShowViewController:(UIViewController *)viewController animated:(BOOL)animated{
    UIViewController *fromViewController = [navigationController.transitionCoordinator viewControllerForKey:UITransitionContextFromViewControllerKey];
    if (!fromViewController) {
        return;
    }
    if ([navigationController.viewControllers containsObject:fromViewController]) {
        // 这里说明是push
        viewController.lb_coordinator = self;
        return;
    }

    if (self.managedViewControllers.count == 0 || ![self.managedViewControllers containsObject:viewController]) {
        // 这里说明入口控制器已经pop，此业务流程结束
        if (self.didCompleted) {
            self.didCompleted(self);
        }
    } else {
        [self didPopTransitionToViewController:viewController fromViewController:fromViewController];
    }
}

- (void)didPopTransitionToViewController:(UIViewController *)toViewController fromViewController:(UIViewController *)fromViewController{
    
}

- (UIResponder *)coordinatingResponder {
    if (self.parentCoordinator) {
        return self.parentCoordinator;
    }
    return self.rootVC.parentViewController;
}

- (NSArray<__kindof UIViewController *> *)managedVCs {
    return self.managedViewControllers.copy;
}
@end
