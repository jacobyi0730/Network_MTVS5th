// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkMTVS5th/Public/HttpUI.h"

#include "HttpPlayer.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/TextBlock.h"

void UHttpUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	HttpPlayer = Cast<AHttpPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());

	ButtonSend_Get->OnClicked.AddDynamic(this, &UHttpUI::OnButtonSend_Get);
}

void UHttpUI::OnButtonSend_Get()
{
	// 주인공에게 GET방식으로 서버에 요청해달라.
	FString endPoint = TEXT("https://apis.data.go.kr/4050000/libnewbk/getLibnewbk");
	
	FString fullUrl = FString::Printf(TEXT("%s?serviceKey=%s&pageNo=%s&numOfRows=%s"),
		*endPoint,
		*EditText_serviceKey->GetText().ToString(),
		*EditText_pageNo->GetText().ToString(),
		*EditText_numOfRows->GetText().ToString()
	);

	HttpPlayer->ReqGet(fullUrl);
}

void UHttpUI::UpdateLog(const FString& LogText)
{
	TextLog->SetText(FText::FromString(LogText));
}


