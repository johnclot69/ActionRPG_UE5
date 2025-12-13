// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ActionRPG.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "RPGAbilityTask_PlayMontageAndWaitForEvent.generated.h"

class URPGAbilitySystemComponent;

/** 使用的委托类型，如果它来自蒙太奇回调，EventTag 和 Payload 可能为空 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRPGPlayMontageAndWaitForEventDelegate, FGameplayTag, EventTag, FGameplayEventData, EventData);

/**
 * 此任务将 PlayMontageAndWait 和 WaitForEvent 组合成一个任务，因此您可以等待多种类型的激活，例如来自近战连击
 * 此代码大部分是从这两个能力任务之一复制而来的
 * 在创建特定于游戏的任务时，这是一个很好的参考任务
 * 预计每个游戏都将有一组特定于游戏的任务来做他们想做的事情
 */
UCLASS()
class ACTIONRPG_API URPGAbilityTask_PlayMontageAndWaitForEvent : public UAbilityTask
{
	GENERATED_BODY()

public:
	// 构造函数和重写
	URPGAbilityTask_PlayMontageAndWaitForEvent(const FObjectInitializer& ObjectInitializer);
	virtual void Activate() override;
	virtual void ExternalCancel() override;
	virtual FString GetDebugString() const override;
	virtual void OnDestroy(bool AbilityEnded) override;

	/** 蒙太奇完全播放完成 */
	UPROPERTY(BlueprintAssignable)
	FRPGPlayMontageAndWaitForEventDelegate OnCompleted;

	/** 蒙太奇开始混合退出 */
	UPROPERTY(BlueprintAssignable)
	FRPGPlayMontageAndWaitForEventDelegate OnBlendOut;

	/** 蒙太奇被中断 */
	UPROPERTY(BlueprintAssignable)
	FRPGPlayMontageAndWaitForEventDelegate OnInterrupted;

	/** 能力任务被另一个能力显式取消 */
	UPROPERTY(BlueprintAssignable)
	FRPGPlayMontageAndWaitForEventDelegate OnCancelled;

	/** 发生了触发游戏性事件之一 */
	UPROPERTY(BlueprintAssignable)
	FRPGPlayMontageAndWaitForEventDelegate EventReceived;

	/**
	 * 播放蒙太奇并等待其结束。如果发生匹配 EventTags（或 EventTags 为空）的游戏性事件，EventReceived 委托将使用标签和事件数据触发。
	 * 如果 StopWhenAbilityEnds 为 true，则如果能力正常结束，此蒙太奇将被中止。当能力被显式取消时，它总是停止。
	 * 在正常执行中，OnBlendOut 在蒙太奇混合退出时调用，OnCompleted 在其完全播放完成时调用
	 * 如果另一个蒙太奇覆盖了此蒙太奇，则调用 OnInterrupted，如果能力或任务被取消，则调用 OnCancelled
	 *
	 * @param TaskInstanceName 设置以覆盖此任务的名称，以便稍后查询
	 * @param MontageToPlay 要在角色上播放的蒙太奇
	 * @param EventTags 任何匹配此标签的游戏性事件都将激活 EventReceived 回调。如果为空，则所有事件都会触发回调
	 * @param Rate 更改以更快或更慢地播放蒙太奇
	 * @param bStopWhenAbilityEnds 如果为 true，则如果能力正常结束，此蒙太奇将被中止。当能力被显式取消时，它总是停止
	 * @param AnimRootMotionTranslationScale 更改以修改根运动的大小，或设置为 0 以完全阻止它
	 */
	UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static URPGAbilityTask_PlayMontageAndWaitForEvent* PlayMontageAndWaitForEvent(
		UGameplayAbility* OwningAbility,
		FName TaskInstanceName,
		UAnimMontage* MontageToPlay,
		FGameplayTagContainer EventTags,
		float Rate = 1.f,
		FName StartSection = NAME_None,
		bool bStopWhenAbilityEnds = true,
		float AnimRootMotionTranslationScale = 1.f);

private:
	/** 正在播放的蒙太奇 */
	UPROPERTY()
	UAnimMontage* MontageToPlay;

	/** 与游戏性事件匹配的标签列表 */
	UPROPERTY()
	FGameplayTagContainer EventTags;

	/** 播放速率 */
	UPROPERTY()
	float Rate;

	/** 开始蒙太奇的片段 */
	UPROPERTY()
	FName StartSection;

	/** 修改如何应用根运动移动 */
	UPROPERTY()
	float AnimRootMotionTranslationScale;

	/** 如果能力结束，是否应中止蒙太奇 */
	UPROPERTY()
	bool bStopWhenAbilityEnds;

	/** 检查能力是否正在播放蒙太奇并停止该蒙太奇，如果停止了蒙太奇则返回 true，否则返回 false。 */
	bool StopPlayingMontage();

	/** 返回我们的能力系统组件 */
	URPGAbilitySystemComponent* GetTargetASC() const;

	void OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted) const;
	void OnAbilityCancelled();
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	void OnGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload) const;

	FOnMontageBlendingOutStarted BlendingOutDelegate;
	FOnMontageEnded MontageEndedDelegate;
	FDelegateHandle CancelledHandle;
	FDelegateHandle EventHandle;
};
