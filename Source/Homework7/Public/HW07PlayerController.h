#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HW07PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class HOMEWORK7_API AHW07PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AHW07PlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;

	virtual void BeginPlay() override;
};
