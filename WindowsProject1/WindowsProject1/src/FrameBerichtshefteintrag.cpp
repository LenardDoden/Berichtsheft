#include "FrameBerichtshefteintrag.h"
#include "DialogNameAnlegen.h"
#include "DialogAbteilungAnlegen.h"
#include "Mainframe.h"


#include "DatabaseID.h"

#include <sstream>
#include <vector>


#include "../../BerichtsheftStructs/Azubi.h"
#include "../../BerichtsheftStructs/Abteilung.h"
#include "../../BerichtsheftStructs/Art.h"
#include "../../BerichtsheftStructs/Berichtsheft.h"
#include "../../BerichtsheftStructs/Tätigkeit.h"
#include "../../BerichtsheftStructs/Woche.h"

#include "../wx/log.h"


wxDEFINE_EVENT(FrameBerichtshefteintrag_Updated, wxCommandEvent);



class WrapperPanelTaetigkeit : public wxObject {
	PanelTaetigkeitbase* _panelTaetigkeit;

public:

	explicit WrapperPanelTaetigkeit(PanelTaetigkeitbase* panelTaetigkeit)
		: _panelTaetigkeit(panelTaetigkeit)

	{

	}

	PanelTaetigkeitbase* Get() const
	{
		return _panelTaetigkeit;
	}
};


void FrameBerichtshefteintrag::OnTaetigkeitEntfernen(wxCommandEvent& event)
{
	const WrapperPanelTaetigkeit* wrapper = static_cast<WrapperPanelTaetigkeit*>(event.GetEventUserData());
	PanelTaetigkeitbase* panel = wrapper->Get();
	const wxWindow* panelTaetigkeit = panel->GetParent();

	if (panelTaetigkeit->GetChildren().size() <= 1) {
		return;
	}

	panel->Destroy();
	Layout();
}


void FrameBerichtshefteintrag::panelbetriebstaetigkeiterstellen()
	
{
	//_panelBetrieb = new PanelTaetigkeitbase;
	// this
	//_panelBetrieb

	auto panelbetriebneu = new PanelTaetigkeitbase(_panelBetrieb/*_panelBetrieb*/);

	
	panelbetriebneu->btn_add_taetigkeit->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameBerichtshefteintrag::OnBetriebTaetigkeitErstellen), NULL, this);
	//panelbetriebneu->btn_delete_taetigkeit->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameBerichtshefteintrag::OnBetriebTaetigkeitLoeschen), NULL, this);

	//panelbetriebneu->btn_add_taetigkeit->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameBerichtshefteintrag::OnSchuleTaetigkeitErstellen), NULL, this);
	//panelbetriebneu->btn_delete_taetigkeit->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameBerichtshefteintrag::OnSchuleTaetigkeitLoeschen), NULL, this);


	_betriebtaetigkeitsizer->Add(panelbetriebneu, 0, wxEXPAND);
	_betriebtaetigkeitsizer->Fit(panelbetriebneu);
	_betriebtaetigkeitsizer->Show(panelbetriebneu);


}

void FrameBerichtshefteintrag::panelschultaetigkeiterstellen()
{

	auto panelschuleneu = new PanelTaetigkeitbase(_panelSchule/*_panelSchule*/);

	panelschuleneu->btn_add_taetigkeit->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameBerichtshefteintrag::OnSchuleTaetigkeitErstellen), NULL, this);
	
	//panelschuleneu->btn_delete_taetigkeit->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameBerichtshefteintrag::OnSchuleTaetigkeitLoeschen), NULL, this);

	_schultaetigkeitsizer->Add(panelschuleneu, 0, wxEXPAND);
	_schultaetigkeitsizer->Fit(panelschuleneu);
	_schultaetigkeitsizer->Show(panelschuleneu);
	
	
	//_schultaetigkeitsizer->Add();
}

