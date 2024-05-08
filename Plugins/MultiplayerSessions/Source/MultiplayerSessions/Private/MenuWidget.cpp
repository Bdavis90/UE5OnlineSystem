// Created by Brandon Davis


#include "MenuWidget.h"

#include "Components/Button.h"
#include "MultiplayerSessionSubsystem.h"

void UMenuWidget::MenuSetup(int32 NumOfPublicConnections, FString TypeOfMatch)
{
	NumPublicConnections = NumOfPublicConnections;
	MatchType = TypeOfMatch;

	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	SetIsFocusable(true);

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();

		if (PlayerController)
		{

			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);
		}
	}

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		MultiplayerSessionSubsystem = GetGameInstance()->GetSubsystem<UMultiplayerSessionSubsystem>();
	}

	if(MultiplayerSessionSubsystem)
	{
		MultiplayerSessionSubsystem->MultiplayerOnCreateSessionComplete.AddDynamic(this, &ThisClass::OnCreateSession);
	}

}

bool UMenuWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (HostButton)
	{
		HostButton->OnClicked.AddDynamic(this, &ThisClass::HostButtonClicked);
	}

	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &ThisClass::JoinButtonClicked);
	}

	return true;
}

void UMenuWidget::NativeDestruct()
{
	Super::NativeDestruct();

	MenuTearDown();
}

void UMenuWidget::OnCreateSession(bool bWasSuccessful)
{
	if(bWasSuccessful)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString(TEXT("Session Created Successfully!")));

		UWorld* World = GetWorld();

		if (World)
		{
			World->ServerTravel("/Game/ThirdPerson/Maps/Lobby?listen");
		}
	} else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString(TEXT("Failed to create session!")));
		
	}
}

void UMenuWidget::HostButtonClicked()
{

	if(MultiplayerSessionSubsystem)
	{
		MultiplayerSessionSubsystem->CreateSession(NumPublicConnections, MatchType);
	}
}

void UMenuWidget::JoinButtonClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString(TEXT("Join Button Clicked")));
	}

}

void UMenuWidget::MenuTearDown()
{
	RemoveFromParent();
	UWorld* World = GetWorld();
	if(World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if(PlayerController)
		{
			FInputModeGameOnly InputModeData;
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(false);
		}
	}
}
