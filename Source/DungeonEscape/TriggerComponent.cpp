// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

#include "Mover.h"

UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

}

void UTriggerComponent::BeginPlay()
{

	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("Actor name is %s"), *GetOwner()->GetActorNameOrLabel());

	//S3 L63
	if (MoverActor) //to samo co MoverActor != nullptr
	{
		Mover = MoverActor->FindComponentByClass<UMover>(); //znajdz komponent po klasie<szukamy komponentu UMover Component w MoverAktor> - jeœli go znajdzie zwróci go do zmiennej jeœli nie zwróci nullptr,
		
		if (Mover) //to samo co Mover != nullptr
		{
			UE_LOG(LogTemp, Warning, TEXT("Mover isn't nullptr"));
			//Mover->ShouldMove = true;
			
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Mover is nullptr"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MoverActor is nullptr"));
	}

	//S3 L65
	if (IsPressurePlate)
	{
		OnComponentBeginOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapBegin);
	//zdarzeie które jest wywo³ywane gdy coœ zacznie nak³adaæ siê na ten komponent np gracz wchodz¹cy na wyzwalacz.po³¹czenie funkcji(ten objekt, adres funkcji która chcemy po³aczyæ
		OnComponentEndOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapEnd);
	//zdarzeie które jest wywo³ywane gdy coœ skoñczy nak³adaæ siê na ten komponent np gracz opuszczaj¹cy wyzwalacz.po³¹czenie funkcji(ten objekt, adres funkcji która chcemy po³aczyæ

	}


}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}
//S3 L65
void UTriggerComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	/*if (OtherActor->ActorHasTag("PressurePlateActivator")) //S3 L66
	
	if (Mover) //Mover != false 
	{
		Mover->ShouldMove = true;
	}
	*/


	//S3 L67
	if (OtherActor && OtherActor->ActorHasTag("PressurePlateActivator"))
	{
		//ActivatorCount = ActivatorCount + 1; //S3 L70
		ActivatorCount++; //to samo co u góry

		if (!IsTriggered && ActivatorCount)
		{
			//Mover->ShouldMove = true;
			Trigger(true);
		}
	}

}

//S3 L65
void UTriggerComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	/*if (OtherActor->ActorHasTag("PressurePlateActivator")) //S3 L66
	{
		if (Mover) //Mover != false
		{
			Mover->ShouldMove = false;
		}
	}
	*/

	

	//S3 L67
	if (OtherActor && OtherActor->ActorHasTag("PressurePlateActivator"))
	{
		//ActivatorCount = ActivatorCount - 1; //S3 L70
		ActivatorCount--; //to samo co u góry

		if (IsTriggered && !ActivatorCount)
		{
			//Mover->ShouldMove = false;
			Trigger(false);
		}
	}

}
//S3 L68
void UTriggerComponent::Trigger(bool NewTriggerValue)
{
	IsTriggered = NewTriggerValue;
	if (Mover)
	{
		Mover->SetShouldMove(NewTriggerValue); //S3 L69
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s doesn,t have a mover to trigger!"), *GetOwner()->GetActorNameOrLabel());
	}
}
