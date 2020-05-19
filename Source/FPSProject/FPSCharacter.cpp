// Fill out your copyright notice in the Description page of Project Settings. (Project Settings �� Description �y�[�W�ɒ��쌠������͂��Ă�������) 

#include "FPSProject.h"
#include "FPSCharacter.h"
#include "Components/CapsuleComponent.h" 

// Sets default values (�f�t�H���g�l��ݒ�) 
AFPSCharacter::AFPSCharacter()
{
    // Set this character to call Tick() every frame. (���̃L�����N�^�[���t���[������ Tick() ���Ăяo���悤�ɐݒ肵�܂�) You can turn this off to improve performance if you don't need it. (�K�v���Ȃ���΃p�t�H�[�}���X�����コ���邽�߂ɃI�t�ɂ��邱�Ƃ��ł��܂�) 
    PrimaryActorTick.bCanEverTick = true;

    // Create a first person camera component. (first person camera �R���|�[�l���g���쐬)
    FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    // Attach the camera component to our capsule component. (camera �R���|�[�l���g�� capsule �R���|�[�l���g�ɃA�^�b�`���܂�)
    FPSCameraComponent->SetupAttachment(GetCapsuleComponent());
    // Position the camera slightly above the eyes. (�ڂ̍�����菭����ɃJ������ݒ�)
    FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
    // Allow the pawn to control camera rotation. (�|�[�����J�����̉�]�𐧌�ł���悤�ɂ��܂�)
    FPSCameraComponent->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned (�Q�[���J�n���܂��̓X�|�[�����ɌĂяo�����)
void AFPSCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (GEngine)
    {
        // Put up a debug message for five seconds. (�f�o�b�O ���b�Z�[�W�� 5 �b�ԕ\��) The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message. ( -1 �̃L�[�l (�ŏ��̈���) �́A���̃��b�Z�[�W���X�V�A���t���b�V������K�v���Ȃ����Ƃ������Ă��܂�) 
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));
    }
}

// Called every frame (�t���[�����ƂɌĂяo�����)

void AFPSCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input (�@�\�Ɠ��͂��o�C���h���邽�߂ɌĂ΂�܂�)

void AFPSCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Set up "movement" bindings. (�ړ��̃o�C���f�B���O���Z�b�g�A�b�v) 
    PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);
    // Set up "look" bindings. (look �̃o�C���f�B���O���Z�b�g�A�b�v) 
    PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);

    // Set up "action" bindings. (�A�N�V�����̃o�C���f�B���O���Z�b�g�A�b�v) 
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::StopJump);
}

void AFPSCharacter::MoveForward(float Value)
{
    // Find out which way is "forward" and record that the player wants to move that way. (�O�i�������m�F���A�v���C���[��������̕����Ɉړ�����悤�ɋL�^) 
    FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
    AddMovementInput(Direction, Value);
}

void AFPSCharacter::MoveRight(float Value)
{
    // Find out which way is "forward" and record that the player wants to move that way. (�E�������m�F���A�v���C���[��������̕����Ɉړ�����悤�ɋL�^) 
    FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
    AddMovementInput(Direction, Value);
}

void AFPSCharacter::StartJump()
{
    bPressedJump = true;
}

void AFPSCharacter::StopJump()
{
    bPressedJump = false;
}