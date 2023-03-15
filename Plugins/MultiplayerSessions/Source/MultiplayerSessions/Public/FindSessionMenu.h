// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FindSessionMenu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UFindSessionMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	
protected:
	virtual bool Initialize() override;
	void OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful);

	class UJoinSessionMenu* JoinSessionMenu;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UJoinSessionMenu> JoinSessionMenuClass;
private:
	UPROPERTY(meta = (BindWidget))
		class UButton* FindSessions_Btn;
	UPROPERTY(meta = (BindWidget))
		class UScrollBox* SessionList_ScrollBox;

	UFUNCTION()
	void FindSessions_BtnClicked();

	// The subsystem to handle all online session functionality
	class UMultiplayerSessionsSubsystem* MultiplayerSessionsSubsystem;
	
	int32 NumPublicConnections{ 4 };
	FString MatchType{ TEXT("FreeForAll") };
	FString PathToLobby{ TEXT("") };
};
