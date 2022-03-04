#include <wx/app.h>
#include "Mainframe.h"

class App : public wxApp {
public:
	virtual bool OnInit();
};

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
