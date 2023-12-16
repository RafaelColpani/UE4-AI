#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem/Public/NavigationSystem.h"
#include "NavigateNPC.generated.h"

DECLARE_CYCLE_STAT_EXTERN(TEXT("AI_Navigate_NPC"), STAT_AINavigateNPC, STATGROUP_AI, );

UCLASS()
class UE4_AI_API ANavigateNPC : public AActor
{
	GENERATED_BODY()
	
public:	
	ANavigateNPC();
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	#pragma region ChangeVariables

	UPROPERTY(EditAnywhere, Category = "Tag Actor Name")
	FName TagActorName = "Point"; 

	UPROPERTY(EditAnywhere, Category = "Basic Config")
	float ActorMoveSpeed = 2.5f;

	UPROPERTY(EditAnywhere, Category = "Basic Config")
	float DistanceThreshold = 2.5f;

	#pragma endregion

	AActor* TagPointActor;
	
	#pragma region Functions

	void MoveActor();
	void DebugArea();

	#pragma endregion
};
