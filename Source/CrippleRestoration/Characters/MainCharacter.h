// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MainCharacter.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;
class UCameraComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UArrowComponent;

UCLASS()
class CRIPPLERESTORATION_API AMainCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TempMesh;
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CapsuleComp;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UArrowComponent* Arrow;

	UPROPERTY(EditAnywhere)
	float MaxSpeed = 40;
	UPROPERTY(EditAnywhere)
	float Speed = 100;

	FVector CurrentVelocity;

	void MoveY(float dir);
	void MoveX(float dir);
	void Stop();

};
