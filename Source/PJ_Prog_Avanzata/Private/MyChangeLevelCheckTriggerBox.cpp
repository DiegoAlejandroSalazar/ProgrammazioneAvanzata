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
        if (OtherActor && OtherActor != this && OtherActor->GetClass()->GetName() != "BP_ThirdPersonCharacter_C_0" || "BP_Hand_C")
        {       
     
            // Controlla se l'oggetto ha il tag specifico
            if (OtherActor->ActorHasTag(TEXT("KeyTag")))
            {

                if (GEngine)
                    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Oggetto Giusto!"));
                OtherActor->Destroy();
               // static ConstructorHelpers::FClassFinder<ACharacter> Assetfile(TEXT("C: / Users / diego / Desktop / ProgrammazioneAvanzata / Content / ThirdPerson / Blueprints / BP_ThirdPersonCharacter.uasset"));
                //UGameplayStatics::GetGameMode(GetWorld());
                //UGameplayStatics::GetPlayerController(getWorld())
                
                //if (LevelNames.IsValidIndex(CurrentLevelIndex))
               // {
                    
                    //UGameplayStatics::OpenLevel(GetWorld(), LevelNames[CurrentLevelIndex]);
                   // CurrentLevelIndex++;

                    // Resetta l'indice se supera la lunghezza dell'array
                   // if (CurrentLevelIndex >= LevelNames.Num())
                   // {
                      //  CurrentLevelIndex = 0; // Torna al primo livello
                   // }
               // }
            }
            else
            {
                if (GEngine)
                    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Oggetto Sbagliato!"));
            }
        }
}