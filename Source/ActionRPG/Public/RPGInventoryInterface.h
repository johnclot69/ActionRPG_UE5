// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ActionRPG.h"
#include "RPGInventoryInterface.generated.h"

/**
 * 为绑定到 ItemSlots 提供一组 RPGItems 的 Actor 的接口
 * 这样做是为了让 RPGCharacterBase 可以在不进行 hacky 的玩家控制器转换的情况下查询库存
 * 它仅设计用于原生类使用
 */
UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class URPGInventoryInterface : public UInterface
{
	GENERATED_BODY()
};

class ACTIONRPG_API IRPGInventoryInterface
{
	GENERATED_BODY()

public:
	/** 返回物品到数据的映射 */
	virtual const TMap<URPGItem*, FRPGItemData>& GetInventoryDataMap() const = 0;

	/** 返回槽位到物品的映射 */
	virtual const TMap<FRPGItemSlot, URPGItem*>& GetSlottedItemMap() const = 0;

	/** 获取库存物品更改的委托 */
	virtual FOnInventoryItemChangedNative& GetInventoryItemChangedDelegate() = 0;

	/** 获取库存槽位更改的委托 */
	virtual FOnSlottedItemChangedNative& GetSlottedItemChangedDelegate() = 0;

	/** 获取库存加载时的委托 */
	virtual FOnInventoryLoadedNative& GetInventoryLoadedDelegate() = 0;
};

