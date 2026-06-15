// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkMTVS5th/Public/HttpPlayer.h"

#include "HttpModule.h"
#include "HttpUI.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/IHttpResponse.h"
#include "ImageUtils.h"


// Sets default values
AHttpPlayer::AHttpPlayer()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHttpPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	HttpUI = Cast<UHttpUI>(CreateWidget(GetWorld(), HttpUIFactory));
	if (HttpUI)
	{
		HttpUI->AddToViewport();
	}
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}

// Called every frame
void AHttpPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AHttpPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void AHttpPlayer::ReqGet(const FString& url)
{
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedPtr<IHttpRequest> req = httpModule.CreateRequest();
	
	req->SetURL(url);
	req->SetVerb(TEXT("GET"));
	req->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	
	req->OnProcessRequestComplete().BindUObject(this, &AHttpPlayer::OnReqGetComplete);
	
	req->ProcessRequest();
}

void AHttpPlayer::OnReqGetComplete(TSharedPtr<IHttpRequest> HttpRequest, TSharedPtr<IHttpResponse> HttpResponse,
	bool bProcessedSuccessfully)
{
	if (bProcessedSuccessfully)
	{
		if (HttpUI)
		{
			FString json = HttpResponse->GetContentAsString();
			ParseLibraryJson_Get(json);
			HttpUI->UpdateLog(json);
		}
		
	}
}

void AHttpPlayer::ParseLibraryJson_Get(const FString& JsonString)
{
	// JSON Reader 생성
    TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(JsonString);
    TSharedPtr<FJsonObject> JsonObject;

    // JSON String을 JsonObject로 역직렬화(Deserialize)
    if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
    {
        // 1. 기본 정보 파싱 (루트 레벨)
        int32 ResultCode = JsonObject->GetIntegerField(TEXT("resultCode"));
        FString ResultMsg = JsonObject->GetStringField(TEXT("resultMsg"));
        int32 NumOfRows = JsonObject->GetIntegerField(TEXT("numOfRows"));
        int32 PageNo = JsonObject->GetIntegerField(TEXT("pageNo"));
        int32 TotalCount = JsonObject->GetIntegerField(TEXT("totalCount"));

        UE_LOG(LogTemp, Log, TEXT("결과 코드: %d, 메시지: %s, 총 개수: %d"), ResultCode, *ResultMsg, TotalCount);

        // 2. "items" 배열 파싱
        const TArray<TSharedPtr<FJsonValue>>* ItemsArray;
        if (JsonObject->TryGetArrayField(TEXT("items"), ItemsArray))
        {
            for (const TSharedPtr<FJsonValue>& ItemValue : *ItemsArray)
            {
                TSharedPtr<FJsonObject> ItemObject = ItemValue->AsObject();
                if (ItemObject.IsValid())
                {
                    // 각 아이템(책)의 정보 파싱
                    int32 No = ItemObject->GetIntegerField(TEXT("no"));
                    FString BookName = ItemObject->GetStringField(TEXT("bk_nm"));
                    FString AuthorName = ItemObject->GetStringField(TEXT("aut_nm"));
                    FString Publisher = ItemObject->GetStringField(TEXT("pblshr"));
                    FString PublishYear = ItemObject->GetStringField(TEXT("pblcn_yr"));
                    FString CallNo = ItemObject->GetStringField(TEXT("callno"));
                    FString Library = ItemObject->GetStringField(TEXT("lib"));
                    FString LoanYn = ItemObject->GetStringField(TEXT("loan_yn"));

                    // 로그 출력 (필요한 데이터만 출력)
                    UE_LOG(LogTemp, Log, TEXT("번호: %d | 책 이름: %s | 저자: %s | 도서관: %s | 대출가능: %s"), 
                        No, *BookName, *AuthorName, *Library, *LoanYn);
                }
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("JSON 파싱에 실패했습니다."));
    }
}

void AHttpPlayer::ReqPost(const FString& url, const FString& content)
{
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedPtr<IHttpRequest> req = httpModule.CreateRequest();
	
	req->SetURL(url);
	req->SetVerb(TEXT("POST"));
	req->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	req->SetContentAsString(content);
	
	req->OnProcessRequestComplete().BindUObject(this, &AHttpPlayer::OnReqPostComplete);
	
	req->ProcessRequest();
}

void AHttpPlayer::OnReqPostComplete(TSharedPtr<IHttpRequest> HttpRequest, TSharedPtr<IHttpResponse> HttpResponse,
	bool bProcessedSuccessfully)
{
	if (HttpUI)
	{
		FString content = HttpResponse->GetContentAsString();
		HttpUI->UpdateLog(content);
	}
}

void AHttpPlayer::ReqWebImage(const FString& url)
{
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedPtr<IHttpRequest> req = httpModule.CreateRequest();
	
	req->SetURL(url);
	req->SetVerb(TEXT("Get"));
	req->SetHeader(TEXT("Content-Type"), TEXT("image/jpeg"));
	
	req->OnProcessRequestComplete().BindUObject(this, &AHttpPlayer::OnReqWebImageComplete);
	
	req->ProcessRequest();
}

void AHttpPlayer::OnReqWebImageComplete(TSharedPtr<IHttpRequest> HttpRequest, TSharedPtr<IHttpResponse> HttpResponse,
	bool bProcessedSuccessfully)
{
	if (bProcessedSuccessfully)
	{
		TArray<uint8> data = HttpResponse->GetContent();
		
		FString imgPath = FPaths::ProjectPersistentDownloadDir() + "/Cat.jpeg";
		FFileHelper::SaveArrayToFile(data, *imgPath);
		
		
		UTexture2D* tex = FImageUtils::ImportBufferAsTexture2D(data); 
		
		if (HttpUI)
		{
			HttpUI->UpdateWebImage(tex);
		}
	}
}
