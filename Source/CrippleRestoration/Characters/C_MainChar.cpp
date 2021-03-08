// Fill out your copyright notice in the Description page of Project Settings.


#include "C_MainChar.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Public/TimerManager.h"

// Sets default values
AC_MainChar::AC_MainChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//bOrientRotationToMovement = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 3000.f, 0.f);

	TempMesh = CreateDefaultSubobject<UStaticMeshComponent>("Temporary mesh");
	TempMesh->SetupAttachment(RootComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring arm");
	SpringArm->SetupAttachment(RootComponent);

	SpringArm->bInheritYaw = false;
	SpringArm->TargetArmLength = 700;
	SpringArm->CameraLagSpeed = 0.3;

	SpringArm->AddLocalRotation(FRotator(-70.f, 0, 0));

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	PC = UGameplayStatics::GetPlayerController(this, 0);

	if(PC){
		PC->bShowMouseCursor = true;
		PC->DefaultMouseCursor = EMouseCursor::Crosshairs;
		PC->bEnableClickEvents = true;
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Yellow, "Player controller created");
	}

}

// Called when the game starts or when spawned
void AC_MainChar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_MainChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotatePlayerToMouse();

}

// Called to bind functionality to input
void AC_MainChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveY", this, &AC_MainChar::MoveY);
	PlayerInputComponent->BindAxis("MoveX", this, &AC_MainChar::MoveX);

	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AC_MainChar::Dash);
	
}

void AC_MainChar::MoveY(float dir){
	AddMovementInput(FVector(0, 1, 0) * dir, Speed);
}

void AC_MainChar::MoveX(float dir){
	AddMovementInput(FVector(1, 0, 0) * dir, Speed);
}

void AC_MainChar::Dash(){
	if(bCanDash){
		GetCharacterMovement()->BrakingFrictionFactor = 0.f;
		LaunchCharacter(GetActorForwardVector() * DashDist, true, true);
		++DashCount;
		if (DashCount > MaxDashes)
			bCanDash = false;
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &AC_MainChar::StopDashing, DashStop, false);
	}
}

void AC_MainChar::StopDashing(){
	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->BrakingFrictionFactor = 2.f;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &AC_MainChar::ResetDash, DashDelay, false);	
}

void AC_MainChar::ResetDash(){
	bCanDash = true;
	DashCount = 1;	
}

void AC_MainChar::RotatePlayerToMouse(){
	FVector WorldLocation;
	FVector WorldDirection;

	FHitResult OutHit;

	PC->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	bool block = GetWorld()->LineTraceSingleByChannel(OutHit, WorldLocation, 
		WorldDirection * 10000 + WorldLocation, ECC_WorldStatic);
	
	UE_LOG(LogTemp, Warning, TEXT("hitRes location: X-%f, Y-%f, Z-%f"), OutHit.Location.X, 
		OutHit.Location.Y, OutHit.Location.Z);

	CurrentMeshRotation = UKismetMathLibrary::FindLookAtRotation(RootComponent->GetComponentLocation(), OutHit.Location);

	GetMesh()->SetWorldRotation(FRotator(0, CurrentMeshRotation.Yaw - 90.f, 0));

}
