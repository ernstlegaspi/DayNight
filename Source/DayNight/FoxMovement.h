#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "FoxMovement.generated.h"

UCLASS()
class DAYNIGHT_API AFoxMovement : public ACharacter {
	GENERATED_BODY()

public:
	AFoxMovement();

	FString FoxName;

protected:
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CapsuleTrigger;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* FoxMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* RKeyAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	class UAnimMontage* RunMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fox")
	AActor* DayActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fox")
	AActor* PointLightActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fox")
	TArray<AActor*> DayApples;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fox")
	TArray<AActor*> NightApples;

	bool IsDay, IsChangeLightPressed, CanShake, IsPitchZero;
	float ChangeLightTime, CameraBoomPitch;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void Move(const FInputActionValue& Value);
	
	void ChangeCharacter(const FInputActionValue& Value);

	void ChangeScenery(AActor* Actor1, AActor* Actor2);

	void HideApple(AActor* Apple, bool Hide);

	virtual void BeginPlay() override;

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};