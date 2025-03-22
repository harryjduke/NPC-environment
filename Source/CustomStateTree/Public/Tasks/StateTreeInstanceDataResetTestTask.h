// Copyright (c) 2025 Harry Duke <harryjduke@gmail.com>

#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"

#include "StateTreeInstanceDataResetTestTask.generated.h"


USTRUCT()
struct CUSTOMSTATETREE_API FStateTreeInstanceDataResetTestTaskInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Parameter")
	bool bTestUProperty = false;

	bool bTestProperty = false;
};

USTRUCT(DisplayName = "Instance Data Reset Test", Category = "Test")
struct CUSTOMSTATETREE_API FStateTreeInstanceDataResetTestTask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FStateTreeInstanceDataResetTestTaskInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
		const FStateTreeTransitionResult& Transition) const override;
};
