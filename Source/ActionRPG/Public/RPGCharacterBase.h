// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ActionRPG.h"
#include "GameFramework/Character.h"
#include "UObject/ScriptInterface.h"
#include "RPGInventoryInterface.h"
#include "AbilitySystemInterface.h"
#include "Abilities/RPGAbilitySystemComponent.h"
#include "Abilities/RPGAttributeSet.h"
#include "GenericTeamAgentInterface.h"
#include "RPGCharacterBase.generated.h"

class URPGGameplayAbility;
class UGameplayEffect;

/** 角色基类，设计用于蓝图化 */
UCLASS()
class ACTIONRPG_API ARPGCharacterBase : public ACharacter, public IAbilitySystemInterface, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// 构造函数和重写
	ARPGCharacterBase();
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
	virtual void OnRep_Controller() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// 实现 IAbilitySystemInterface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	/** 返回当前生命值，如果死亡则为 0 */
	UFUNCTION(BlueprintCallable)
	virtual float GetHealth() const;

	/** 返回最大生命值，生命值永远不会超过此值 */
	UFUNCTION(BlueprintCallable)
	virtual float GetMaxHealth() const;

	/** 返回当前法力值 */
	UFUNCTION(BlueprintCallable)
	virtual float GetMana() const;

	/** 返回最大法力值，法力值永远不会超过此值 */
	UFUNCTION(BlueprintCallable)
	virtual float GetMaxMana() const;

	/** 返回当前移动速度 */
	UFUNCTION(BlueprintCallable)
	virtual float GetMoveSpeed() const;

	/** 返回传递给能力系统的角色等级  */
	UFUNCTION(BlueprintCallable)
	virtual int32 GetCharacterLevel() const;

	/** 修改角色等级，这可能会改变能力。成功返回 true */
	UFUNCTION(BlueprintCallable)
	virtual bool SetCharacterLevel(int32 NewLevel);

	/**
	 * 尝试激活指定物品槽中的任何能力。如果未找到可激活的能力或激活失败，将返回 false
	 * 如果它认为已激活则返回 true，但也可能因为后续激活失败而出现误报。
	 * 如果 bAllowRemoteActivation 为 true，它将远程激活本地/服务器能力，如果为 false，它将仅尝试在本地激活能力
	 */
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	bool ActivateAbilitiesWithItemSlot(FRPGItemSlot ItemSlot, bool bAllowRemoteActivation = true);

	/** 返回绑定到物品槽的活动能力列表。仅在能力当前正在运行时才返回 */
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void GetActiveAbilitiesWithItemSlot(FRPGItemSlot ItemSlot, TArray<URPGGameplayAbility*>& ActiveAbilities);

	/**
	 * 尝试激活所有与指定标签匹配的能力
	 * 如果它认为已激活则返回 true，但也可能因为后续激活失败而出现误报。
	 * 如果 bAllowRemoteActivation 为 true，它将远程激活本地/服务器能力，如果为 false，它将仅尝试在本地激活能力
	 */
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	bool ActivateAbilitiesWithTags(FGameplayTagContainer AbilityTags, bool bAllowRemoteActivation = true);

	/** 返回与指定标签匹配的活动能力列表。仅在能力当前正在运行时才返回 */
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void GetActiveAbilitiesWithTags(FGameplayTagContainer AbilityTags, TArray<URPGGameplayAbility*>& ActiveAbilities);

	/** 返回冷却标签的总时间和剩余时间。如果未找到活动冷却，则返回 false */
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	bool GetCooldownRemainingForTag(FGameplayTagContainer CooldownTags, float& TimeRemaining, float& CooldownDuration);

