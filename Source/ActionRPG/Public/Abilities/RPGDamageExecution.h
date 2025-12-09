// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ActionRPG.h"
#include "GameplayEffectExecutionCalculation.h"
#include "RPGDamageExecution.generated.h"

/**
 * 伤害执行，允许通过将原始伤害数值与攻击力和防御力结合来造成伤害
 * 大多数游戏都会希望实现多个特定于游戏的执行
 */
UCLASS()
class ACTIONRPG_API URPGDamageExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	// 构造函数和重写
	URPGDamageExecution();
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

};