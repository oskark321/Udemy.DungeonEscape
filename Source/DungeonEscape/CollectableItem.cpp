// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectableItem.h"

// Sets default values
ACollectableItem::ACollectableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//S3 L72	
	Tags.Add("CollectableItem"); //dodanie tagu i nazwy
}

// Called when the game starts or when spawned
void ACollectableItem::BeginPlay()
{
	Super::BeginPlay();
	
	//S3 L88
	//ItemName = GetActorNameOrLabel();
}

// Called every frame
void ACollectableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

