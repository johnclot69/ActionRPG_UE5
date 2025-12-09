// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ActionRPG.h"
#include "Items/RPGItem.h"
#include "GameFramework/SaveGame.h"
#include "RPGSaveGame.generated.h"

/** 版本列表，原生代码将处理任何旧版本的修复 */
namespace ERPGSaveGameVersion
{
	enum type
	{
		// 初始版本
		Initial,
		// 添加了库存
		AddedInventory,
		// 添加了 ItemData 以存储数量/等级
		AddedItemData,

		// -----<新版本必须在此行之前添加>-------------------------------------------------
		VersionPlusOne,
		LatestVersion = VersionPlusOne - 1
	};
}

/** 写入和读取保存游戏存档的对象，带有数据版本 */
UCLASS(BlueprintType)
class ACTIONRPG_API URPGSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	/** 构造函数 */
	URPGSaveGame()
	{
		// 设置为当前版本，这将在加载时的序列化过程中被覆盖
		SavedDataVersion = ERPGSaveGameVersion::LatestVersion;
	}

	/** 物品到物品数据的映射 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = SaveGame)
	TMap<FPrimaryAssetId, FRPGItemData> InventoryData;

	/** 槽位物品的映射 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = SaveGame)
	TMap<FRPGItemSlot, FPrimaryAssetId> SlottedItems;

	/** 用户的唯一 ID */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = SaveGame)
	FString UserId;

protected:
	/** 已弃用的存储物品方式，这会被读入但不会被写出 */
	UPROPERTY()
	TArray<FPrimaryAssetId> InventoryItems_DEPRECATED;

	/** 存档保存时的 LatestVersion */
	UPROPERTY()
	int32 SavedDataVersion;

	/** 重写以允许版本修复 */
	virtual void Serialize(FArchive& Ar) override;
};
