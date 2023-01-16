#include "PlatformManager.h"
#include "FoxMovement.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

APlatformManager::APlatformManager() {
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	TriggerBox->SetCollisionProfileName(TEXT("OverlapAll"));
	TriggerBox->SetGenerateOverlapEvents(true);
	RootComponent = TriggerBox;
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APlatformManager::OnBeginOverlap);

	TriggerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Trigger Mesh"));
	TriggerMesh->SetupAttachment(TriggerBox);

	PlatformDestroyTime = 0.f;
}

void APlatformManager::BeginPlay() {
	Super::BeginPlay();

	Fox = (AFoxMovement*)UGameplayStatics::GetActorOfClass(GetWorld(), AFoxMovement::StaticClass());
}

void APlatformManager::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if(PlatformDestroyTime > 0) {
		PlatformDestroyTime -= DeltaTime;

		if(PlatformDestroyTime <= 0.f) Destroy();
	}
}

void APlatformManager::OnBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if(*OtherActor->GetFName().ToString() == Fox->FoxName && CanBeDestroyed) PlatformDestroyTime = 2.f;
}