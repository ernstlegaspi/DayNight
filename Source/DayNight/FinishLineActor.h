#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FinishLineActor.generated.h"

UCLASS()
class DAYNIGHT_API AFinishLineActor : public AActor {
	GENERATED_BODY()
	
public:	
	AFinishLineActor();

	UPROPERTY(EditAnywhere)
	class UBoxComponent* TriggerBox;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* TriggerMesh;

	UPROPERTY(EditAnywhere)
	float AppleCountInStage;

	UFUNCTION()
	void OnFinishBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	short int AppleCount;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};