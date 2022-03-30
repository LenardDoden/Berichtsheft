#include "FrameBerichtshefteintrag.h"
#include "DialogNameAnlegen.h"
#include "DialogAbteilungAnlegen.h"
#include "Mainframe.h"


#include "DatabaseID.h"

#include <sstream>
#include <vector>
#include <string>
#include <regex>


#include "../../BerichtsheftStructs/Azubi.h"
#include "../../BerichtsheftStructs/Abteilung.h"
#include "../../BerichtsheftStructs/Art.h"
#include "../../BerichtsheftStructs/Berichtsheft.h"
#include "../../BerichtsheftStructs/T‰tigkeit.h"
#include "../../BerichtsheftStructs/Woche.h"

#include "../wx/log.h"


wxDEFINE_EVENT(FrameBerichtshefteintrag_Updated, wxCommandEvent);

wxString AbteilungWxString;
wxString VornameWxString;
wxString NachnameWxString;






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



class transaction {
	mk::sqlite::database _db;
	bool _active{true};

public:
	transaction(mk::sqlite::database db) 
   : _db(std::move(db)) 
   {
      mk::sqlite::execute(db, "BEGIN");
	}

	~transaction()
	{
      if (!_active) {
         return;
      }

		try {
         mk::sqlite::execute(_db, "ROLLBACK");
		}
		catch (const std::exception& e) {
         wxLogDebug(__FUNCTION__ " %s", e.what());
		}
	}

	void commit() {
      assert(_active); // comit wurde mehrmals aufgerufen
		mk::sqlite::execute(_db, "COMMIT");
      _active = false;
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
	auto panelbetriebneu = new PanelTaetigkeitbase(_panelBetrieb/*_panelBetrieb*/);

	// TODO :nachvollziehen wie das copy if statement arbeite
	//		dann in die combobox ¸bernehmen 
	//		ResetMethoden f¸r die Comboboxen von Auﬂen


	panelbetriebneu->btn_add_taetigkeit->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameBerichtshefteintrag::OnBetriebTaetigkeitErstellen), NULL, this);
	
	_betriebtaetigkeitsizer->Add(panelbetriebneu, 0, wxEXPAND);
	_betriebtaetigkeitsizer->Fit(panelbetriebneu);
	_betriebtaetigkeitsizer->Show(panelbetriebneu);

}

void FrameBerichtshefteintrag::panelschultaetigkeiterstellen()
{
	auto panelschuleneu = new PanelTaetigkeitbase(_panelSchule/*_panelSchule*/);

	panelschuleneu->btn_add_taetigkeit->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameBerichtshefteintrag::OnSchuleTaetigkeitErstellen), NULL, this);

	_schultaetigkeitsizer->Add(panelschuleneu, 0, wxEXPAND);
	_schultaetigkeitsizer->Fit(panelschuleneu);
	_schultaetigkeitsizer->Show(panelschuleneu);
}


FrameBerichtshefteintrag::FrameBerichtshefteintrag( wxWindow* parent, mk::sqlite::database db )
:
FrameBerichtshefteintragbase( parent )
,_db(db)
{
	_choiceAusbildungsjahr->SetLabelText("");

   ResetNameChoice();
   ResetAbteilungChoice();
  
   panelbetriebstaetigkeiterstellen();
   panelschultaetigkeiterstellen();

   ResetTaetigkeitBetriebChoice();
   ResetTaetigkeitSchuleChoice();

}






void FrameBerichtshefteintrag::ResetNameChoice () 
{
   _choiceName->Clear();


   auto azubi_tabelle = AzubiTabelle{_db};

   for (const auto& i : azubi_tabelle.List()) {
      std::stringstream beschreibung;
      beschreibung << i.vorname << " " << i.nachname;
	  
	  _choiceName->Append(beschreibung.str(), new DatabaseID{ i.id });

	  auto auswahlzahlname = _choiceName->FindString(VornameWxString + " " + NachnameWxString);
	  _choiceName->SetSelection(auswahlzahlname);

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

		auto auswahlzahlabteilung = _choiceAbteilung->FindString(AbteilungWxString);
		_choiceAbteilung->SetSelection(auswahlzahlabteilung);
	}
}

