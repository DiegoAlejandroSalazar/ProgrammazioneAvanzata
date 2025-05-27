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
    

    TArray<AActor*> Aactor = TArray<AActor*>();
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), GetClass(), Aactor);
    for (AActor* Actor : Aactor)
    {
        AMyChangeLevelCheckTriggerBox* x = Cast<AMyChangeLevelCheckTriggerBox>(Actor);
        AllLevelKeys += x->keysNeeded;
    }
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
                    int32 AllCurrentKey = 0;
                    TArray<AActor*> Aactor = TArray<AActor*>();
                    UGameplayStatics::GetAllActorsOfClass(GetWorld(), GetClass(), Aactor);
                    for (AActor* Actor : Aactor)
                    {
                        AMyChangeLevelCheckTriggerBox* x = Cast<AMyChangeLevelCheckTriggerBox>(Actor);
                        AllCurrentKey += x->CurrentKeys;
                    }
                    if (AllCurrentKey == AllLevelKeys)
                    {
                        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Orange, TEXT("tutte chiavi inserite"));
                        if (BlueprintActorRef)
                        {
                            // Il nome deve corrispondere esattamente a quello definito nel Blueprint.
                            FName NomeEvento(TEXT("LookAtDoor"));
                            UFunction* FunzioneEvento = BlueprintActorRef->FindFunction(NomeEvento);

                            if (FunzioneEvento)
                            {
                                // Se l'evento non prevede parametri, possiamo passare un puntatore nullo.
                                BlueprintActorRef->ProcessEvent(FunzioneEvento, nullptr);
                                UE_LOG(LogTemp, Warning, TEXT("Evento '%s' chiamato correttamente."), *NomeEvento.ToString());
                            }
                            else
                            {
                                UE_LOG(LogTemp, Warning, TEXT("Funzione '%s' non trovata nell'oggetto Blueprint."), *NomeEvento.ToString());
                            }
                        }
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