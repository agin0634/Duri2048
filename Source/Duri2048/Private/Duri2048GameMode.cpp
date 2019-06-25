#include "Duri2048GameMode.h"
#include "Public/Math/UnrealMathUtility.h"
#include "Public/TimerManager.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

ADuri2048GameMode::ADuri2048GameMode() 
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADuri2048GameMode::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATile::StaticClass(), Tiles);

	for (int i = 0; i < Tiles.Num(); i++) 
	{
		AllTiles.Add(Cast<ATile>(Tiles[i]));
	}
	
	GiveTilesXY(AllTiles);

	// First Generate
	GenerateTile();
	GenerateTile();
}


bool ADuri2048GameMode::CheckMove()
{
	int x = 0;
	int y = 0;

	//Check x
	for(int j = 0; j < 4; j++) 
	{
		for (int i = 0; i < 3; i++) 
		{
			if (AllTiles[x]->Number == AllTiles[x + 1]->Number) 
			{
				return true;
			}
			x++;
		}
		x++;
	}

	//Check y
	for (int j = 0; j < 4; j++) 
	{
		y = j;
		for (int i = 0; i < 3; i++)
		{
			if (AllTiles[y]->Number == AllTiles[y + 4]->Number)
			{
				return true;
			}
			y += 4;
		}
	}
	return false;
}

void ADuri2048GameMode::CheckWin()
{
	for (int i = 0; i < AllTiles.Num() - 1; i++) 
	{
		if (AllTiles[i]->Number == 2048) 
		{
			UE_LOG(LogTemp, Warning, TEXT("Win"));
			GameOverTitle = "You Win :->";
		}
	}
}

void ADuri2048GameMode::GenerateTile()
{
	// Check Win
	CheckWin();

	for (int i = 0; i < Tiles.Num(); i++)
	{
		if (AllTiles[i]->Number == 0) 
		{
			EmptyTiles.Add(AllTiles[i]);
		}
	}

	if (EmptyTiles.Num() > 0) 
	{
		int x = FMath::RandRange(0, EmptyTiles.Num() - 1);
		int y = FMath::RandRange(1, 10);

		if (y == 1) 
		{
			EmptyTiles[x]->Number = 4;
		}
		else 
		{
			EmptyTiles[x]->Number = 2;
		}

		EmptyTiles[x]->IsNewGenerate = true;
		EmptyTiles[x]->TileCurrentScale = FVector(0.01, 0.01, 0.1);

		// Check Lose
		if (EmptyTiles.Num() - 1 == 0) 
		{
			if (CheckMove() == false) 
			{
				UE_LOG(LogTemp, Warning, TEXT("Lose"));
				GameOverTitle = "You Lose :-(";
			}
		}		
		EmptyTiles.Empty();
	}
}

bool ADuri2048GameMode::MoveUpIndex(int32 Line, bool IsX)
{
	TArray<ATile*> CurrentTiles;
	bool bIsMove = false;
		
	// Reset Merge
	for (int i = 0; i < AllTiles.Num(); i++) 
	{
		AllTiles[i]->Mergethisturn = false;
	}

	// Check Move X or Y
	if (IsX) 
	{
		for (int i = 0; i < Tiles.Num(); i++) 
		{
			if (Line == AllTiles[i]->Tileindex_X) 
			{
				CurrentTiles.Add(AllTiles[i]);
			}
		}
	}
	else
	{
		for (int i = 0; i < Tiles.Num(); i++)
		{
			if (Line == AllTiles[i]->Tileindex_Y)
			{
				CurrentTiles.Add(AllTiles[i]);
			}
		}
	}

	for (int j = 0; j < CurrentTiles.Num() - 1; j++) 
	{
		for (int i = CurrentTiles.Num() - 1; i > 0; i--) 
		{
			//Move Tiles
			if (CurrentTiles[i]->Number == 0 && CurrentTiles[i-1]->Number != 0) 
			{
				CurrentTiles[i]->Number = CurrentTiles[i - 1]->Number;
				CurrentTiles[i - 1]->Number = 0; 
				bIsMove = true;
			}

			//Merge Tiles
			if (CurrentTiles[i]->Number != 0 && CurrentTiles[i]->Number == CurrentTiles[i - 1]->Number &&
				CurrentTiles[i]->Mergethisturn == false  && CurrentTiles[i - 1]->Mergethisturn == false)
			{
				CurrentTiles[i]->Number *= 2;
				CurrentTiles[i - 1]->Number = 0;
				CurrentTiles[i]->Mergethisturn = true;

				AddScore(CurrentTiles[i]->Number);
				
				bIsMove = true;
			}
		}
	}
	return bIsMove;
}

bool ADuri2048GameMode::MoveDownIndex(int32 Line, bool IsX)
{
	TArray<ATile*> CurrentTiles;
	bool bIsMove = false;

	// Reset Merge
	for (int i = 0; i < AllTiles.Num(); i++)
	{
		AllTiles[i]->Mergethisturn = false;
	}

	// Check Move X or Y
	if (IsX)
	{
		for (int i = 0; i < Tiles.Num(); i++)
		{
			if (Line == AllTiles[i]->Tileindex_X)
			{
				CurrentTiles.Add(AllTiles[i]);
			}
		}
	}
	else
	{
		for (int i = 0; i < Tiles.Num(); i++)
		{
			if (Line == AllTiles[i]->Tileindex_Y)
			{
				CurrentTiles.Add(AllTiles[i]);
			}
		}
	}

	for (int j = 0; j < CurrentTiles.Num() - 1; j++)
	{
		for (int i = 0; i < CurrentTiles.Num() - 1; i++)
		{
			//Move Tiles
			if (CurrentTiles[i]->Number == 0 && CurrentTiles[i + 1]->Number != 0)
			{
				CurrentTiles[i]->Number = CurrentTiles[i + 1]->Number;
				CurrentTiles[i + 1]->Number = 0;
				bIsMove = true;
			}

			//Merge Tiles
			if (CurrentTiles[i]->Number != 0 && CurrentTiles[i]->Number == CurrentTiles[i + 1]->Number &&
				CurrentTiles[i]->Mergethisturn == false && CurrentTiles[i + 1]->Mergethisturn == false)
			{
				CurrentTiles[i]->Number *= 2;
				CurrentTiles[i + 1]->Number = 0;
				CurrentTiles[i]->Mergethisturn = true;

				AddScore(CurrentTiles[i]->Number);

				bIsMove = true;
			}
		}
	}
	return bIsMove;
}

void ADuri2048GameMode::GiveTilesXY(TArray<ATile*> Tiles)
{
	int32 X = 0;
	int32 Y = 0;

	for (int i = 0; i < Tiles.Num(); i++) 
	{
		if ((i + 1) % 4 == 0) 
		{
			Tiles[i]->Tileindex_X = X;
			Tiles[i]->Tileindex_Y = Y;
			Y++;
			X = 0;
		}
		else
		{
			Tiles[i]->Tileindex_X = X;
			Tiles[i]->Tileindex_Y = Y;
			X++;
		}
	}
}

void ADuri2048GameMode::AddScore(int score)
{
	Score += score;
	UE_LOG(LogTemp, Warning, TEXT("%i"), Score);
}






