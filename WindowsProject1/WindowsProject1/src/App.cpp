#include <wx/app.h>
#include "Mainframe.h"

class App : public wxApp {
public:
	virtual bool OnInit();
};

bool App::OnInit() {
	auto frame = new Mainframe{ nullptr };
	frame->Show();
	return true;
}

wxIMPLEMENT_APP(App);
