// Copyright Epic Games, Inc. All Rights Reserved.

#include "RPGSaveGame.h"
#include "RPGGameInstanceBase.h"

void URPGSaveGame::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	if (Ar.IsLoading() && SavedDataVersion != ERPGSaveGameVersion::LatestVersion)
	{
		if (SavedDataVersion < ERPGSaveGameVersion::AddedItemData)
		{
			// 从列表格式转换为“物品数据映射（map）”格式
			for (const FPrimaryAssetId& ItemId : InventoryItems_DEPRECATED)
			{
				InventoryData.Add(ItemId, FRPGItemData(1, 1));
			}

			InventoryItems_DEPRECATED.Empty();
		}
		
		SavedDataVersion = ERPGSaveGameVersion::LatestVersion;
	}
}