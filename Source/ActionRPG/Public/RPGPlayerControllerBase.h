// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ActionRPG.h"
#include "GameFramework/PlayerController.h"
#include "RPGInventoryInterface.h"
#include "RPGPlayerControllerBase.generated.h"

/** PlayerController 的基类，应进行蓝图化 */
UCLASS()
class ACTIONRPG_API ARPGPlayerControllerBase : public APlayerController, public IRPGInventoryInterface
{
	GENERATED_BODY()

public:
	// 构造函数和重写
	ARPGPlayerControllerBase() {}
	virtual void BeginPlay() override;

	/** 所有该玩家拥有的物品的映射，从定义到数据 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	TMap<URPGItem*, FRPGItemData> InventoryData;

	/** 槽位的映射，从类型/数量到物品，从 RPGGameInstanceBase 上的 ItemSlotsPerType 初始化 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	TMap<FRPGItemSlot, URPGItem*> SlottedItems;

	/** 当库存物品被添加或移除时调用的委托 */
	UPROPERTY(BlueprintAssignable, Category = Inventory)
	FOnInventoryItemChanged OnInventoryItemChanged;

	/** 上述的原生版本，在 BP 委托之前调用 */
	FOnInventoryItemChangedNative OnInventoryItemChangedNative;

	/** 当库存槽位改变时调用的委托 */
	UPROPERTY(BlueprintAssignable, Category = Inventory)
	FOnSlottedItemChanged OnSlottedItemChanged;

	/** 在库存更改并通知所有委托后调用 */
	UFUNCTION(BlueprintImplementableEvent, Category = Inventory)
	void InventoryItemChanged(bool bAdded, URPGItem* Item);

	/** 在物品装备并通知所有委托后调用 */
	UFUNCTION(BlueprintImplementableEvent, Category = Inventory)
	void SlottedItemChanged(FRPGItemSlot ItemSlot, URPGItem* Item);

	/** 上述的原生版本，在 BP 委托之前调用 */
	FOnSlottedItemChangedNative OnSlottedItemChangedNative;

	/** 当库存加载/重新加载时调用的委托 */
	UPROPERTY(BlueprintAssignable, Category = Inventory)
	FOnInventoryLoaded OnInventoryLoaded;

	/** 上述的原生版本，在 BP 委托之前调用 */
	FOnInventoryLoadedNative OnInventoryLoadedNative;

	/** 添加新的库存物品，如果可能的话，将其添加到空槽中。如果物品支持计数，您可以添加多个计数。如果需要，添加时也会更新等级 */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool AddInventoryItem(URPGItem* NewItem, int32 ItemCount = 1, int32 ItemLevel = 1, bool bAutoSlot = true);

	/** 移除库存物品，也会从槽位中移除。移除计数 <= 0 表示移除所有副本 */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool RemoveInventoryItem(URPGItem* RemovedItem, int32 RemoveCount = 1);

	/** 返回给定类型的所有库存物品。如果未传递类型，它将返回所有物品 */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	void GetInventoryItems(TArray<URPGItem*>& Items, FPrimaryAssetType ItemType);

	/** 返回在库存中找到的此物品的实例数。这使用 GetItemData 中的计数 */
	UFUNCTION(BlueprintPure, Category = Inventory)
	int32 GetInventoryItemCount(URPGItem* Item) const;

	/** 返回与物品关联的物品数据。如果未找到，则返回 false */
	UFUNCTION(BlueprintPure, Category = Inventory)
	bool GetInventoryItemData(URPGItem* Item, FRPGItemData& ItemData) const;

	/** 将物品设置到槽位，如果需要，将从其他槽位移除。如果传递 null，这将清空槽位 */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool SetSlottedItem(FRPGItemSlot ItemSlot, URPGItem* Item);

	/** 返回槽位中的物品，如果为空则返回 null */
	UFUNCTION(BlueprintPure, Category = Inventory)
	URPGItem* GetSlottedItem(FRPGItemSlot ItemSlot) const;

	/** 返回给定类型的所有槽位物品。如果未传递类型，它将返回所有物品 */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	void GetSlottedItems(TArray<URPGItem*>& Items, FPrimaryAssetType ItemType, bool bOutputEmptyIndexes);

	/** 用库存中的物品填充任何空槽位 */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	void FillEmptySlots();

	/** 手动保存库存，这会自动从添加/移除函数调用 */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool SaveInventory();

	/** 从游戏实例上的保存游戏加载库存，这将替换数组 */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool LoadInventory();

	// 实现 IRPGInventoryInterface
	virtual const TMap<URPGItem*, FRPGItemData>& GetInventoryDataMap() const override
	{
		return InventoryData;
	}
	virtual const TMap<FRPGItemSlot, URPGItem*>& GetSlottedItemMap() const override
	{
		return SlottedItems;
	}
	virtual FOnInventoryItemChangedNative& GetInventoryItemChangedDelegate() override
	{
		return OnInventoryItemChangedNative;
	}
	virtual FOnSlottedItemChangedNative& GetSlottedItemChangedDelegate() override
	{
		return OnSlottedItemChangedNative;
	}
	virtual FOnInventoryLoadedNative& GetInventoryLoadedDelegate() override
	{
		return OnInventoryLoadedNative;
	}

protected:
	/** 自动将特定物品放入槽位，如果有任何更改则返回 true */
	bool FillEmptySlotWithItem(URPGItem* NewItem);

	/** 调用库存更新回调 */
	void NotifyInventoryItemChanged(bool bAdded, URPGItem* Item);
	void NotifySlottedItemChanged(FRPGItemSlot ItemSlot, URPGItem* Item);
	void NotifyInventoryLoaded();

	/** 当全局保存游戏加载后调用 */
	void HandleSaveGameLoaded(URPGSaveGame* NewSaveGame);
};
