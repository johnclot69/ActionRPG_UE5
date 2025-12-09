// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ActionRPG.h"
#include "Engine/GameInstance.h"
#include "RPGGameInstanceBase.generated.h"

class URPGItem;
class URPGSaveGame;

/**
 * GameInstance 的基类，应进行蓝图化
 * 大多数游戏需要创建 GameInstance 的特定游戏子类
 * 一旦你创建了原生子类的蓝图子类，你会希望在项目设置中将其设置为默认值
 */
UCLASS()
class ACTIONRPG_API URPGGameInstanceBase : public UGameInstance
{
	GENERATED_BODY()

public:
	// 构造函数
	URPGGameInstanceBase();

	/** 添加到新玩家的库存物品列表 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory)
	TMap<FPrimaryAssetId, FRPGItemData> DefaultInventory;

	/** 每种类型物品的槽位数 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory)
	TMap<FPrimaryAssetType, int32> ItemSlotsPerType;

	/** 用于保存的槽位名称 */
	UPROPERTY(BlueprintReadWrite, Category = Save)
	FString SaveSlot;

	/** 特定于平台的用户索引 */
	UPROPERTY(BlueprintReadWrite, Category = Save)
	int32 SaveUserIndex;

	/** 当保存游戏已加载/重置时调用的委托 */
	UPROPERTY(BlueprintAssignable, Category = Inventory)
	FOnSaveGameLoaded OnSaveGameLoaded;

	/** 保存游戏加载/重置的原生委托 */
	FOnSaveGameLoadedNative OnSaveGameLoadedNative;

	/**
	 * 将默认库存添加到库存数组
	 * @param InventoryArray 要修改的库存
	 * @param RemoveExtra 如果为 true，则移除默认库存以外的任何内容
	 */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	void AddDefaultInventory(URPGSaveGame* SaveGame, bool bRemoveExtra = false);

	/** 如果这是一个有效的物品槽，则返回 true */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool IsValidItemSlot(FRPGItemSlot ItemSlot) const;

	/** 返回当前保存游戏，以便用于初始化状态。在调用 WriteSaveGame 之前，更改不会被写入 */
	UFUNCTION(BlueprintCallable, Category = Save)
	URPGSaveGame* GetCurrentSaveGame();

	/** 设置是否启用保存/加载。如果禁用，它将始终算作新角色 */
	UFUNCTION(BlueprintCallable, Category = Save)
	void SetSavingEnabled(bool bEnabled);

	/** 同步加载保存游戏。如果失败，它将为您创建一个新的。如果已加载则返回 true，如果创建了一个新游戏则返回 false */
	UFUNCTION(BlueprintCallable, Category = Save)
	bool LoadOrCreateSaveGame();

	/** 处理使用 AsyncLoadGameFromSlot 加载 USaveGame 对象后所需的最终设置。如果已加载则返回 true，如果创建了一个新游戏则返回 false */
	UFUNCTION(BlueprintCallable, Category = Save)
	bool HandleSaveGameLoaded(USaveGame* SaveGameObject);

	/** 获取用于库存保存的保存游戏槽位和用户索引，准备传递给 GameplayStatics 保存函数 */
	UFUNCTION(BlueprintCallable, Category = Save)
	void GetSaveSlotInfo(FString& SlotName, int32& UserIndex) const;

	/** 将当前保存游戏对象写入磁盘。写入磁盘发生在后台线程中 */
	UFUNCTION(BlueprintCallable, Category = Save)
	bool WriteSaveGame();

	/** 将当前保存游戏重置为默认值。这将擦除玩家数据！直到下一次 WriteSaveGame 之前，这不会保存到磁盘 */
	UFUNCTION(BlueprintCallable, Category = Save)
	void ResetSaveGame();

protected:
	/** 当前保存游戏对象 */
	UPROPERTY()
	URPGSaveGame* CurrentSaveGame;

	/** 是否尝试实际保存到磁盘 */
	UPROPERTY()
	bool bSavingEnabled;

	/** 如果我们正在保存中，则为 true */
	UPROPERTY()
	bool bCurrentlySaving;

	/** 如果在保存期间请求了另一个保存，则为 true */
	UPROPERTY()
	bool bPendingSaveRequested;

	/** 当异步保存发生时调用 */
	virtual void HandleAsyncSave(const FString& SlotName, const int32 UserIndex, bool bSuccess);
};