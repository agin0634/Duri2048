#include "Tile.h"
#include "Math/UnrealMathVectorCommon.h"

ATile::ATile()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set Root Static Mesh
	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMesh"));
	RootComponent = RootMesh;

	// Set Tile Text Render
	TileText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TileText"));
	TileText->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	TileText->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	TileText->VerticalAlignment = EVerticalTextAligment::EVRTA_TextCenter;

}

void ATile::BeginPlay()
{
	Super::BeginPlay();

	// Set Dynamic Material Instance
	TileMaterialInstance = RootMesh->CreateDynamicMaterialInstance(0);
	
	ApplyStyle();
}

void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Generate Pop-up ,Tile Style and Visibility
	if (Number == 0)
	{
	    RootMesh->SetVisibility(false, true);
		RootMesh->SetRelativeScale3D(TileMinScale);
		TileCurrentScale = TileMinScale;
		IsNewGenerate = false;
		ApplyStyle();
	}
	else
	{
		RootMesh->SetVisibility(true, true);
		if (IsNewGenerate) 
		{
			if (TileCurrentScale == TileMaxScale)
			{
				IsNewGenerate = false;
				TileCurrentScale = TileMinScale;
			}
			else
			{
				RootMesh->SetRelativeScale3D(FMath::Lerp(TileCurrentScale, TileMaxScale, 0.15f));
				TileCurrentScale = FVector(RootMesh->GetRelativeTransform().GetScale3D());
			}
		}
		else
		{
			RootMesh->SetRelativeScale3D(TileMaxScale);
		}
		ApplyStyle();
	}
}

void ATile::ApplyStyle()
{
	switch (Number)
	{
	case 2:
		TileText->Text = FText::FromString(FString::FromInt(Number));
		if (TileMaterialInstance != nullptr) 
		{
			TileMaterialInstance->SetVectorParameterValue(FName("TileColor"), FLinearColor(0.184,0.27,0.184));
		}
		TileText->TextRenderColor = FColor(FLinearColor(0.0156, 0.0141, 0.0104).ToFColor(false));
		TileText->WorldSize = 80;
		break;

	case 4:
		TileText->Text = FText::FromString("4"); 
		if (TileMaterialInstance != nullptr)
		{
			TileMaterialInstance->SetVectorParameterValue(FName("TileColor"), FLinearColor(0.158,0.688,0.077));
		}
		TileText->TextRenderColor = FColor(FLinearColor(0.0156,0.0141,0.0104).ToFColor(false));
		TileText->WorldSize = 80;
		break;

	case 8:
		TileText->Text = FText::FromString("8");
		if (TileMaterialInstance != nullptr)
		{
			TileMaterialInstance->SetVectorParameterValue(FName("TileColor"), FLinearColor(0.0257,0.0908,0.0162));
		}
		TileText->TextRenderColor = FColor(FLinearColor(0.761, 0.723, 0.631).ToFColor(false));
		TileText->WorldSize = 80;
		break;

	case 16:
		TileText->Text = FText::FromString("16");
		if (TileMaterialInstance != nullptr)
		{
			TileMaterialInstance->SetVectorParameterValue(FName("TileColor"), FLinearColor(0.144,0.231,0.309));
		}
		TileText->TextRenderColor = FColor(FLinearColor(0.0156, 0.0141, 0.0104).ToFColor(false));
		TileText->WorldSize = 70;
		break;

	case 32:
		TileText->Text = FText::FromString("32");
		if (TileMaterialInstance != nullptr)
		{
			TileMaterialInstance->SetVectorParameterValue(FName("TileColor"), FLinearColor(0.0627,0.342,0.708));
		}
		TileText->TextRenderColor = FColor(FLinearColor(0.0156, 0.0141, 0.0104).ToFColor(false));
		TileText->WorldSize = 70;
		break;

	case 64:
		TileText->Text = FText::FromString("64");
		if (TileMaterialInstance != nullptr)
		{
			TileMaterialInstance->SetVectorParameterValue(FName("TileColor"), FLinearColor(0.00369,0.0328,0.135));
		}
		TileText->TextRenderColor = FColor(FLinearColor(0.761, 0.723, 0.631).ToFColor(false));
		TileText->WorldSize = 70;
		break;

	case 128:
		TileText->Text = FText::FromString("128");
		if (TileMaterialInstance != nullptr)
		{
			TileMaterialInstance->SetVectorParameterValue(FName("TileColor"), FLinearColor(0.392,0.136,0.0595));
		}
		TileText->TextRenderColor = FColor(FLinearColor(0.0156, 0.0141, 0.0104).ToFColor(false));
		TileText->WorldSize = 60;
		break;

	case 256:
		TileText->Text = FText::FromString("256");
		if (TileMaterialInstance != nullptr)
		{
			TileMaterialInstance->SetVectorParameterValue(FName("TileColor"), FLinearColor(0.698,0.0941,0.0872));
		}
		TileText->TextRenderColor = FColor(FLinearColor(0.0156, 0.0141, 0.0104).ToFColor(false));
		TileText->WorldSize = 60;
		break;

	case 512:
		TileText->Text = FText::FromString("512");
		if (TileMaterialInstance != nullptr)
		{
			TileMaterialInstance->SetVectorParameterValue(FName("TileColor"), FLinearColor(0.141,0.0217,0.0139));
		}
		TileText->TextRenderColor = FColor(FLinearColor(0.0156, 0.0141, 0.0104).ToFColor(false));
		TileText->TextRenderColor = FColor(FLinearColor(0.761, 0.723, 0.631).ToFColor(false));
		TileText->WorldSize = 60;
		break;

	case 1024:
		TileText->Text = FText::FromString("1024");
		if (TileMaterialInstance != nullptr)
		{
			TileMaterialInstance->SetVectorParameterValue(FName("TileColor"), FLinearColor(0.939,0.753,0.231));
		}
		TileText->TextRenderColor = FColor(FLinearColor(0.0156, 0.0141, 0.0104).ToFColor(false));
		TileText->WorldSize = 50;
		break;

	case 2048:
		TileText->Text = FText::FromString("2048");
		if (TileMaterialInstance != nullptr)
		{
			TileMaterialInstance->SetVectorParameterValue(FName("TileColor"), FLinearColor(0.939, 0.624, 0.0232));
		}
		TileText->TextRenderColor = FColor(FLinearColor(0.0156, 0.0141, 0.0104).ToFColor(false));
		TileText->WorldSize = 50;
		break;

	default:
		break;
	}
	
}

