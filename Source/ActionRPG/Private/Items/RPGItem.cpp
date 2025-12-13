// Copyright Epic Games, Inc. All Rights Reserved.

#include "Items/RPGItem.h"

bool URPGItem::IsConsumable() const
{
	if (MaxCount <= 0)
	{
		return true;
	}
	return false;
}

FString URPGItem::GetIdentifierString() const
{
	return GetPrimaryAssetId().ToString();
}

FPrimaryAssetId URPGItem::GetPrimaryAssetId() const
{
	// 这是一个 DataAsset 而不是蓝图，因此可以直接使用原始 FName
	// 对于蓝图，你需要处理去掉末尾的 “_C” 后缀
	return FPrimaryAssetId(ItemType, GetFName());
}