#pragma once

#include "SMCore.h"

namespace SMEngine { namespace Core
{
	/*
	Update
	*/
	interface SMIUpdateEventHandler
	{
	public:
		virtual void Update() = 0;
	};

	/*
	Watch
	*/
	interface SMIWatchAlarmEventHandler
	{
	public:
		virtual void Alarm() = 0;
	};

	/*
	Touch
	*/
	class SMTouchEventArgs
	{
	public:
		int x, y;
	};

	interface SMITouchPressedEventHandler
	{
	public:
		virtual void TouchPressed(const SMTouchEventArgs &args) = 0;
	};

	interface SMITouchReleasedEventHandler
	{
	public:
		virtual void TouchReleased(const SMTouchEventArgs &args) = 0;
	};

	/*
	Keyboard
	*/
	enum Keyboard
	{
		KEY_SOUND_UP,
		KEY_SOUND_DOWN
	};

	class SMKeyboardEventArgs
	{
	public:
		Keyboard key;
	};

	interface SMIKeyPressedEventHandler
	{
	public:
		virtual void KeyPressed(const SMKeyboardEventArgs &args) = 0;
	};

	/*
	Orientation
	*/
	class SMOrientationEventArgs
	{
	public:
		enum Orientation { PORTRAIT, LANDSCAPE, PORTRAIT_REVERSE, LANDSCAPE_REVERSE };
		Orientation orientation;
	};

	interface SMIOrientationEventHandler
	{
	public:
		virtual void OrientationChanged(const SMOrientationEventArgs &args) = 0;
	};

	/*
	App Init and Terminate
	*/
	class SMAppInitTerminateEventArgs
	{
	public:
		enum ApplicationState { INITIALIZING, TERMINATE };
		ApplicationState applicationState;
	};

	interface SMIAppInitTerminateEventHandler
	{
	public:
		virtual void InitTerminateChanged(const SMAppInitTerminateEventArgs &args) = 0;
	};

	/*
	App Init and Terminate
	*/
	class SMAppForeBackGroundEventArgs
	{
	public:
		enum GroundState { FOREGROUND, BACKGROUND };
		GroundState groundState;
	};

	interface SMIAppForeBackGroundEventHandler
	{
	public:
		virtual void ForeBackGroundChanged(const SMAppForeBackGroundEventArgs &args) = 0;
	};

	/*
	Battery
	*/
	class SMBatteryLevelChangedEventArgs
	{
	public:
		enum BatteryLevel { BATTERY_FULL, BATTERY_HIGH, BATTERY_LOW, BATTERY_CRITICAL, BATTERY_EMPTY };
		BatteryLevel batteryLevel;
	};

	interface SMIBatteryLevelChangedEventHandler
	{
	public:
		virtual void BatteryLevelChanged(const SMBatteryLevelChangedEventArgs &args) = 0;
	};

	/*
	Low memory
	*/
	interface SMILowMemoryEventHandler
	{
	public:
		virtual void LowMemory() = 0;
	};

	/*
	App Screen On and Off
	*/
	class SMAppScreenOnOffEventArgs
	{
	public:
		enum ScreenState { ON, OFF };
		ScreenState screenState;
	};

	interface SMIAppScreenOnOffEventHandler
	{
	public:
		virtual void ScreenOnOffChanged(const SMAppScreenOnOffEventArgs &args) = 0;
	};

	/*
	Observer pattern
	*/
	template <typename T> class SMObserverEventArgs
	{
	public:
		T subject;
	};

    /*
	GUI
	*/
	template <typename T> interface SMIClickedEventHandler
	{
	public:
		virtual void Clicked(const SMObserverEventArgs<T> &args) = 0;
	};

	//TimerControl
	template <typename T> interface SMITickEventHandler
	{
	public:
		virtual void Tick(const SMObserverEventArgs<T> &args) = 0;
	};

	//TimeLabelControl
	template <typename T> interface SMITickMinEventHandler
	{
	public:
		virtual void Tick(const SMObserverEventArgs<T> &args) = 0;
	};

	//TimeLabelControl
	template <typename T> interface SMITickMaxEventHandler
	{
	public:
		virtual void Tick(const SMObserverEventArgs<T> &args) = 0;
	};
};};
