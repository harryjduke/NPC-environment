// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"

#include "NPCAttributeSet.generated.h"

/**
 * The core attributes for NPCs
 */
UCLASS()
class NPCENVIRONMENT_DEMO_API UNPCAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

protected:
	/**
	 * The thirst level of the NPC, the higher the value the thirstier the NPC is.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Thirst;

	/**
	 * The hunger level of the NPC, the higher the value the hungrier the NPC is.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Hunger;

public:
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UNPCAttributeSet, Thirst);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Thirst);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Thirst);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Thirst);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UNPCAttributeSet, Hunger);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Hunger);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Hunger);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Hunger);

};
