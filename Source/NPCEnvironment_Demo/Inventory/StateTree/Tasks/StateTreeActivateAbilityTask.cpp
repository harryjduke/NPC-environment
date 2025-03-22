// Copyright (c) 2025 Harry Duke <harryjduke@gmail.com>

#include "StateTreeActivateAbilityTask.h"

#include "StateTreeExecutionContext.h"

EStateTreeRunStatus FStateTreeActivateAbilityTask::EnterState(FStateTreeExecutionContext& Context,
                                                              const FStateTreeTransitionResult& Transition) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	if (!IsValid(InstanceData.AbilitySystemComponent))
	{
		UE_VLOG(Context.GetOwner(), LogStateTree, Warning, TEXT("FStateTreeActivateAbility EnterState Failed: Invalid Ability System Component."));
		return EStateTreeRunStatus::Failed;
	}

	const FGameplayAbilitySpec AbilitySpec(InstanceData.AbilityClass, InstanceData.Level, InstanceData.InputID);
	InstanceData.AbilitySpecHandle = InstanceData.AbilitySystemComponent->GiveAbility(AbilitySpec);

	if (!InstanceData.AbilitySystemComponent->TryActivateAbility(InstanceData.AbilitySpecHandle, true))
	{
		return EStateTreeRunStatus::Failed;
	}

	if (!InstanceData.bCanSucceed)
	{
		return EStateTreeRunStatus::Running;
	}

	if (InstanceData.bSucceedOnAbilityCompletion)
	{
		InstanceData.OnAbilityEndedHandle = InstanceData.AbilitySystemComponent->OnAbilityEnded.AddLambda(
			[InstanceData = &InstanceData](const FAbilityEndedData& AbilityEndedData)
			{
				if (InstanceData->AbilitySpecHandle != AbilityEndedData.AbilitySpecHandle)
				{
					return;
				}

				InstanceData->bAbilityEnded = true;
				InstanceData->bAbilityCancelled = AbilityEndedData.bWasCancelled;
			});

		return EStateTreeRunStatus::Running;
	}

	return EStateTreeRunStatus::Succeeded;
}

void FStateTreeActivateAbilityTask::ExitState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	 FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	if (!IsValid(InstanceData.AbilitySystemComponent))
	{
		UE_VLOG(Context.GetOwner(), LogStateTree, Warning, TEXT("FStateTreeActivateAbility ExitState Failed: Invalid Ability System Component."));
		return;
	}

	if (InstanceData.bCancelOnAbilityExitState)
	{
		InstanceData.AbilitySystemComponent->CancelAbilityHandle(InstanceData.AbilitySpecHandle);
	}

	InstanceData.AbilitySystemComponent->ClearAbility(InstanceData.AbilitySpecHandle);

	if (InstanceData.bSucceedOnAbilityCompletion)
	{
		InstanceData.AbilitySystemComponent->OnAbilityEnded.Remove(InstanceData.OnAbilityEndedHandle);
	}

	InstanceData.bAbilityEnded = false;
	InstanceData.bAbilityCancelled = false;
}

EStateTreeRunStatus FStateTreeActivateAbilityTask::Tick(FStateTreeExecutionContext& Context,
	const float DeltaTime) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	if (InstanceData.bAbilityEnded)
	{
		return InstanceData.bAbilityCancelled ? EStateTreeRunStatus::Failed : EStateTreeRunStatus::Succeeded;
	}

	return EStateTreeRunStatus::Running;
}
