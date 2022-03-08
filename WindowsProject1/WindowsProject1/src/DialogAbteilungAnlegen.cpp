#include "DialogAbteilungAnlegen.h"
#include <wx/log.h>


DialogAbteilungAnlegen::DialogAbteilungAnlegen(wxWindow* parent)
:
DialogAbteilungAnlegenBase(parent)
{

}



void DialogAbteilungAnlegen::OnOKClicked(wxCommandEvent& event)
{

	bool success = true;


	const auto abteilung_name = _eingabe_abteilung->GetValue();


	if (abteilung_name.empty() || abteilung_name.size() > 100) {
		wxLogMessage("%s", "Bitte geben Sie einen gültigen Nachnamen (kleiner 100 Zeichen) ein.");
		success = false;
	}


	if (success) {
		event.Skip();
	}

}




