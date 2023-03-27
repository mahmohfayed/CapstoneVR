// Fill out your copyright notice in the Description page of Project Settings.


#include "JoinSessionMenu.h"
#include "Components/Button.h"
#include "MultiplayerSessionsSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Components/TextBlock.h"
#include "OnlineSubsystem.h"

void UJoinSessionMenu::Construct()
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		30.f,
		FColor::Blue,
		FString(TEXT("Construct Called")));

	if (ServerNameText)
	{
		ServerNameText->SetText(FText::FromString(SearchResult.GetSessionIdStr()));
		GEngine->AddOnScreenDebugMessage(
			-1,
			30.f,
			FColor::Blue,
			SearchResult.GetSessionIdStr());
	}
	if (PingText)
	{
		PingText->SetText(FText::FromString(FString::Printf(TEXT("%d"), SearchResult.PingInMs)));
		GEngine->AddOnScreenDebugMessage(
			-1,
			30.f,
			FColor::Blue,
			FString::Printf(TEXT("Ping: %d"), SearchResult.PingInMs));
	}
}

bool UJoinSessionMenu::Initialize()
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		30.f,
		FColor::Blue,
		FString(TEXT("UJoinSessionMenu::Initialize() Called")));
	if (!Super::Initialize())
	{
		return false;
	}
	if (JoinSession_Btn)
	{
		JoinSession_Btn->OnClicked.AddDynamic(this, &UJoinSessionMenu::JoinSession_BtnClicked);
	}

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
	}
	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->MultiplayerOnJoinSessionComplete.AddUObject(this, &UJoinSessionMenu::OnJoinSession);
	}
	return true;
}

void UJoinSessionMenu::OnJoinSession(EOnJoinSessionCompleteResult::Type Result)
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{
		IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			FString Address;
			SessionInterface->GetResolvedConnectString(NAME_GameSession, Address);

			APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
			if (PlayerController)
			{
				PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
			}
		}
	}
	if (Result != EOnJoinSessionCompleteResult::Success)
	{
		JoinSession_Btn->SetIsEnabled(true);
	}
}

void UJoinSessionMenu::JoinSession_BtnClicked()
{
	JoinSession_Btn->SetIsEnabled(false);
	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->JoinSession(SearchResult);
	}
}
