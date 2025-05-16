// Copyright (c) 2025 Harry Duke <harryjduke@gmail.com>


#include "Structure.h"

DEFINE_LOG_CATEGORY(LogStructure);

// Sets default values
AStructure::AStructure()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStructure::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AStructure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AStructure::BuildStructure(ANPCCharacter* NPCCharacter)
{
	if (!CompletedActorClass)
	{
		UE_LOG(LogStructure, Error, TEXT("Failed to build structure, no valid Completed Actor Class."));
		return false;
	}

	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		UE_LOG(LogStructure, Error, TEXT("Failed to build structure, no valid World."));
		return false;
	}

	if (!IsValid(NPCCharacter))
	{
		UE_LOG(LogStructure, Error, TEXT("Failed to build structure, no valid NPC Character."));
		return false;
	}

	UInventoryComponent* NPCInventoryComponent = NPCCharacter->GetInventoryComponent();
	if (!IsValid(NPCInventoryComponent))
	{
		UE_LOG(LogStructure, Error, TEXT("Failed to build structure, NPC Character has no valid Inventory Component."));
		return false;
	}
	for (auto [ItemClass, Quantity] : BuildRequirements)
	{
		if (NPCInventoryComponent->GetNumberOfItemsByClass(ItemClass) >= Quantity)
		{
			NPCInventoryComponent->RemoveItemsFromInventoryByClass(ItemClass, Quantity);
		}
		else
		{
			UE_LOG(LogStructure, Verbose, TEXT("Failed to build structure, Build Requirements not met."));
			return false;
		}
	}

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.Instigator = NPCCharacter;

	World->SpawnActor<AActor>(CompletedActorClass, GetActorTransform(), SpawnParameters);

	this->Destroy();

	return true;
}
