// Fill out your copyright notice in the Description page of Project Settings.

#include "CellularAutomata.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"


// Sets default values
ACellularAutomata::ACellularAutomata()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Tilemap = CreateOptionalDefaultSubobject<UPaperTileMapComponent>(TEXT("TileMap"));

	static ConstructorHelpers::FObjectFinder<UPaperTileSet> Tile(TEXT("PaperTileSet'/Game/2DSideScroller/Textures/MyTile.MyTile'"));
	TileSet = Tile.Object;

	EmptyInfo.PackedTileIndex = 9;
	EmptyInfo.TileSet = TileSet;
}

void ACellularAutomata::OnConstruction(const FTransform& Transform) 
{

	Super::OnConstruction(Transform);

	FillInfo.PackedTileIndex = TileIndex;
	FillInfo.TileSet = TileSet;

	EmptyInfo.PackedTileIndex = EmptyIndex;
	EmptyInfo.TileSet = TileSet;

	//initialize 2d array of bool to check if the wall was occupied or not
	occupied = new bool*[TileHeight];
	for (int i = 0; i < TileHeight; i++)
		occupied[i] = new bool[TileWidth];

	Tilemap->CreateNewTileMap(TileWidth, TileHeight, 32, 32, 1.0f, true);
	RandomFill();
	MakeCavern();
	FillCavern();
}

void ACellularAutomata::FillCavern() 
{
	for (int y = 0; y < TileHeight; y++)
	{
		for (int x = 0; x < TileHeight; x++)
		{
			if (occupied[x][y])
				Tilemap->SetTile(x,y,0, FillInfo);
			else
				Tilemap->SetTile(x, y, 0, EmptyInfo);
		}
	}
}

void ACellularAutomata::RandomFill()
{
	if (IsValid(TileSet))
	{
		for (int y = 0; y < TileHeight; y++)
		{
			for (int x = 0; x < TileWidth; x++)
			{
				float chance = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				if (chance <= FillPercent)
					occupied[x][y] = true;
				else
					occupied[x][y] = false;
			}
		}
	}
}

int32 ACellularAutomata::CountTileNeighbors(int32 x, int32 y) 
{
	int32 WallCount = 0;
	for (int yi = y-1; yi <= y+1; yi++) 
	{
		for (int xi = x-1; xi <= x+1; xi++)
		{
			if (!(xi == x &&  yi == y))
			{
				if ((xi >= 0 && xi < TileWidth) && (yi >= 0 && yi < TileHeight))
					if (occupied[xi][yi])
						WallCount++;
			}
		}
	}
	return WallCount;
}

void ACellularAutomata::MakeCavern() 
{
	for (int i = 0; i < Iterations; i++) 
	{
		if (bUseMethodTwo) 
		{
			bool** filledtemp = new bool*[TileHeight];  //Method 1
			for (int i = 0; i < TileHeight; i++)
				filledtemp[i] = new bool[TileWidth];

			for (int y = 0; y < TileHeight; y++)
			{
				for (int x = 0; x < TileWidth; x++)
				{
					int count = CountTileNeighbors(x, y);

					if (occupied[x][y]) 
					{
						if (count < DeathLimit)
							filledtemp[x][y] = false;
						else
							filledtemp[x][y] = true;
					}
					else 
					{
						if (count > BirthLimit)
							filledtemp[x][y] = true;
						else
							filledtemp[x][y] = false;
					}
				}
			}
			occupied = filledtemp;
		}
		else 
		{
			for (int y = 0; y < TileHeight; y++)
			{
				for (int x = 0; x < TileWidth; x++)
				{
					int count = CountTileNeighbors(x, y);

					if (count >= BirthLimit && occupied[x][y])
						occupied[x][y] = true;
					if (count >= DeathLimit && !occupied[x][y])
						occupied[x][y] = true;
				}
			}
		}
	}
}


// Called when the game starts or when spawned
void ACellularAutomata::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACellularAutomata::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

