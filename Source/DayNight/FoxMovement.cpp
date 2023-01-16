#include "FoxMovement.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"

AFoxMovement::AFoxMovement() {
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CapsuleTrigger = CreateDefaultSubobject<UCapsuleComponent>(TEXT("FOX CAPSULE TRIGGER"));
	CapsuleTrigger->InitCapsuleSize(20.f, 50.f);
	CapsuleTrigger->SetCollisionProfileName(TEXT("Trigger"));
	CapsuleTrigger->SetupAttachment(RootComponent);
	CapsuleTrigger->OnComponentBeginOverlap.AddDynamic(this, &AFoxMovement::OnBeginOverlap);
	
	IsDay = true;
	IsChangeLightPressed = false;
	ChangeLightTime = 0.f;

	FoxName = *GetFName().ToString();
}

void AFoxMovement::BeginPlay() {
	Super::BeginPlay();

	if(APlayerController* FoxController = Cast<APlayerController>(GetController())) {
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(FoxController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(FoxMappingContext, 1);
		}
	}
}

void AFoxMovement::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if(IsChangeLightPressed) {
		ChangeLightTime -= DeltaTime;

		if(ChangeLightTime <= 0.f) IsChangeLightPressed = false;
	}
}

void AFoxMovement::Move(const FInputActionValue& Value) {
	const FVector DirVal = Value.Get<FVector>();

	if(Controller != nullptr) {
		FRotator FoxRotation = GetControlRotation();
		FRotator NewYawRotation(0, FoxRotation.Yaw, 0);

		FVector Forward = FRotationMatrix(NewYawRotation).GetUnitAxis(EAxis::X);
		FVector Right = FRotationMatrix(NewYawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Forward, DirVal.Y);
		AddMovementInput(Right, DirVal.X);
	}
}

void AFoxMovement::ChangeCharacter(const FInputActionValue& Value) {
	const bool Val = Value.Get<bool>();

	if(Controller != nullptr && Val && ChangeLightTime <= 0.f) {
		IsChangeLightPressed = true;
		ChangeLightTime = 1.f;
		ChangeScenery(IsDay ? DayActor : PointLightActor, IsDay ? PointLightActor : DayActor);

		for(AActor* DayApple : DayApples) HideApple(DayApple, IsDay);
		for(AActor* NightApple : NightApples) HideApple(NightApple, !IsDay);

		IsDay = !IsDay;
	}
}

void AFoxMovement::ChangeScenery(AActor* Actor1, AActor* Actor2) {
	Actor1->SetActorHiddenInGame(true);
	Actor1->SetActorTickEnabled(false);
	Actor2->SetActorHiddenInGame(false);
	Actor2->SetActorTickEnabled(true);
}

void AFoxMovement::HideApple(AActor* Apple, bool Hide) {
	Apple->SetActorHiddenInGame(Hide);
	Apple->SetActorEnableCollision(!Hide);
	Apple->SetActorTickEnabled(!Hide);
}

void AFoxMovement::OnBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

}

void AFoxMovement::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFoxMovement::Move);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(RKeyAction, ETriggerEvent::Triggered, this, &AFoxMovement::ChangeCharacter);
	}
}