void FrameBerichtshefteintrag::ResetTaetigkeitBetriebChoice()
{
	for (auto& valuesbetrieb : _panelBetrieb->GetChildren())
	{
		const auto panel = static_cast<PanelTaetigkeitbase*>(valuesbetrieb);
		panel->combo_beschreibung_taetigkeit->Clear();
		
		//auto taetigkeitenbetriebanfangspanel = TaetigkeitTabelle{ _db };


		TaetigkeitTabelle taetigkeit_tabelle(_db);
		auto komplettliste = taetigkeit_tabelle.List();
		decltype(komplettliste) vorschlag_tabelle_betrieb;
		std::copy_if(begin(komplettliste), end(komplettliste), std::back_inserter(vorschlag_tabelle_betrieb), [](const auto& o)
		{
			return o.art_fk == 1;
		});

		for (const auto& i : vorschlag_tabelle_betrieb) {

			panel->combo_beschreibung_taetigkeit->Append(i.beschreibung);
		}
	}
}

void FrameBerichtshefteintrag::ResetTaetigkeitSchuleChoice()
{
	for (auto& valuesschule : _panelSchule->GetChildren())
	{
		const auto panel = static_cast<PanelTaetigkeitbase*>(valuesschule);
		panel->combo_beschreibung_taetigkeit->Clear();
		
		panel->combo_stunden->SetValue("1.5");
		
		TaetigkeitTabelle taetigkeit_tabelle(_db);
		auto komplettliste = taetigkeit_tabelle.List();
		decltype(komplettliste) vorschlag_tabelle_schule;
		std::copy_if(begin(komplettliste), end(komplettliste), std::back_inserter(vorschlag_tabelle_schule), [](const auto& o)
		{
			return o.art_fk == 2;
		});


		//auto taetigkeitenschuleanfangspanel = TaetigkeitTabelle{ _db };
		
		for (const auto& i : vorschlag_tabelle_schule) {
			panel->combo_beschreibung_taetigkeit->Append(i.beschreibung);

			
		}
	}
}


void FrameBerichtshefteintrag::OnButtonNeuAbteilung(wxCommandEvent & /*event*/)
{
	DialogAbteilungAnlegen dlg(this);

	if (dlg.ShowModal() == wxID_OK) {
		auto abteilung = Abteilung{};
		abteilung.name = dlg._eingabe_abteilung->GetValue();

		AbteilungWxString = abteilung.name;

		auto abteilung_tabelle = AbteilungTabelle{ _db };
		abteilung_tabelle.Save(abteilung);

		ResetAbteilungChoice();
	}
}


void FrameBerichtshefteintrag::OnButtonNeuName(wxCommandEvent & /*event*/) 
{
   DialogNameAnlegen dlg(this);
   if (dlg.ShowModal() == wxID_OK) {
      // TODO: Neuen Namen speichern
      auto azubi = Azubi{};
      azubi.vorname = dlg._eingabe_vorname->GetValue();
      azubi.nachname = dlg._eingabe_nachname->GetValue();


	  //
	  VornameWxString = azubi.vorname;
	  NachnameWxString = azubi.nachname;

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
		wxLogMessage("%s", "Bitte w‰hle einen Montag aus.");
	}
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

		wxLogMessage("%s", "Bitte w‰hle einen Freitag aus.");
	}
}

