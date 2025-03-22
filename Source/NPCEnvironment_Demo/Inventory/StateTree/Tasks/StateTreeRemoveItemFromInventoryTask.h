// Copyright (c) 2025 Harry Duke <harryjduke@gmail.com>

#pragma once

#include "StateTreeTaskBase.h"
#include "NPCEnvironment_Demo/Inventory/InventoryComponent.h"

#include "StateTreeRemoveItemFromInventoryTask.generated.h"

USTRUCT()
struct FStateTreeRemoveItemFromInventoryTaskInstanceData
{
	GENERATED_BODY()

	/**
	 * The inventory component to add the item to.
	 */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInventoryComponent* InventoryComponent = nullptr;

	/**
	 * The subclass of AItem associated with the items to remove.
	 */
	UPROPERTY(EditAnywhere, Category = "Parameter")
	TSubclassOf<AItem> ItemClass = nullptr;

	/**
	 * If true, items will be removed from the inventory even if there are not enough to remove the full 'RemoveAmount'.
	 */
	UPROPERTY(EditAnywhere, Category = "Parameter")
	bool bRemovePartialAmount = false;

	/**
	 * The number of items successfully removed.
	 */
	UPROPERTY(EditAnywhere, Category = "Output")
	int32 AmountRemoved = 0;
};

/**
 * Task that removes an item from the inventory of the given Inventory Component
 */
USTRUCT(DisplayName = "Remove Item From Inventory", Category = "Custom|Inventory")
struct FStateTreeRemoveItemFromInventoryTask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FStateTreeRemoveItemFromInventoryTaskInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
		const FStateTreeTransitionResult& Transition) const override;
};
