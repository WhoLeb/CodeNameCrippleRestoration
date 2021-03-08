// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_MainChar.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;
class UCameraComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UArrowComponent;
class UAnimMontage;

UCLASS()
class CRIPPLERESTORATION_API AC_MainChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_MainChar();

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
	float BaseSpeed = 300;
	UPROPERTY(EditAnywhere)
	float Speed = 300;
	UPROPERTY(EditAnywhere)
	float DashDist = 900;
	
	UPROPERTY(EditAnywhere)
	float DashDelay = 0.5f;
	UPROPERTY(EditAnywhere)
	float DashStop = 0.1f;

	UPROPERTY(VisibleAnywhere)
	int MaxDashes = 2;
	
	int DashCount = 1;
	bool bCanDash = true;

	void MoveY(float dir);
	void MoveX(float dir);
	void Dash();

	APlayerController* PC;

	UPROPERTY()
	FTimerHandle UnusedHandle;
	void StopDashing();
	void ResetDash();

	FRotator CurrentMeshRotation;

	void RotatePlayerToMouse();

	void PlayMyAttacAnim();

	UPROPERTY(EditAnywhere)
		UAnimMontage* AttacAnim;

};
