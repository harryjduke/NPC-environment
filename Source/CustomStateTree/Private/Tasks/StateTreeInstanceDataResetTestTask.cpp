#include "Tasks/StateTreeInstanceDataResetTestTask.h"

#include "StateTreeExecutionContext.h"

EStateTreeRunStatus FStateTreeInstanceDataResetTestTask::EnterState(FStateTreeExecutionContext& Context,
                                                                    const FStateTreeTransitionResult& Transition) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	UE_LOG(LogTemp, Log, TEXT("UProperty %s"), InstanceData.bTestUProperty ? TEXT("True") : TEXT("False"));
	UE_LOG(LogTemp, Log, TEXT("Property %s"), InstanceData.bTestProperty ? TEXT("True") : TEXT("False"));

	InstanceData.bTestUProperty = true;
	InstanceData.bTestProperty = true;

	return EStateTreeRunStatus::Succeeded;
}
