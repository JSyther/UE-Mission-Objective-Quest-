#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MissionData.h"  // Include your mission-related structs/enums here
#include "MissionComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class YOURGAME_API UMissionComponent : public UObject
{
    GENERATED_BODY()

public:
    UMissionComponent();

public:
    // Currently active mission data
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mission")
    FMissionData CurrentMission;

    // Starts the mission if not already started
    UFUNCTION(BlueprintCallable, Category = "Mission")
    void StartMission();

    // Completes the mission and triggers reward logic
    UFUNCTION(BlueprintCallable, Category = "Mission")
    void CompleteMission();

    // Fails the mission and updates state
    UFUNCTION(BlueprintCallable, Category = "Mission")
    void FailMission();

    // Resets the mission data to initial state
    UFUNCTION(BlueprintCallable, Category = "Mission")
    void ResetMission();

    // Updates progress of a specific objective by index
    UFUNCTION(BlueprintCallable, Category = "Mission")
    void UpdateObjectiveProgress(int32 ObjectiveIndex, int32 NewProgress);

    // Checks if all objectives are completed
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Mission")
    bool AreAllObjectivesCompleted() const;

    // Returns whether mission is currently active
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Mission")
    bool IsMissionActive() const;

    // Event triggered when mission state changes (optional, you can add delegate if needed)
    // DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMissionStateChanged, EMissionState, NewState);
    // UPROPERTY(BlueprintAssignable, Category = "Mission")
    // FOnMissionStateChanged OnMissionStateChanged;
};
