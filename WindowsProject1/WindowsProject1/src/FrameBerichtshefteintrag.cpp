#include "FrameBerichtshefteintrag.h"
#include "DialogNameAnlegen.h"
#include "DialogAbteilungAnlegen.h"

#include "DatabaseID.h"

#include <sstream>

#include "../../BerichtsheftStructs/Azubi.h"
#include "../../BerichtsheftStructs/Abteilung.h"

#include "../wx/log.h"


wxDEFINE_EVENT(FrameBerichtshefteintrag_Updated, wxCommandEvent);


FrameBerichtshefteintrag::FrameBerichtshefteintrag( wxWindow* parent, mk::sqlite::database db )
:
FrameBerichtshefteintragbase( parent )
,_db(db)
{
	_choiceAusbildungsjahr->SetLabelText("");

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
	  
	  _choiceName->Append(beschreibung.str(), new DatabaseID{ i.id });

   }
}
 
void FrameBerichtshefteintrag::ResetAbteilungChoice()
{
	_choiceAbteilung->Clear();

	auto abteilung_tabelle = AbteilungTabelle{ _db };
	

	for (const auto& i : abteilung_tabelle.List()) {
		std::stringstream beschreibung_abteilung;
		beschreibung_abteilung << i.name;
		
		_choiceAbteilung->Append(beschreibung_abteilung.str(), new DatabaseID{ i.id });

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


	/*
	if (dlg.ShowModal() == wxID_Uebernehmen)
	{
		auto abteilung = Abteilung{};
		abteilung.name = dlg._eingabe_abteilung->GetValue();

		auto abteilung_tabelle = AbteilungTabelle{ _db };
		abteilung_tabelle.Save(abteilung);

		ResetAbteilungChoice();
	}
	*/
	
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

void FrameBerichtshefteintrag::OnCalendarVonChanged(wxCalendarEvent & /*event*/)
{
	auto kalendar_auswahl = _calendarVon->GetDate();
	auto kalender_auswahl_tag = kalendar_auswahl.GetWeekDay();

	wxString tag = std::to_string(kalender_auswahl_tag);

	if (wxAtoi(tag) == 1)
	{
		kalendar_auswahl.Add(wxDateSpan(0, 0, 0, 4));
		_calendarBis->SetDate(kalendar_auswahl);
	}

	else {

		wxLogMessage("%s", "Bitte w�hle einen Montag aus.");
	}

	//wxLogMessage(tag);
}



void FrameBerichtshefteintrag::OnCalendarBisChanged(wxCalendarEvent & /*event*/)
{
	auto kalendar_auswahl = _calendarBis->GetDate();
	auto kalender_auswahl_tag = kalendar_auswahl.GetWeekDay();

	wxString tag = std::to_string(kalender_auswahl_tag);

	if (wxAtoi(tag) == 5)
	{
	
		kalendar_auswahl.Add(wxDateSpan(0, 0, 0, -4));
		_calendarVon->SetDate(kalendar_auswahl);
	}

	else {

		wxLogMessage("%s", "Bitte w�hle einen Freitag aus.");
	}
}


void FrameBerichtshefteintrag::OnButtonSpeichern(wxCommandEvent & /*event*/) {
   // TODO: speichern

   wxCommandEvent updateEvent(FrameBerichtshefteintrag_Updated);
   wxPostEvent(this, updateEvent);


   auto index_Name = _choiceName->GetSelection();
   auto index_Jahr = _choiceAusbildungsjahr->GetSelection();
   auto index_Abteilung = _choiceAbteilung->GetSelection();
   auto datum_von = _calendarVon->GetDate();
   auto datum_bis = _calendarBis->GetDate();

   if (index_Name && index_Jahr && index_Abteilung)
   {
   
   wxClientData* name_Id = _choiceName->GetClientObject(index_Name);
   auto name_Database_ID = static_cast<DatabaseID*>(name_Id)->id;

   DatabaseID jahr_Database_ID = index_Jahr;

   wxClientData* abteilung_Id = _choiceAbteilung->GetClientObject(index_Abteilung);
   auto abteilung_Database_ID = static_cast<DatabaseID*>(abteilung_Id)->id;
   


   //wxClientData* Datum_Client_Von = _calendarVon->GetClientObject(datum_von);

   //wxClientData* Datum_Client_Bis = _calendarBis->

   
   

   //TODO: T�tigkeiten



   //wxString wxstring_Name = std::to_string(index_Name);
   //wxString teststring = std::to_string(name_Database_ID);
   //wxLogMessage(teststring);
   
   
  
   //wxString teststringdrei = std::to_string(abteilung_Database_ID);
   //wxLogMessage(teststringdrei);

   
   
   
   }
   
   else {
	   wxLogError("Nicht alle Felder ausgef�llt");
   }

}