protected:
	/** 此角色的等级，一旦生成后不应直接修改 */
	UPROPERTY(EditAnywhere, Replicated, Category = Abilities)
	int32 CharacterLevel;

	/** 创建时授予此角色的能力。这些将通过标签或事件激活，并不绑定到特定输入 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Abilities)
	TArray<TSubclassOf<URPGGameplayAbility>> GameplayAbilities;

	/** 物品槽到游戏性能力类的映射，这些在库存添加任何能力之前绑定 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Abilities)
	TMap<FRPGItemSlot, TSubclassOf<URPGGameplayAbility>> DefaultSlottedAbilities;

	/** 创建时应用的被动游戏性效果 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Abilities)
	TArray<TSubclassOf<UGameplayEffect>> PassiveGameplayEffects;

	/** 用于处理能力系统交互的组件 */
	UPROPERTY()
	URPGAbilitySystemComponent* AbilitySystemComponent;

	/** 由能力系统修改的属性列表 */
	UPROPERTY()
	URPGAttributeSet* AttributeSet;

	/** 此角色的库存源的缓存指针，可以为空 */
	UPROPERTY()
	TScriptInterface<IRPGInventoryInterface> InventorySource;

	/** 如果为 true，表示我们已初始化能力 */
	UPROPERTY()
	int32 bAbilitiesInitialized;

	/** 槽位到该槽位授予的能力的映射。我稍后可能会重构这个 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	TMap<FRPGItemSlot, FGameplayAbilitySpecHandle> SlottedAbilities;

	/** 委托句柄 */
	FDelegateHandle InventoryUpdateHandle;
	FDelegateHandle InventoryLoadedHandle;

	/**
	 * 当角色受到伤害时调用，这可能已经将其杀死
	 *
	 * @param DamageAmount 造成的伤害量，未基于当前生命值进行钳制
	 * @param HitInfo 产生此伤害的命中信息
	 * @param DamageTags 造成伤害的事件的游戏性标签
	 * @param InstigatorCharacter 发起此伤害的角色
	 * @param DamageCauser 实际造成伤害的 Actor，可能是武器或射弹
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void OnDamaged(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, ARPGCharacterBase* InstigatorCharacter, AActor* DamageCauser);

	/**
	 * 当生命值改变时调用，无论是来自治疗还是受到伤害
	 * 对于伤害，这是在 OnDamaged/OnKilled 之外调用的
	 *
	 * @param DeltaValue 生命值的变化值，正值为治疗，负值为消耗。如果为 0，则变化量未知
	 * @param EventTags 改变生命值的事件的游戏性标签
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	/**
	 * 当法力值改变时调用，无论是来自回复还是作为消耗被使用
	 *
	 * @param DeltaValue 法力值的变化值，正值为回复，负值为消耗。如果为 0，则变化量未知
	 * @param EventTags 改变法力值的事件的游戏性标签
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void OnManaChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	/**
	 * 当移动速度改变时调用
	 *
	 * @param DeltaValue 移动速度的变化值
	 * @param EventTags 改变移动速度的事件的游戏性标签
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void OnMoveSpeedChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	/** 当槽位物品改变时调用，绑定到接口上的委托 */
	void OnItemSlotChanged(FRPGItemSlot ItemSlot, URPGItem* Item);
	void RefreshSlottedGameplayAbilities();

	/** 应用初始游戏性能力和效果 */
	void AddStartupGameplayAbilities();

	/** 尝试移除任何初始游戏性能力 */
	void RemoveStartupGameplayAbilities();

	/** 如果需要，添加槽位物品能力  */
	void AddSlottedGameplayAbilities();

	/** 根据默认值和库存填充能力规格 */
	void FillSlottedAbilitySpecs(TMap<FRPGItemSlot, FGameplayAbilitySpec>& SlottedAbilitySpecs);

	/** 移除槽位游戏性能力，如果 force 为 false，则仅移除无效的能力 */
	void RemoveSlottedGameplayAbilities(bool bRemoveAll);

	// 这些调用来自 RPGAttributeSet，它们会调用上述 BP 事件
	virtual void HandleDamage(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, ARPGCharacterBase* InstigatorCharacter, AActor* DamageCauser);
	virtual void HandleHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
	virtual void HandleManaChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
	virtual void HandleMoveSpeedChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	/** 持 AIPerceptionSystem 所需 */
	virtual FGenericTeamId GetGenericTeamId() const override;

	// 友元类，以允许访问上面的处理函数
	friend URPGAttributeSet;
};
