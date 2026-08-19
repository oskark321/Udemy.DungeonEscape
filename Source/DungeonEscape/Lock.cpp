// Fill out your copyright notice in the Description page of Project Settings.


#include "Lock.h"

#include "TriggerComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ALock::ALock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//S3 L 73

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	//tworzymy nowy podobjekt który bêdzie w edytorze jako objekt BP_Class<klasa komponentu który chcê utworzyæ>(nazwa tego komponentu widoczna w edytorze) - zwraca wskaŸnik
	SetRootComponent(RootComp); //ustawiamy RootComp jako komponent g³ówny

	TriggerComp = CreateDefaultSubobject<UTriggerComponent>(TEXT("Trigger Component"));
	//tworzymy nowy podobjekt który bêdzie w edytorze jako objekt BP_Class<klasa komponentu który chcê utworzyæ>(nazwa tego komponentu widoczna w edytorze) - zwraca wskaŸnik
	TriggerComp->SetupAttachment(RootComp); //dodajemy komponent do komponentu g³ównego

	KeyItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Key Item Mesh Component"));
	//tworzymy nowy podobjekt który bêdzie w edytorze jako objekt BP_Class<klasa komponentu który chcê utworzyæ>(nazwa tego komponentu widoczna w edytorze) - zwraca wskaŸnik
	KeyItemMesh->SetupAttachment(RootComp); //dodajemy komponent do Root Component

	Tags.Add("Lock"); //dodajemy nowy tag do klasy

}

// Called when the game starts or when spawned
void ALock::BeginPlay()
{
	Super::BeginPlay();
	
	SetIsKeyPlaced(false);
	

	//S3 L88
	//KeyItemName = GetActorNameOrLabel();
}

// Called every frame
void ALock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//S3 L80
	//UE_LOG(LogTemp, Warning, TEXT("Time from start game :%f"), GetWorld()->TimeSeconds);

}

bool ALock::GetIsKeyPlaced()
{
	return IsKeyPlaced;
}

void ALock::SetIsKeyPlaced(bool NewIsKeyPlaced)
{
	IsKeyPlaced = NewIsKeyPlaced;

	TriggerComp->Trigger(NewIsKeyPlaced);
	KeyItemMesh->SetVisibility(NewIsKeyPlaced); //ustawiamy widocznoœæ siatki komponentu kluczowego na true - widoczny false - niewidoczna
}



