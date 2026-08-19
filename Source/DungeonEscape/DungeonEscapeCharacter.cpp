// Copyright Epic Games, Inc. All Rights Reserved.

#include "DungeonEscapeCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DungeonEscape.h"

#include "CollectableItem.h"
#include "Lock.h"

ADungeonEscapeCharacter::ADungeonEscapeCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	// Create the first person mesh that will be viewed only by this character's owner
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));

	FirstPersonMesh->SetupAttachment(GetMesh());
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));

	// Create the Camera Component	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCameraComponent->SetupAttachment(FirstPersonMesh, FName("head"));
	FirstPersonCameraComponent->SetRelativeLocationAndRotation(FVector(-2.8f, 5.89f, 0.0f), FRotator(0.0f, 90.0f, -90.0f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
	FirstPersonCameraComponent->bEnableFirstPersonScale = true;
	FirstPersonCameraComponent->FirstPersonFieldOfView = 70.0f;
	FirstPersonCameraComponent->FirstPersonScale = 0.6f;

	// configure the character comps
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

	GetCapsuleComponent()->SetCapsuleSize(34.0f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->AirControl = 0.5f;


}

void ADungeonEscapeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ADungeonEscapeCharacter::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ADungeonEscapeCharacter::DoJumpEnd);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADungeonEscapeCharacter::MoveInput);

		// Looking/Aiming
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADungeonEscapeCharacter::LookInput);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ADungeonEscapeCharacter::LookInput);

		// S3 L78 Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ADungeonEscapeCharacter::InteractInput);
		//po≥πczenie akcji wyjúciowej Interact Action z funkcjπ ktÛrπ chcemy wywo≥aÊ ponaciúniÍciu przycisku
	}
	else
	{
		UE_LOG(LogDungeonEscape, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}


}


void ADungeonEscapeCharacter::MoveInput(const FInputActionValue& Value)
{
	// get the Vector2D move axis
	FVector2D MovementVector = Value.Get<FVector2D>();

	// pass the axis values to the move input
	DoMove(MovementVector.X, MovementVector.Y);

}

void ADungeonEscapeCharacter::LookInput(const FInputActionValue& Value)
{
	// get the Vector2D look axis
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// pass the axis values to the aim input
	DoAim(LookAxisVector.X, LookAxisVector.Y);

}

