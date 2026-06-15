// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkMTVS5th/Public/HttpUI.h"

#include "HttpPlayer.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UHttpUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	HttpPlayer = Cast<AHttpPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());

	ButtonSend_Get->OnClicked.AddDynamic(this, &UHttpUI::OnButtonSend_Get);
	ButtonSend_Post->OnClicked.AddDynamic(this, &UHttpUI::OnButtonSend_Post);
	ButtonWebImage->OnClicked.AddDynamic(this, &UHttpUI::OnButtonWebImage);
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

void UHttpUI::OnButtonSend_Post()
{
	FString url = TEXT("http://127.0.0.1:8000/echo");
	
	TMap<FString, FString> map;
	map.Add(TEXT("key"), TEXT("value"));
	FString content = MapToJson(map);
	
	HttpPlayer->ReqPost(url, content);
}

void UHttpUI::OnButtonWebImage()
{
	// 웹에서 이미지를 다운로드 받고  그 결과를 ImageWeb에 표현하고싶다.
	FString url = TEXT("https://cdn.imweb.me/upload/S20220518fbea59f8e9828/77d99edcb5dbf.jpg");
	HttpPlayer->ReqWebImage(url);
}

void UHttpUI::UpdateWebImage(UTexture2D* txt)
{
	ImageWeb->SetBrushFromTexture(txt, false);
}

void UHttpUI::UpdateLog(const FString& LogText)
{
	TextLog->SetText(FText::FromString(LogText));
}

FString UHttpUI::MapToJson(const TMap<FString, FString>& map)
{
	TSharedPtr<FJsonObject> json = MakeShared<FJsonObject>();
	
	for (auto& pair : map)
	{
		json->SetStringField(pair.Key, pair.Value);
	}
	
	FString jsonData;
	
	auto writer = TJsonWriterFactory<TCHAR>::Create(&jsonData);
	FJsonSerializer::Serialize(json.ToSharedRef(), writer);
	
	return jsonData;
}


