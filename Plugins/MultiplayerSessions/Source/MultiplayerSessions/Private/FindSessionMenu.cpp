// Fill out your copyright notice in the Description page of Project Settings.


#include "FindSessionMenu.h"
#include "JoinSessionMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "MultiplayerSessionsSubsystem.h"
#include "OnlineSessionSettings.h"

bool UFindSessionMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	if (FindSessions_Btn)
	{
		FindSessions_Btn->OnClicked.AddDynamic(this, &UFindSessionMenu::FindSessions_BtnClicked);
	}
	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
	}
	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->MultiplayerOnFindSessionsComplete.AddUObject(this, &UFindSessionMenu::OnFindSessions);
	}
	return true;
}

void UFindSessionMenu::OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful)
{
	if (MultiplayerSessionsSubsystem == nullptr)
	{
		FindSessions_Btn->SetIsEnabled(true);
		return;
	}
	APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();

	for (auto Result : SessionResults)
	{
		FString SettingsValue;
		Result.Session.SessionSettings.Get(FName("MatchType"), SettingsValue);
		
		if (SettingsValue == MatchType) // loop through all of SettingsValue (which is FreeForAll now)
		{
			if (JoinSessionMenuClass)
			{
				JoinSessionMenu = CreateWidget<UJoinSessionMenu>(PlayerController, JoinSessionMenuClass);
				JoinSessionMenu->SearchResult = Result;
				SessionList_ScrollBox->AddChild(JoinSessionMenu);
				if (SessionList_ScrollBox)
				{
					SessionList_ScrollBox->AddChild(JoinSessionMenu);
				}
			}
		}
	}

	if (!bWasSuccessful || SessionResults.Num() == 0)
	{
		FindSessions_Btn->SetIsEnabled(true);
		return;
	}
	FindSessions_Btn->SetIsEnabled(true);

}

void UFindSessionMenu::FindSessions_BtnClicked()
{
	FindSessions_Btn->SetIsEnabled(false);
	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->FindSessions(10000);
	}
}
