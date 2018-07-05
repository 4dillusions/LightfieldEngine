#include "SMMessageWindow.h"

namespace SMEngine { namespace Gui
{
	SMMessageWindow::SMMessageWindow(const SMString &name, SMGuiLayer *guiLayer, const SMString &message) :
			ClickedEvent(&SMIClickedEventHandler<SMMessageWindow *>::Clicked), name(name), guiLayer(guiLayer), isOk(false), isVisible(false)
	{
		SMString controlName;
		controlName.Append(name);
		controlName.Append("imgBackground");
		imgBackground = new SMImageControl(controlName, SMRectangle(18, 255, 444, 290), "Window.png", true);
		guiLayer->Add(imgBackground);

		controlName.Clear();
		controlName.Append(name);
		controlName.Append("lblMessage");
		lblMessage = new SMLabelControl(controlName, message, SMVector2D(240, 356), 15);
		lblMessage->OffsetPositionCenter();
		guiLayer->Add(lblMessage);

		controlName.Clear();
		controlName.Append(name);
		controlName.Append("btnYes");
		btnYes = new SMButtonControl(controlName, "YES", 20, SMRectangle(62, 422, 170, 80), "Button.png", true);
		btnYes->ClickedEvent += this;
		guiLayer->Add(btnYes);

		controlName.Clear();
		controlName.Append(name);
		controlName.Append("btnNo");
		btnNo = new SMButtonControl(controlName, "NO", 20, SMRectangle(252, 422, 170, 80), "Button.png", true);
		btnNo->ClickedEvent += this;
		guiLayer->Add(btnNo);
	}

	void SMMessageWindow::Show()
	{
		this->isVisible = true;
		guiLayer->IsVisible(true);
	}

	void SMMessageWindow::Hide()
	{
		this->isVisible = false;
		guiLayer->IsVisible(false);
	}

	void SMMessageWindow::Clicked(const SMObserverEventArgs<SMControl *> &args)
	{
		if (isVisible)
		{
			isOk = args.subject->Name() == btnYes->Name();

			controlArgs.subject = this;
			ClickedEvent(controlArgs);
		}

		Hide();
	}
};};
