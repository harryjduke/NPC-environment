// Copyright (c) 2025 Harry Duke <harryjduke@gmail.com>

#pragma once

#include "AbilitySystemComponent.h"
#include "StateTreeTaskBase.h"

#include "StateTreeActivateAbilityTask.generated.h"

USTRUCT()
struct NPCENVIRONMENT_DEMO_API FStateTreeActivateAbilityTaskInstanceData
{
	GENERATED_BODY()

	/**
	 * The Ability System Component to activate the ability on.
	 */
	UPROPERTY(EditAnywhere, Category = "Input")
	UAbilitySystemComponent* AbilitySystemComponent = nullptr;

	/**
	 * Type of ability to grant.
	 */
	UPROPERTY(EditAnywhere, Category = "Parameter")
	TSubclassOf<UGameplayAbility> AbilityClass = nullptr;

	/**
	 * Level to grant the ability at.
	 */
	UPROPERTY(EditAnywhere, Category = "Parameter")
	int32 Level = 0;

	/**
	 * Input ID value to bind ability activation to.
	 */
	UPROPERTY(EditAnywhere, Category = "Parameter")
	int32 InputID = -1;

	/**
	 * If true, this task will succeed if the ability is successfully activated.
	 */
	UPROPERTY(EditAnywhere, Category = "Parameter")
	bool bCanSucceed = true;

	/**
	 * If true and `bCanSucceed` is true, this task will only succeed when the ability completes.
	 */
	UPROPERTY(EditAnywhere, Category = "Parameter")
	bool bSucceedOnAbilityCompletion = true;

	/**
	 * If true, the task will be cancelled when the state exits
	 */
	UPROPERTY(EditAnywhere, Category = "Parameter")
	bool bCancelOnAbilityExitState = true;

	/**
	 * Used by the task to hold the handle of the activated ability spec
	 */
	FGameplayAbilitySpecHandle AbilitySpecHandle;

	/**
	 * Used by the task to remove the delegate when the state ends
	 */
	FDelegateHandle OnAbilityEndedHandle;

	/**
	 * Used by the task to track whether the activated ability has ended
	 */
	bool bAbilityEnded = false;

	/**
	 * Used by the task to track whether the activated ability was cancelled
	 */
	bool bAbilityCancelled = false;
};

/**
 * Task that activates an ability on the Ability System Component.
 */
USTRUCT(DisplayName = "Activate Ability", Category = "Custom|Gamplay Abilty System")
struct NPCENVIRONMENT_DEMO_API FStateTreeActivateAbilityTask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FStateTreeActivateAbilityTaskInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
		const FStateTreeTransitionResult& Transition) const override;

	virtual void ExitState(FStateTreeExecutionContext& Context,
		const FStateTreeTransitionResult& Transition) const override;

	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;
};
