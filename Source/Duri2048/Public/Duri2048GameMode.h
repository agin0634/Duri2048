#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Tile.h"
#include "Duri2048GameMode.generated.h"

UCLASS()
class DURI2048_API ADuri2048GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
		ADuri2048GameMode();

		UFUNCTION(BlueprintCallable, Category = "Tiles")
		void GenerateTile();
		UFUNCTION(BlueprintCallable, Category = "Tiles")
		bool MoveUpIndex(int32 Line, bool IsX);
		UFUNCTION(BlueprintCallable, Category = "Tiles")
		bool MoveDownIndex(int32 Line, bool IsX);

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Score = 0;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString GameOverTitle;

		TArray<AActor*> Tiles;
		TArray<ATile*> AllTiles;
		TArray<ATile*> EmptyTiles;
		
protected:
	virtual void BeginPlay() override;

private:
	void GiveTilesXY(TArray<ATile*> Tiles);
	void AddScore(int score);
	void CheckWin();
	bool CheckMove();
	
};
