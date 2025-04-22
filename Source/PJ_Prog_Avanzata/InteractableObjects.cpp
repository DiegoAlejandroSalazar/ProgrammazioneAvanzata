// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObjects.h"

// Sets default values
AInteractableObjects::AInteractableObjects()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    SetActorTickEnabled(true);
	Tags.Add(FName(TEXT("InteractableTag")));

}

// Called when the game starts or when spawned
void AInteractableObjects::BeginPlay()
{
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("Oggetto in movimento"));
}
void AInteractableObjects::CheckIfMoving()
{
    FVector CurrentVelocity = GetVelocity(); // Assuming GetVelocity() is available on your actor

    if (CurrentVelocity.IsNearlyZero(1.0f)) // Use a tolerance for comparison
    {
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("Oggetto fermo"));;
        // Perform actions when the actor is not moving
    }
    else
    {
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("Oggetto in movimento"));
        // Perform actions when the actor is moving
    }
}

// Called every frame
void AInteractableObjects::Tick(float DeltaTime)
{
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("Oggetto in movimento"));
    Super::Tick(DeltaTime);
    CheckIfMoving();

}

