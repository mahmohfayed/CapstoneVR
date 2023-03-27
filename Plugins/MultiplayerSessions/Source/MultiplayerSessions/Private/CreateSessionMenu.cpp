// Fill out your copyright notice in the Description page of Project Settings.


#include "CreateSessionMenu.h"
#include "Components/Button.h"
#include "MultiplayerSessionsSubsystem.h"

bool UCreateSessionMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	if (CreateSession_Btn)
	{
		CreateSession_Btn->OnClicked.AddDynamic(this, &ThisClass::CreateSession_BtnClicked);
	}
	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
	}

	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->MultiplayerOnCreateSessionComplete.AddDynamic(this, &ThisClass::OnCreateSession);
	}
	// On Default this will take everyone to the level Select map
	LobbyPath = "/Game/LevelSelect/Maps/Map_LevelSelect?listen";
	return true;
}

void UCreateSessionMenu::OnCreateSession(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			World->ServerTravel(LobbyPath);
		}
	}
	else
	{
		CreateSession_Btn->SetIsEnabled(true);
	}
}

void UCreateSessionMenu::CreateSession_BtnClicked()
{
	CreateSession_Btn->SetIsEnabled(false);
	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->CreateSession(4, FString("FreeForAll")); // This is where you say which MatchType you want to use (FreeForAll in this case)
	}
}
