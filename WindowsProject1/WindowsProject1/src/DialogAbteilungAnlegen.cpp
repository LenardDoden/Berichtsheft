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
		wxLogMessage("%s", "Bitte geben Sie einen gültigen Abteilungsnamen (kleiner 100 Zeichen) ein.");
		success = false;
	}

	if (success) {
		event.Skip();
	}
}

/*
void DialogAbteilungAnlegen::OnUebernehmenClicked(wxCommandEvent & event)
{
	bool success = true;

	const auto abteilung_name = _eingabe_abteilung->GetValue();

	if (abteilung_name.empty() || abteilung_name.size() > 100) {
		wxLogMessage("%s", "Bitte geben Sie einen gültigen Abteilungsnamen (kleiner 100 Zeichen) ein.");
		success = false;
	}


	if (success) {
		event.Skip();
	}
*/

	

	/*
	bool success = true;
	const auto abteilung_name = _eingabe_abteilung->GetValue();

	if (abteilung_name.empty() || abteilung_name.size() > 100)
	{
		wxLogMessage("%s", "Bitte geben Sie einen gültigen Nachnamen (kleiner 100 Zeichen) ein.");
		success = false;
	}

	if (success) {

		uebernehmenevent.Skip();
	}
	
}
	*/

void DialogAbteilungAnlegen::OnTextAbteilungChanged(wxCommandEvent & event)
{
	//TODO Aufgabe
	//auto laenge_abeilung_feld = _eingabe_abteilung->GetValue();
	
	
	auto eingabe_abteilung_feld_text = _eingabe_abteilung->GetLineText(0);
	auto laenge_eingabe_abteilung_feld_text = eingabe_abteilung_feld_text.size();

	_btnOk->SetDefault();


	if (laenge_eingabe_abteilung_feld_text < 1 || laenge_eingabe_abteilung_feld_text > 100)
	{
		_eingabe_abteilung->SetBackgroundColour(*wxRED);

		//wxLogMessage(eingabe_abteilung_feld_text);
	}

	else {
		_eingabe_abteilung->SetBackgroundColour(*wxWHITE);
	}
}

