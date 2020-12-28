//
//  LBBaseCoordinator+FeatureModule.m
//  LBCoordinator
//
//  Created by gxy on 2020/12/6.
//

#import "LBBaseCoordinator+FeatureModule.h"
#import <objc/runtime.h>

@implementation LBBaseCoordinator (FeatureModule)
- (void)startFeatureModule:(id<LBFeatureModule>)module {

}

- (void)setModuleContext:(id<LBFeatureModule>)moduleContext{
    objc_setAssociatedObject(self, @selector(moduleContext), moduleContext, OBJC_ASSOCIATION_ASSIGN);
}

- (id<LBFeatureModule>)moduleContext{
    return objc_getAssociatedObject(self, @selector(moduleContext));
}
@end
