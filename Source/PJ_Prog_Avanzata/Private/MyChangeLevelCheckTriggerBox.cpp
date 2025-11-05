// Fill out your copyright notice in the Description page of Project Settings.

#include "MyChangeLevelCheckTriggerBox.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMeshActor.h"

AMyChangeLevelCheckTriggerBox::AMyChangeLevelCheckTriggerBox()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMyChangeLevelCheckTriggerBox::BeginPlay()
{
    Super::BeginPlay();
    
    //prende tutti gli attori mychangelevelchecktriggerbox nel livello e fa la somma di tutte le chiavi necessarie
    TArray<AActor*> Aactor = TArray<AActor*>();
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), GetClass(), Aactor);
    for (AActor* Actor : Aactor)
    {
        AMyChangeLevelCheckTriggerBox* x = Cast<AMyChangeLevelCheckTriggerBox>(Actor);
        AllLevelKeys += x->KeysNeeded;
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
        if (CurrentKeys != KeysNeeded) {
            if (OtherActor && OtherActor != this && OtherActor->GetClass()->GetName() != "BP_ThirdPersonCharacter_C_0" || "BP_Hand_C")
            {       
             // Controlla se l'oggetto ha il tag keytag
                if (OtherActor->ActorHasTag(TEXT("KeyTag")))
                {
                    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Oggetto Giusto!"));
                    OtherActor->Tags.Add("Chiave Inserita");
                    OtherActor->Destroy();
                    CurrentKeys++;
                    //se le chiavi correnti sono uguali alle chiave necessarie fa partire suono distrugge il boiler non completo e spawna nella stessa posizione quello aggiustato
                    if (CurrentKeys == KeysNeeded) {
                        UGameplayStatics::PlaySoundAtLocation(this, AllKeysInsertedSound, GetActorLocation());
                        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("boiler aggiustato"));
                        FTransform LocationToSpawn = BoilerIncompleto->GetActorTransform();
                        BoilerIncompleto->Destroy();
                        FActorSpawnParameters SpawnParams;
                        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
                        if (BoilerIncompleto && BoilerCompleto)
                        {
                            GetWorld()->SpawnActor<AActor>(BoilerCompleto, LocationToSpawn, SpawnParams);
                        }
                    }
                    int32 AllCurrentKey = 0;
                    TArray<AActor*> Aactor = TArray<AActor*>();
                    UGameplayStatics::GetAllActorsOfClass(GetWorld(), GetClass(), Aactor);
                    for (AActor* Actor : Aactor)
                    {
                        AMyChangeLevelCheckTriggerBox* x = Cast<AMyChangeLevelCheckTriggerBox>(Actor);
                        AllCurrentKey += x->CurrentKeys;
                    }
                    //dopo aver viso se tutte le chiavi del livello sono state inserite chiama l'evento lookatdoor della porta
                    if (AllCurrentKey == AllLevelKeys)
                    {
                        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Orange, TEXT("tutte chiavi inserite"));
                        if (Door)
                        {
                            // Il nome deve corrispondere esattamente a quello definito nel Blueprint.
                            FName NomeEvento(TEXT("LookAtDoor"));
                            UFunction* FunzioneEvento = Door->FindFunction(NomeEvento);

                            if (FunzioneEvento)
                            {
                                // Se l'evento non prevede parametri, possiamo passare un puntatore nullo.
                                Door->ProcessEvent(FunzioneEvento, nullptr);
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