// Fill out your copyright notice in the Description page of Project Settings. (Project Settings �� Description �y�[�W�ɒ��쌠������͂��Ă�������) 
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
    // Sets default values for this character's properties. (���̃L�����N�^�[�̃v���p�e�B�̃f�t�H���g�l��ݒ�) 
    AFPSCharacter();

protected:
    // Called when the game starts or when spawned (�Q�[���J�n���܂��̓X�|�[�����ɌĂяo�����)
    virtual void BeginPlay() override;

public:
    // Called every frame (�t���[�����ƂɌĂяo�����)
    virtual void Tick(float DeltaSeconds) override;

    // Called to bind functionality to input (�@�\�Ɠ��͂��o�C���h���邽�߂ɌĂ΂�܂�)
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Handles input for moving forward and backward. (�O������̈ړ��̓��͂�����) 
    UFUNCTION()
        void MoveForward(float Value);

    // Handles input for moving right and left. (���E�̈ړ��̓��͂�����)       UFUNCTION()
    void MoveRight(float Value);

    // Sets jump flag when key is pressed.
    UFUNCTION()
        void StartJump();

    // Clears jump flag when key is released (�L�[������̃W�����v�t���O���N���A)
    UFUNCTION()
        void StopJump();

    // FPS camera (FPS �J����)
    UPROPERTY(EditAnywhere)
    UCameraComponent* FPSCameraComponent;

    // First-person mesh (arms), visible only to the owning player. (��l�̃��b�V�� (�r)�A���L���Ă���v���C���[�ɂ̂݌����܂�) 
    UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
    USkeletalMeshComponent* FPSMesh;

    // Function that handles firing projectiles. (���˕����A�N�e�B�x�[�g����֐�)
    UFUNCTION()
    void Fire();

    // Gun muzzle's offset from the camera location. (�J�����ʒu����e���̃I�t�Z�b�g)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    FVector MuzzleOffset;

    // Projectile class to spawn. (�X�|�[������ Projectile �N���X)
    UPROPERTY(EditDefaultsOnly, Category = Projectile)
    TSubclassOf<class AFPSProjectile> ProjectileClass;

};