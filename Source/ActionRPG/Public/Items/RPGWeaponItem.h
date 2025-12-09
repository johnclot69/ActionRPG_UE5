// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Items/RPGItem.h"
#include "RPGWeaponItem.generated.h"

/** 武器的原生基类，应进行蓝图化 */
UCLASS()
class ACTIONRPG_API URPGWeaponItem : public URPGItem
{
	GENERATED_BODY()

public:
	/** 构造函数 */
	URPGWeaponItem()
	{
		ItemType = URPGAssetManager::WeaponItemType;
	}

	/** 要生成的武器 Actor */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
	TSubclassOf<AActor> WeaponActor;
};