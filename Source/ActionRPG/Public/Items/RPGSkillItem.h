// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Items/RPGItem.h"
#include "RPGSkillItem.generated.h"

/** 技能的原生基类，应进行蓝图化 */
UCLASS()
class ACTIONRPG_API URPGSkillItem : public URPGItem
{
	GENERATED_BODY()

public:
	/** 构造函数 */
	URPGSkillItem()
	{
		ItemType = URPGAssetManager::SkillItemType;
	}
};