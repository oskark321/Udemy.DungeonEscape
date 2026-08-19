// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lock.generated.h"

UCLASS()
class DUNGEONESCAPE_API ALock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//S3 L73
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere)
	class UTriggerComponent* TriggerComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* KeyItemMesh;

	UPROPERTY(EditAnywhere)
	FString KeyItemName;

	bool GetIsKeyPlaced();
	void SetIsKeyPlaced(bool NewIsKeyPlaced);

private:

	UPROPERTY(VisibleAnywhere)
	bool IsKeyPlaced = false;

};
