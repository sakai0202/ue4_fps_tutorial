// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSProject.h"
#include "FPSProjectGameModeBase.h"

void AFPSProjectGameModeBase::StartPlay()

{
    Super::StartPlay();
    if (GEngine)

    {
        // Display a debug message for five seconds. (デバッグ メッセージを 5 秒間表示)  
        // The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message. ( -1 のキー値 (最初の引数) は、このメッセージを更新、リフレッシュする必要がないことを示しています) 
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameMode!"));
    }

    UE_LOG(LogTemp, Warning, TEXT("%s: Hello!"), __FUNCTIONW__);
}