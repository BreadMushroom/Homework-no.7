#include "HW07GameMode.h"
#include "Pawn_ver0.h"
#include "HW07PlayerController.h"

AHW07GameMode::AHW07GameMode()
{
	DefaultPawnClass = APawn_ver0::StaticClass();
	PlayerControllerClass = AHW07PlayerController::StaticClass();
}
