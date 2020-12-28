//
//  LBCoordinatorEventHandler.h
//  MainProject-MultiPod
//
//  Created by gxy on 2020/12/7.
//  Copyright © 2020 Bruce. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <LBCoordinator/UIResponder+LBCoordinating.h>

NS_ASSUME_NONNULL_BEGIN

@protocol LBCoordinatorEventHandler <NSObject>

- (void)handleEvent:(LBCoordinatorEventName)event
             object:(nullable id)object
           userInfo:(nullable NSDictionary *)userInfo
       asyncHandler:(nullable void (^)(id _Nullable data))asyncHandler;
@end

NS_ASSUME_NONNULL_END
