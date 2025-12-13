// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ActionRPG.h"
#include "Engine/AssetManager.h"
#include "UObject/PrimaryAssetId.h"
#include "RPGAssetManager.generated.h"

class URPGItem;

/**
 * 资产管理器的游戏实现，覆盖功能并存储特定于游戏的类型
 * 预计大多数游戏都会希望覆盖 AssetManager，因为它为特定于游戏的加载逻辑提供了一个好地方
 * 这是通过在 DefaultEngine.ini 中设置 AssetManagerClassName 来使用的
 */
UCLASS()
class ACTIONRPG_API URPGAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	// 构造函数和重写
	URPGAssetManager() {}
	virtual void StartInitialLoading() override;

	/** 物品的静态类型 */
	static const FPrimaryAssetType	PotionItemType;
	static const FPrimaryAssetType	SkillItemType;
	static const FPrimaryAssetType	TokenItemType;
	static const FPrimaryAssetType	WeaponItemType;

	/** 返回当前的 AssetManager 对象 */
	static URPGAssetManager& Get();

	/**
	 * 同步加载 RPGItem 子类，这可能会造成卡顿，但在您无法等待异步加载时很有用
	 * 这不会保留对物品的引用，因此如果未以其他方式加载，它将被垃圾回收
	 *
	 * @param PrimaryAssetId 要加载的资产标识符
	 * @param bDisplayWarning 如果为 true，则在物品加载失败时记录警告
	 */
	URPGItem* ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning = true) const;
};

