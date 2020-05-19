// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSProject.h"
#include "FPSProjectGameModeBase.h"

void AFPSProjectGameModeBase::StartPlay()

{
    Super::StartPlay();
    if (GEngine)

    {
        // Display a debug message for five seconds. (�f�o�b�O ���b�Z�[�W�� 5 �b�ԕ\��)  
        // The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message. ( -1 �̃L�[�l (�ŏ��̈���) �́A���̃��b�Z�[�W���X�V�A���t���b�V������K�v���Ȃ����Ƃ������Ă��܂�) 
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameMode!"));
    }

    UE_LOG(LogTemp, Warning, TEXT("%s: Hello!"), __FUNCTIONW__);
}