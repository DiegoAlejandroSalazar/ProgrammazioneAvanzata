// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObjects.h"

// Sets default values
AInteractableObjects::AInteractableObjects()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(FName(TEXT("InteractableTag")));

}

// Called when the game starts or when spawned
void AInteractableObjects::BeginPlay()
{
	
}

// Called every frame
void AInteractableObjects::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetVelocity().IsNearlyZero(1.0f)) {
		
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("Oggetto fermo"));
        // Perform actions when the actor is not moving
    }
    else
    {
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("Oggetto in movimento"));
        // Perform actions when the actor is moving
    }

}

