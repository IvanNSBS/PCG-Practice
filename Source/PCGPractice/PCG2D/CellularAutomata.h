// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperTileMapComponent.h"
#include "PaperTileSet.h"
#include "CellularAutomata.generated.h"

UCLASS()
class PCGPRACTICE_API ACellularAutomata : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACellularAutomata();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Tile, meta = (AllowPrivateAccess = "true"))
		class UPaperTileMapComponent* Tilemap;

	virtual void OnConstruction(const FTransform& Transform) override;

	int32 CountTileNeighbors(int32 x, int32 y);

	FPaperTileInfo FillInfo;
	FPaperTileInfo EmptyInfo;

	bool** occupied;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile)
		UPaperTileSet* TileSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TileProperties)
		int32 TileIndex = 299;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TileProperties)
		int32 EmptyIndex = 9;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TileProperties)
		float FillPercent = 0.4f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TileProperties)
		int32 TileHeight = 64;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TileProperties)
		int32 TileWidth = 64;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TileProperties)
		int32 Iterations = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TileProperties)
		int32 BirthLimit = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TileProperties)
		int32 DeathLimit = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TileProperties)
		bool bUseMethodTwo = false;

	UFUNCTION(BlueprintCallable)
		void RandomFill();
	
	UFUNCTION(BlueprintCallable)
		void MakeCavern();

	void FillCavern();
};
