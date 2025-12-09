// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ActionRPG.h"
#include "Engine/DataAsset.h"
#include "Styling/SlateBrush.h"
#include "RPGAssetManager.h"
#include "RPGItem.generated.h"

class URPGGameplayAbility;

/** 所有物品的基类，请勿直接进行蓝图化 */
UCLASS(Abstract, BlueprintType)
class ACTIONRPG_API URPGItem : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/** 构造函数 */
	URPGItem()
		: Price(0)
		, MaxCount(1)
		, MaxLevel(1)
		, AbilityLevel(1)
	{}

	/** 此物品的类型，在原生父类中设置 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	FPrimaryAssetType ItemType;

	/** 用户可见的短名称 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FText ItemName;

	/** 用户可见的长描述 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FText ItemDescription;

	/** 要显示的图标 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FSlateBrush ItemIcon;

	/** 游戏中的价格 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	int32 Price;

	/** 库存中一次可拥有的最大实例数，<= 0 表示无限 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Max)
	int32 MaxCount;

	/** 返回物品是否为消耗品（MaxCount <= 0） */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Max)
	bool IsConsumable() const;

	/** 此物品的最大等级，<= 0 表示无限 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Max)
	int32 MaxLevel;

	/** 如果此物品在槽位中，则授予的能力 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Abilities)
	TSubclassOf<URPGGameplayAbility> GrantedAbility;

	/** 此物品授予的能力等级。<= 0 表示角色等级 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Abilities)
	int32 AbilityLevel;

	/** 返回逻辑名称，等同于主要资产 ID */
	UFUNCTION(BlueprintCallable, Category = Item)
	FString GetIdentifierString() const;

	/** 重写以使用保存的类型 */
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};


