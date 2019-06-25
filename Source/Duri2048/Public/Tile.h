#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class DURI2048_API ATile : public AActor
{
	GENERATED_BODY()
	
public:
	ATile();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tile")
	UStaticMeshComponent* RootMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tile")
	UTextRenderComponent* TileText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Tileindex_X;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Tileindex_Y;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Number = 0;

	bool Mergethisturn = false;
	bool IsNewGenerate = false;
	FVector TileCurrentScale;

	void ApplyStyle();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	FText TileNumber;
	FColor TileColor;
	UMaterialInstanceDynamic* TileMaterialInstance;
	FVector TileMaxScale = FVector(2.7, 2.7, 1.5);
	FVector TileMinScale = FVector(0.01, 0.01, 0.1);
};
