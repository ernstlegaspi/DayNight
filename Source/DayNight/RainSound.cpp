#include "RainSound.h"
#include "Kismet/GameplayStatics.h"

ARainSound::ARainSound() {
	PrimaryActorTick.bCanEverTick = true;
}

void ARainSound::BeginPlay() {
	Super::BeginPlay();

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), RainSound, GetActorLocation(), FRotator::ZeroRotator);
}

void ARainSound::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}