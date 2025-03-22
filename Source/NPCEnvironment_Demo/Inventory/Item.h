// Copyright (c) 2025 Harry Duke <harryjduke@gmail.com>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Item.generated.h"

/**
 * Base class for 'item' actors
 */
UCLASS()
class NPCENVIRONMENT_DEMO_API AItem : public AActor
{
	GENERATED_BODY()


public:
	// Sets default values for this actor's properties
	AItem();

private:
	// Data about this class of item used by the inventory system to identify and reconstruct the item
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
