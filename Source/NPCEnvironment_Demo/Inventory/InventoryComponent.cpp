// Copyright (c) 2025 Harry Duke <harryjduke@gmail.com>

#include "InventoryComponent.h"

DEFINE_LOG_CATEGORY(LogInventory);

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FItemData* UInventoryComponent::GetItemDataByClass(const TSubclassOf<AItem>& ItemClass)
{
	return Items.FindByPredicate([&ItemClass](const FItemData& ItemData)
	{
		return ItemData.ItemClass == ItemClass;
	});
}

int32 UInventoryComponent::GetNumberOfItemsByClass(const TSubclassOf<AItem>& ItemClass)
{
	if (const FItemData* ItemData = GetItemDataByClass(ItemClass); ItemData != nullptr)
	{
		return ItemData->Quantity;
	}

	return 0;
}

void UInventoryComponent::AddItemToInventory(const AItem* Item)
{
	UClass* ItemClass = Item->GetClass();
	if (FItemData* ItemData = GetItemDataByClass(ItemClass); ItemData != nullptr)
	{
		UE_VLOG_HISTOGRAM(GetOwner(), LogInventory, VeryVerbose, FName("InventoryItemQuantityGraph"),
     		                  ItemClass->GetFName(),
     		                  FVector2D((GetWorld() ? GetWorld()->GetTimeSeconds() : 0.f), ItemData->Quantity));
		ItemData->Quantity++;
		UE_VLOG_HISTOGRAM(GetOwner(), LogInventory, VeryVerbose, FName("InventoryItemQuantityGraph"),
		                  ItemClass->GetFName(),
		                  FVector2D((GetWorld() ? GetWorld()->GetTimeSeconds() : 0.f), ItemData->Quantity));
	}
	else
	{
		UE_VLOG_HISTOGRAM(GetOwner(), LogInventory, VeryVerbose, FName("InventoryItemQuantityGraph"),
	                  ItemClass->GetFName(),
	                  FVector2D((GetWorld() ? GetWorld()->GetTimeSeconds() : 0.f), 0));
		Items.Push(FItemData(TSubclassOf<AItem>(ItemClass)));
		UE_VLOG_HISTOGRAM(GetOwner(), LogInventory, VeryVerbose, FName("InventoryItemQuantityGraph"),
		                  ItemClass->GetFName(),
		                  FVector2D((GetWorld() ? GetWorld()->GetTimeSeconds() : 0.f), 1));
	}
}

int32 UInventoryComponent::RemoveItemsFromInventoryByClass(
	const TSubclassOf<AItem> ItemClass,
	const int32 RemoveAmount,
	const bool bRemovePartialAmount)
{
	if (RemoveAmount <= 0)
	{
		UE_LOG(LogInventory, Warning, TEXT("Attempted to remove zero or negative number of items"));
		return 0;
	}
	FItemData* ItemData = GetItemDataByClass(ItemClass);
	if (!ItemData)
	{
		UE_LOG(LogInventory, Warning, TEXT("Item class not found in inventory"));
		return 0;
	}

	const int32 ActualRemoveAmount = FMath::Min(RemoveAmount, ItemData->Quantity);

	if (ActualRemoveAmount < RemoveAmount && !bRemovePartialAmount)
	{
		UE_LOG(LogInventory, Warning, TEXT("Insufficient items and partial removal not allowed"));
		return 0;
	}

	UE_VLOG_HISTOGRAM(GetOwner(), LogInventory, VeryVerbose, FName("InventoryItemQuantityGraph"),
	                  ItemClass->GetFName(),
	                  FVector2D((GetWorld() ? GetWorld()->GetTimeSeconds() : 0.f), ItemData->Quantity));

	ItemData->Quantity -= ActualRemoveAmount;
	if (ItemData->Quantity <= 0)
	{
		Items.RemoveSingleSwap(*ItemData);
	}

	UE_VLOG_HISTOGRAM(GetOwner(), LogInventory, VeryVerbose, FName("InventoryItemQuantityGraph"),
	                  ItemClass->GetFName(),
	                  FVector2D((GetWorld() ? GetWorld()->GetTimeSeconds() : 0.f), ItemData->Quantity));

	return ActualRemoveAmount;
}
