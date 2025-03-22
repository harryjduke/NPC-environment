// Copyright (c) 2025 Harry Duke <harryjduke@gmail.com>

#pragma once

#include "StateTreeTaskBase.h"
#include "NPCEnvironment_Demo/Inventory/InventoryComponent.h"
#include "NPCEnvironment_Demo/Inventory/Item.h"

#include "StateTreeAddItemToInventoryTask.generated.h"

USTRUCT()
struct NPCENVIRONMENT_DEMO_API FStateTreeAddItemToInventoryTaskInstanceData
{
	GENERATED_BODY()

	/**
	 * The inventory component to add the item to.
	 */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInventoryComponent* InventoryComponent = nullptr;

	/**
	 * The item to add to the inventory.
	 */
	UPROPERTY(EditAnywhere, Category = "Input")
	const AItem* Item = nullptr;

	/**
	 * If true, the task will succeed if the item is successfully added to the inventory.
	 */
	UPROPERTY(EditAnywhere, Category = "Parameter")
	bool bCanSucceed = true;
};

/**
 * Task that adds an item to the inventory of the given Inventory Component
 */
USTRUCT(DisplayName = "Add Item to Inventory", Category = "Custom|Inventory")
struct NPCENVIRONMENT_DEMO_API FStateTreeAddItemToInventoryTask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FStateTreeAddItemToInventoryTaskInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
		const FStateTreeTransitionResult& Transition) const override;
};
