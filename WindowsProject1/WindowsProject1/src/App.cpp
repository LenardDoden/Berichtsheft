#include <wx/app.h>
#include "Mainframe.h"

class App : public wxApp {

public:
	void OnUnhandledException();
	virtual bool OnInit();


};

void App::OnUnhandledException()
{
	try
	{
		std::rethrow_exception(std::current_exception());

	}
	catch (const std::exception& e)
	{
		wxLogFatalError(__FUNCTION__ "%s", e.what());
		throw;
	}
}

bool App::OnInit() {

	try {

		auto frame = new Mainframe{ nullptr };
		frame->Show();
		return true;
	}

	catch (std::exception& e) {
		wxLogFatalError("App::OnInit: %s", e.what());
		//throw
	}

	return false;
}




wxIMPLEMENT_APP(App);
