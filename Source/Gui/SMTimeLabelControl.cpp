#include "SMTimeLabelControl.h"
#include "SMFontSprite.h"

namespace SMEngine { namespace Gui
{
	SMTimeLabelControl::SMTimeLabelControl(const SMString &name, const SMWatch &watch, bool isForward, const SMVector2D &position, int height)
		: SMLabelControl(name, SMString().AppendStr("00 00"), position, height), watch(watch), timerControl(nullptr), isForward(isForward),
			  TickMinEvent(&SMITickMinEventHandler<SMTimeLabelControl *>::Tick), TickMaxEvent(&SMITickMaxEventHandler<SMTimeLabelControl *>::Tick)
	{
		SMString timerName;
		timerName.Append(name);
		timerName.Append("timer");

		timerControl = new SMTimerControl(timerName, 1000);
		timerControl->TickEvent += this;
		controls.Add(timerControl);

		this->watch.AlarmEvent += this;

		SetTimerTexts();
	}

	SMTimeLabelControl::~SMTimeLabelControl()
	{
		timerControl->TickEvent -= this;
		watch.AlarmEvent -= this;
	}

	void SMTimeLabelControl::Tick(const SMObserverEventArgs<SMTimerControl *> &args)
	{
		if (isForward) watch++;
		else watch--;

		Time(watch.time);
	}

	void SMTimeLabelControl::Alarm()
	{
		timerLabelArgs.subject = this;

		if (watch.Min())
		{
			TickMinEvent(timerLabelArgs);
			Stop();
		}
		else if(watch.Max())
		{
			TickMaxEvent(timerLabelArgs);
			Stop();
		}
	}

	void SMTimeLabelControl::SetTimerTexts()
	{
		minuteText.Clear();
		minuteText.Append(watch.time.minute, 2);

		secondText.Clear();
		secondText.Append(watch.time.second, 2);

		int index = 0;
		for (componentList.First(); componentList.IsDone(); componentList.Next())
		{
			switch (index)
			{
				case 0:
				case 1:
					dynamic_cast<SMFontSprite *>(componentList.Current())->Character(minuteText[index]);
					break;

				case 3:
				case 4:
					dynamic_cast<SMFontSprite *>(componentList.Current())->Character(secondText[index - 3]);
					break;
			}

			++index;
		}
	}

	void SMTimeLabelControl::Time(const SMTime &time)
	{
		watch.time = time;
		SetTimerTexts();
	}

	void SMTimeLabelControl::Start()
	{
		if (timerControl != nullptr)
			timerControl->Start();
	}

	void SMTimeLabelControl::Stop()
	{
		if (timerControl != nullptr)
			timerControl->Stop();
	}
};};
