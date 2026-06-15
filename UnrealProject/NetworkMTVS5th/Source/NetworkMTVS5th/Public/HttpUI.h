// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HttpPlayer.h"
#include "Blueprint/UserWidget.h"
#include "HttpUI.generated.h"

/**
 * 
 */
UCLASS()
class NETWORKMTVS5TH_API UHttpUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UEditableText> EditText_serviceKey;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UEditableText> EditText_pageNo;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UEditableText> EditText_numOfRows;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UTextBlock> TextLog;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UButton> ButtonSend_Get;

	UPROPERTY()
	TObjectPtr<class AHttpPlayer> HttpPlayer;
	
	UFUNCTION()
	void OnButtonSend_Get();
	
	void UpdateLog(const FString& LogText);
	
};