void FrameBerichtshefteintrag::OnBetriebTaetigkeitErstellen(wxCommandEvent& event) {
	auto _paneltaetigkeitbetriebneu = new PanelTaetigkeitbase(_panelBetrieb/*_panelSchule*/);
	_betriebtaetigkeitsizer->Add(_paneltaetigkeitbetriebneu,0, wxEXPAND);
	bSizer1->Layout();

	
	//auto taetigkeitenbetrieb = TaetigkeitTabelle{ _db };
	_paneltaetigkeitbetriebneu->combo_beschreibung_taetigkeit->Clear();

	TaetigkeitTabelle taetigkeit_tabelle(_db);
	auto komplettliste = taetigkeit_tabelle.List();
	decltype(komplettliste) vorschlag_tabelle_betrieb;
	std::copy_if(begin(komplettliste), end(komplettliste), std::back_inserter(vorschlag_tabelle_betrieb), [](const auto& o)
	{
		return o.art_fk == 1;
	});

	for (const auto& i : vorschlag_tabelle_betrieb) {

		_paneltaetigkeitbetriebneu->combo_beschreibung_taetigkeit->Append(i.beschreibung);
	}


	//StundenBetrieb Vorschaueintr‰ge
	/*
	auto stundenbetrieb = BerichtsheftTabelle{ _db };
	_paneltaetigkeitbetriebneu->combo_stunden->Clear();

	for (const auto& ii : stundenbetrieb.List()) {

		auto stringminutenbetrieb = std::to_string(ii.minuten);
		_paneltaetigkeitbetriebneu->combo_stunden->Append(stringminutenbetrieb);
	}
	*/

	/*

	TaetigkeitTabelle tabelle(_db);
	auto komplettListe = tabelle.List();
	decltype(komplettListe) schulliste;
	std::copy_if(begin(komplettListe), end(komplettListe), std::back_inserter(schulliste), [](const auto& o) {return o.art_fk == 1; });
	*/

	_paneltaetigkeitbetriebneu->btn_delete_taetigkeit->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameBerichtshefteintrag::OnTaetigkeitEntfernen/*OnBetriebTaetigkeitLoeschen*/), new
	WrapperPanelTaetigkeit(_paneltaetigkeitbetriebneu), this);

	_paneltaetigkeitbetriebneu->btn_add_taetigkeit->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameBerichtshefteintrag::OnBetriebTaetigkeitErstellen), new
	WrapperPanelTaetigkeit(_paneltaetigkeitbetriebneu), this);
}




void FrameBerichtshefteintrag::OnBetriebTaetigkeitLoeschen(wxCommandEvent & event)
{
	_betriebtaetigkeitsizer->Detach(0);
	_betriebtaetigkeitsizer->Layout();
	bSizer1->Layout();
}



void PanelTaetigkeitbase::OnTextComboStundenChanged(wxCommandEvent & event)
{
	auto textcombostunden = PanelTaetigkeitbase::combo_stunden->GetValue();

	std::string regexstring = textcombostunden.ToStdString();

	auto pattern = "\\d+\\.*\\d*";

	if (std::regex_match(regexstring, std::regex(pattern)))
	{
		combo_stunden->SetBackgroundColour(*wxWHITE);
		//wxLogMessage("passt zum Regex");
		wxWindow::Refresh();
	}

	else
	{
		//wxLogMessage("passt nicht zum Regex");
		combo_stunden->SetBackgroundColour(*wxRED);
		wxWindow::Refresh();
	}
}


