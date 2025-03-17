// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NPC_AIController.generated.h"

UCLASS()
class NPCENVIRONMENT_DEMO_API ANPC_AIController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANPC_AIController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
