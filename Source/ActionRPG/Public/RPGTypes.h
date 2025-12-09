// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ----------------------------------------------------------------------------------------------------------------
// 此头文件用于整个游戏中的类和蓝图使用的枚举和结构体
// 将这些收集在单个头文件中通过避免递归头文件包含问题来提供帮助
// 这也是放置数据表行结构体等内容的好地方
// ----------------------------------------------------------------------------------------------------------------

#include "UObject/PrimaryAssetId.h"
#include "RPGTypes.generated.h"

class URPGItem;
class URPGSaveGame;

/** 表示物品槽位的结构体，在 UI 中显示 */
USTRUCT(BlueprintType)
struct ACTIONRPG_API FRPGItemSlot
{
	GENERATED_BODY()

	/** 构造函数，-1 表示无效槽位 */
	FRPGItemSlot()
		: SlotNumber(-1)
	{}

	FRPGItemSlot(const FPrimaryAssetType& InItemType, int32 InSlotNumber)
		: ItemType(InItemType)
		, SlotNumber(InSlotNumber)
	{}

	/** 可以放入此槽位的物品类型 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FPrimaryAssetType ItemType;

	/** 此槽位的编号，0 索引 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 SlotNumber;

	/** 相等运算符 */
	bool operator==(const FRPGItemSlot& Other) const
	{
		return ItemType == Other.ItemType && SlotNumber == Other.SlotNumber;
	}
	bool operator!=(const FRPGItemSlot& Other) const
	{
		return !(*this == Other);
	}

	/** 实现以便可以在 Map/Set 中使用  */
	friend inline uint32 GetTypeHash(const FRPGItemSlot& Key)
	{
		uint32 Hash = 0;

		Hash = HashCombine(Hash, GetTypeHash(Key.ItemType));
		Hash = HashCombine(Hash, (uint32)Key.SlotNumber);
		return Hash;
	}

	/** 如果槽位有效则返回 true */
	bool IsValid() const
	{
		return ItemType.IsValid() && SlotNumber >= 0;
	}
};


/** 关于玩家库存中 URPGItem 的额外信息 */
USTRUCT(BlueprintType)
struct ACTIONRPG_API FRPGItemData
{
	GENERATED_BODY()

	/** 构造函数，默认为数量/等级 1，以便在蓝图中声明它们能给您预期的行为 */
	FRPGItemData()
		: ItemCount(1)
		, ItemLevel(1)
	{}

	FRPGItemData(int32 InItemCount, int32 InItemLevel)
		: ItemCount(InItemCount)
		, ItemLevel(InItemLevel)
	{}

	/** 库存中此物品的实例数，永远不能低于 1 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 ItemCount;

	/** 此物品的等级。此等级由所有实例共享，永远不能低于 1 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 ItemLevel;

	/** 相等运算符 */
	bool operator==(const FRPGItemData& Other) const
	{
		return ItemCount == Other.ItemCount && ItemLevel == Other.ItemLevel;
	}
	bool operator!=(const FRPGItemData& Other) const
	{
		return !(*this == Other);
	}

	/** 如果计数大于 0 则返回 true */
	bool IsValid() const
	{
		return ItemCount > 0;
	}

	/** 追加物品数据，这将添加计数并覆盖其他所有内容 */
	void UpdateItemData(const FRPGItemData& Other, int32 MaxCount, int32 MaxLevel)
	{
		if (MaxCount <= 0)
		{
			MaxCount = MAX_int32;
		}

		if (MaxLevel <= 0)
		{
			MaxLevel = MAX_int32;
		}

		ItemCount = FMath::Clamp(ItemCount + Other.ItemCount, 1, MaxCount);
		ItemLevel = FMath::Clamp(Other.ItemLevel, 1, MaxLevel);
	}
};

/** 当库存物品更改时调用的委托 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventoryItemChanged, bool, bAdded, URPGItem*, Item);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInventoryItemChangedNative, bool, URPGItem*);

/** 当库存槽位内容更改时调用的委托 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSlottedItemChanged, FRPGItemSlot, ItemSlot, URPGItem*, Item);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSlottedItemChangedNative, FRPGItemSlot, URPGItem*);

/** 当整个库存已加载时调用的委托，所有物品可能已被替换 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryLoaded);
DECLARE_MULTICAST_DELEGATE(FOnInventoryLoadedNative);

/** 当保存游戏已加载/重置时调用的委托 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaveGameLoaded, URPGSaveGame*, SaveGame);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnSaveGameLoadedNative, URPGSaveGame*);
