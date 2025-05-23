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
        if (CurrentKeys != keysNeeded) {
            if (OtherActor && OtherActor != this && OtherActor->GetClass()->GetName() != "BP_ThirdPersonCharacter_C_0" || "BP_Hand_C")
            {       

             // Controlla se l'oggetto ha il tag specifico
                if (OtherActor->ActorHasTag(TEXT("KeyTag")))
                {
                    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Oggetto Giusto!"));
                    OtherActor->Destroy();
                    CurrentKeys++;
                    if (CurrentKeys == keysNeeded) {
                        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Tutte le chiavi inserite"));
                    }
            }
            else
            {
                if (GEngine)
                    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Oggetto Sbagliato!"));
            }
        }

        }
}