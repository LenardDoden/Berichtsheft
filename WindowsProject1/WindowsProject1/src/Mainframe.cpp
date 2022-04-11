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

   //std::vector<mk::sqlite::result>test;

   _listBoxWoche->Clear();


   for (const auto& i : woche_liste ) {// mehrere Loops hintereinander
      std::stringstream beschreibung;
      beschreibung << i.beginn << "- " << i.ende <<  ", Ausbildungsjahr: " << i.ausbildungsjahr;



	  _listBoxWoche->Append(beschreibung.str(), new DatabaseID{ i.id }); //hier die weiteren werte anfügen 
   }
   

   

   /*
   std::vector<int64_t> test;

   for (const auto& i : berichtsheft_liste)
   {


	   test.push_back(i.id);

	   auto test2 = test;

   }
   */


   /*
   for (const auto& i : berichtsheft_liste) {
	   std::stringstream beschreibung;
	   beschreibung << i.id << i.woche_fk;

	   _listBoxWoche->Append(beschreibung.str(), new DatabaseID{ i.id });
   }
   */
   
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

	auto index = _listBoxWoche->GetSelection();
	auto selectionstring = _listBoxWoche->GetString(index);

	wxClientData* woche_id = _listBoxWoche->GetClientObject(_listBoxWoche->GetSelection());


	//Berichtsheft berichtsheft;
	//berichtsheft.woche_fk = static_cast<DatabaseID*>(woche_id)->id;

	//Woche anhand der Id aus Clientdata
	auto woche_tabelle = WocheTabelle{ *_db };
	auto wochenwerte = woche_tabelle.Load(static_cast<DatabaseID*>(woche_id)->id);

	auto beginnwert = wochenwerte.beginn;
	auto endewert = wochenwerte.ende;
	auto jahrwert = wochenwerte.ausbildungsjahr;
	auto abteilung_fk_wert = wochenwerte.abteilung_fk;

	
	//Abteilung anhand des Foreign Keys aus der Woche Tabelle
	auto abteilung_tabelle = AbteilungTabelle{ *_db };
	auto abteilungwerte = abteilung_tabelle.Load(abteilung_fk_wert);

	auto abteilungnamewert = abteilungwerte.name;


	auto anzahlitems = _listBoxWoche->GetCount();

	 //nach Berichtsheft_id fragen anhand der Wochen_Id
	  
	


	std::vector<int64_t> retBerichtsheftID = {};

	auto resberichtsheftID = mk::sqlite::result{ *_db, R"(
SELECT berichtsheft_id FROM berichtsheft WHERE woche_fk = ?
)", wochenwerte.id };

	while (resberichtsheftID)
	{
		int ii = 0;
		retBerichtsheftID.push_back(resberichtsheftID[ii]);
		++resberichtsheftID;
	}

	int berichtsheftIDAnzahl = retBerichtsheftID.size();

	auto berichtsheft_tabelle = BerichtsheftTabelle{ *_db };



	std::vector<int> auswahlberichtsheftidvector;
	std::vector<int> auswahlberichtsheftminutenvector;
	std::vector<int> auswahlberichtshefttaetigkeitfkvector;
	std::vector<int> auswahlberichtsheftazubifkvector;


	for (int i = 0; i < berichtsheftIDAnzahl; i++)
	{
		auto berichtsheftwerte = berichtsheft_tabelle.Load(retBerichtsheftID[i]);

		auswahlberichtsheftidvector.push_back(berichtsheftwerte.id);
		auswahlberichtsheftminutenvector.push_back(berichtsheftwerte.minuten);
		auswahlberichtshefttaetigkeitfkvector.push_back(berichtsheftwerte.taetigkeit_fk);
		auswahlberichtsheftazubifkvector.push_back(berichtsheftwerte.azubi_fk);
	}

	//Gesammelte Daten
	//Woche: ID, Beginn, Ende, Ausbildungsjahr, Abteilung_fk
	//Abteilung: Id, Name
	//Berichtsheft: Id, Minuten, Taetigkeit_fk, Azubi_fk
	//Azubi: Name
	//Taetigkeit: Beschreibung, Art

	auto azubi_tabelle = AzubiTabelle{ *_db };
	auto azubiwerte = azubi_tabelle.Load(auswahlberichtsheftazubifkvector[0]);
	
	auto taetigkeit_tabelle = TaetigkeitTabelle{ *_db };
	
	std::vector<std::string> auswahltaetigkeitbeschreibungvector;
	std::vector<int> auswahltaetigkeitartvector;
	int anzahltaetigkeiten = auswahlberichtshefttaetigkeitfkvector.size();

	for (int i = 0; i < anzahltaetigkeiten; i++)
	{
		auto taetigkeitswerte = taetigkeit_tabelle.Load(auswahlberichtshefttaetigkeitfkvector[i]);

		auswahltaetigkeitbeschreibungvector.push_back(taetigkeitswerte.beschreibung);
		auswahltaetigkeitartvector.push_back(taetigkeitswerte.art_fk);
	}

	


	//std::vector<std::string> taetigkeitwertebeschreibung;
	//std::vector<int> taetigkeitwerteart_fk;

	//auto taetigkeitwerte = taetigkeit_tabelle.Load

	//auto wochenwerte = woche_tabelle.Load(static_cast<DatabaseID*>(woche_id)->id);
	
	//Berichtsheft anhand der Ids passend zur woche_fk


	auto eintrag = new FrameBerichtshefteintrag(this, *_db);

	

	/*
	for (auto& values : eintrag->bSizer1->GetChildren())

		values.
	*/

	/*
	auto betrieboeffnen = eintrag->_panelBetrieb->GetChildren();
	auto schuleoeffnen = eintrag->_panelSchule->GetChildren();
	*/

	
	//auto ueberschrift = eintrag->GetChildren();

	//ueberschrift.get

	eintrag->m_staticText1->SetLabelText("Test");

	eintrag->Show();

	
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
