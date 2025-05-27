// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "MyChangeLevelCheckTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class PJ_PROG_AVANZATA_API AMyChangeLevelCheckTriggerBox : public ATriggerBox
{
	GENERATED_BODY()
public:
    AMyChangeLevelCheckTriggerBox();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UFUNCTION()
    void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "keysNeeded")
    int32 keysNeeded;
    UPROPERTY(BlueprintReadWrite, Category = "CurrentKeys")
    int32 CurrentKeys = 0;
    int32 AllLevelKeys = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
    AActor* BlueprintActorRef;


    

};
