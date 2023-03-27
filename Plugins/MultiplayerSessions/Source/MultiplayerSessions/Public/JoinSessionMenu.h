// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "JoinSessionMenu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UJoinSessionMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	void Construct();
	FOnlineSessionSearchResult SearchResult;

protected:
	virtual bool Initialize() override;
	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);

private:
	UPROPERTY(meta = (BindWidget))
		class UButton* JoinSession_Btn;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* PingText;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* ServerNameText;

	UFUNCTION()
	void JoinSession_BtnClicked();

	class UMultiplayerSessionsSubsystem* MultiplayerSessionsSubsystem;
	
};
