// Copyright (c) 2025 Harry Duke <harryjduke@gmail.com>

#include "StateTreeAddItemToInventoryTask.h"

#include "StateTreeExecutionContext.h"

EStateTreeRunStatus FStateTreeAddItemToInventoryTask::EnterState(FStateTreeExecutionContext& Context,
                                                                 const FStateTreeTransitionResult& Transition) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	if (!IsValid(InstanceData.InventoryComponent))
	{
		UE_VLOG(Context.GetOwner(), LogStateTree, Warning, TEXT("FStateTreeAddItemToInventory Failed: Invalid Inventory Component."));
		return EStateTreeRunStatus::Failed;
	}

	InstanceData.InventoryComponent->AddItemToInventory(InstanceData.Item);

	return InstanceData.bCanSucceed ? EStateTreeRunStatus::Succeeded : EStateTreeRunStatus::Running;
}