FrameBerichtshefteintrag::FrameBerichtshefteintrag( wxWindow* parent, mk::sqlite::database db )
:
FrameBerichtshefteintragbase( parent )
,_db(db)
{
	_choiceAusbildungsjahr->SetLabelText("");

   ResetNameChoice();
   ResetAbteilungChoice();
   
  //TODO: Batrieb und Schultätigkeiten Panele einfügen

   panelbetriebstaetigkeiterstellen();
   panelschultaetigkeiterstellen();
   
   
  
  //PanelTaetigkeitbase::panelbetriebstaetigkeiterstellen(wxWindow* parent);
   //PanelTaetigkeitbase::panelschultaetigkeiterstellen(wxWindow* parent);

  
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

		wxLogMessage("%s", "Bitte wähle einen Montag aus.");
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

		wxLogMessage("%s", "Bitte wähle einen Freitag aus.");
	}
}

void FrameBerichtshefteintrag::OnBetriebTaetigkeitErstellen(wxCommandEvent& event) {
	auto _paneltaetigkeitbetriebneu = new PanelTaetigkeitbase(_panelBetrieb/*_panelSchule*/);
	_betriebtaetigkeitsizer->Add(_paneltaetigkeitbetriebneu,0, wxEXPAND);
	//bSizer7->Layout();
	bSizer1->Layout();

	_paneltaetigkeitbetriebneu->btn_delete_taetigkeit->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameBerichtshefteintrag::OnTaetigkeitEntfernen/*OnBetriebTaetigkeitLoeschen*/), new
	WrapperPanelTaetigkeit(_paneltaetigkeitbetriebneu), this);

	_paneltaetigkeitbetriebneu->btn_add_taetigkeit->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameBerichtshefteintrag::OnBetriebTaetigkeitErstellen), new
	WrapperPanelTaetigkeit(_paneltaetigkeitbetriebneu), this);
}

void FrameBerichtshefteintrag::OnBetriebTaetigkeitLoeschen(wxCommandEvent & event)
{
	//wxLogMessage("Hallo test BetriebLoeschen");
	//auto count = _betriebtaetigkeitsizer->GetItemCount();
	_betriebtaetigkeitsizer->Detach(0);
	_betriebtaetigkeitsizer->Layout();
	//bSizer7->Layout();
	bSizer1->Layout();
}

void FrameBerichtshefteintrag::OnSchuleTaetigkeitErstellen(wxCommandEvent & event)
{
	//wxLogMessage("Hallo test SchuleErstellen");
	auto _paneltaetigkeitschuleneu = new PanelTaetigkeitbase(_panelSchule);
	_schultaetigkeitsizer->Add(_paneltaetigkeitschuleneu, 0, wxEXPAND);
	//bSizer7->Layout();
	bSizer1->Layout();

	_paneltaetigkeitschuleneu->btn_delete_taetigkeit->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameBerichtshefteintrag::OnTaetigkeitEntfernen/*OnBetriebTaetigkeitLoeschen*/), new
		WrapperPanelTaetigkeit(_paneltaetigkeitschuleneu), this);

	_paneltaetigkeitschuleneu->btn_add_taetigkeit->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameBerichtshefteintrag::OnSchuleTaetigkeitErstellen), new
		WrapperPanelTaetigkeit(_paneltaetigkeitschuleneu), this);

	
}

void FrameBerichtshefteintrag::OnSchuleTaetigkeitLoeschen(wxCommandEvent & event)
{
	//wxLogMessage("Hallo test schuleLoeschen");
	_schultaetigkeitsizer->Detach(0);
	_schultaetigkeitsizer->Layout();
	//bSizer7->Layout();
	bSizer1->Layout();

	
}



//_betriebtaetigkeitsizer->Layout();
//_schultaetigkeitsizer->Layout();
//wxLogMessage("Hallo test BetriebErstellen");