void FrameBerichtshefteintrag::OnSchuleTaetigkeitErstellen(wxCommandEvent & event)
{
	auto _paneltaetigkeitschuleneu = new PanelTaetigkeitbase(_panelSchule);
	_schultaetigkeitsizer->Add(_paneltaetigkeitschuleneu, 0, wxEXPAND);
	bSizer1->Layout();

	//bisherige Eintr‰ge als Auswahlmˆglichkeit

	//auto taetigkeitenschule = TaetigkeitTabelle{ _db };
	_paneltaetigkeitschuleneu->combo_beschreibung_taetigkeit->Clear();

	TaetigkeitTabelle taetigkeit_tabelle(_db);
	auto komplettliste = taetigkeit_tabelle.List();
	decltype(komplettliste) vorschlag_tabelle_schule;
	std::copy_if(begin(komplettliste), end(komplettliste), std::back_inserter(vorschlag_tabelle_schule), [](const auto& o)
	{
		return o.art_fk == 2;
	});

	for (const auto& i : vorschlag_tabelle_schule) {

		_paneltaetigkeitschuleneu->combo_beschreibung_taetigkeit->Append(i.beschreibung);
	}

	_paneltaetigkeitschuleneu->combo_stunden->SetValue("1.5");


	/*
	auto stundenschule = BerichtsheftTabelle{ _db };
	_paneltaetigkeitschuleneu->combo_stunden->Clear();

	for (const auto& ii : stundenschule.List()) {

		auto stringminutenschule = std::to_string(ii.minuten);
		_paneltaetigkeitschuleneu->combo_stunden->Append(stringminutenschule);
	}
	*/

	

	_paneltaetigkeitschuleneu->btn_delete_taetigkeit->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameBerichtshefteintrag::OnTaetigkeitEntfernen/*OnBetriebTaetigkeitLoeschen*/), new
		WrapperPanelTaetigkeit(_paneltaetigkeitschuleneu), this);

	_paneltaetigkeitschuleneu->btn_add_taetigkeit->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameBerichtshefteintrag::OnSchuleTaetigkeitErstellen), new
		WrapperPanelTaetigkeit(_paneltaetigkeitschuleneu), this);
}



void FrameBerichtshefteintrag::OnSchuleTaetigkeitLoeschen(wxCommandEvent & event)
{
	_schultaetigkeitsizer->Detach(0);
	_schultaetigkeitsizer->Layout();
	bSizer1->Layout();
}

void FrameBerichtshefteintrag::OnButtonDrucken(wxCommandEvent & /*event*/) {

	wxLogMessage("Drucken geklickt");
}


