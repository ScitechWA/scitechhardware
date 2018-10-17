

#include "CoreMinimal.h"
#include "ScitechHardwareComponent.h"


// Sets default values for this component's properties
UScitechHardwareComponent::UScitechHardwareComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bAutoActivate = true;
	bWantsInitializeComponent = true;

	// ...
}


// Called when the game starts
void UScitechHardwareComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	ScitechHardwareOpenPort(ComPort);
	ScitechHardwareStartReading();
	ScitechHardwareStartWriting();
}

bool UScitechHardwareComponent::IsAvailable()
{
	return ScitechHardwareDelegate::ScitechHardwareIsAvailable();
}

void UScitechHardwareComponent::OnRegister()
{
	UActorComponent::OnRegister();

	ValidSelfPointer = this;
	SetInterfaceDelegate(GetOwner());
	ScitechHardwareStartup();
}

// Called every frame
void UScitechHardwareComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ScitechHardwareTick(DeltaTime);

	// ...
}

void UScitechHardwareComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UActorComponent::EndPlay(EndPlayReason);

	ScitechHardwareStopWriting();
	ScitechHardwareStopReading();
	ScitechHardwareClosePort();
}
