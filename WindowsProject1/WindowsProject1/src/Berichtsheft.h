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
#include <wx/sizer.h>
#include <wx/choice.h>
#include <wx/bmpbuttn.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/calctrl.h>
#include <wx/panel.h>
#include <wx/scrolwin.h>
#include <wx/tglbtn.h>
#include <wx/textctrl.h>
#include <wx/dialog.h>
#include <wx/combobox.h>
#include <wx/listbox.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class PanelBerichtshefteintrag
///////////////////////////////////////////////////////////////////////////////
class PanelBerichtshefteintrag : public wxPanel
{
	private:

	protected:
		wxScrolledWindow* m_scrolledWindow1;
		wxStaticText* m_staticText1;
		wxStaticText* m_staticText3;
		wxChoice* m_choice1;
		wxBitmapButton* m_bpButton3;
		wxStaticText* m_staticText4;
		wxChoice* m_choice2;
		wxStaticText* m_staticText2;
		wxChoice* m_choice3;
		wxBitmapButton* m_bpButton5;
		wxStaticText* m_staticText7;
		wxCalendarCtrl* m_calendar1;
		wxStaticText* m_staticText8;
		wxCalendarCtrl* m_calendar2;
		wxStaticText* m_staticText5;
		wxStaticText* m_staticText12;
		wxPanel* m_panel1;
		wxStaticText* m_staticText6;
		wxStaticText* m_staticText13;
		wxPanel* m_panel2;
		wxToggleButton* btn_speichern;
		wxToggleButton* btn_drucken;

		// Virtual event handlers, override them in your derived class
		virtual void Onbtnabteilungaddclicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void Onbiscalendarchanged( wxCalendarEvent& event ) { event.Skip(); }
		virtual void Onbuttondruckenclicked( wxCommandEvent& event ) { event.Skip(); }


	public:

		PanelBerichtshefteintrag( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 700,750 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );

		~PanelBerichtshefteintrag();

};

///////////////////////////////////////////////////////////////////////////////
/// Class DialogNameAnlegen
///////////////////////////////////////////////////////////////////////////////
class DialogNameAnlegen : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText14;
		wxTextCtrl* eingabe_vorname;
		wxStaticText* m_staticText15;
		wxTextCtrl* eingabe_nachname;
		wxButton* m_button3;
		wxButton* m_button4;

	public:

		DialogNameAnlegen( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Name eintragen"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );

		~DialogNameAnlegen();

};

///////////////////////////////////////////////////////////////////////////////
/// Class PanelTaetigkeit
///////////////////////////////////////////////////////////////////////////////
class PanelTaetigkeit : public wxPanel
{
	private:

	protected:
		wxComboBox* combo_beschreibung_taetigkeit;
		wxComboBox* combo_stunden;
		wxBitmapButton* btn_add_taetigkeit;
		wxBitmapButton* btn_delete_taetigkeit;

		// Virtual event handlers, override them in your derived class
		virtual void Onbuttonaddclicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void Onbuttondeleteclicked( wxCommandEvent& event ) { event.Skip(); }


	public:

		PanelTaetigkeit( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );

		~PanelTaetigkeit();

};

///////////////////////////////////////////////////////////////////////////////
/// Class DialogAbteilungAnlegen
///////////////////////////////////////////////////////////////////////////////
class DialogAbteilungAnlegen : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText16;
		wxTextCtrl* eingabe_abteilung;
		wxButton* m_button5;
		wxButton* m_button6;

	public:

		DialogAbteilungAnlegen( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Abteilung eintragen"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );

		~DialogAbteilungAnlegen();

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
		wxListBox* m_listBox1;
		wxButton* m_button1;
		wxButton* m_button2;

	public:

		Mainframebase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~Mainframebase();

};