void FrameBerichtshefteintrag::OnButtonSpeichern(wxCommandEvent & /*event*/) {
	

   wxCommandEvent updateEvent(FrameBerichtshefteintrag_Updated);
   wxPostEvent(this, updateEvent);


   auto index_Name = _choiceName->GetSelection();
   auto index_Jahr = _choiceAusbildungsjahr->GetSelection();
   auto index_Abteilung = _choiceAbteilung->GetSelection();
   auto datum_von = _calendarVon->GetDate();
   auto datum_bis = _calendarBis->GetDate();



   if (!(_choiceName->GetSelection() != wxNOT_FOUND
      && _choiceAusbildungsjahr->GetSelection() != wxNOT_FOUND 
      && _choiceAbteilung->GetSelection() != wxNOT_FOUND 
      && _calendarBis->GetDate() != _calendarVon->GetDate())) {

      wxLogError("Nicht alle Felder ausgef¸llt oder 2 mal das Gleiche Datum ausgew‰hlt");
      return;
   }


   transaction trans(_db);

	Woche woche;
	woche.beginn = datum_von.FormatISODate();
	woche.ende = datum_bis.FormatISODate();

	woche.ausbildungsjahr = _choiceAusbildungsjahr->GetString(index_Jahr);
	wxClientData* abteilung_Id = _choiceAbteilung->GetClientObject(index_Abteilung);
	woche.abteilung_fk = static_cast<DatabaseID*>(abteilung_Id)->id;

	WocheTabelle woche_tabelle(_db);


	   

	//woche.id = woche_tabelle.Save(woche);
	   


	Berichtsheft berichtsheft;
	berichtsheft.woche_fk = woche.id;
	wxClientData* name_Id = _choiceName->GetClientObject(index_Name);
	berichtsheft.azubi_fk = static_cast<DatabaseID*>(name_Id)->id;


	BerichtsheftTabelle berichtsheft_tabelle(_db);


	//Anzahl Children 
	   
	/*
	int anzahl_childrenbetrieb = _panelBetrieb->GetChildren().GetCount();
	int anzahl_childrenschule = _panelSchule->GetChildren().GetCount();

	wxString childrenWxBetrieb;
	wxString childrenWxSchule;

	childrenWxBetrieb << anzahl_childrenbetrieb;
	childrenWxSchule << anzahl_childrenschule;

	wxLogMessage(childrenWxBetrieb + childrenWxSchule);
	*/
	

	for (const auto& valuesbetrieb : _panelBetrieb->GetChildren()) {
		const auto panel = static_cast<const PanelTaetigkeitbase*>(valuesbetrieb);
		const auto beschreibung = panel->combo_beschreibung_taetigkeit->GetValue();



		auto stundentext = panel->combo_stunden->GetValue();
		std::string stundentextstdstring = stundentext.ToStdString();
		std::string kommastring = ",";

		double stunden{};

		if (stundentext.find(kommastring) != std::string::npos) {
			wxLogError("Die Stunden des Betriebes konnten nicht in eine Flieﬂkommazahl umgewandelt werden. Bitte nutze statt des Kommas einen Punkt als Dezimaltrennzeichen der Stundenanzahl");
         return;
		}
		else if (!panel->combo_stunden->GetValue().ToDouble(&stunden)) {
			wxLogError("Die Stunden des Betriebes konnten nicht in eine Flieﬂkommazahl umgewandelt werden.");
         return;
		}
		else {
         Taetigkeit taetigkeit;
         taetigkeit.beschreibung = beschreibung;
         taetigkeit.art_fk = 1;
            
         TaetigkeitTabelle taetigkeit_tabelle(_db);
         taetigkeit.id = taetigkeit_tabelle.Save(taetigkeit);

         berichtsheft.taetigkeit_fk = taetigkeit.id;


         Art art;
         art.name = "Betrieb";

         auto art_tabelle = ArtTabelle(_db);
          

         art.id = art_tabelle.Save(art);

         berichtsheft.minuten = stunden * 60;
         berichtsheft_tabelle.Save(berichtsheft);
		}
	}

	for (const auto& valuesschule : _panelSchule->GetChildren()) {
		const auto panel = static_cast<const PanelTaetigkeitbase*>(valuesschule);
		const auto beschreibung = panel->combo_beschreibung_taetigkeit->GetValue();


		//wenn combo_stunden ein Komma enth‰lt, Fehlermeldung und Hinweis auf Punkt als Dezimaltrennzeichen

		auto stundentext = panel->combo_stunden->GetValue();
		std::string stundentextstdstring = stundentext.ToStdString();
		std::string kommastring = ",";

		double stunden{};

		if (stundentext.find(kommastring) != std::string::npos) {
			wxLogError("Die Stunden der Schule konnten nicht in eine Flieﬂkommazahl umgewandelt werden. Bitte nutze statt des Kommas einen Punkt als Dezimaltrennzeichen der Stundenanzahl");
			return;
		}
		else if (!panel->combo_stunden->GetValue().ToDouble(&stunden)) {
			wxLogError("Die Stunden der Schule konnten nicht in eine Flieﬂkommazahl umgewandelt werden");
			return;
		}
		else {
         Taetigkeit taetigkeit;
         taetigkeit.beschreibung = beschreibung;
         taetigkeit.art_fk = 2;

         TaetigkeitTabelle taetigkeit_tabelle(_db);
         taetigkeit.id = taetigkeit_tabelle.Save(taetigkeit);

         berichtsheft.taetigkeit_fk = taetigkeit.id;
          
         Art art;
         art.name = "Schule";

         ArtTabelle art_tabelle(_db);
         art.id = art_tabelle.Save(art);


         berichtsheft.minuten = stunden * 60;
         berichtsheft_tabelle.Save(berichtsheft);
		}
	}

   trans.commit();
}
