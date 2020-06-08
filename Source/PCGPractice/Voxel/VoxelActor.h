// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "VoxelActor.generated.h"

struct FMeshSection
{
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;
	TArray<FColor> VertexColors;
	TArray<FProcMeshTangent> Tangents;

	int32 elementID = 0;
};

UCLASS()
class PCGPRACTICE_API AVoxelActor : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray <UMaterialInterface*> Materials;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
		int32 randomSeed = 123456;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
		int32 voxelSize = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
		int32 chunkLineElements = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
		int32 chunkXIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
		int32 chunkYIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
		float xMUlt = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
		float yMUlt = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
		float zMUlt = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
		float frequency = 1;

	UPROPERTY()
		int32 chunkTotalElements;

	UPROPERTY()
		int32 chunkZElements;

	UPROPERTY()
		int32 chunkLineElementsP2;

	UPROPERTY()
		int32 voxelSizeHalf;

	UPROPERTY()
		TArray<int32> chunkFields;

	UPROPERTY()
		UProceduralMeshComponent* ProceduralMeshComponent;

	UFUNCTION(BlueprintNativeEvent)
		TArray<int32> GetNoise();
	virtual TArray<int32> GetNoise_Implementation();

public:	
	// Sets default values for this actor's properties
	AVoxelActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	void GenerateChunk();

	void UpdateMesh();
	
};
