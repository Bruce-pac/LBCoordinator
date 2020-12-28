//
//  LBBaseCoordinator.m
//  Tendaisy
//
//  Created by Bruce on 2019/12/3.
//  Copyright © 2019 Bruce. All rights reserved.
//

#import "LBBaseCoordinator.h"
#import "UIViewController+LBCoordinator.h"

@interface LBBaseCoordinator ()
@property (nonatomic, copy, readwrite) NSString *identifier;
@property (nonatomic, strong) NSMutableDictionary<NSString *, id<LBCoordinating>> *childCoordinatorContainer;

@end

@implementation LBBaseCoordinator

- (void)start{
    [self startWithOptions:nil];
}

- (void)startWithOptions:(NSDictionary *)options {
    NSAssert(NO, @"%@ not implementated '-(void)startWithOptions:'", [self class]);
}

- (void)stopWithCompletion:(void (^)(void))completion{
    if (completion) {
        completion();
    }
}

- (void)activate{

}

- (void)addChildCoordinator:(id<LBCoordinating>)child{
    NSAssert(child != self, ([NSString stringWithFormat:@"ChildCoordinator %@ must not be equal to parentCoordinator", child]));
    [self.childCoordinatorContainer setObject:child forKey:child.identifier];
    child.parentCoordinator = self;
}

- (void)startChildCoordinator:(id<LBCoordinating>)child{
    [self addChildCoordinator:child];
    [child startWithOptions:nil];
}

- (void)stopChildCoordinator:(id<LBCoordinating>)child{
    child.parentCoordinator = nil;
    __weak typeof(self) weakSelf = self;
    [child stopWithCompletion:^{
        __strong typeof(self) strongSelf = weakSelf;
        [strongSelf.childCoordinatorContainer removeObjectForKey:child.identifier];
    }];
}

- (NSArray<id<LBCoordinating>> *)childCoordinators{
    return self.childCoordinatorContainer.allValues;
}

- (UIResponder *)coordinatingResponder{
    return (UIResponder *)self.parentCoordinator;
}

- (NSString *)description
{
    return [NSString stringWithFormat:@"identifier - %@ \n parentCoordinator - %@ \n childCoordinators - %@",
            self.identifier,
            self.parentCoordinator,
            self.childCoordinators];
}
#pragma mark - Lazy load

- (NSString *)identifier{
    if (!_identifier) {
        _identifier = NSStringFromClass([self class]);
    }
    return _identifier;
}

- (NSMutableDictionary<NSString *,id<LBCoordinating>> *)childCoordinatorContainer{
    if (!_childCoordinatorContainer) {
        _childCoordinatorContainer = [NSMutableDictionary dictionary];
    }
    return _childCoordinatorContainer;
}

@end
