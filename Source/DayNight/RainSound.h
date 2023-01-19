#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RainSound.generated.h"

UCLASS()
class DAYNIGHT_API ARainSound : public AActor {
	GENERATED_BODY()
	
public:	
	ARainSound();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Raid")
	class USoundBase* RainSound;

	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
