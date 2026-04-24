#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Pawn_ver0.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;

UCLASS()
class HOMEWORK7_API APawn_ver0 : public APawn
{
	GENERATED_BODY()

public:
	
	APawn_ver0();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="CharacterComp")
	UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CharacterComp")
	USkeletalMeshComponent* SkeletalComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CharacterComp")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CharacterComp")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MoveSpeed")
	float MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MouseSpeed")
	float RotationSpeed;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);
};
