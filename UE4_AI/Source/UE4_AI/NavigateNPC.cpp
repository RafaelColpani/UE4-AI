#include "NavigateNPC.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

/**
 * @brief DEFINE_STAT 
 *
 * @param STAT_AINavigateNPC ///
*/
DEFINE_STAT(STAT_AINavigateNPC);

ANavigateNPC::ANavigateNPC()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANavigateNPC::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> TagsActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TagActorName, TagsActors);

	if (TagsActors.Num() > 0)
	{
		TagPointActor = TagsActors[0];
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Not found with the tag %s"), *TagActorName.ToString());
	}
}

void ANavigateNPC::Tick(float DeltaTime)
{
	SCOPE_CYCLE_COUNTER(STAT_AINavigateNPC);

	Super::Tick(DeltaTime);

	if (TagPointActor)
	{
		MoveActor();
		DebugArea();

		if (FVector::Dist(GetActorLocation(), TagPointActor->GetActorLocation()) < DistanceThreshold)
		{
			TArray<AActor*> TagsActors;
			UGameplayStatics::GetAllActorsWithTag(GetWorld(), TagActorName, TagsActors);

			if (TagsActors.Num() > 1)
			{
				int32 Index = TagsActors.Find(TagPointActor);
				TagPointActor = TagsActors[(Index + 1) % TagsActors.Num()];
			}
		}
	}
}

void ANavigateNPC::MoveActor()
{
	FVector CurrentActorPos = GetActorLocation();

	FVector TargetPos = TagPointActor->GetActorLocation();

	FVector TargetDirection = (TargetPos - CurrentActorPos).GetSafeNormal();

	FVector NewPos = CurrentActorPos + TargetDirection * ActorMoveSpeed;

	SetActorLocation(NewPos);
}

void ANavigateNPC::DebugArea()
{
    FVector CurrentActorPos = GetActorLocation();
    FVector TargetPos = TagPointActor->GetActorLocation();
    FVector TargetDirection = (TargetPos - CurrentActorPos).GetSafeNormal();
    float TargetDist = FVector::Dist(CurrentActorPos, TargetPos);
    FVector CubeDebugSize = FVector(100.0f, 100.0f, 1.0f);


    FColor CubeColor = FColor::Blue;
    float DistChangeColor = 900.0f; 
    if (TargetDist < DistChangeColor)
    {
        CubeColor = FColor::Red;
    }

	if (TargetDist < DistChangeColor - 500.0f)
    {
        CubeColor = FColor::Black;
    }

    int32 NumCubesDebug = FMath::CeilToInt(TargetDist / CubeDebugSize.X);

    for (int32 i = 0; i < NumCubesDebug; ++i)
    {
        FVector CubeDebugPos = CurrentActorPos + TargetDirection * (i * CubeDebugSize.X);
        DrawDebugBox(GetWorld(), CubeDebugPos, CubeDebugSize, FQuat::Identity, CubeColor, false, -1, 0, 2);
    }
}
