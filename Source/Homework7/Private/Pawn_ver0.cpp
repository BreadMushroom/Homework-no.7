#include "Pawn_ver0.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "HW07PlayerController.h"

APawn_ver0::APawn_ver0()
{
	PrimaryActorTick.bCanEverTick = false;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(CapsuleComp);

	SkeletalComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal"));
	SkeletalComp->SetupAttachment(CapsuleComp);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(CapsuleComp);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	MoveSpeed = 600.0f;
	RotationSpeed = 90.0f;
}


void APawn_ver0::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AHW07PlayerController* PlayerController = Cast<AHW07PlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&APawn_ver0::Move
				);
			}
			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&APawn_ver0::Look
				);
			}
		}
	}
}

//1.Move 함수 선언 
//2.FVector2D 키보드 입력값 받아오기
//3.DeltaTime 불러오기
//4.전진, 좌우 움직임 구현
//5.앞뒤/좌우 값을 합쳐서 하나의 이동 벡터 만들기
//6.실제 위치에 적용

void APawn_ver0::Move(const FInputActionValue& value)
{
	const FVector2D MoveInput = value.Get<FVector2D>();
	float DeltaTime = GetWorld()->GetDeltaSeconds();

	if (!MoveInput.IsNearlyZero())
	{
		float ForwardStep = MoveInput.X * MoveSpeed * DeltaTime;
		float RightStep = MoveInput.Y * MoveSpeed * DeltaTime;

		FVector DeltaLocation(ForwardStep, RightStep, 0.0f);
		AddActorLocalOffset(DeltaLocation, true);
	}
}

void APawn_ver0::Look(const FInputActionValue& value)
{
	const FVector2D LookInput = value.Get<FVector2D>();

	if (!LookInput.IsNearlyZero())
	{
		float DeltaTime = GetWorld()->GetDeltaSeconds();

		FRotator ActorRotation = FRotator::ZeroRotator;
		ActorRotation.Yaw = LookInput.X * RotationSpeed * DeltaTime;
		AddActorLocalRotation(ActorRotation);
		
		if (SpringArmComp)
		{
			FRotator NewArmRotation = SpringArmComp->GetRelativeRotation();

			float PitchAmount = LookInput.Y * RotationSpeed * DeltaTime;
			NewArmRotation.Pitch = FMath::Clamp(NewArmRotation.Pitch + PitchAmount, -80.0f, 80.0f);

			SpringArmComp->SetRelativeRotation(NewArmRotation);
		}
	}
}



