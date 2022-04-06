#include "Mainframe.h"

#include <wx/stdpaths.h>
#include <wx/log.h>
#include <wx/filefn.h>
#include <wx/filepicker.h>
#include <wx/mimetype.h>
#include <wx/dir.h>

#include <sstream>

#include "FrameBerichtshefteintrag.h"

#include "../../BerichtsheftStructs/Abteilung.h" 
#include "../../BerichtsheftStructs/Art.h" 
#include "../../BerichtsheftStructs/Azubi.h" 
#include "../../BerichtsheftStructs/Berichtsheft.h" 
#include "../../BerichtsheftStructs/Tätigkeit.h" 
#include "../../BerichtsheftStructs/Woche.h" 

#include <regex>

#include "DatabaseID.h"

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
   const auto woche_liste = woche_tabelle.List();

   _listBoxWoche->Clear();
   for (const auto& i : woche_liste) {
      std::stringstream beschreibung;
      beschreibung << i.beginn << "- " << i.ende <<  ", Ausbildungsjahr: " << i.ausbildungsjahr;

	  _listBoxWoche->Append(beschreibung.str(), new DatabaseID{ i.id });
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
	auto index = _listBoxWoche->GetSelection();
	auto selectionstring = _listBoxWoche->GetString(index);


	auto selectionstringstartdatum = selectionstring.SubString(0, 9).ToStdString();
	auto pattern = "\\d{4}\\-\\d{2}\\-\\d{2}";


	if (std::regex_match(selectionstringstartdatum, std::regex(pattern)))
	{

//Woche_id		
		std::vector<std::string> retListDataWoche = {};

		auto resListWoche = mk::sqlite::result{ *_db, R"(
SELECT woche_id FROM Woche WHERE beginn = ?
)", selectionstringstartdatum };

		while (resListWoche)
		{
			int ii = 0;
			retListDataWoche.push_back(resListWoche[ii]);
			++resListWoche;
		}

		wxString anzahlitemsimresultvector;
		wxString woche_id_deserstenitems;
		
		
		auto anzahl = retListDataWoche.size();
		anzahlitemsimresultvector << anzahl;
		
		if (anzahlitemsimresultvector == "1")
		{
			auto erstesitemwochevector = retListDataWoche[0];
			woche_id_deserstenitems << erstesitemwochevector;
			wxLogMessage("Woche_ID = " + woche_id_deserstenitems);

//abteilung_fk

			std::vector<std::string> retListDataWocheAbteilung_fk = {};

			auto resListDataWocheAbteilung_fk = mk::sqlite::result{ *_db, R"(
	SELECT abteilung_fk FROM woche WHERE woche_id = ?
	)", erstesitemwochevector };

			while (resListDataWocheAbteilung_fk)
			{
				int ii = 0;
				retListDataWocheAbteilung_fk.push_back(resListDataWocheAbteilung_fk[0]);
				++resListDataWocheAbteilung_fk;
			}

			auto erstesitemabteilung_fk = retListDataWocheAbteilung_fk[0];

			wxString wx_wocheAbteilung_fk;
			wx_wocheAbteilung_fk << erstesitemabteilung_fk;
			wxLogMessage("Abteilung_Fk = " + wx_wocheAbteilung_fk);


//Abteilung

			std::vector<std::string> retListDataAbteilung = {};

			auto resListDataAbteilung = mk::sqlite::result{ *_db, R"(
	SELECT name FROM abteilung WHERE abteilung_id = ?
	)", erstesitemabteilung_fk };

			while (resListDataAbteilung)
			{
				int ii = 0;
				retListDataAbteilung.push_back(resListDataAbteilung[0]);
				++resListDataAbteilung;
			}

			auto erstesitemabteilung = retListDataAbteilung[0];

			wxString wx_Abteilung;
			wx_Abteilung << erstesitemabteilung;
			wxLogMessage("Abteilung Name = " + wx_Abteilung);

			
//woche_ausbildungsjahr

			std::vector<std::string> retListDataWocheAusbildungsjahr = {};

			auto resListDataWocheAusbildungsjahr = mk::sqlite::result{ *_db, R"(
	SELECT ausbildungsjahr FROM woche WHERE woche_id = ?
	)", erstesitemwochevector };

				while (resListDataWocheAusbildungsjahr)
				{
					int ii = 0;
					retListDataWocheAusbildungsjahr.push_back(resListDataWocheAusbildungsjahr[0]);
					++resListDataWocheAusbildungsjahr;
				}

				auto erstesitemausbildungjahr = retListDataWocheAusbildungsjahr[0];

				wxString wx_woche_ausbildungsjahr;
				wx_woche_ausbildungsjahr << erstesitemausbildungjahr;
				wxLogMessage("Ausbildungsjahr = " + wx_woche_ausbildungsjahr);

//Azubi_FK
			std::vector<std::string> retListDataBerichtsheftAzubi_fk = {};
			
			auto resListDataBerichtsheftAzubi_fk = mk::sqlite::result{ *_db, R"(
	SELECT azubi_fk FROM berichtsheft WHERE woche_fk = ?
	)", erstesitemwochevector };

			while (resListDataBerichtsheftAzubi_fk)
			{
				int ii = 0;
				retListDataBerichtsheftAzubi_fk.push_back(resListDataBerichtsheftAzubi_fk[ii]);
				++resListDataBerichtsheftAzubi_fk;
			}

			auto erstesitemazubi_fk = retListDataBerichtsheftAzubi_fk[0];
			
			wxString azubi_fk_string;
			azubi_fk_string << erstesitemazubi_fk;
			wxLogMessage("Azubi_FK = " + azubi_fk_string);

//Azubi
			std::vector<std::string> retListDataBerichtsheftAzubiVorname = {};
			std::vector<std::string> retListDataBerichtsheftAzubiNachname = {};

			auto resListDataBerichtsheftAzubiVorname = mk::sqlite::result{ *_db, R"(
	SELECT vorname FROM azubi WHERE azubi_id = ?
	)", erstesitemazubi_fk };


			while (resListDataBerichtsheftAzubiVorname)
			{
				int ii = 0;
				retListDataBerichtsheftAzubiVorname.push_back(resListDataBerichtsheftAzubiVorname[ii]);
				++resListDataBerichtsheftAzubiVorname;
			}

			auto vorname = retListDataBerichtsheftAzubiVorname[0];
			wxString wx_vorname;
			wx_vorname << vorname;
			wxLogMessage("Vorname des Azubis: " + wx_vorname);

			auto resListDataBerichtsheftAzubiNachname = mk::sqlite::result{ *_db, R"(
	SELECT nachname FROM azubi WHERE azubi_id = ?
	)", erstesitemazubi_fk };

			while (resListDataBerichtsheftAzubiNachname)
			{
				int ii = 0;
				retListDataBerichtsheftAzubiNachname.push_back(resListDataBerichtsheftAzubiNachname[ii]);
				++resListDataBerichtsheftAzubiNachname;
			}

			auto nachname = retListDataBerichtsheftAzubiNachname[0];
			wxString wx_nachname;
			wx_nachname << nachname;
			wxLogMessage("Nachnamme des Azubis: " + wx_nachname);



			

			
			auto eintrag = new FrameBerichtshefteintrag(this, *_db);
			eintrag->Show();
			

		}

		else if (anzahlitemsimresultvector == "0")
		{
			wxLogMessage("Keine Items im Resultvector");
		}

		

		else
		{
			wxLogMessage("Mehr als ein Item im Resultvector");
		}

	}

	

	else
	{
		wxLogMessage("Das Datum ist nicht im Format YYYY-MM-DD");
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
