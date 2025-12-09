// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ActionRPG.h"
#include "AbilitySystemComponent.h"
#include "Abilities/RPGAbilityTypes.h"
#include "RPGAbilitySystemComponent.generated.h"

class URPGGameplayAbility;

/**
 * 具有特定游戏数据的能力系统组件的子类
 * 大多数游戏都需要创建一个特定于游戏的子类来提供实用函数
 */
UCLASS()
class ACTIONRPG_API URPGAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// 构造函数和重写
	URPGAbilitySystemComponent();

	/** 返回当前与标签匹配的活动能力实例列表 */
	void GetActiveAbilitiesWithTags(const FGameplayTagContainer& GameplayTagContainer, TArray<URPGGameplayAbility*>& ActiveAbilities);

	/** 返回用于能力激活的默认等级，源自角色 */
	int32 GetDefaultAbilityLevel() const;

	/** AbilitySystemGlobals 中函数的版本，返回正确的类型 */
	static URPGAbilitySystemComponent* GetAbilitySystemComponentFromActor(const AActor* Actor, bool LookForComponent = false);

};