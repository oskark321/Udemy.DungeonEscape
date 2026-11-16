// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "TriggerComponent.generated.h"

class UMover;
class UPrimitiveComponent;
class AActor;


/**
 * 
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()
	

public:
	UTriggerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//S3 63
	UPROPERTY(EditAnywhere)
	AActor* MoverActor;

	UMover* Mover;

	//wywo³anie gdy coœ wchodzi do sfery komponentu 
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//wywo³anie gdy coœ opuszcza sferê komponentu
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere)
	bool IsPressurePlate = false;

	//S6 L68
	UPROPERTY(VisibleAnywhere)
	bool IsTriggered = false;

	UPROPERTY(VisibleAnywhere)
	int32 ActivatorCount = 0;

	void Trigger(bool NewTriggerValue);

};
