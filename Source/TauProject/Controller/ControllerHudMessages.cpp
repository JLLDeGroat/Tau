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