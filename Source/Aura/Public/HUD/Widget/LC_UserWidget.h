// Copyright Curyło Łukasz

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LC_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API ULC_UserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
	
};
