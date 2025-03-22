// Copyright (c) 2025 Harry Duke <harryjduke@gmail.com>

#pragma once

#include "AITypes.h"
#include "StateTreeConditionBase.h"
#include "NPCEnvironment_Demo/Inventory/InventoryComponent.h"
#include "NPCEnvironment_Demo/Inventory/Item.h"

#include "StateTreeCompareInventoryItemQuantityCondition.generated.h"

USTRUCT()
struct FStateTreeCompareInventoryItemQuantityConditionInstanceData
{
	GENERATED_BODY()

	/**
	 * The inventory component to add the item to.
	 */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInventoryComponent* InventoryComponent;

	/**
	 * The subclass of AItem that the item is associated with.
	 */
	UPROPERTY(EditAnywhere, Category = "Parameter")
	TSubclassOf<AItem> ItemClass;

	/**
	 * The value to compare the Attribute against
	 */
	UPROPERTY(EditAnywhere, Category = "Parameter")
	int32 Right = 0.0f;
};
STATETREE_POD_INSTANCEDATA(FStateTreeCompareInventoryItemQuantityConditionInstanceData)

/**
 * Condition for comparing the number of a specific item in an inventory against an integer
 */
USTRUCT(DisplayName = "Inventory Item Quantity Compare", Category = "Custom|Inventory")
struct FStateTreeCompareInventoryItemQuantityCondition : public FStateTreeConditionCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FStateTreeCompareInventoryItemQuantityConditionInstanceData;

	FStateTreeCompareInventoryItemQuantityCondition() = default;
	explicit FStateTreeCompareInventoryItemQuantityCondition(const EGenericAICheck InOperator, const EStateTreeCompare InInverts = EStateTreeCompare::Default)
		: bInvert(InInverts == EStateTreeCompare::Invert)
		, Operator(InOperator)
	{}

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;
#if WITH_EDITOR
	virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;
#endif

	/**
	 * Inverts the result of the condition when true
	 */
	UPROPERTY(EditAnywhere, Category = "Parameter")
	bool bInvert = false;

	/**
	 * The comparison operation used
	 */
	UPROPERTY(EditAnywhere, Category = "Parameter", meta = (InvalidEnumValues = "IsTrue"))
	EGenericAICheck Operator = EGenericAICheck::Equal;
};
