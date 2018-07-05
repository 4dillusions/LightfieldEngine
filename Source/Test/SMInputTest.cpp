#include "SMInputTest.h"
#include "..\\Test\\SMTest.h"
#include "..\\Input\\SMInput.h"

using namespace SMEngine::Input;

namespace SMEngine { namespace Test
{
	class InputTouchPressedTest : public SMITouchPressedEventHandler
	{
	public:
		InputTouchPressedTest()
		{
			SMInput::Instance()->TouchPressedEvent += this;
		}

		~InputTouchPressedTest()
		{
			SMInput::Instance()->TouchPressedEvent -= this;
		}

		override void TouchPressed(const SMTouchEventArgs &args)
		{
			SMString text;
			text.Append("SMInput::OnTouchPressed ");
			text.Append(args.x);
			text.Append("_");
			text.Append(args.y);

			SMLogger::Instance().WriteOutput(text);
		}
	};

	InputTouchPressedTest *touchPressed;

    void SMInputTest::SMTouchTest()
    {
    	touchPressed = new InputTouchPressedTest(); //egy kis memory leak, tesztnél eltekintek tõle
    }
};};