void ADungeonEscapeCharacter::InteractInput()
{

	//UE_LOG(LogTemp, Warning, TEXT("Interact"));

	//S3 L81
	FVector StartLineTracing = FirstPersonCameraComponent->GetComponentLocation();
	FVector EndLineTracing = StartLineTracing + (FirstPersonCameraComponent->GetForwardVector() * MaxInteractionDistance);

	//DrawDebugLine(GetWorld(), StartLineTracing, EndLineTracing, FColor::Green, false, 5.0f);

	//S3 L83
	FCollisionShape InteractionSphere = FCollisionShape::MakeSphere(InteractionSphereRadius);
	//DrawDebugSphere(GetWorld(), StartLineTracing, InteractionSphereRadius, 20, FColor::Blue, false, 5.0f);
	//DrawDebugSphere(GetWorld(), EndLineTracing, InteractionSphereRadius, 20, FColor::Blue, false, 5.0f);

	//S3 L84 i 85
	/*
	FVector MyVector;
	FVector& MyVectorRef = MyVector; //referencja dla MyVector
	MyVectorRef = GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("MyVectorRef = MyVector: %s"), *MyVector.ToCompactString());
	
	FVector TestVector = FVector(1.1f, 2.2f, 3.3f);
	UE_LOG(LogTemp, Warning, TEXT("TestVector is %s"), *TestVector.ToCompactString());
	TestFunction(TestVector);
	UE_LOG(LogTemp, Warning, TEXT("TestVector is %s"), *TestVector.ToCompactString());
	*/

	//S3 L86
	FHitResult HitResult;

	bool HasHit = GetWorld()->SweepSingleByChannel(HitResult,
		StartLineTracing, EndLineTracing,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		InteractionSphere);
//przeszukuje pojedynczo po kana≥ach (wynik trafienia - funkcja SweepSingleByChannel wype≥nia tπ zmiennπ informacjami o trafieniu w aktora, startowy, i koÒcowy wektor trafienia,
//obrÛt dla úledzenia kszta≥tu - w tym przypadku bÍdzie bez obrotu poniewaø go nie chcemy FQuat to struktura uøywana do wykonywania obliczeÒ obrotu, kana≥ úledzenia - utworzony
//przez nas wczeúniej w edytorze INTERACT - aby dowiedzieÊ siÍ jaki to kana≥ otwieramy plik w naszym projekcie/Config/DefaultEngine.ini i w tym pliku szukamy nazwy kana≥u ktÛry wczeúniej
//utowrzyliúmy i tam bÍdzie nazwa ECC_ i raczej chyba GameTraceChannel i jakiú nr np 2 - úledzenie kszta≥tu bÍdzie w obrÍbie tylko tego kana≥u czyli INTERACT,
//kszta≥t kolizji jaki ma byÊ úlecdzony w tym przypadku sfera czyli kula)

	if (HasHit)
	{
		AActor* HitActor = HitResult.GetActor();
		//UE_LOG(LogTemp, Warning, TEXT("Hit Actor Name is: %s"), *HitActor->GetActorNameOrLabel());
		//S3 L87
		if (HitActor->ActorHasTag("CollectableItem"))
		{
			//S3 L88			
			ACollectableItem* CollectableItem = Cast<ACollectableItem>(HitActor);
			//konwertuje wskaünik trafionego aktora w wskaünik ACollectableItem <tutaj mamy typ klasy w jaki chcemy przekonwertowaÊ>(tutaj wskaünik ktÛry chcemy przekonwertowaÊ)
			if (CollectableItem)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Collectable Actor Name is %s"), *CollectableItem->ItemName);
				
				//S3 L89
				ItemListArray.Add(CollectableItem->ItemName); //dpdanie elementu tablicy

				CollectableItem->Destroy();
			}
			
		}
		else if (HitActor->ActorHasTag("Lock"))
		{
			//S3 L88
			ALock* LockItem = Cast<ALock>(HitActor);
			//konwertuje wskaünik trafionego aktora w wskaünik ALock <tutaj mamy typ klasy w jaki chcemy przekonwertowaÊ>(tutaj wskaünik ktÛry chcemy przekonwertowaÊ)
			if (LockItem)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Lock Actor Name is %s"), *LockItem->KeyItemName);

				//S3 L90
				/* to jest po mojemu i dzia≥a ale kaødy przedmiot musi mieÊ swojπ nazwÍ innπ
				if (!LockItem->GetIsKeyPlaced() && ItemListArray.Contains(LockItem->KeyItemName))
					//spradzamy czy LockItem jest pusty czy nie ma na nim statuetki i przeszukujemy tablicÍ czy znajduje siÍ tam odpowiednia statuetka odpowiednia nazwa przedmiotu
				{
					ItemListArray.Remove(LockItem->KeyItemName); //usuwamy elemet tablicy ale po nazwie/danych w tej tablicy
					//RemoveAt(0) usuwa element tablicy ale po indeksie 
					LockItem->SetIsKeyPlaced(true);
					//k≥adziemy przedmiot na stole Lock, po usuniÍciu z listy w≥πczamy na tym stole siatkÍ Mesh na widoczna
				}
				else
					{
						UE_LOG(LogTemp, Warning, TEXT("Key Item not in inventory!"));
					}
				
				*/
				if (!LockItem->GetIsKeyPlaced())
				//spradzamy czy aktor Lock jest pusty czy nie ma na nim statuetki
				{
					int32 ItemsRemoved = ItemListArray.RemoveSingle(LockItem->KeyItemName);
					//przeszukuje tablicÍ i usuwamy pierwsze wystπpienie okreúlonego elementu po nazwie i zwraca wartoúÊ 1 jeúli usunÍ≥a 0 jeúli nie
					if (ItemsRemoved)
					{
						LockItem->SetIsKeyPlaced(true);
						//k≥adziemy przedmiot na stole Lock, po usuniÍciu z listy w≥πczamy na tym stole siatkÍ Mesh na widoczna
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("Key Item not in inventory!"));
					}
				}
				//S3 L91
				else
				{
					LockItem->SetIsKeyPlaced(false);
					ItemListArray.Add(LockItem->KeyItemName);
				}
			}
			
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Actor hit!"));
	}
}

//S3 L85
void ADungeonEscapeCharacter::TestFunction(FVector& Vector)
{
	Vector.X = 11.1f;
	Vector.Y = 22.2f;
	Vector.Z = 33.3f;
}

void ADungeonEscapeCharacter::DoAim(float Yaw, float Pitch)
{
	if (GetController())
	{
		// pass the rotation inputs
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ADungeonEscapeCharacter::DoMove(float Right, float Forward)
{
	if (GetController())
	{
		// pass the move inputs
		AddMovementInput(GetActorRightVector(), Right);
		AddMovementInput(GetActorForwardVector(), Forward);
	}
}

void ADungeonEscapeCharacter::DoJumpStart()
{
	// pass Jump to the character
	Jump();
}

void ADungeonEscapeCharacter::DoJumpEnd()
{
	// pass StopJumping to the character
	StopJumping();
}
