#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformManager.generated.h"

UCLASS()
class DAYNIGHT_API APlatformManager : public AActor {
	GENERATED_BODY()
	
public:	
	APlatformManager();

	UPROPERTY(EditAnywhere)
	class UBoxComponent* TriggerBox;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* TriggerMesh;

	UPROPERTY(EditAnywhere)
	bool CanBeDestroyed;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;

private:
	float PlatformDestroyTime;

public:	
	virtual void Tick(float DeltaTime) override;

};