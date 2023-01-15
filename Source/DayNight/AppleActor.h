#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AppleActor.generated.h"

UCLASS()
class DAYNIGHT_API AAppleActor : public AActor {
	GENERATED_BODY()
	
public:	
	AAppleActor();

protected:
	UPROPERTY(EditAnywhere)
	class UBoxComponent* TriggerBox;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* TriggerMesh;

	class AFinishLineActor* FinishLine;

	UFUNCTION()
	void OnAppleBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherCmp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};
