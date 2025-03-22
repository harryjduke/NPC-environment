// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "NPCAttributeSet.h"
#include "GameFramework/Character.h"
#include "NPCEnvironment_Demo/Inventory/InventoryComponent.h"
#include "NPCCharacter.generated.h"

/**
 * The character used by NPCs
 */
UCLASS()
class NPCENVIRONMENT_DEMO_API ANPCCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	/** Ability System Component. Required to use Gameplay Attributes and Gameplay Abilities. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Gameplay Ability System", meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystemComponent;

	/**
	 * Inventory Component. Provides an inventory to store items.
	 */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* InventoryComponent;


private:
	/**
	 * The attribute set for NPCs
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Ability System", meta = (AllowPrivateAccess = "true"))
	const UNPCAttributeSet*	AttributeSet;

public:
	// Sets default values for this character's properties
	ANPCCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }

	//~ Begin IAbilitySystemInterface
	/**
	 * Get this NPC's Ability System Component
	 * @return The Ability System Component
	 */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface
};
