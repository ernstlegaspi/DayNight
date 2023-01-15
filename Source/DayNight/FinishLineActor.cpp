#include "FinishLineActor.h"
#include "Components/BoxComponent.h"

AFinishLineActor::AFinishLineActor() {
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Finish Line Trigger Box"));
	TriggerBox->SetCollisionProfileName(TEXT("OverlapAll"));
	TriggerBox->SetGenerateOverlapEvents(true);
	RootComponent = TriggerBox;
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFinishLineActor::OnFinishBeginOverlap);

	TriggerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Finish Line Mesh"));
	TriggerMesh->SetupAttachment(TriggerBox);

	AppleCount = 0;
	AppleCountInStage = 6;
}

void AFinishLineActor::BeginPlay() {
	Super::BeginPlay();
}

void AFinishLineActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AFinishLineActor::OnFinishBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if(AppleCount == AppleCountInStage) UE_LOG(LogTemp, Warning, TEXT("Stage Finished."));
}