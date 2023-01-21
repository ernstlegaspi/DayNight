#include "FoxMovement.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

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
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bUsePawnControlRotation = true;

	IsDay = true;
	IsChangeLightPressed = false;
	IsPitchZero = false;
	CanShake = false;
	ChangeLightTime = 0.f;
	CameraBoomPitch = -40.f;

	FoxName = *GetFName().ToString();
}

void AFoxMovement::BeginPlay() {
	Super::BeginPlay();

	if(APlayerController* FoxController = Cast<APlayerController>(GetController())) {
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(FoxController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(FoxMappingContext, 1);
		}
	}

	if(UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance()) {
		if(RunMontage) {
			//AnimInstance->Montage_Play(RunMontage);
			//AnimInstance->Montage_JumpToSection("Run");
			ACharacter::PlayAnimMontage(RunMontage);
		}
	}
}

void AFoxMovement::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if(CanShake && GetCharacterMovement()->IsMovingOnGround()) {
		if(CameraBoomPitch >= -40.f && !IsPitchZero) {
			CameraBoomPitch += DeltaTime * 800;

			if(CameraBoomPitch >= -30.f) {
				IsPitchZero = true;
				CameraBoomPitch = -30.f;
			}
		}
		else {
			if(CameraBoomPitch <= -30.f && IsPitchZero) {
				CameraBoomPitch -= DeltaTime * 800;

				if(CameraBoomPitch <= -40.f) {
					IsPitchZero = false;
					CameraBoomPitch = -40.f;
					CanShake = false;
				}
			}
		}

		CameraBoom->SetRelativeRotation(FRotator(CameraBoomPitch, 0, 0));
	}

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
	if(OtherActor != this && OtherActor->GetFName().ToString().Contains("Platform", ESearchCase::IgnoreCase, ESearchDir::FromStart)) CanShake = true;
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