#include "AppleActor.h"
#include "FinishLineActor.h"
#include "FoxMovement.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AAppleActor::AAppleActor() {
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Apple Trigger Box"));
	TriggerBox->SetCollisionProfileName(TEXT("OverlapAll"));
	TriggerBox->SetGenerateOverlapEvents(true);
	RootComponent = TriggerBox;
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AAppleActor::OnAppleBeginOverlap);

	TriggerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Apple Mesh"));
	TriggerMesh->SetupAttachment(TriggerBox);
}

void AAppleActor::BeginPlay() {
	Super::BeginPlay();

	FinishLine = (AFinishLineActor*)UGameplayStatics::GetActorOfClass(GetWorld(), AFinishLineActor::StaticClass());
	Fox = (AFoxMovement*)UGameplayStatics::GetActorOfClass(GetWorld(), AFoxMovement::StaticClass());

	if(!IsDay) HideApple(true);
}

void AAppleActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AAppleActor::HideApple(bool Hide) {
	SetActorHiddenInGame(Hide);
	SetActorEnableCollision(!Hide);
	SetActorTickEnabled(!Hide);
}

void AAppleActor::OnAppleBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherCmp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if(*OtherActor->GetFName().ToString() == Fox->FoxName) {
		++FinishLine->AppleCount;
		Destroy();
	}
}