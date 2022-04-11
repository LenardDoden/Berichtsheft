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
#include "../../BerichtsheftStructs/Tätigkeit.h"
#include "../../BerichtsheftStructs/Woche.h"

#include "../wx/log.h"
#include "wx/print.h"



wxDEFINE_EVENT(FrameBerichtshefteintrag_Updated, wxCommandEvent);

struct BeschreibungStunde {
	std::string beschreibung;
	std::string stunde;
};

struct Data {
	std::string azubiName;
	std::string ausbildungsjahr;
	std::string abteilung;
	std::string ausbildungswocheVom;
	std::string ausbildungswocheBis;
	std::string ausbildungWoche;
	std::vector<BeschreibungStunde> bspeintragbetrieb;
	std::vector<BeschreibungStunde> bspeintragschule;
	std::string bspeintragbetriebstunden;
	std::string bspeintragschulestunden;
	std::string jahr;
};



wxString AbteilungWxString;
wxString VornameWxString;
wxString NachnameWxString;

class PrinterImpl : public wxPrintout {
public:
	PrinterImpl(std::shared_ptr<Data> data)
		: wxPrintout("Ausdruck")
		, m_data(data)
	{

	}

	


	void GetPageInfo(int* minPage, int* maxPage, int* pageFrom, int* pageTo) override
	{
		*minPage = 1;
		*maxPage = m_maxPage;
		*pageFrom = *minPage;
		*pageTo = *maxPage;
	}

	bool HasPage(int pageNum) override
	{
		return pageNum > 0 && pageNum <= m_maxPage;
	}

	void OnPreparePrinting() override
	{
		wxPrintout::OnPreparePrinting();

		m_maxPage = 1;

		wxSize dpi;
		GetPPIScreen(&dpi.x, &dpi.y);

		constexpr auto ppi_to_ppmm = 1.0 / 25.4;
		m_ppmm.x = dpi.x * ppi_to_ppmm;
		m_ppmm.y = dpi.y * ppi_to_ppmm;
	}

