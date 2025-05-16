// Copyright (c) 2025 Harry Duke <harryjduke@gmail.com>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Inventory/InventoryComponent.h"
#include "NPC/NPCCharacter.h"
#include "Structure.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogStructure, Log, All);

UCLASS()
class NPCENVIRONMENT_DEMO_API AStructure : public AActor
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess=true))
	TSubclassOf<AActor> CompletedActorClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess=true))
	TArray<FItemData> BuildRequirements;

public:
	// Sets default values for this actor's properties
	AStructure();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	bool BuildStructure(ANPCCharacter* NPCCharacter);
};
