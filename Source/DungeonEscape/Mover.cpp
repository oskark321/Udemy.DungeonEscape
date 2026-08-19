// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	/*S3 L54
	float MyFloat = 10.2f;
	UE_LOG(LogTemp, Warning, TEXT("Only MyFloat = %f"), MyFloat);

	float* FloatPtr = &MyFloat;
	float Result = *FloatPtr;
	UE_LOG(LogTemp, Warning, TEXT("Result = *FloatPtr = %f"), Result);

	*FloatPtr = 9.2f;
	UE_LOG(LogTemp, Warning, TEXT("MyFloat when i use *FloatPtr = %f"), MyFloat);
	UE_LOG(LogTemp, Warning, TEXT("*FloatPtr = %f"), *FloatPtr);

	UE_LOG(LogTemp, Warning, TEXT("Result = %f"), Result);
	Result = *FloatPtr + 5.2f;
	UE_LOG(LogTemp, Warning, TEXT("again Result = *FloatPtr + 5.2 = %f"), Result);

	UE_LOG(LogTemp, Warning, TEXT("&MyFloat = %p"), &MyFloat);
	UE_LOG(LogTemp, Warning, TEXT("FloatPtr = %p"), FloatPtr);

	// ---

	FVector MyVector = FVector(1.0f, 1.0f, 1.0f);
	UE_LOG(LogTemp, Warning, TEXT("MyVector.X = %f"), MyVector.X);

	FVector* VectorPtr = &MyVector;
	UE_LOG(LogTemp, Warning, TEXT("MyVector.X = VectorPtr->X = %f"), VectorPtr->X);

	(*VectorPtr).X = 2.3f;
	UE_LOG(LogTemp, Warning, TEXT("wypisuje MyVector.X ale uzywam wskaznika: (*VectorPtr).X = %f"), MyVector.X);
	VectorPtr->X = 4.8f; // to samo znak strza³ki -> zastêpuje to co na górze
	UE_LOG(LogTemp, Warning, TEXT("wypisuje MyVector.X ale uzywam wskaznika: VectorPtr->X = %f"), MyVector.X);
	VectorPtr->Y = 5.7f; // to samo znak strza³ki -> zastêpuje to co na górze
	UE_LOG(LogTemp, Warning, TEXT("wypisuje MyVector.Y ale uzywam wskaznika: VectorPtr->Y = %f"), MyVector.Y);
	VectorPtr->Z = 12.6f; // to samo znak strza³ki -> zastêpuje to co na górze
	UE_LOG(LogTemp, Warning, TEXT("wypisuje MyVector.Z ale uzywam wskaznika: VectorPtr->Z = %f"), MyVector.Z);

	FString VectorString = MyVector.ToCompactString(); //zmienia FVector na String
	UE_LOG(LogTemp, Warning, TEXT("MyVector.ToCompactString() string czyli s i *: %s"), *MyVector.ToCompactString());

	UE_LOG(LogTemp, Warning, TEXT(" adress MyVector: &MyVector = %p"), &MyVector);
	UE_LOG(LogTemp, Warning, TEXT("adress VectorPtr: VectorPtr = %p"), VectorPtr);
	*/

	/*S3 L55
	ActorOwner = GetOwner();
	UE_LOG(LogTemp, Warning, TEXT("My Owner is called %s"), *ActorOwner->GetActorNameOrLabel()); //pobiera nazwê aktora ale przez wlasciciela GetOwner()
	ActorLocation = ActorOwner->GetActorLocation(); //pobiera lokalizacj¹ aktora ale przez wlasciciela GetOwner()
	*/

	//S3 L56
	StartLocation = GetOwner()->GetActorLocation();
	//TargetLocation = StartLocation + MoveOffset;

	//S3 L69
	SetShouldMove(false);

}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//UE_LOG(LogTemp, Warning, TEXT("Test"));
	/*S3 L55
	if (ActorOwner != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Owner location : %s"), *ActorLocation.ToCompactString());
		ActorLocation.Z = ActorLocation.Z + 100.0f * DeltaTime;
		ActorOwner->SetActorLocation(ActorLocation); //ustawia nowa lokalizacjê aktora ale przez wlasciciela GetOwner()
	}
	*/

	/*/S3 L56

	if (ShouldMove) //ShouldMove == true
	{
		//TestFloat = TestFloat + 1.0f;
		//UE_LOG(LogTemp, Warning, TEXT("go go go %f"), TestFloat);
		
		FVector CurrentLocation = GetOwner()->GetActorLocation();

		FVector NewLocation;

		float Speed = MoveOffset.Length() / MoveTime; // prêdkoœæ = przesuniêcie ruchu.d³ugoœæ wektora jako liczbê zmiennoprzecinkow¹ / czas ruchu

		NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
		//interpoluje z obecnego do docelowego wektora ze sta³ym krokiem sta³ym przesuniêciem

		GetOwner()->SetActorLocation(NewLocation);
	}
	*/

	//S3 L57
	/*
	if (ShouldMove) //odpowiada tylko za kierunek, ruch mamy osobno
	{
		TargetLocation = StartLocation + MoveOffset;
	}
	else
	{
		TargetLocation = StartLocation;
	}
	*/
	FVector CurrentLocation = GetOwner()->GetActorLocation();

	//S3 L58
	ReachedTarget = CurrentLocation.Equals(TargetLocation);
	//Equals to funkcja ze struktury FVector która porównuje dwa wektory i zwaraca wartoœæ logiczn¹ czy s¹ równe to TRUE czy nie to FALSE

	if (!ReachedTarget) // = (ReachedTarget == false)
	{

		float Speed = MoveOffset.Length() / MoveTime; //prêdkoœæ = przesuniêcie ruchu.d³ugoœæ wektora jako liczbê zmiennoprzecinkow¹ / czas ruchu

		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
		//interpoluje z obecnego do docelowego wektora ze sta³ym krokiem sta³ym przesuniêciem

		GetOwner()->SetActorLocation(NewLocation);

		//TestFloat = TestFloat + 1;
		//UE_LOG(LogTemp, Warning, TEXT("go go go x %f"), TestFloat)
	}


}

//S3 L69
bool UMover::GetShouldMove()
{
	return ShouldMove;
}

void UMover::SetShouldMove(bool NewShouldMove)
{
	ShouldMove = NewShouldMove;

	if (ShouldMove) //odpowiada tylko za kierunek, ruch mamy osobno
	{
		TargetLocation = StartLocation + MoveOffset;
	}
	else
	{
		TargetLocation = StartLocation;
	}

}

