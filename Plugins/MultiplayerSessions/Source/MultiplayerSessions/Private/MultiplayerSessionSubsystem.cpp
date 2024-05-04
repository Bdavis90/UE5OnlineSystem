// Created by Brandon Davis


#include "MultiplayerSessionSubsystem.h"

#include "OnlineSubsystem.h"

UMultiplayerSessionSubsystem::UMultiplayerSessionSubsystem()
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();

	if(Subsystem)
	{
		
		SessionInterface = Subsystem->GetSessionInterface();
	}
}
