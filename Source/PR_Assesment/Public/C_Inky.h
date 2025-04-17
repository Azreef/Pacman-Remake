
#pragma once

#include "CoreMinimal.h"
#include "C_Ghost.h"
#include "C_Inky.generated.h"

UCLASS()
class PR_ASSESMENT_API AC_Inky : public AC_Ghost
{
	GENERATED_BODY()
	
protected:
	FVector2D CalculateChaseTargetGrid();

	float _CurrentBlinkySearchTime = 0;
	class AC_Blinky* _BlinkyPointer;

public:
	virtual void Tick(float DeltaTime) override;

	AC_Inky();

	void GetBlinkyPointer();

	UPROPERTY(EditAnywhere, Category = "Inky", meta = (ToolTip = "How long before timeout in searching Blinky (in Seconds)"))
	float _BlinkySearchTimeoutTime = 60;

	

};
