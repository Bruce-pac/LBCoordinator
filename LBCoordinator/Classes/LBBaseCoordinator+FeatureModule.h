//
//  LBBaseCoordinator+FeatureModule.h
//  LBCoordinator
//
//  Created by gxy on 2020/12/6.
//

#import <LBCoordinator/LBCoordinator.h>
#import <LBCoordinator/LBFeatureModule.h>

NS_ASSUME_NONNULL_BEGIN

@interface LBBaseCoordinator (FeatureModule)

@property (nonatomic, weak) id<LBFeatureModule> moduleContext;
- (void)startFeatureModule:(id<LBFeatureModule>)module;
@end

NS_ASSUME_NONNULL_END
