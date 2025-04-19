#pragma once

#include "I_Collectable.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class U_Collectable : public UInterface
{
    GENERATED_BODY()
};

class PR_ASSESMENT_API I_Collectable
{
    GENERATED_BODY()

public:
    virtual void OnCollected() = 0;
};