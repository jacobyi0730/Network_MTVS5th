// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interfaces/IHttpRequest.h"
#include "HttpPlayer.generated.h"

UCLASS()
class NETWORKMTVS5TH_API AHttpPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AHttpPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UHttpUI> HttpUIFactory;
	
	UPROPERTY()
	TObjectPtr<UHttpUI> HttpUI;

	void ReqGet(const FString& url);
	void OnReqGetComplete(TSharedPtr<IHttpRequest> HttpRequest, TSharedPtr<IHttpResponse> HttpResponse, bool bProcessedSuccessfully);
	
	void ParseLibraryJson_Get(const FString& JsonString);

	void ReqPost(const FString& url, const FString& content);
	void OnReqPostComplete(TSharedPtr<IHttpRequest> HttpRequest, TSharedPtr<IHttpResponse> HttpResponse, bool bProcessedSuccessfully);
	
};