void FrameBerichtshefteintrag::OnButtonSpeichern(wxCommandEvent & /*event*/) {
	

   wxCommandEvent updateEvent(FrameBerichtshefteintrag_Updated);
   wxPostEvent(this, updateEvent);

   auto index_Name = _choiceName->GetSelection();
   auto index_Jahr = _choiceAusbildungsjahr->GetSelection();
   auto index_Abteilung = _choiceAbteilung->GetSelection();
   auto datum_von = _calendarVon->GetDate();
   auto datum_bis = _calendarBis->GetDate();




   std::vector<std::string> taetigkeitbetriebvector;
   std::vector<std::string> stundenbetriebvector;
   std::vector<std::string> taetigkeitschulevector;
   std::vector<std::string> stundenschulevector;

   auto taetigkeitsbeschreibungen = mk::sqlite::result{ _db, R"(
		SELECT beschreibung FROM taetigkeit)" };

   while (taetigkeitsbeschreibungen)
   {
	   int index = 0;
	   taetigkeitbetriebvector.push_back(taetigkeitsbeschreibungen[index]);
	   ++taetigkeitsbeschreibungen;
   }




   if (taetigkeitbetriebvector.size() > 0)
   {
	   for (auto& valuesbetrieb : _panelBetrieb->GetChildren())
	   {
		   int index = 0;
		   const auto panel = static_cast<PanelTaetigkeitbase*>(valuesbetrieb);
		   panel->combo_beschreibung_taetigkeit->Append(taetigkeitbetriebvector[index]);
		   ++index;
	   }
   }
   

   //Anzahl der Items 

   auto groessevector = taetigkeitbetriebvector.size();

   std::string groessevectorstring;
   std::stringstream zahlstream;
   zahlstream << groessevector;
   zahlstream >> groessevectorstring;
   wxString wxgroessevector(groessevectorstring);
   wxLogMessage(wxgroessevector);

   


   if (index_Name && index_Jahr && index_Abteilung)
   {
	   Woche woche;
	   woche.beginn = datum_von.FormatISODate();
	   woche.ende = datum_bis.FormatISODate();
	   woche.ausbildungsjahr = index_Jahr;

	   wxClientData* abteilung_Id = _choiceAbteilung->GetClientObject(index_Abteilung);
	   woche.abteilung_fk = static_cast<DatabaseID*>(abteilung_Id)->id;

	   WocheTabelle woche_tabelle(_db);
	   woche.id = woche_tabelle.Save(woche);

	   
	   Berichtsheft berichtsheft;
	   berichtsheft.woche_fk = woche.id;

	   wxClientData* name_Id = _choiceName->GetClientObject(index_Name);
	   berichtsheft.azubi_fk = static_cast<DatabaseID*>(name_Id)->id;

	   
	   BerichtsheftTabelle berichtsheft_tabelle(_db);

	   


	  /* wxClientData* name_Id = _choiceName->GetClientObject(index_Name);
	   auto name_Database_ID = static_cast<DatabaseID*>(name_Id)->id;
	   DatabaseID jahr_Database_ID = index_Jahr;

	   auto nameInhalt = _choiceName->GetString(index_Name);
	   auto jahrInhalt = _choiceAusbildungsjahr->GetString(index_Jahr);
	   auto abteilungInhalt = _choiceAbteilung->GetString(index_Abteilung);*/
	   
	

	   //TODO: Values in die Datenbank eintragen


	  



	   for (auto& valuesbetrieb : _panelBetrieb->GetChildren())
	   {

		   const auto panel = static_cast<PanelTaetigkeitbase*>(valuesbetrieb);
		   const auto beschreibung = panel->combo_beschreibung_taetigkeit->GetValue();

		   
		   //TaetigkeitTabelle taetigkeit_tabelle(_db);

		   /*auto alleTaetigkeiten = mk::sqlite::result{ _db, R"(
		SELECT bescreibung FROM taetigkeit)" };*/

	




		   auto count = panel->combo_beschreibung_taetigkeit->GetCount();
		   berichtsheft.taetigkeit_fk = count + 1;

		  

		 

			//panel->combo_beschreibung_taetigkeit->Insert

		   //id der Beschreibung
		   //alle in die combobox eintragen und dann über den Index
		   //berichtsheft.taetigkeit_fk = 

		   double stunden{};

		   if (!panel->combo_stunden->GetValue().ToDouble(&stunden))
		   {
			   wxLogError("Die Stunden des Betriebes konnten nicht in eine Fließkomazahl umgewandelt werden");
		   }

		   berichtsheft.minuten = stunden * 60;

		   berichtsheft_tabelle.Save(berichtsheft);

	   }


	   for (auto& valuesschule : _panelSchule->GetChildren())
	   {

		   const auto panel = static_cast<PanelTaetigkeitbase*>(valuesschule);

		   const auto beschreibung = panel->combo_beschreibung_taetigkeit->GetValue();

		   //id der Beschreibung
		   // berichtsheft.taetigkeit_fa

		   double stunden{};

		   if (!panel->combo_stunden->GetValue().ToDouble(&stunden))
		   {
			   wxLogError("Die Stunden der Schule konnten nicht in eine Fließkommazahl umgewandelt werden");

		   }
			


		   berichtsheft.minuten = stunden * 60;

		   berichtsheft_tabelle.Save(berichtsheft);

	   }
   }
   
   else {
	   wxLogError("Nicht alle Felder ausgefüllt");
   }

}
		   /*auto valuestaetigkeitenbetrieb = static_cast<PanelTaetigkeitbase*>(valuesbetrieb)->combo_beschreibung_taetigkeit->GetValue();
		   auto valuesstundenbetrieb = static_cast<PanelTaetigkeitbase*>(valuesbetrieb)->combo_stunden->GetValue();
		   
		   taetigkeitbetriebvector.push_back(valuestaetigkeitenbetrieb);
		   stundenbetriebvector.push_back(valuesstundenbetrieb);*/


		   //wxLogMessage(valuestundenbetrieb);
	   



	   /*
	   for (auto& valuestundentaetigkeit : _panelBetrieb->GetChildren())
	   {
			static_cast<PanelTaetigkeitbase*>(valuestundentaetigkeit)->combo_stunden->GetValue();
	   }
	   */


	   /*
	   for (auto& valuesschule : _panelSchule->GetChildren())
	   {
		   auto valuestaetigkeitschule = static_cast<PanelTaetigkeitbase*>(valuesschule)->combo_beschreibung_taetigkeit->GetValue();
		   auto valuesstundenschule = static_cast<PanelTaetigkeitbase*>(valuesschule)->combo_stunden->GetValue();

		   taetigkeitschulevector.push_back(valuestaetigkeitschule);
		   stundenschulevector.push_back(valuesstundenschule);


		   //wxLogMessage(valuestaetigkeitschule);
		   //wxLogMessage(valuesstundenschule);
	   }

	   */

	  


	   /*
	   for (auto& valuestundenbetrieb : _panelSchule->GetChildren())
	   {
		   static_cast<PanelTaetigkeitbase*>(valuestundenbetrieb)->combo_stunden->GetValue();
	   }
	   */
			   
	   










	   //wxWindowList 
	   // static cast pointer um auf member zugreifen zu können

	   //if (panelInhalt.size() > 0)
		//   wxLogMessage("hallo");


	   //auto abteilungInhalt = _choiceAbteilung->



	   //wxLogMessage(nameInhalt);
	   //wxLogMessage(jahrInhalt);
	   //wxLogMessage(abteilungInhalt);


		// _calendarVon->GetClientObject(datum_von);
	   //wxClientData* Datum_Client_Bis = _calendarBis->

	   //TODO: Tätigkeiten

	   //wxString wxstring_Name = std::to_string(index_Name);
	   //wxString teststring = std::to_string(name_Database_ID);
	   //wxLogMessage(teststring);

	   //wxString teststringdrei = std::to_string(abteilung_Database_ID);
	   //wxLogMessage(teststringdrei);



