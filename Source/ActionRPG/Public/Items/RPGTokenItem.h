// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Items/RPGItem.h"
#include "RPGTokenItem.generated.h"

/** 代币/货币的原生基类，应进行蓝图化 */
UCLASS()
class ACTIONRPG_API URPGTokenItem : public URPGItem
{
	GENERATED_BODY()

public:
	/** 构造函数 */
	URPGTokenItem()
	{
		ItemType = URPGAssetManager::TokenItemType;
		MaxCount = 0; // 无限
	}
};