// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ----------------------------------------------------------------------------------------------------------------
// 此头文件用于在项目中共享的特定于能力的结构和枚举
// 每个游戏可能都需要这样一个文件来处理其对系统的扩展
// 此文件是 FGameplayEffectContext 和 FGameplayAbilityTargetData 子类的好去处
// ----------------------------------------------------------------------------------------------------------------

#include "ActionRPG.h"
#include "GameplayEffectTypes.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "RPGAbilityTypes.generated.h"

class URPGAbilitySystemComponent;
class UGameplayEffect;
class URPGTargetType;


/**
 * 定义游戏性效果列表、标签和目标信息的结构体
 * 这些容器在蓝图或资产中静态定义，然后在运行时转换为 Spec
 */
USTRUCT(BlueprintType)
struct FRPGGameplayEffectContainer
{
	GENERATED_BODY()

public:
	FRPGGameplayEffectContainer() {}

	/** 设置目标选择的方式 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffectContainer)
	TSubclassOf<URPGTargetType> TargetType;

	/** 要应用于目标的游戏性效果列表 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffectContainer)
	TArray<TSubclassOf<UGameplayEffect>> TargetGameplayEffectClasses;
};

/** RPGGameplayEffectContainer 的“已处理”版本，可以传递并最终应用 */
USTRUCT(BlueprintType)
struct FRPGGameplayEffectContainerSpec
{
	GENERATED_BODY()

public:
	FRPGGameplayEffectContainerSpec() {}

	/** 计算出的目标数据 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffectContainer)
	FGameplayAbilityTargetDataHandle TargetData;

	/** 要应用于目标的游戏性效果列表 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffectContainer)
	TArray<FGameplayEffectSpecHandle> TargetGameplayEffectSpecs;

	/** 如果具有任何有效的效果规格，则返回 true */
	bool HasValidEffects() const;

	/** 如果具有任何有效的目标，则返回 true */
	bool HasValidTargets() const;

	/** 将新目标添加到目标数据 */
	void AddTargets(const TArray<FHitResult>& HitResults, const TArray<AActor*>& TargetActors);
};
