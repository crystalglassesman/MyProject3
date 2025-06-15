// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "WebSocketsModule.h"

void UMyGameInstance::Init()
{
	Super::Init();
	ConnectToWebSocket();
}

void UMyGameInstance::ConnectToWebSocket()
{
	const FString ServerUrl = TEXT("ws://localhost:8765");

	// Load WebSockets module
	FWebSocketsModule& WebSocketsModule = FModuleManager::LoadModuleChecked<FWebSocketsModule>(TEXT("WebSockets"));
	WebSocket = WebSocketsModule.CreateWebSocket(ServerUrl);

	WebSocket->OnMessage().AddLambda([this](const FString& Message) {
		if (Message == TEXT("1") || Message == TEXT("0")) {
			UE_LOG(LogTemp, Log, TEXT("Received message: %s"), *Message);
		}
	});

	// Connect
	WebSocket->Connect();
}

void UMyGameInstance::Shutdown()
{
	if (WebSocket->IsConnected())
	{
		WebSocket->Close();
	}
	Super::Shutdown();

}
