// Copyright (c) 2025 Harry Duke <harryjduke@gmail.com>

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogInventory, Log, All);

/**
 * The data held in the inventory that represents each item type.
 */
USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()

	/**
	 * The subclass of AItem that this item is associated with.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AItem> ItemClass;

	/**
	 * The number of this item held in the inventory.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity = 1;

	friend bool operator==(const FItemData& Lhs, const FItemData& RHS)
	{
		return Lhs.ItemClass == RHS.ItemClass;
	}
};

/**
 * An actor component that provides inventory functionality to the actor
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NPCENVIRONMENT_DEMO_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()


public:
	// Sets default values for this component's properties
	UInventoryComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * Returns the number of items associated with the given class stored in the inventory.
	 * @param ItemClass The subclass of AItem that the item is associated with.
	 * @return The number of items associated with the given class stored in the inventory.
	 */
	UFUNCTION(BlueprintCallable)
	int32 GetNumberOfItemsByClass(const TSubclassOf<AItem>& ItemClass);

	/**
	 * Adds an item to the inventory by taking the given AItem's class
	 * @param Item The item to add to the inventory
	 */
	UFUNCTION(BlueprintCallable)
	void AddItemToInventory(const AItem* Item);

	/**
	 * Remove the given number of items of the given class from the inventory.
	 * @param ItemClass The subclass of AItem associated with the items to remove.
	 * @param RemoveAmount The number of items to remove.
	 * @param bRemovePartialAmount If true, items will be removed from the inventory even if there are not enough to
	 * remove the full 'RemoveAmount'.
	 * @return The number of items successfully removed.
	 */
	UFUNCTION(BlueprintCallable)
	int32 RemoveItemsFromInventoryByClass(const TSubclassOf<AItem> ItemClass, int32 RemoveAmount = 1,
		bool bRemovePartialAmount = false);

protected:
	// Data about each item in the inventory used by the inventory system to identify and reconstruct the item
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,  meta = (AllowPrivateAccess = "true"));
	TArray<FItemData> Items;

	// Called when the game starts
	virtual void BeginPlay() override;

private:
	FItemData* GetItemDataByClass(const TSubclassOf<AItem>& ItemClass);
};
