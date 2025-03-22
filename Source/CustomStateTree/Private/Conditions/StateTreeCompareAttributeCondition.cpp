#include "Conditions/StateTreeCompareAttributeCondition.h"

#include "AbilitySystemComponent.h"
#include "StateTreeExecutionContext.h"
#include "StateTreeNodeDescriptionHelpers.h"

#define LOCTEXT_NAMESPACE "CustomStateTree"

bool CompareFloats(const float Left, const float Right, const EGenericAICheck Operator)
{
	switch (Operator)
	{
	case EGenericAICheck::Equal:
		return Left == Right;
		break;
	case EGenericAICheck::NotEqual:
		return Left != Right;
		break;
	case EGenericAICheck::Less:
		return Left < Right;
		break;
	case EGenericAICheck::LessOrEqual:
		return Left <= Right;
		break;
	case EGenericAICheck::Greater:
		return Left > Right;
		break;
	case EGenericAICheck::GreaterOrEqual:
		return Left >= Right;
		break;
	default:
		ensureMsgf(false, TEXT("Unhandled operator %d"), Operator);
		return false;
		break;
	}
}

bool FStateTreeCompareAttributeCondition::TestCondition(FStateTreeExecutionContext& Context) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	//UAbilitySystemComponent* AbilitySystemComponent = InstanceData.AbilitySystemComponent->GetAbilitySystemComponent();
	if (!IsValid(InstanceData.AbilitySystemComponent))
	{
		UE_LOG(LogStateTree, Warning, TEXT("CompareAttribute Condition: Invalid AbilitySystemObject"));
		return false ^ bInvert;
	}
	bool bGameplayAttributeFound;
	float GameplayAttributeValue =
		InstanceData.AbilitySystemComponent->GetGameplayAttributeValue(InstanceData.Attribute, bGameplayAttributeFound);
	if (!bGameplayAttributeFound)
	{
		UE_LOG(LogStateTree, Warning, TEXT("CompareAttribute Condition: Object has no AbilitySystemComponent"));
        return false ^ bInvert;
	}
	const bool bResult = CompareFloats(GameplayAttributeValue, InstanceData.Right, Operator);

	return bResult ^ bInvert;
}

#if WITH_EDITOR
FText FStateTreeCompareAttributeCondition::GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const
{
	const FInstanceDataType* InstanceData = InstanceDataView.GetPtr<FInstanceDataType>();
	check(InstanceData);

	FText AbilitySystemObjectValue = BindingLookup.GetBindingSourceDisplayName(FStateTreePropertyPath(ID, GET_MEMBER_NAME_CHECKED(FInstanceDataType, AbilitySystemComponent)), Formatting);

    FText AttributeValue = BindingLookup.GetBindingSourceDisplayName(FStateTreePropertyPath(ID, GET_MEMBER_NAME_CHECKED(FInstanceDataType, Attribute)), Formatting);
    FText AttributeSetValue = FText::GetEmpty();

    if (AttributeValue.IsEmpty())
    {
        if (InstanceData->Attribute.IsValid())
        {
        	AttributeSetValue = FText::FromString(InstanceData->Attribute.GetAttributeSetClass()->GetName());
            AttributeValue = FText::FromString(InstanceData->Attribute.AttributeName);
        }
        else
        {
            AttributeValue = LOCTEXT("InvalidAttribute", "Invalid");
            AttributeSetValue = LOCTEXT("InvalidAttributeSet", "Invalid");
        }
    }

    FText RightValue = BindingLookup.GetBindingSourceDisplayName(FStateTreePropertyPath(ID, GET_MEMBER_NAME_CHECKED(FInstanceDataType, Right)), Formatting);
    if (RightValue.IsEmpty())
    {
        RightValue = FText::AsNumber(InstanceData->Right);
    }

    const FText InvertText = UE::StateTree::DescHelpers::GetInvertText(bInvert, Formatting);
    const FText OperatorText = UE::StateTree::DescHelpers::GetOperatorText(Operator, Formatting);

    if (!AttributeSetValue.IsEmpty())
    {
        return FText::FormatNamed(LOCTEXT("CompareAttributeWithSet", "{EmptyOrNot}{AbilitySystemObject}.{AttributeSet}.{Attribute} {Op} {Right}"),
            TEXT("EmptyOrNot"), InvertText,
            TEXT("AbilitySystemObject"), AbilitySystemObjectValue,
            TEXT("AttributeSet"), AttributeSetValue,
            TEXT("Attribute"), AttributeValue,
            TEXT("Op"), OperatorText,
            TEXT("Right"), RightValue);
    }
    else
    {
        return FText::FormatNamed(LOCTEXT("CompareAttribute", "{EmptyOrNot}{AbilitySystemObject}.{Attribute} {Op} {Right}"),
            TEXT("EmptyOrNot"), InvertText,
            TEXT("AbilitySystemObject"), AbilitySystemObjectValue,
            TEXT("Attribute"), AttributeValue,
            TEXT("Op"), OperatorText,
            TEXT("Right"), RightValue);
    }

}
#endif

#undef LOCTEXT_NAMESPACE