	const wxFont& FontDefault()
	{
		static auto font = wxFont{ 12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Liberation Serif" };
		return font;
	}

	const wxFont& FontKlausel()
	{
		static auto font = wxFont{ 10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Liberation Serif" };
		return font;
	}

	const wxFont& FontBold()
	{
		static auto font = wxFont{ 12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Liberation Serif" };
		return font;
	}

	const wxFont& FontLight()
	{
		static auto font = wxFont{ 10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_THIN, false, "Liberation Serif" };
		return font;
	}

	const wxFont& FontTitle()
	{
		static auto font = wxFont{ 14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Liberation Serif" };
		return font;
	}


	void NewPage()
	{
		cursor = wxPoint{ 0, 0 };

		auto dc = GetDC(); // https://docs.wxwidgets.org/3.0/classwx_d_c.html
		dc->SetPen(*wxBLACK_PEN);
		dc->SetBrush(*wxGREY_BRUSH); // wxTRANSPARENT_BRUSH

		DrawHeader();

		DrawFooter();
	}

	void DrawHeader()
	{
		auto dc = GetDC(); // https://docs.wxwidgets.org/3.0/classwx_d_c.html

		cursor.y = MMToPixelY(15);
		const auto leftMargin = MMToPixelX(15);

		dc->SetFont(FontTitle());


		DrawTextcenter("Ausbildungsnachweis (Woche " + m_data->ausbildungWoche + " - " + m_data->jahr + ")", leftMargin, cursor.y, MMToPixelX(190) - leftMargin);

		cursor.y += dc->GetCharHeight();

		auto laengeunterstrich = dc->GetTextExtent("Ausbildungsnachweis (Woche " + m_data->ausbildungWoche + " - " + m_data->jahr + ")");
		auto laengeunterstrichint = laengeunterstrich.GetWidth();

		dc->DrawLine(cursor.x, cursor.y, cursor.x + laengeunterstrichint, cursor.y);


		const int spalten[] = {
		   leftMargin,
		   leftMargin + MMToPixelX(50),
		   leftMargin + MMToPixelX(95),
		   leftMargin + MMToPixelX(145),
		   leftMargin + MMToPixelX(175)
		};

		cursor.y += dc->GetCharHeight() * 2;

		auto pos3 = MMToPixelX(190);

		dc->DrawLine(leftMargin, cursor.y, pos3, cursor.y);
		dc->DrawLine(leftMargin, cursor.y + dc->GetCharHeight(), pos3, cursor.y + dc->GetCharHeight());
		dc->DrawLine(leftMargin, cursor.y + dc->GetCharHeight() * 2, pos3, cursor.y + dc->GetCharHeight() * 2);
		dc->DrawLine(leftMargin, cursor.y + dc->GetCharHeight() * 3, pos3, cursor.y + dc->GetCharHeight() * 3);
		dc->DrawLine(leftMargin, cursor.y, leftMargin, cursor.y + dc->GetCharHeight() * 3);
		dc->DrawLine(spalten[1], cursor.y, spalten[1], cursor.y + dc->GetCharHeight() * 3);
		dc->DrawLine(spalten[2], cursor.y, spalten[2], cursor.y + dc->GetCharHeight() * 3);
		dc->DrawLine(spalten[3], cursor.y, spalten[3], cursor.y + dc->GetCharHeight() * 3);
		dc->DrawLine(spalten[4], cursor.y, spalten[4], cursor.y + dc->GetCharHeight() * 3);



		dc->SetFont(FontBold());
		dc->DrawText("Name Auszubildende/r:", spalten[0] + 5, cursor.y);
		dc->SetFont(FontDefault());
		dc->DrawText(m_data->azubiName, spalten[1] + 5, cursor.y);
		cursor.y += dc->GetCharHeight() + 5;


		dc->SetFont(FontBold());
		dc->DrawText("Ausbildungsjahr:", spalten[0] + 5, cursor.y);
		dc->DrawText("Ausbildende Abteilung:", spalten[2] + 5, cursor.y);
		dc->SetFont(FontDefault());
		dc->DrawText(m_data->ausbildungsjahr, spalten[1] + 5, cursor.y);
		dc->DrawText(m_data->abteilung, spalten[3] + 5, cursor.y);
		cursor.y += dc->GetCharHeight() + 5;

		dc->SetFont(FontBold());
		dc->DrawText("Ausbildungswoche vom:", spalten[0] + 5, cursor.y);
		dc->DrawText("bis:", spalten[2] + 5, cursor.y);
		dc->SetFont(FontDefault());
		dc->DrawText(m_data->ausbildungswocheVom, spalten[1] + 5, cursor.y);
		dc->DrawText(m_data->ausbildungswocheBis, spalten[3] + 5, cursor.y);
		cursor.y += dc->GetCharHeight();
	}

	void DrawTextcenter(std::string text, int x, int y, int w)
	{
		auto dc = GetDC();
		wxCoord outw;
		wxCoord outh;
		dc->GetTextExtent(text, &outw, &outh);

		dc->DrawText(text, x - outw / 2 + w / 2, y);
		cursor.x = x - outw / 2 + w / 2;
	}

	void drawcontenttable(std::string bezeichnung, std::vector<BeschreibungStunde> daten)
	{
		size_t SplitByWidth(const std::string& text, int width);

		auto dc = GetDC();
		const auto leftMargin = MMToPixelX(15);
		auto pos2 = MMToPixelX(160);
		auto pos3 = MMToPixelX(190);
		wxBrush brush;
		brush.SetColour(204, 204, 204);

		dc->SetBrush(brush);
		dc->DrawRectangle(leftMargin, cursor.y, pos3 - leftMargin, dc->GetCharHeight());

		dc->SetFont(FontBold());

		dc->DrawLine(pos2, cursor.y, pos2, cursor.y + dc->GetCharHeight());

		DrawTextcenter(bezeichnung + ": ", leftMargin, cursor.y, pos2 - leftMargin);
		DrawTextcenter("Stunden:", pos2, cursor.y, pos3 - pos2);

		cursor.y += dc->GetCharHeight();

		dc->SetFont(FontDefault());

		for (auto zeile : daten)
		{
			dc->DrawLine(leftMargin, cursor.y, pos3, cursor.y);

			auto textlaenge = dc->GetTextExtent(zeile.beschreibung);

			gettextlaenge(zeile.beschreibung);

			int splitmaßwidth = 520;
			int splitmaßchar = 80;



			if (textlaenge.GetWidth() > splitmaßwidth)
			{

				auto anzahlzeilen = textlaenge.GetWidth() / splitmaßwidth;

				DrawTextcenter(zeile.stunde, pos2 + 3, cursor.y + dc->GetCharHeight() / 2, pos3 - pos2);

				std::vector<std::string> splitstringvector;


				for (auto i = 0; i < anzahlzeilen + 1; ++i)
				{
					splitstringvector.push_back(zeile.beschreibung.substr(i*splitmaßchar, splitmaßchar));
				}


				std::string austausch;
				std::vector<std::string> austauschvector;
				std::vector<size_t> letzteleerzeilevektor;

				for (auto i = 0; i < anzahlzeilen + 1; ++i)
				{
					auto letzteleerzeile = splitstringvector[i].rfind(" ");
					austausch = splitstringvector[i].substr(letzteleerzeile + 1, splitstringvector[i].length());

					letzteleerzeilevektor.push_back(letzteleerzeile);
					austauschvector.push_back(austausch);
				}

				//letzte zeile löschen
				for (auto i = 0; i < anzahlzeilen; ++i)
				{
					splitstringvector[i].erase(letzteleerzeilevektor[i], splitstringvector[i].length());
				}


				//Austauschvektor in den splitstringvektor
				for (auto u = 0; u < anzahlzeilen; ++u)
				{
					splitstringvector[1].insert(0, austauschvector[u]);
				}


				//vektorinhalt zeichnen
				for (auto x : splitstringvector)
				{
					//draw vectoritems
					dc->DrawText(x, leftMargin + 3, cursor.y + dc->GetCharHeight() / 2);

					dc->DrawLine(leftMargin, cursor.y, leftMargin, cursor.y + dc->GetCharHeight()*1.5);
					dc->DrawLine(pos2, cursor.y, pos2, cursor.y + dc->GetCharHeight()*1.5);
					dc->DrawLine(pos3, cursor.y, pos3, cursor.y + dc->GetCharHeight()*1.5);


					cursor.y += dc->GetCharHeight()*1.5;

					if (cursor.y > 950)
					{

						dc->DrawText("Cursor.Y ist größer als 2", leftMargin + 3, cursor.y + dc->GetCharHeight() / 2);

					}
				}
			}

			else
			{
				dc->DrawText(zeile.beschreibung, leftMargin + 3, cursor.y + dc->GetCharHeight() / 2);

				dc->DrawLine(leftMargin, cursor.y, leftMargin, cursor.y + dc->GetCharHeight()*1.5);
				dc->DrawLine(pos2, cursor.y, pos2, cursor.y + dc->GetCharHeight()*1.5);
				dc->DrawLine(pos3, cursor.y, pos3, cursor.y + dc->GetCharHeight()*1.5);

				DrawTextcenter(zeile.stunde, pos2 + 3, cursor.y + dc->GetCharHeight() / 2, pos3 - pos2);
				cursor.y += dc->GetCharHeight()*1.5;
			}
		}

		dc->DrawLine(leftMargin, cursor.y, pos3, cursor.y);
	}

	void gettextlaenge(wxString string)
	{
		const auto leftMargin = MMToPixelX(15);
		auto dc = GetDC();
		auto textlaenge = dc->GetTextExtent(string);
	}

	void DrawBody()
	{
		auto dc = GetDC();
		cursor.y = MMToPixelX(50);

		cursor.y += dc->GetCharHeight();
		drawcontenttable("Betriebliche Tätigkeiten", m_data->bspeintragbetrieb);
		cursor.y += dc->GetCharHeight();
		drawcontenttable("Schulische Tätigkeiten", m_data->bspeintragschule);
	}

	void DrawFooter()
	{
		auto dc = GetDC();
		const auto leftMargin = MMToPixelX(15);

		cursor.y = MMToPixelY(260);

		dc->SetFont(FontKlausel());

		auto pos2 = leftMargin + MMToPixelX(140);

		dc->DrawText("Durch die nachfolgende Unterschrift wird die Richtigkeit und Vollständigkeit der obigen Angaben bestätigt.", leftMargin, cursor.y);
		cursor.y += dc->GetCharHeight() * 5;

		dc->DrawLine(leftMargin, cursor.y, leftMargin + MMToPixelX(64), cursor.y);
		dc->DrawLine(pos2 - 90, cursor.y, pos2 + MMToPixelX(36), cursor.y);


		dc->SetFont(FontDefault());
		dc->DrawText("Datum, Unterschrift Auszubildende/r", leftMargin, cursor.y);
		dc->DrawText("Datum, Unterschrift Ausbildende/r", pos2 - 90, cursor.y);
	}

	bool OnPrintPage(int pageNum) override
	{
		MapScreenSizeToPaper();

		if (HasPage(pageNum)) {
			NewPage();
			DrawBody();

			return true;
		}

		return false;
	}

private:
	std::shared_ptr<Data> m_data;

	struct PPMM {
		float x;
		float y;
	} m_ppmm{ 0.0, 0.0 };
	int m_maxPage{};

	int MMToPixelX(int mm) const
	{
		return static_cast<int>(mm * m_ppmm.x);
	}

	int MMToPixelY(int mm) const
	{
		return static_cast<int>(mm * m_ppmm.y);
	}

	wxPoint cursor{};
};





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
      mk::sqlite::execute(_db, "BEGIN");
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
	//		dann in die combobox übernehmen 
	//		ResetMethoden für die Comboboxen von Außen


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
   _choiceName->Clear();//choice_name im Frameberichtshefteintrag wird geleert

   auto azubi_tabelle = AzubiTabelle{_db}; //neue Azubitabelle mit Werten aus _db wird erstellt
  
 

   for (const auto& i : azubi_tabelle.List()) {//für alle azubi_ids in azubi_tabelle werden
	   std::stringstream beschreibung;
	   beschreibung << i.vorname << " " << i.nachname; //eine beschreibung aus vor und nachname erstellt

	   _choiceName->Append(beschreibung.str(), new DatabaseID{ i.id }); //und an die _choicename Choicebox angehängt, sowie die id als Clientdata 
	   

	   auto auswahlzahlname = _choiceName->FindString(VornameWxString + " " + NachnameWxString);//der ausgewählte Name wird
	   _choiceName->SetSelection(auswahlzahlname);											   //direkt in der Box selber vorausgewählt

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
		wxLogMessage("%s", "Bitte wähle einen Montag aus.");
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

		wxLogMessage("%s", "Bitte wähle einen Freitag aus.");
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


	//StundenBetrieb Vorschaueinträge
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

	//bisherige Einträge als Auswahlmöglichkeit

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

	//Daten

	BeschreibungStunde Betriebbeschreibungstunde;
	BeschreibungStunde Schulbeschreibungstunde;

	auto nameindex = _choiceName->GetSelection();
	auto namedruck = _choiceName->GetString(nameindex);
	
	auto jahrindex = _choiceAusbildungsjahr->GetSelection();
	auto jahrdruck= _choiceAusbildungsjahr->GetString(jahrindex);

	auto abteilungindex = _choiceAbteilung->GetSelection();
	auto abteilungdruck = _choiceAbteilung->GetString(abteilungindex);

	auto jahrvomdruck = _calendarVon->GetDate();
	auto jahrvomdruckstring = jahrvomdruck.FormatISODate();

	auto jahrbisdruck = _calendarBis->GetDate();
	auto jahrbisdruckstring = jahrbisdruck.FormatISODate();

	auto jahr = jahrvomdruck.GetYear();
	wxString jahrstring;
	jahrstring << jahr;


	//xLogMessage("Drucken geklickt");
	//Druckimpl

	auto data = std::make_shared<Data>();
	auto wochevomjahr = jahrvomdruck.GetWeekOfYear();
	wxString wochevomjahrstring = std::to_string(wochevomjahr);


	for (const auto& valuesbetrieb : _panelBetrieb->GetChildren()) {
		const auto panel = static_cast<const PanelTaetigkeitbase*>(valuesbetrieb);

		const auto beschreibung = panel->combo_beschreibung_taetigkeit->GetValue();
		const auto stundentext = panel->combo_stunden->GetValue();

		/*wxLogMessage(beschreibung);
		wxLogMessage(stundentext);*/

		Betriebbeschreibungstunde.beschreibung = beschreibung;
		Betriebbeschreibungstunde.stunde = stundentext;

		data->bspeintragbetrieb.push_back(Betriebbeschreibungstunde);
		
		//wxLogMessage("test");

	}

	for (const auto& valuesschule : _panelSchule->GetChildren()) {
		const auto panel = static_cast<const PanelTaetigkeitbase*>(valuesschule);

		const auto beschreibung = panel->combo_beschreibung_taetigkeit->GetValue();
		const auto stundentext = panel->combo_stunden->GetValue();

		/*wxLogMessage(beschreibung);
		wxLogMessage(stundentext);*/

		Schulbeschreibungstunde.beschreibung = beschreibung;
		Schulbeschreibungstunde.stunde = stundentext;

		data->bspeintragschule.push_back(Schulbeschreibungstunde);
	}

	
	data->azubiName = namedruck;
	data->ausbildungsjahr = jahrdruck;
	data->abteilung = abteilungdruck;
	data->ausbildungswocheVom = jahrvomdruckstring;
	data->ausbildungswocheBis = jahrbisdruckstring;
	data->ausbildungWoche = wochevomjahrstring;
	data->jahr = jahrstring;
	

	/*wxLogMessage(wxString(data->azubiName));
	wxLogMessage(wxString(data->ausbildungsjahr));
	wxLogMessage(wxString(data->abteilung));
	wxLogMessage(wxString(data->ausbildungswocheVom));
	wxLogMessage(wxString(data->ausbildungswocheBis));
	wxLogMessage(wxString(wochevomjahrstring));
*/
	
	auto printData = new wxPrintData{};
	printData->SetPaperId(wxPAPER_A4);
	printData->SetOrientation(wxPORTRAIT);

	auto preview = new wxPrintPreview{ new PrinterImpl{data}, new PrinterImpl{data}, printData};

	auto frame = new wxPreviewFrame{ preview, this, "Vorschau", wxDefaultPosition, wxSize{800, 600} };
	frame->Center(wxBOTH);
	frame->InitializeWithModality(wxPreviewFrame_WindowModal);
	frame->Show(true);
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

      wxLogError("Nicht alle Felder ausgefüllt oder 2 mal das Gleiche Datum ausgewählt.");
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

	woche.id = woche_tabelle.Save(woche);

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
	
	std::vector<std::string> retArt = {};
	auto resArt = mk::sqlite::result{ _db, R"(
SELECT name FROM art 
)" };
	while (resArt)
	{
		int ii = 0;
		retArt.push_back(resArt[ii]);
		++resArt;
	}


	for (const auto& valuesbetrieb : _panelBetrieb->GetChildren()) {
		const auto panel = static_cast<const PanelTaetigkeitbase*>(valuesbetrieb);
		const auto beschreibung = panel->combo_beschreibung_taetigkeit->GetValue();

		auto stundentext = panel->combo_stunden->GetValue();
		std::string stundentextstdstring = stundentext.ToStdString();
		std::string kommastring = ",";

		double stunden{};

		if (stundentext.find(kommastring) != std::string::npos) {
			wxLogError("Die Stunden des Betriebes konnten nicht in eine Fließkommazahl umgewandelt werden. Bitte nutze statt des Kommas einen Punkt als Dezimaltrennzeichen der Stundenanzahl.");
         return;
		}
		else if (!panel->combo_stunden->GetValue().ToDouble(&stunden)) {
			wxLogError("Die Stunden des Betriebes konnten nicht in eine Fließkommazahl umgewandelt werden.");
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

		
		 if (std::find(retArt.begin(), retArt.end(), "Betrieb") != retArt.end())
		 {
			 //wxLogMessage("Betrieb bereits in Art vorhanden");
		 }


		 else
		 {
			 //wxLogMessage("Betrieb noch nicht in Art vorhanden");
			 art.name = "Betrieb";
			 auto art_tabelle = ArtTabelle(_db);
			 art.id = art_tabelle.Save(art);
		 }



         berichtsheft.minuten = stunden * 60;
         berichtsheft_tabelle.Save(berichtsheft);
		}
	}

	for (const auto& valuesschule : _panelSchule->GetChildren()) {
		const auto panel = static_cast<const PanelTaetigkeitbase*>(valuesschule);
		const auto beschreibung = panel->combo_beschreibung_taetigkeit->GetValue();


		//wenn combo_stunden ein Komma enthält, Fehlermeldung und Hinweis auf Punkt als Dezimaltrennzeichen

		auto stundentext = panel->combo_stunden->GetValue();
		std::string stundentextstdstring = stundentext.ToStdString();
		std::string kommastring = ",";

		double stunden{};

		if (stundentext.find(kommastring) != std::string::npos) {
			wxLogError("Die Stunden der Schule konnten nicht in eine Fließkommazahl umgewandelt werden. Bitte nutze statt des Kommas einen Punkt als Dezimaltrennzeichen der Stundenanzahl.");
			return;
		}
		else if (!panel->combo_stunden->GetValue().ToDouble(&stunden)) {
			wxLogError("Die Stunden der Schule konnten nicht in eine Fließkommazahl umgewandelt werden.");
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

		 if (std::find(retArt.begin(), retArt.end(), "Betrieb") != retArt.end())
		 {
			 //wxLogMessage("Schule bereits in Art vorhanden");
		 }

		 else
		 {
			 //wxLogMessage("Schule noch nicht in Art vorhanden");
			 art.name = "Schule";

			 auto art_tabelle = ArtTabelle(_db);
			 art.id = art_tabelle.Save(art);
		 }

         berichtsheft.minuten = stunden * 60;
         berichtsheft_tabelle.Save(berichtsheft);

		}
	}

   trans.commit();
}
