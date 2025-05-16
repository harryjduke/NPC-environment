// Copyright (c) 2025 Harry Duke <harryjduke@gmail.com>

#pragma once

#include "CoreMinimal.h"
#include "SmartObjectRuntime.h"
#include "StateTreeTaskBase.h"

#include "StateTreeMoveToEntranceAndUseSmartObjectTask.generated.h"


USTRUCT()
struct CUSTOMSTATETREE_API FStateTreeMoveToEntranceAndUseSmartObjectTaskInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Context)
	TObjectPtr<AActor> Actor;

	UPROPERTY(EditAnywhere, Category = Input)
	FSmartObjectClaimHandle ClaimHandle;
};

USTRUCT(DisplayName = "Move to Entrance and Use Smart Object", Category = "Custom|Smart Object")
struct CUSTOMSTATETREE_API FStateTreeMoveToEntranceAndUseSmartObjectTask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FStateTreeMoveToEntranceAndUseSmartObjectTaskInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }


	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
	                                       const FStateTreeTransitionResult& Transition) const override;
};
