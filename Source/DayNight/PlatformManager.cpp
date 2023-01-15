#include "PlatformManager.h"
#include "Components/BoxComponent.h"

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
}

void APlatformManager::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if(PlatformDestroyTime > 0) {
		PlatformDestroyTime -= DeltaTime;

		if(PlatformDestroyTime <= 0.f) Destroy();
	}
}

void APlatformManager::OnBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Warning, TEXT("OAKY"));
	if(CanBeDestroyed) PlatformDestroyTime = 2.f;
}