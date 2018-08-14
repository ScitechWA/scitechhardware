#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "ScitechHardwareDelegate.h"


/**
 * The public interface to CV Classifier module.
 */
class IScitechHardware : public IModuleInterface
{

public:

	/**
	 * Singleton-like access to this module's interface.  This is just for convenience!
	 * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	 *
	 * @return Returns singleton instance, loading the module on demand if needed
	 */
	static inline IScitechHardware& Get()
	{
		return FModuleManager::LoadModuleChecked< IScitechHardware >( "ScitechHardware" );
	}

	/**
	 * Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	 *
	 * @return True if the module is loaded and ready to use
	 */
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded( "ScitechHardware" );
	}
	
	virtual bool IsConnected() = 0;
	virtual bool OpenPort(int ComPortNumber) = 0;
	virtual bool ClosePort() = 0;
	virtual bool StartReading() = 0;
	virtual bool StopReading() = 0;
	virtual bool StartWriting() = 0;
	virtual bool StopWriting() = 0;
	virtual bool Update() = 0;
	virtual bool GetDigitalValue(int ValueIndex) = 0;
	virtual bool GetDigitalValueSinceLastUpdate(int ValueIndex) = 0;
	virtual int GetAnalogueValue(int ValueIndex) = 0;
	virtual void SendString(FString outputString) = 0;

	virtual void SetDelegate(ScitechHardwareDelegate* newDelegate) {};

	virtual void ScitechHardwareTick(float DeltaTime) {};
};
