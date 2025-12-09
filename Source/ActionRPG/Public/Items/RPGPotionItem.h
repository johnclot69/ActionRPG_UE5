// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Items/RPGItem.h"
#include "RPGPotionItem.generated.h"

/** 药水的原生基类，应进行蓝图化 */
UCLASS()
class ACTIONRPG_API URPGPotionItem : public URPGItem
{
	GENERATED_BODY()

public:
	/** 构造函数 */
	URPGPotionItem()
	{
		ItemType = URPGAssetManager::PotionItemType;
	}
};