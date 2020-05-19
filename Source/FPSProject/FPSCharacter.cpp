// Fill out your copyright notice in the Description page of Project Settings. (Project Settings の Description ページに著作権情報を入力してください) 

#include "FPSProject.h"
#include "FPSProjectile.h"
#include "FPSCharacter.h"
#include "Components/CapsuleComponent.h" 

//https://forums.unrealengine.com/development-discussion/c-gameplay-programming/1688235-how-to-attach-a-ucameracomponent-to-a-capsule

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


    // Create a first person mesh component for the owning player. (所有しているプレイヤーのために一人称メッシュを作成) 
    FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
    // Only the owning player sees this mesh. (このメッシュは所有しているプレイヤーだけから見えます)
    FPSMesh->SetOnlyOwnerSee(true);
    // Attach the FPS mesh to the FPS camera. (FPS メッシュを FPS カメラにアタッチします)
    FPSMesh->SetupAttachment(FPSCameraComponent);
    // Disable some environmental shadowing to preserve the illusion of having a single mesh. (一部の背景のシャドウイングを無効にして、ひとつのメッシュを持っているという錯覚を維持します) 
    FPSMesh->bCastDynamicShadow = false;
    FPSMesh->CastShadow = false;

    // The owning player doesn't see the regular (third-person) body mesh. (所有しているプレイヤーは、通常の (三人称視点の) ボディ メッシュは見えません) 
    GetMesh()->SetOwnerNoSee(true);

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

    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);
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

void AFPSCharacter::Fire()
{
    // Attempt to fire a projectile. (発射物の発射をアクティベートしようとします)
    if (ProjectileClass)
    {
        // Get the camera transform. (カメラのトランスフォームを取得)
        FVector CameraLocation;
        FRotator CameraRotation;
        GetActorEyesViewPoint(CameraLocation, CameraRotation);

        // Transform MuzzleOffset from camera space to world space (カメラ空間からワールド空間に MuzzleOffset をトランスフォーム)
        FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
        FRotator MuzzleRotation = CameraRotation;
        // Skew the aim to be slightly upwards. (照準を若干上方向に傾斜させます) 
        MuzzleRotation.Pitch += 10.0f;
        UWorld* World = GetWorld();
        if (World)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = GetInstigator();
            // Spawn the projectile at the muzzle. (銃口で発射物をスポーンします)
            AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
            if (Projectile)
            {
                // Set the projectile's initial trajectory. (発射物の初期べロシティを設定) 
                FVector LaunchDirection = MuzzleRotation.Vector();
                Projectile->FireInDirection(LaunchDirection);
            }
        }
    }
}