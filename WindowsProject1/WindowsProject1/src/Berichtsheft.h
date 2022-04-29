///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/sizer.h>
#include <wx/dialog.h>
#include <wx/textctrl.h>
#include <wx/combobox.h>
#include <wx/bmpbuttn.h>
#include <wx/panel.h>
#include <wx/listbox.h>
#include <wx/frame.h>
#include <wx/choice.h>
#include <wx/calctrl.h>
#include <wx/scrolwin.h>
#include <wx/tglbtn.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class DialogVorhandenenEintragOeffnenBase
///////////////////////////////////////////////////////////////////////////////
class DialogVorhandenenEintragOeffnenBase : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText15;
		wxButton* buttonJaVorhandenenBerichtOeffnen;
		wxButton* buttonNeinVorhandenenBerichtNichtOeffnen;

		// Virtual event handlers, override them in your derived class
		virtual void OnButtonJaVorhandenenBerichtOeffnen( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonNeinVorhandenenBErichtNichtOeffnen( wxCommandEvent& event ) { event.Skip(); }


	public:

		DialogVorhandenenEintragOeffnenBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );

		~DialogVorhandenenEintragOeffnenBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class DialogNameAnlegenbase
///////////////////////////////////////////////////////////////////////////////
class DialogNameAnlegenbase : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText14;
		wxStaticText* m_staticText15;
		wxButton* _btnOK;
		wxButton* m_button4;

		// Virtual event handlers, override them in your derived class
		virtual void OnTextVornameChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTextNachnameChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOKClicked( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxTextCtrl* _eingabe_vorname;
		wxTextCtrl* _eingabe_nachname;

		DialogNameAnlegenbase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Name eintragen"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE );

		~DialogNameAnlegenbase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class PanelTaetigkeitbase
///////////////////////////////////////////////////////////////////////////////
class PanelTaetigkeitbase : public wxPanel
{
	private:

	protected:

		// Virtual event handlers, override them in your derived class
		virtual void OnTextComboStundenChanged(wxCommandEvent& event);
		virtual void Onbuttonaddclicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void Onbuttondeleteclicked( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxComboBox* combo_beschreibung_taetigkeit;
		wxComboBox* combo_stunden;
		wxBitmapButton* btn_add_taetigkeit;
		wxBitmapButton* btn_delete_taetigkeit;

		PanelTaetigkeitbase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 480,-1 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );

		~PanelTaetigkeitbase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class DialogAbteilungAnlegenBase
///////////////////////////////////////////////////////////////////////////////
class DialogAbteilungAnlegenBase : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText16;
		wxButton* _btnOk;
		wxButton* m_button6;

		// Virtual event handlers, override them in your derived class
		virtual void OnTextAbteilungChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOKClicked( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxTextCtrl* _eingabe_abteilung;

		DialogAbteilungAnlegenBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Abteilung eintragen"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );

		~DialogAbteilungAnlegenBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class Mainframebase
///////////////////////////////////////////////////////////////////////////////
class Mainframebase : public wxFrame
{
	private:

	protected:
		wxPanel* m_panel3;
		wxStaticText* m_staticText9;
		wxListBox* _listBoxWoche;
		wxButton* _btnNeu;
		wxButton* _btnOeffnen;

		// Virtual event handlers, override them in your derived class
		virtual void OnWocheSelectionChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnWocheDoubleClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonNeu( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonOeffnen( wxCommandEvent& event ) { event.Skip(); }


	public:

		Mainframebase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~Mainframebase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class FrameBerichtshefteintragbase
///////////////////////////////////////////////////////////////////////////////
class FrameBerichtshefteintragbase : public wxFrame
{
	private:

	protected:
		wxScrolledWindow* m_scrolledWindow1;
		wxStaticText* m_staticText3;
		wxBitmapButton* _btnNeuName;
		wxStaticText* m_staticText4;
		wxStaticText* m_staticText2;
		wxBitmapButton* _btnNeuAbteilung;
		wxStaticText* m_staticText7;
		wxStaticText* m_staticText8;
		wxStaticText* m_staticText5;
		wxStaticText* m_staticText12;
		wxStaticText* m_staticText6;
		wxStaticText* m_staticText13;
		wxToggleButton* _btnSpeichern;
		wxToggleButton* _btnDrucken;
		wxToggleButton* _btnLoeschen;

		// Virtual event handlers, override them in your derived class
		virtual void OnButtonNeuName( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonNeuAbteilung( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCalendarVonChanged( wxCalendarEvent& event ) { event.Skip(); }
		virtual void OnCalendarBisChanged( wxCalendarEvent& event ) { event.Skip(); }
		virtual void OnButtonSpeichern( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonDrucken( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonLoeschen( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxBoxSizer* bSizer1;
		wxStaticText* m_staticText1;
		wxChoice* _choiceName;
		wxChoice* _choiceAusbildungsjahr;
		wxChoice* _choiceAbteilung;
		wxCalendarCtrl* _calendarVon;
		wxCalendarCtrl* _calendarBis;
		wxBoxSizer* bSizer7;
		wxPanel* _panelBetrieb;
		wxGridSizer* _betriebtaetigkeitsizer;
		wxGridSizer* gSizer3;
		wxPanel* _panelSchule;
		wxGridSizer* _schultaetigkeitsizer;

		FrameBerichtshefteintragbase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Berichtsheft Eintrag"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 542,650 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~FrameBerichtshefteintragbase();

};

