#include "Mainframe.h"

#include <wx/stdpaths.h>
#include <wx/log.h>
#include <wx/filefn.h>
#include <wx/filepicker.h>
#include <wx/mimetype.h>
#include <wx/dir.h>


#include <sstream>

#include "FrameBerichtshefteintrag.h"
#include "Berichtsheft.h"

#include "../../BerichtsheftStructs/Abteilung.h" 
#include "../../BerichtsheftStructs/Art.h" 
#include "../../BerichtsheftStructs/Azubi.h" 
#include "../../BerichtsheftStructs/Berichtsheft.h" 
#include "../../BerichtsheftStructs/Tätigkeit.h" 
#include "../../BerichtsheftStructs/Woche.h" 

#include "DatabaseID.h"
#include "../../mk_sqlite/result.h"

Mainframe::Mainframe(wxWindow *parent)
   :
   Mainframebase(parent)
{
   const auto userdirectory = wxStandardPaths::Get().GetUserDataDir() + ".db";
   wxLogDebug(__FUNCTION__ " Benutzer Datenbankpfad: %s", userdirectory);

   const bool exist = wxFileExists(userdirectory);
   _db = std::make_unique<mk::sqlite::database>(userdirectory.ToStdString());

   if (!exist) {
      NeueDatenbank();
   }

   ResetWocheListe();
}


void Mainframe::ResetWocheListe () 
{
   auto woche_tabelle = WocheTabelle{*_db};
   const auto woche_liste = woche_tabelle.List();//Vorher Sicherheitupdate machen

   
   auto berichtsheft_tabelle = BerichtsheftTabelle{ *_db };
   const auto berichtsheft_liste = berichtsheft_tabelle.List();

   _listBoxWoche->Clear();


   for (const auto& i : woche_liste ) {// mehrere Loops hintereinander
      std::stringstream beschreibung;
	  wxDateTime test;
	  test.ParseISODate(i.beginn);
	  
      beschreibung << i.beginn << "- " << i.ende <<  ", Ausbildungsjahr: " << i.ausbildungsjahr << ", Woche: " << test.GetWeekOfYear();

	  _listBoxWoche->Append(beschreibung.str(), new DatabaseID{ i.id }); //hier die weiteren werte 
   }
   
}

void Mainframe::OnWocheUpdated (wxCommandEvent& /*event*/) 
{
   wxLogDebug(__FUNCTION__ " Bericht wurde aktualisiert");
   ResetWocheListe();
}



void Mainframe::OnButtonNeu(wxCommandEvent & /*event*/) 
{ 
   auto eintrag = new FrameBerichtshefteintrag(this, *_db);

   eintrag->Show();

   eintrag->Bind(FrameBerichtshefteintrag_Updated, &Mainframe::OnWocheUpdated, this);
}


void Mainframe::OnButtonOeffnen(wxCommandEvent & /*event*/)
{

	auto eintrag = new FrameBerichtshefteintrag(this, *_db);

	
	if (_listBoxWoche->GetCount() > 0)

	{
		auto selection = _listBoxWoche->GetSelection();
		
		if (selection != wxNOT_FOUND)
		{
			auto index = _listBoxWoche->GetSelection();
			auto selectionstring = _listBoxWoche->GetString(index);

			wxClientData* woche_id = _listBoxWoche->GetClientObject(_listBoxWoche->GetSelection());

			//Id anhand der Id 
			auto woche_tabelle = WocheTabelle{ *_db };
			auto wochenwerte = woche_tabelle.Load(static_cast<DatabaseID*>(woche_id)->id);

			// ID an Funktion übergeben
			auto wochen_id_weitergabe = wochenwerte.id;
			
			//Funktion um Daten einzutragen
			eintrag->LoadDataForFrameOeffnen(wochen_id_weitergabe);

			eintrag->Show();
		}
		
		else
		{
			wxLogMessage("Kein Bericht ausgewählt");
		}
	}

	else {
		wxLogMessage("Es wurde noch kein Bericht angelegt");
	}
}


void Mainframe::NeueDatenbank () 
{
   wxLogDebug(__FUNCTION__ " erzeuge neue Datenbank");

   BerichtsheftTabelle{*_db}.provision();
   ArtTabelle{*_db}.provision();
   AzubiTabelle{*_db}.provision();
   TaetigkeitTabelle{*_db}.provision();
   WocheTabelle{*_db}.provision();
   AbteilungTabelle{*_db}.provision();
}
