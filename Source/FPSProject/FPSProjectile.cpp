// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSProject.h"
#include "FPSProjectile.h"

// Sets default values
AFPSProjectile::AFPSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Use a sphere as a simple collision representation (�ȈՂȃR���W�����\���ɋ��̂��g�p)
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));

	// Set the sphere's collision radius. (���̂̃R���W�������a��ݒ肵�܂�)
	CollisionComponent->InitSphereRadius(15.0f);
	// Set the root component to be the collision component. (���[�g �R���|�[�l���g�� collision �R���|�[�l���g�ɐݒ肵�܂�)
	RootComponent = CollisionComponent;

	// Use this component to drive this projectile's movement. (���̃R���|�[�l���g���g���Ĕ��˕��̓����𑀍삵�܂�)
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;

	// Die after 3 seconds. (3 �b��ɏ���)
	InitialLifeSpan = 3.0f;

}

// Called when the game starts or when spawned
void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Function that initializes the projectile's velocity in the shoot direction. (���˕����ɔ��˕��̂׃��V�e�B������������֐�)
void AFPSProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

