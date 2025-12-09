// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ActionRPG.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Abilities/RPGAbilityTypes.h"
#include "RPGTargetType.generated.h"

class ARPGCharacterBase;
class AActor;
struct FGameplayEventData;

/**
 * 用于确定能力目标的类
 * 旨在通过蓝图化来运行目标逻辑
 * 这不是 GameplayAbilityTargetActor 的子类，因为此类从未在世界中实例化
 * 这可以用作特定于游戏的目标蓝图的基础
 * 如果您的目标更复杂，您可能需要将其在世界中实例化一次或作为池化的 Actor
 */
UCLASS(Blueprintable, meta = (ShowWorldContextPin))
class ACTIONRPG_API URPGTargetType : public UObject
{
	GENERATED_BODY()

public:
	// 构造函数和重写
	URPGTargetType() {}

	/** 调用以确定要应用游戏性效果的目标 */
	UFUNCTION(BlueprintNativeEvent)
	void GetTargets(ARPGCharacterBase* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const;
};

/** 使用所有者的简单目标类型 */
UCLASS(NotBlueprintable)
class ACTIONRPG_API URPGTargetType_UseOwner : public URPGTargetType
{
	GENERATED_BODY()

public:
	// 构造函数和重写
	URPGTargetType_UseOwner() {}

	/** 使用传入的事件数据 */
	virtual void GetTargets_Implementation(ARPGCharacterBase* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const override;
};

/** 从事件数据中提取目标的简单目标类型 */
UCLASS(NotBlueprintable)
class ACTIONRPG_API URPGTargetType_UseEventData : public URPGTargetType
{
	GENERATED_BODY()

public:
	// 构造函数和重写
	URPGTargetType_UseEventData() {}

	/** 使用传入的事件数据 */
	virtual void GetTargets_Implementation(ARPGCharacterBase* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const override;
};
