#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PointLightActor.generated.h"

UCLASS()
class DAYNIGHT_API APointLightActor : public AActor {
	GENERATED_BODY()
	
public:	
	APointLightActor();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "APoint Light")
	AActor* PlayerPos;

	UPROPERTY(EditAnywhere, Category = "APoint Light")
	FVector Offset;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
