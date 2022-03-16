#include "DialogNameAnlegen.h"
#include <wx/log.h>


DialogNameAnlegen::DialogNameAnlegen( wxWindow* parent )
:
DialogNameAnlegenbase( parent )
{
	
}

void DialogNameAnlegen::OnOKClicked( wxCommandEvent& event )
{
   bool succes = true;

   const auto nachname = _eingabe_nachname->GetValue();


   if (nachname.empty() || nachname.size() > 10) {
      wxLogMessage("%s", "Bitte geben Sie einen gültigen Nachnamen (kleiner 100 Zeichen) ein.");
      succes = false;
   }


   const auto vorname = _eingabe_vorname->GetValue();
   if (vorname.empty() || vorname.size() > 10) {
      wxLogMessage("%s", "Bitte geben Sie einen gültigen Vornamen (kleiner 100 Zeichen) ein.");
      succes = false;
   }

  
   if (succes) {
      event.Skip();
   }
}

void DialogNameAnlegen::OnTextVornameChanged(wxCommandEvent & event)
{
	auto eingabe_vorname_feld_text = _eingabe_vorname->GetLineText(0);
	auto laenge_eingabe_vorname_feld_text = eingabe_vorname_feld_text.size();


	if (laenge_eingabe_vorname_feld_text > 10)
	{
		_eingabe_vorname->SetBackgroundColour(*wxRED);
	}

	else
	{
		_eingabe_vorname->SetBackgroundColour(*wxWHITE);
	}


	
}

void DialogNameAnlegen::OnTextNachnameChanged(wxCommandEvent & event)
{

	auto eingabe_nachname_feld_text = _eingabe_nachname->GetLineText(0);
	auto laenge_eingabe_nachname_feld_text = eingabe_nachname_feld_text.size();


	if (laenge_eingabe_nachname_feld_text > 10)
	{
		_eingabe_nachname->SetBackgroundColour(*wxRED);
	}

	else
	{
		_eingabe_nachname->SetBackgroundColour(*wxWHITE);
	}
}
