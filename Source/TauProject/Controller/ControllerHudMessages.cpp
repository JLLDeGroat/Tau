// Fill out your copyright notice in the Description page of Project Settings.

#include "ControllerHudMessages.h"


UControllerHudMessages::UControllerHudMessages() {

}


void UControllerHudMessages::MessageShown() {
	bShowMessage = false;
	bCurrentlyShowingMessage = false;
	if (MessageQueue.Num() > 0) {
		ShowMessage(MessageQueue[0]);
		MessageQueue.RemoveAt(0);
	}

}

void UControllerHudMessages::ShowMessage(FString message) {
	if (bShowMessage) {
		MessageQueue.Add(message);
	}
	else {
		Message = message;
		bShowMessage = true;
		bCurrentlyShowingMessage = true;
	}
}

#pragma region Completion Messages

int32 UControllerHudMessages::GetCompletionMessageQueueCount() {
	return CompletionMessageQueue.Num();
}
TArray<FString> UControllerHudMessages::GetCompletionMessageQueue() {
	return CompletionMessageQueue;
}

void UControllerHudMessages::ShowCompletionMessage(FString Message) {	
	CompletionMessageQueue.Add(Message);	
	bShowCompletionMessage = true;	
}

void UControllerHudMessages::FinishedShowingCompletionMessage() {
	bShowCompletionMessage = false;
	bCurrentlyShowingCompletionMessage = false;

	CompletionMessageQueue.RemoveAt(0);

	if (GetCompletionMessageQueueCount() > 0) {
		bShowCompletionMessage = true;
	}
}

FString UControllerHudMessages::GetFirstCompletionMessage(){
	return CompletionMessageQueue[0];
}

bool UControllerHudMessages::GetCurrentlyShowingCompletionMessage() {
	return bCurrentlyShowingCompletionMessage;
}

bool UControllerHudMessages::GetShouldShowCompletionMessage() {
	return bShowCompletionMessage;
}

void UControllerHudMessages::SetCurrentlyShowingCompletionMessage(bool val) {
	bCurrentlyShowingCompletionMessage = val;
}

#pragma endregion