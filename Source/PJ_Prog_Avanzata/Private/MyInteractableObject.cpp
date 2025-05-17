// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInteractableObject.h"

// Sets default values
AMyInteractableObject::AMyInteractableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(FName(TEXT("InteractableTag")));
}

// Called when the game starts or when spawned
void AMyInteractableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyInteractableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

