// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:
	//S3 L69
	UPROPERTY(VisibleAnywhere)
	bool ShouldMove = false; //powinien siê ruszyæ


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FVector StartLocation; //lokalizacja pocz¹tkowa
	FVector TargetLocation; //lokalizacja docelowa
	UPROPERTY(EditAnywhere)
	FVector MoveOffset; //przesuniêcie ruchu

	UPROPERTY(VisibleAnywhere)
	bool ReachedTarget = false;

	UPROPERTY(EditAnywhere)
	float MoveTime = 4.0f; //czas ruchu

	float TestFloat;

	bool GetShouldMove();
	void SetShouldMove(bool NewShouldMove);
		
};
