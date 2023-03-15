// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CreateSessionMenu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UCreateSessionMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	// Create a String as such /Game/Maps/Lobby?listen
	UPROPERTY(EditAnywhere)
		FString LobbyPath;
protected:
	virtual bool Initialize() override;

	//
	// Callback for the custom delegates on the MultiplayerSessionSubsystem
	//
	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);

private:
	UPROPERTY(meta = (BindWidget))
		class UButton* CreateSession_Btn;

	

	UFUNCTION()
	void CreateSession_BtnClicked();

	class UMultiplayerSessionsSubsystem* MultiplayerSessionsSubsystem;


};
