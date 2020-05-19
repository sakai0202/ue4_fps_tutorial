// Fill out your copyright notice in the Description page of Project Settings. (Project Settings の Description ページに著作権情報を入力してください) 

#include "FPSProject.h"
#include "FPSCharacter.h"
#include "Components/CapsuleComponent.h" 

// Sets default values (デフォルト値を設定) 
AFPSCharacter::AFPSCharacter()
{
    // Set this character to call Tick() every frame. (このキャラクターがフレーム毎に Tick() を呼び出すように設定します) You can turn this off to improve performance if you don't need it. (必要がなければパフォーマンスを向上させるためにオフにすることができます) 
    PrimaryActorTick.bCanEverTick = true;

    // Create a first person camera component. (first person camera コンポーネントを作成)
    FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    // Attach the camera component to our capsule component. (camera コンポーネントを capsule コンポーネントにアタッチします)
    FPSCameraComponent->SetupAttachment(GetCapsuleComponent());
    // Position the camera slightly above the eyes. (目の高さより少し上にカメラを設定)
    FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
    // Allow the pawn to control camera rotation. (ポーンがカメラの回転を制御できるようにします)
    FPSCameraComponent->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned (ゲーム開始時またはスポーン時に呼び出される)
void AFPSCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (GEngine)
    {
        // Put up a debug message for five seconds. (デバッグ メッセージを 5 秒間表示) The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message. ( -1 のキー値 (最初の引数) は、このメッセージを更新、リフレッシュする必要がないことを示しています) 
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));
    }
}

// Called every frame (フレームごとに呼び出される)

void AFPSCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input (機能と入力をバインドするために呼ばれます)

void AFPSCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Set up "movement" bindings. (移動のバインディングをセットアップ) 
    PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);
    // Set up "look" bindings. (look のバインディングをセットアップ) 
    PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);

    // Set up "action" bindings. (アクションのバインディングをセットアップ) 
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::StopJump);
}

void AFPSCharacter::MoveForward(float Value)
{
    // Find out which way is "forward" and record that the player wants to move that way. (前進方向を確認し、プレイヤーがそちらの方向に移動するように記録) 
    FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
    AddMovementInput(Direction, Value);
}

void AFPSCharacter::MoveRight(float Value)
{
    // Find out which way is "forward" and record that the player wants to move that way. (右方向を確認し、プレイヤーがそちらの方向に移動するように記録) 
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