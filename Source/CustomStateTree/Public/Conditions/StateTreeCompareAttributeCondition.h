// Copyright (c) 2025 Harry Duke <harryjduke@gmail.com>

#pragma once

#include "AbilitySystemInterface.h"
#include "AITypes.h"
#include "AttributeSet.h"
#include "StateTreeConditionBase.h"

#include "StateTreeCompareAttributeCondition.generated.h"

USTRUCT()
struct CUSTOMSTATETREE_API FStateTreeCompareAttributeConditionInstanceData
{
	GENERATED_BODY()

	/**
	 * The Ability System Component that has the Attribute Set with the desired Attribute
	 */
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	/**
	 * The Attribute to compare
	 */
	UPROPERTY(EditAnywhere, Category = "Parameter")
	FGameplayAttribute Attribute;

	/**
	 * The value to compare the Attribute against
	 */
	UPROPERTY(EditAnywhere, Category = "Parameter")
	float Right = 0.0f;
};
STATETREE_POD_INSTANCEDATA(FStateTreeCompareAttributeConditionInstanceData)

/**
 * Condition for comparing a Gameplay Attribute against a float
 */
USTRUCT(DisplayName = "Gameplay Attribute Compare", Category = "Custom|Gameplay Ability System|Attributes")
struct CUSTOMSTATETREE_API FStateTreeCompareAttributeCondition : public FStateTreeConditionCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FStateTreeCompareAttributeConditionInstanceData;

	FStateTreeCompareAttributeCondition() = default;
	explicit FStateTreeCompareAttributeCondition(const EGenericAICheck InOperator, const EStateTreeCompare InInverts = EStateTreeCompare::Default)
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
