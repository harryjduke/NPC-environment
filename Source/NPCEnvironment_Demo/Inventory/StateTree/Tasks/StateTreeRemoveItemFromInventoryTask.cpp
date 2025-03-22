#include "StateTreeRemoveItemFromInventoryTask.h"

#include "StateTreeExecutionContext.h"

EStateTreeRunStatus FStateTreeRemoveItemFromInventoryTask::EnterState(FStateTreeExecutionContext& Context,
                                                                      const FStateTreeTransitionResult& Transition) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	if (!IsValid(InstanceData.InventoryComponent))
	{
		UE_VLOG(Context.GetOwner(), LogStateTree, Warning, TEXT("FStateTreeRemoveItemFromInventory Failed: Invalid Inventory Component."));
		return EStateTreeRunStatus::Failed;
	}

	InstanceData.AmountRemoved = InstanceData.InventoryComponent->RemoveItemsFromInventoryByClass(InstanceData.ItemClass);

	if (InstanceData.AmountRemoved == 0)
	{

		UE_VLOG(Context.GetOwner(), LogStateTree, Warning, TEXT("FStateTreeRemoveItemFromInventory failed because no items were removed."));
		return EStateTreeRunStatus::Failed;
	}
	return EStateTreeRunStatus::Succeeded;
}
