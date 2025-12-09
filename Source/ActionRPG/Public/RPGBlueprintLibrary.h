// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ActionRPG.h"
#include "RPGTypes.h"
#include "Abilities/RPGAbilityTypes.h"
#include "RPGBlueprintLibrary.generated.h"

/**
 * 特定于游戏的蓝图库
 * 大多数游戏需要实现一个或多个蓝图函数库，以便将其原生代码暴露给蓝图
 */
UCLASS()
class URPGBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:
	/** 显示原生加载屏幕，例如在地图转换时。如果 bPlayUntilStopped 为 false，它将显示 PlayTime 的时间并自动停止 */
	UFUNCTION(BlueprintCallable, Category = Loading)
	static void PlayLoadingScreen(bool bPlayUntilStopped, float PlayTime);

	/** 如果可见，则关闭原生加载屏幕。如果 bPlayUntilStopped 为 true，则必须调用此函数 */
	UFUNCTION(BlueprintCallable, Category = Loading)
	static void StopLoadingScreen();

	/** 如果正在从编辑器预览运行，则返回 true */
	UFUNCTION(BlueprintPure, Category = Loading)
	static bool IsInEditor();

	/** ItemSlot 的相等运算符 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (RPGItemSlot)", CompactNodeTitle = "==", Keywords = "== equal"), Category = Inventory)
	static bool EqualEqual_RPGItemSlot(const FRPGItemSlot& A, const FRPGItemSlot& B);

	/** ItemSlot 的不等运算符 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "NotEqualEqual (RPGItemSlot)", CompactNodeTitle = "!=", Keywords = "!= not equal"), Category = Inventory)
	static bool NotEqual_RPGItemSlot(const FRPGItemSlot& A, const FRPGItemSlot& B);

	/** ItemSlot 的有效性检查 */
	UFUNCTION(BlueprintPure, Category = Inventory)
	static bool IsValidItemSlot(const FRPGItemSlot& ItemSlot);

	/** 检查规格是否有任何效果 */
	UFUNCTION(BlueprintPure, Category = Ability)
	static bool DoesEffectContainerSpecHaveEffects(const FRPGGameplayEffectContainerSpec& ContainerSpec);

	/** 检查规格是否有任何目标 */
	UFUNCTION(BlueprintPure, Category = Ability)
	static bool DoesEffectContainerSpecHaveTargets(const FRPGGameplayEffectContainerSpec& ContainerSpec);

	/** 将目标添加到传入的效果容器规格的副本中并返回它 */
	UFUNCTION(BlueprintCallable, Category = Ability, meta = (AutoCreateRefTerm = "HitResults,TargetActors"))
	static FRPGGameplayEffectContainerSpec AddTargetsToEffectContainerSpec(const FRPGGameplayEffectContainerSpec& ContainerSpec, const TArray<FHitResult>& HitResults, const TArray<AActor*>& TargetActors);

	/** 应用从能力制作的容器规格 */
	UFUNCTION(BlueprintCallable, Category = Ability)
	static TArray<FActiveGameplayEffectHandle> ApplyExternalEffectContainerSpec(const FRPGGameplayEffectContainerSpec& ContainerSpec);

	//返回编辑器中“项目设置”>“描述”部分中设置的项目版本
	UFUNCTION(BlueprintPure, Category = "Project")
	static FString GetProjectVersion();
};
