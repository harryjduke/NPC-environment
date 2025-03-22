// Copyright (c) 2025 Harry Duke <harryjduke@gmail.com>

#include "StateTreeCompareInventoryItemQuantityCondition.h"

#include "StateTreeExecutionContext.h"
#include "StateTreeNodeDescriptionHelpers.h"

#define LOCTEXT_NAMESPACE "NPCEnvironment_Demo"

bool CompareIntegers(const int32 Left, const int32 Right, const EGenericAICheck Operator)
{
	switch (Operator)
	{
	case EGenericAICheck::Equal:
		return Left == Right;
	case EGenericAICheck::NotEqual:
		return Left != Right;
	case EGenericAICheck::Less:
		return Left < Right;
	case EGenericAICheck::LessOrEqual:
		return Left <= Right;
	case EGenericAICheck::Greater:
		return Left > Right;
	case EGenericAICheck::GreaterOrEqual:
		return Left >= Right;
	default:
		ensureMsgf(false, TEXT("Unhandled operator %d"), Operator);
		return false;
	}
}

bool FStateTreeCompareInventoryItemQuantityCondition::TestCondition(FStateTreeExecutionContext& Context) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	if (!IsValid(InstanceData.InventoryComponent))
	{
		UE_LOG(LogStateTree, Warning, TEXT("CompareInventoryItemQuantityCondition Failed: Invalid Inventory Component"));
		return false ^ bInvert;
	}

	const int32 InventoryItemQuantity = InstanceData.InventoryComponent->GetNumberOfItemsByClass(InstanceData.ItemClass);
	const bool bResult = CompareIntegers(InventoryItemQuantity, InstanceData.Right, Operator);

	return bResult ^ bInvert;
}

#if WITH_EDITOR
FText FStateTreeCompareInventoryItemQuantityCondition::GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const
{
	const FInstanceDataType* InstanceData = InstanceDataView.GetPtr<FInstanceDataType>();
	check(InstanceData);

	FText InventoryComponentValue = BindingLookup.GetBindingSourceDisplayName(FStateTreePropertyPath(ID, GET_MEMBER_NAME_CHECKED(FInstanceDataType, InventoryComponent)), Formatting);
	FText InventoryComponentOwnerValue = FText::GetEmpty();

	if (InventoryComponentValue.IsEmpty())
	{
		if (IsValid(InstanceData->InventoryComponent))
		{
			InventoryComponentOwnerValue = FText::FromString(InstanceData->InventoryComponent->GetOwner()->GetName());
		}
		else
		{
			InventoryComponentOwnerValue = LOCTEXT("InvalidInventoryComponent", "Invalid");
		}
	}

    FText ItemClassName = BindingLookup.GetBindingSourceDisplayName(FStateTreePropertyPath(ID, GET_MEMBER_NAME_CHECKED(FInstanceDataType, ItemClass)), Formatting);

    if (ItemClassName.IsEmpty())
    {
        if (IsValid(InstanceData->ItemClass))
        {
        	ItemClassName = FText::FromString(InstanceData->ItemClass->GetName());
        }
        else
        {
            ItemClassName = LOCTEXT("InvalidItemClass", "Invalid");
        }
    }

    FText RightValue = BindingLookup.GetBindingSourceDisplayName(FStateTreePropertyPath(ID, GET_MEMBER_NAME_CHECKED(FInstanceDataType, Right)), Formatting);
    if (RightValue.IsEmpty())
    {
        RightValue = FText::AsNumber(InstanceData->Right);
    }

    const FText InvertText = UE::StateTree::DescHelpers::GetInvertText(bInvert, Formatting);
    const FText OperatorText = UE::StateTree::DescHelpers::GetOperatorText(Operator, Formatting);

	if (!InventoryComponentValue.IsEmpty())
	{
		return FText::FormatNamed(
			LOCTEXT("CompareInventoryItemQuantity",
			        "{EmptyOrNot}Number of {ItemClass}s in {InventoryComponent} {Op} {Right}"),
			TEXT("EmptyOrNot"), InvertText,
			TEXT("ItemClass"), ItemClassName,
			TEXT("InventoryComponent"), InventoryComponentValue,
			TEXT("Op"), OperatorText,
			TEXT("Right"), RightValue);
	}
	return FText::FormatNamed(
		LOCTEXT("CompareInventoryItemQuantity",
		        "{EmptyOrNot}Number of {ItemClass}s in {InventoryComponentOwner}'s Inventory {Op} {Right}"),
		TEXT("EmptyOrNot"), InvertText,
		TEXT("ItemClass"), ItemClassName,
		TEXT("InventoryComponentOwner"), InventoryComponentOwnerValue,
		TEXT("Op"), OperatorText,
		TEXT("Right"), RightValue);


}
#endif

#undef LOCTEXT_NAMESPACE