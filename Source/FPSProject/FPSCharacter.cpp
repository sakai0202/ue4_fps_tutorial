// Fill out your copyright notice in the Description page of Project Settings. (Project Settings �� Description �y�[�W�ɒ��쌠������͂��Ă�������) 

#include "FPSProject.h"
#include "FPSProjectile.h"
#include "FPSCharacter.h"
#include "Components/CapsuleComponent.h" 

//https://forums.unrealengine.com/development-discussion/c-gameplay-programming/1688235-how-to-attach-a-ucameracomponent-to-a-capsule

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


    // Create a first person mesh component for the owning player. (���L���Ă���v���C���[�̂��߂Ɉ�l�̃��b�V�����쐬) 
    FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
    // Only the owning player sees this mesh. (���̃��b�V���͏��L���Ă���v���C���[�������猩���܂�)
    FPSMesh->SetOnlyOwnerSee(true);
    // Attach the FPS mesh to the FPS camera. (FPS ���b�V���� FPS �J�����ɃA�^�b�`���܂�)
    FPSMesh->SetupAttachment(FPSCameraComponent);
    // Disable some environmental shadowing to preserve the illusion of having a single mesh. (�ꕔ�̔w�i�̃V���h�E�C���O�𖳌��ɂ��āA�ЂƂ̃��b�V���������Ă���Ƃ������o���ێ����܂�) 
    FPSMesh->bCastDynamicShadow = false;
    FPSMesh->CastShadow = false;

    // The owning player doesn't see the regular (third-person) body mesh. (���L���Ă���v���C���[�́A�ʏ�� (�O�l�̎��_��) �{�f�B ���b�V���͌����܂���) 
    GetMesh()->SetOwnerNoSee(true);

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

    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);
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

void AFPSCharacter::Fire()
{
    // Attempt to fire a projectile. (���˕��̔��˂��A�N�e�B�x�[�g���悤�Ƃ��܂�)
    if (ProjectileClass)
    {
        // Get the camera transform. (�J�����̃g�����X�t�H�[�����擾)
        FVector CameraLocation;
        FRotator CameraRotation;
        GetActorEyesViewPoint(CameraLocation, CameraRotation);

        // Transform MuzzleOffset from camera space to world space (�J������Ԃ��烏�[���h��Ԃ� MuzzleOffset ���g�����X�t�H�[��)
        FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
        FRotator MuzzleRotation = CameraRotation;
        // Skew the aim to be slightly upwards. (�Ə����኱������ɌX�΂����܂�) 
        MuzzleRotation.Pitch += 10.0f;
        UWorld* World = GetWorld();
        if (World)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = GetInstigator();
            // Spawn the projectile at the muzzle. (�e���Ŕ��˕����X�|�[�����܂�)
            AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
            if (Projectile)
            {
                // Set the projectile's initial trajectory. (���˕��̏����׃��V�e�B��ݒ�) 
                FVector LaunchDirection = MuzzleRotation.Vector();
                Projectile->FireInDirection(LaunchDirection);
            }
        }
    }
}