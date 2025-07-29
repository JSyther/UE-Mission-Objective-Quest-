/**
 * FMissionObjective:
 * Represents an individual objective within a mission, encapsulating
 * descriptive details, progress tracking (e.g., counts for collection or kill goals),
 * and completion status. Designed to be flexible enough to support
 * a variety of mission tasks, it includes reset functionality to allow
 * easy mission retries or state resets.
 * 
 * FMissionData:
 * Encapsulates all relevant data for a mission, including unique identification,
 * descriptive metadata (title, narrative), current mission state (NotStarted, InProgress, Completed, Failed),
 * and a collection of related mission objectives.
 * 
 * It further maintains reward information such as experience points and currency,
 * which are granted upon successful completion of the mission.
 * 
 * The structure supports key utility methods to reset the mission state and objectives,
 * as well as to assess whether all objectives have been completed, enabling
 * straightforward integration with mission management systems.
 * 
 * This modular and extensible design facilitates maintainability and scalability,
 * allowing for easy addition of new mission parameters, objectives, or reward types.
 * It separates mission data representation from mission logic, promoting clean
 * architecture principles and easing integration with Unreal Engine’s serialization
 * and Blueprint systems.
 * 
 * Intended for use in diverse mission-based gameplay systems, this design
 * can accommodate simple linear quests as well as more complex, branching mission structures.
 */



UENUM(BlueprintType)
enum class EMissionState : uint8
{
    NotStarted    UMETA(DisplayName = "Not Started"),
    InProgress    UMETA(DisplayName = "In Progress"),
    Completed     UMETA(DisplayName = "Completed"),
    Failed        UMETA(DisplayName = "Failed")
};

USTRUCT(BlueprintType)
struct FMissionObjective
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Description;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool bIsCompleted = false;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 CurrentCount = 0;  // For objectives requiring collection or kills

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 TargetCount = 1;

    void Reset()
    {
        bIsCompleted = false;
        CurrentCount = 0;
    }
};

USTRUCT(BlueprintType)
struct FMissionData
{
    GENERATED_BODY()

    // Current mission state
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mission")
    EMissionState State = EMissionState::NotStarted;

    // Unique mission identifier
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mission")
    FName MissionID;

    // Human-readable mission title
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mission")
    FString Title;

    // Description or narrative for the mission
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mission")
    FString Description;

    // List of mission objectives
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mission")
    TArray<FMissionObjective> Objectives;

    // Rewards granted upon completion
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mission")
    int32 ExperienceReward = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mission")
    int32 CurrencyReward = 0;

    // Resets mission to initial state
    void ResetMission()
    {
        State = EMissionState::NotStarted;
        for (FMissionObjective& Obj : Objectives)
        {
            Obj.Reset();
        }
    }

    // Check if all objectives are completed
    bool AreAllObjectivesCompleted() const
    {
        for (const FMissionObjective& Obj : Objectives)
        {
            if (!Obj.bIsCompleted)
                return false;
        }
        return true;
    }


// Mark the mission as completed and update state accordingly
void CompleteMission()
{
    State = EMissionState::Completed;
}

// Mark the mission as failed and update state accordingly
void FailMission()
{
    State = EMissionState::Failed;
}

// Check if the mission is currently active (InProgress)
bool IsMissionActive() const
{
    return State == EMissionState::InProgress;
}

// Start the mission by setting state to InProgress if not already started
void StartMission()
{
    if (State == EMissionState::NotStarted)
    {
        State = EMissionState::InProgress;
    }
}

// Update progress for a specific objective by index
void UpdateObjectiveProgress(int32 ObjectiveIndex, int32 NewProgress)
{
    if (Objectives.IsValidIndex(ObjectiveIndex))
    {
        Objectives[ObjectiveIndex].Progress = NewProgress;
        if (Objectives[ObjectiveIndex].Progress >= Objectives[ObjectiveIndex].Goal)
        {
            Objectives[ObjectiveIndex].bIsCompleted = true;
        }
    }
}

// Get the number of completed objectives
int32 GetCompletedObjectiveCount() const
{
    int32 Count = 0;
    for (const FMissionObjective& Obj : Objectives)
    {
        if (Obj.bIsCompleted)
            ++Count;
    }
    return Count;
}

// Get total number of objectives
int32 GetTotalObjectiveCount() const
{
    return Objectives.Num();
}

};
