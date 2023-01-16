#include "PointLightActor.h"

APointLightActor::APointLightActor() {
	PrimaryActorTick.bCanEverTick = true;
}

void APointLightActor::BeginPlay() {
	Super::BeginPlay();
}

void APointLightActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	SetActorLocation(PlayerPos->GetActorLocation() + Offset);
}