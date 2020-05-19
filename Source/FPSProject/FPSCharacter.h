// Fill out your copyright notice in the Description page of Project Settings. (Project Settings の Description ページに著作権情報を入力してください) 
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "FPSCharacter.generated.h"

UCLASS()
class FPSPROJECT_API AFPSCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties. (このキャラクターのプロパティのデフォルト値を設定) 
    AFPSCharacter();

protected:
    // Called when the game starts or when spawned (ゲーム開始時またはスポーン時に呼び出される)
    virtual void BeginPlay() override;

public:
    // Called every frame (フレームごとに呼び出される)
    virtual void Tick(float DeltaSeconds) override;

    // Called to bind functionality to input (機能と入力をバインドするために呼ばれます)
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Handles input for moving forward and backward. (前後方向の移動の入力を処理) 
    UFUNCTION()
        void MoveForward(float Value);

    // Handles input for moving right and left. (左右の移動の入力を処理)       UFUNCTION()
    void MoveRight(float Value);

    // Sets jump flag when key is pressed.
    UFUNCTION()
        void StartJump();

    // Clears jump flag when key is released (キー解放時のジャンプフラグをクリア)
    UFUNCTION()
        void StopJump();

    // FPS camera (FPS カメラ)
    UPROPERTY(EditAnywhere)
    UCameraComponent* FPSCameraComponent;

    // First-person mesh (arms), visible only to the owning player. (一人称メッシュ (腕)、所有しているプレイヤーにのみ見えます) 
    UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
    USkeletalMeshComponent* FPSMesh;

};