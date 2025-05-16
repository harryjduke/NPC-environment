#include "Tasks/StateTreeMoveToEntranceAndUseSmartObjectTask.h"

#include "StateTreeExecutionContext.h"
#include "AI/AITask_UseGameplayBehaviorSmartObject.h"

EStateTreeRunStatus FStateTreeMoveToEntranceAndUseSmartObjectTask::EnterState(FStateTreeExecutionContext& Context,
                                                                              const FStateTreeTransitionResult& Transition) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);


		return EStateTreeRunStatus::Running;
}
