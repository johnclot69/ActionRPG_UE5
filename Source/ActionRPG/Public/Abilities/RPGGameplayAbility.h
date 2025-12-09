// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ActionRPG.h"
#include "Abilities/GameplayAbility.h"
#include "Abilities/RPGAbilityTypes.h"
#include "RPGGameplayAbility.generated.h"

/**
 * 具有特定游戏数据的能力蓝图类型的子类
 * 此类使用 GameplayEffectContainers 允许根据触发标签更轻松地执行游戏性效果
 * 大多数游戏都需要实现一个子类以支持其特定于游戏的代码
 */
UCLASS()
class ACTIONRPG_API URPGGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	// 构造函数和重写
	URPGGameplayAbility();

	/** 游戏性标签到游戏性效果容器的映射 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayEffects)
	TMap<FGameplayTag, FRPGGameplayEffectContainer> EffectContainerMap;

	/** 制作稍后应用的游戏性效果容器规格，使用传入的容器 */
	UFUNCTION(BlueprintCallable, Category = Ability, meta=(AutoCreateRefTerm = "EventData"))
	virtual FRPGGameplayEffectContainerSpec MakeEffectContainerSpecFromContainer(const FRPGGameplayEffectContainer& Container, const FGameplayEventData& EventData, int32 OverrideGameplayLevel = -1);

	/** 搜索并制作稍后应用的游戏性效果容器规格，从 EffectContainerMap 中搜索 */
	UFUNCTION(BlueprintCallable, Category = Ability, meta = (AutoCreateRefTerm = "EventData"))
	virtual FRPGGameplayEffectContainerSpec MakeEffectContainerSpec(FGameplayTag ContainerTag, const FGameplayEventData& EventData, int32 OverrideGameplayLevel = -1);

	/** 应用之前创建的游戏性效果容器规格 */
	UFUNCTION(BlueprintCallable, Category = Ability)
	virtual TArray<FActiveGameplayEffectHandle> ApplyEffectContainerSpec(const FRPGGameplayEffectContainerSpec& ContainerSpec);

	/** 应用游戏性效果容器，通过创建然后应用规格 */
	UFUNCTION(BlueprintCallable, Category = Ability, meta = (AutoCreateRefTerm = "EventData"))
	virtual TArray<FActiveGameplayEffectHandle> ApplyEffectContainer(FGameplayTag ContainerTag, const FGameplayEventData& EventData, int32 OverrideGameplayLevel = -1);
};