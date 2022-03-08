#include "FrameBerichtshefteintrag.h"
#include "DialogNameAnlegen.h"
#include "DialogAbteilungAnlegen.h"

#include <sstream>

#include "../../BerichtsheftStructs/Azubi.h"
#include "../../BerichtsheftStructs/Abteilung.h"

wxDEFINE_EVENT(FrameBerichtshefteintrag_Updated, wxCommandEvent);


FrameBerichtshefteintrag::FrameBerichtshefteintrag( wxWindow* parent, mk::sqlite::database db )
:
FrameBerichtshefteintragbase( parent )
,_db(db)
{

   ResetNameChoice();
   ResetAbteilungChoice();
}


void FrameBerichtshefteintrag::ResetNameChoice () 
{
   _choiceName->Clear();

   auto azubi_tabelle = AzubiTabelle{_db};

   for (const auto& i : azubi_tabelle.List()) {
      std::stringstream beschreibung;
      beschreibung << i.vorname << " " << i.nachname;
      _choiceName->Insert(beschreibung.str(), 0);
   }
}

void FrameBerichtshefteintrag::ResetAbteilungChoice()
{
	_choiceAbteilung->Clear();

	auto abteilung_tabelle = AbteilungTabelle{ _db };

	for (const auto& i : abteilung_tabelle.List()) {
		std::stringstream beschreibung_abteilung;
		beschreibung_abteilung << i.name;
		_choiceAbteilung->Insert(beschreibung_abteilung.str(), 0);
	}
}

void FrameBerichtshefteintrag::OnButtonNeuAbteilung(wxCommandEvent & /*event*/)
{
	DialogAbteilungAnlegen dlg(this);


	//dlg.Show();

	
	if (dlg.ShowModal() == wxID_OK) {
		auto abteilung = Abteilung{};
		abteilung.name = dlg._eingabe_abteilung->GetValue();

		auto abteilung_tabelle = AbteilungTabelle{ _db };
		abteilung_tabelle.Save(abteilung);

		ResetAbteilungChoice();
	}
	
}




void FrameBerichtshefteintrag::OnButtonNeuName(wxCommandEvent & /*event*/) 
{
   DialogNameAnlegen dlg(this);
   if (dlg.ShowModal() == wxID_OK) {
      // TODO: Neuen namen speichern
      auto azubi = Azubi{};
      azubi.vorname = dlg._eingabe_vorname->GetValue();
      azubi.nachname = dlg._eingabe_nachname->GetValue();

      auto azubi_tabelle = AzubiTabelle{_db};
      azubi_tabelle.Save(azubi);

      ResetNameChoice();
   }
}


	/*
	DialogAbteilungAnlegen dlg(this);
	if (dlg.ShowModal() == wxID_OK) {

		//Neue Abteilung anlegen 
		auto abteilung = Abteilung{};
		abteilung.name = dlg._eingabe_abteilung->GetValue();
		
		auto abteilung_tabelle = AbteilungTabelle{ _db };
		abteilung_tabelle.Save(abteilung);

		ResetAbteilungChoice();
	}
}
	*/



void FrameBerichtshefteintrag::OnButtonSpeichern(wxCommandEvent & /*event*/) {
   // TODO: speichern
   wxCommandEvent updateEvent(FrameBerichtshefteintrag_Updated);
   wxPostEvent(this, updateEvent);
}
