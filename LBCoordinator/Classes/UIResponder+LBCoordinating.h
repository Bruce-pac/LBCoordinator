//
//  UIResponder+LBCoordinator.h
//  Tendaisy
//
//  Created by Bruce on 2019/12/3.
//  Copyright © 2019 Bruce. All rights reserved.
//

#import <UIKit/UIKit.h>

/*
 问题：
 1. 响应链变扭，两种方式
 2. 性能
 3. 总控复杂
 */

typedef NSString* LBCoordinatorEventName NS_TYPED_EXTENSIBLE_ENUM;
typedef NSString* LBCoordinatorEventUserInfoKey NS_TYPED_EXTENSIBLE_ENUM;

NS_ASSUME_NONNULL_BEGIN
// 所有模块定义的拓展的消息可以放到相似命名的文件里，比如xxEvents.{h,m}，然后可以利用DSL和脚本，扫描所有文件生成文档，列出所有需要处理的组件间消息。

/// DESC: 此消息表示直接利用反射调用方法，可从userInfo里取出对应key的target和selector，然后利用XMRouter等调用。
extern LBCoordinatorEventName const kCoordinatorReflectSelectorEvent;
extern LBCoordinatorEventUserInfoKey const kCoordinatorReflectUserInfoKeyTarget;
extern LBCoordinatorEventUserInfoKey const kCoordinatorReflectUserInfoKeySelector;

/*
 业务组件可以类比UIView/UIViewController，
 想一想我们使用UIView的时候是怎么写的，我们是在一个UIView里面组合不同的UIView来实现一个更复杂的UIView，或者在UIViewController里面组合不同的childViewController，从而得以划分逻辑实现更易复用的类，而这些不同的UIView之间处理事件则是利用到了响应者链模式解耦，
 因此完全可以利用响应者链进行跨组件通信。
 利用基于消息的响应者链既灵活又相对安全，也没有额外的性能消耗，不会产生过多无关的调用栈。
 */
@interface UIResponder (LBCoordinating)
@property (nonatomic, readonly, nullable) UIResponder *coordinatingResponder;

- (void)lb_coordinatingMessage:(LBCoordinatorEventName)event
                        object:(nullable id)object
                      userInfo:(nullable NSDictionary *)userInfo;

- (void)lb_coordinatingMessage:(LBCoordinatorEventName)event
                        object:(nullable id)object
                      userInfo:(nullable NSDictionary *)userInfo
                  asyncHandler:(nullable void (^)(id _Nullable data))asyncHandler;

/// 还可以扩展Promise风格
//- (Promise *)lbPromise_coordinatingMessage:(LBCoordinatorEventName)event
//                               object:(nullable id)object
//                             userInfo:(nullable NSDictionary *)userInfo;

@end

NS_ASSUME_NONNULL_END
