// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"

#include "MyChangeLevelCheckTriggerBox.h"

AMyChangeLevelCheckTriggerBox::AMyChangeLevelCheckTriggerBox()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMyChangeLevelCheckTriggerBox::BeginPlay()
{
    Super::BeginPlay();

    // Bind the overlap function
    OnActorBeginOverlap.AddDynamic(this, &AMyChangeLevelCheckTriggerBox::OnOverlapBegin);
}

void AMyChangeLevelCheckTriggerBox::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMyChangeLevelCheckTriggerBox::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
    if (OtherActor && OtherActor != this)
    {
        if (OtherActor && OtherActor != this)
        {
            // Controlla se l'oggetto ha il tag specifico
            if (OtherActor->ActorHasTag(TEXT("KeyTag")))
            {
                if (LevelNames.IsValidIndex(CurrentLevelIndex))
                {
                    UGameplayStatics::OpenLevel(GetWorld(), LevelNames[CurrentLevelIndex]);
                    CurrentLevelIndex++;

                    // Resetta l'indice se supera la lunghezza dell'array
                    if (CurrentLevelIndex >= LevelNames.Num())
                    {
                        CurrentLevelIndex = 0; // Torna al primo livello
                    }
                }
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Oggetto errato!"));
            }
        }
    }
}