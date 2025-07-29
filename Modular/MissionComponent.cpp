#include "MissionComponent.h"

UMissionComponent::UMissionComponent()
{
  
}

void UMissionComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UMissionComponent::StartMission()
{
    if (CurrentMission.State == EMissionState::NotStarted)
    {
        CurrentMission.State = EMissionState::InProgress;
        // Notify mission state change if needed
    }
}

void UMissionComponent::CompleteMission()
{
    if (CurrentMission.State == EMissionState::InProgress && CurrentMission.AreAllObjectivesCompleted())
    {
        CurrentMission.State = EMissionState::Completed;
        // Handle rewards and notifications here
    }
}

void UMissionComponent::FailMission()
{
    if (CurrentMission.State == EMissionState::InProgress)
    {
        CurrentMission.State = EMissionState::Failed;
        // Handle fail logic here
    }
}

void UMissionComponent::ResetMission()
{
    CurrentMission.ResetMission();
    // Notify mission reset if needed
}

void UMissionComponent::UpdateObjectiveProgress(int32 ObjectiveIndex, int32 NewProgress)
{
    if (CurrentMission.Objectives.IsValidIndex(ObjectiveIndex))
    {
        FMissionObjective& Objective = CurrentMission.Objectives[ObjectiveIndex];
        Objective.Progress = FMath::Clamp(NewProgress, 0, Objective.Target);
        Objective.bIsCompleted = (Objective.Progress >= Objective.Target);

        if (CurrentMission.AreAllObjectivesCompleted())
        {
            CompleteMission();
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("UpdateObjectiveProgress: Invalid ObjectiveIndex %d"), ObjectiveIndex);
    }
}

bool UMissionComponent::AreAllObjectivesCompleted() const
{
    return CurrentMission.AreAllObjectivesCompleted();
}

bool UMissionComponent::IsMissionActive() const
{
    return CurrentMission.State == EMissionState::InProgress;
}
