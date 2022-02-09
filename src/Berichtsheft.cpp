///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "Berichtsheft.h"

#include "pic/add.xpm"
#include "pic/delete.xpm"

///////////////////////////////////////////////////////////////////////////

PanelBerichtshefteintrag::PanelBerichtshefteintrag( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	m_scrolledWindow1 = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow1->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	m_staticText1 = new wxStaticText( m_scrolledWindow1, wxID_ANY, wxT("Ausbildungsnachweis Nr:"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText1->Wrap( -1 );
	m_staticText1->SetFont( wxFont( 18, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true, wxT("Caladea") ) );

	bSizer2->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );


	bSizer9->Add( bSizer2, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText3 = new wxStaticText( m_scrolledWindow1, wxID_ANY, wxT("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	m_staticText3->SetFont( wxFont( 14, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true, wxT("Caladea") ) );

	fgSizer1->Add( m_staticText3, 0, wxALL|wxALIGN_RIGHT, 5 );

	wxArrayString m_choice1Choices;
	m_choice1 = new wxChoice( m_scrolledWindow1, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice1Choices, 0 );
	m_choice1->SetSelection( 0 );
	fgSizer1->Add( m_choice1, 0, wxALL, 5 );

	m_bpButton3 = new wxBitmapButton( m_scrolledWindow1, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|0 );

	m_bpButton3->SetBitmap( wxBitmap( add_xpm ) );
	fgSizer1->Add( m_bpButton3, 0, wxALL, 5 );

	m_staticText4 = new wxStaticText( m_scrolledWindow1, wxID_ANY, wxT("Ausbildungsjahr"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	m_staticText4->SetFont( wxFont( 14, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true, wxT("Caladea") ) );

	fgSizer1->Add( m_staticText4, 0, wxALL|wxALIGN_RIGHT, 5 );

	wxString m_choice2Choices[] = { wxT("1"), wxT("2"), wxT("3") };
	int m_choice2NChoices = sizeof( m_choice2Choices ) / sizeof( wxString );
	m_choice2 = new wxChoice( m_scrolledWindow1, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice2NChoices, m_choice2Choices, 0 );
	m_choice2->SetSelection( 0 );
	fgSizer1->Add( m_choice2, 0, wxALL|wxEXPAND, 5 );


	fgSizer1->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText2 = new wxStaticText( m_scrolledWindow1, wxID_ANY, wxT("Abteilung"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	m_staticText2->SetFont( wxFont( 14, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true, wxT("Caladea") ) );

	fgSizer1->Add( m_staticText2, 0, wxALL|wxALIGN_RIGHT, 5 );

	wxArrayString m_choice3Choices;
	m_choice3 = new wxChoice( m_scrolledWindow1, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice3Choices, 0 );
	m_choice3->SetSelection( 0 );
	fgSizer1->Add( m_choice3, 0, wxALL, 5 );

	m_bpButton5 = new wxBitmapButton( m_scrolledWindow1, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|0 );

	m_bpButton5->SetBitmap( wxBitmap( add_xpm ) );
	fgSizer1->Add( m_bpButton5, 0, wxALL, 5 );


	bSizer5->Add( fgSizer1, 1, wxALIGN_CENTER_HORIZONTAL, 5 );


	bSizer9->Add( bSizer5, 0, wxEXPAND|wxTOP, 20 );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );

	m_staticText7 = new wxStaticText( m_scrolledWindow1, wxID_ANY, wxT("Vom:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	m_staticText7->SetFont( wxFont( 14, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true, wxT("Caladea") ) );

	bSizer10->Add( m_staticText7, 0, wxALL, 5 );

	m_calendar1 = new wxCalendarCtrl( m_scrolledWindow1, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxCAL_SHOW_HOLIDAYS );
	bSizer10->Add( m_calendar1, 0, wxALL, 5 );


	bSizer6->Add( bSizer10, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );

	m_staticText8 = new wxStaticText( m_scrolledWindow1, wxID_ANY, wxT("Bis:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	m_staticText8->SetFont( wxFont( 14, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true, wxT("Caladea") ) );

	bSizer11->Add( m_staticText8, 0, wxALL, 5 );

	m_calendar2 = new wxCalendarCtrl( m_scrolledWindow1, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxCAL_SHOW_HOLIDAYS );
	bSizer11->Add( m_calendar2, 0, wxALL, 5 );


	bSizer6->Add( bSizer11, 1, wxEXPAND, 5 );


	bSizer9->Add( bSizer6, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP, 20 );

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );

	wxGridSizer* gSizer2;
	gSizer2 = new wxGridSizer( 0, 2, 0, 0 );

	m_staticText5 = new wxStaticText( m_scrolledWindow1, wxID_ANY, wxT("Betriebliche Tätigkeiten:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	m_staticText5->SetFont( wxFont( 14, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true, wxT("Caladea") ) );

	gSizer2->Add( m_staticText5, 0, wxALL, 5 );

	m_staticText12 = new wxStaticText( m_scrolledWindow1, wxID_ANY, wxT("Stunden:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	m_staticText12->SetFont( wxFont( 14, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true, wxT("Caladea") ) );

	gSizer2->Add( m_staticText12, 0, wxALL, 5 );


	bSizer7->Add( gSizer2, 0, wxEXPAND, 5 );

	m_panel1 = new wxPanel( m_scrolledWindow1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer7->Add( m_panel1, 0, wxEXPAND | wxALL, 5 );

	wxGridSizer* gSizer3;
	gSizer3 = new wxGridSizer( 0, 2, 0, 0 );

	m_staticText6 = new wxStaticText( m_scrolledWindow1, wxID_ANY, wxT("Schulische Tätigkeiten"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	m_staticText6->SetFont( wxFont( 14, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true, wxT("Caladea") ) );

	gSizer3->Add( m_staticText6, 0, wxALL, 5 );

	m_staticText13 = new wxStaticText( m_scrolledWindow1, wxID_ANY, wxT("Stunden:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	m_staticText13->SetFont( wxFont( 14, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true, wxT("Caladea") ) );

	gSizer3->Add( m_staticText13, 0, wxALL, 5 );


	bSizer7->Add( gSizer3, 0, wxEXPAND, 5 );

	m_panel2 = new wxPanel( m_scrolledWindow1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer7->Add( m_panel2, 0, wxEXPAND | wxALL, 5 );


	bSizer9->Add( bSizer7, 1, wxEXPAND|wxTOP, 20 );


	m_scrolledWindow1->SetSizer( bSizer9 );
	m_scrolledWindow1->Layout();
	bSizer9->Fit( m_scrolledWindow1 );
	bSizer1->Add( m_scrolledWindow1, 1, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer25;
	bSizer25 = new wxBoxSizer( wxHORIZONTAL );

	btn_speichern = new wxToggleButton( this, wxID_ANY, wxT("Speichern"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer25->Add( btn_speichern, 0, wxALL, 5 );

	btn_drucken = new wxToggleButton( this, wxID_ANY, wxT("Drucken"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer25->Add( btn_drucken, 0, wxALL, 5 );


	bSizer1->Add( bSizer25, 0, wxALIGN_CENTER_HORIZONTAL, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	// Connect Events
	m_bpButton5->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelBerichtshefteintrag::Onbtnabteilungaddclicked ), NULL, this );
	m_calendar2->Connect( wxEVT_CALENDAR_SEL_CHANGED, wxCalendarEventHandler( PanelBerichtshefteintrag::Onbiscalendarchanged ), NULL, this );
	btn_drucken->Connect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( PanelBerichtshefteintrag::Onbuttondruckenclicked ), NULL, this );
}

PanelBerichtshefteintrag::~PanelBerichtshefteintrag()
{
	// Disconnect Events
	m_bpButton5->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelBerichtshefteintrag::Onbtnabteilungaddclicked ), NULL, this );
	m_calendar2->Disconnect( wxEVT_CALENDAR_SEL_CHANGED, wxCalendarEventHandler( PanelBerichtshefteintrag::Onbiscalendarchanged ), NULL, this );
	btn_drucken->Disconnect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( PanelBerichtshefteintrag::Onbuttondruckenclicked ), NULL, this );

}

DialogNameAnlegen::DialogNameAnlegen( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer30;
	bSizer30 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer26;
	bSizer26 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer27;
	bSizer27 = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText14 = new wxStaticText( this, wxID_ANY, wxT("Vorname"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	fgSizer2->Add( m_staticText14, 0, wxALL|wxALIGN_RIGHT, 5 );

	eingabe_vorname = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( eingabe_vorname, 0, wxALL, 5 );

	m_staticText15 = new wxStaticText( this, wxID_ANY, wxT("Nachname"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	fgSizer2->Add( m_staticText15, 0, wxALL|wxALIGN_RIGHT, 5 );

	eingabe_nachname = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( eingabe_nachname, 0, wxALL, 5 );


	bSizer27->Add( fgSizer2, 1, wxEXPAND, 5 );


	bSizer26->Add( bSizer27, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer( wxHORIZONTAL );

	m_button3 = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer28->Add( m_button3, 0, wxALL, 5 );

	m_button4 = new wxButton( this, wxID_CANCEL, wxT("Abbrechen"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer28->Add( m_button4, 0, wxALL, 5 );


	bSizer26->Add( bSizer28, 0, wxALIGN_CENTER_HORIZONTAL, 5 );


	bSizer30->Add( bSizer26, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer30 );
	this->Layout();
	bSizer30->Fit( this );

	this->Centre( wxBOTH );
}

DialogNameAnlegen::~DialogNameAnlegen()
{
}

PanelTaetigkeit::PanelTaetigkeit( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxHORIZONTAL );

	combo_beschreibung_taetigkeit = new wxComboBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0, NULL, 0 );
	bSizer16->Add( combo_beschreibung_taetigkeit, 1, wxALL, 5 );

	combo_stunden = new wxComboBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 75,-1 ), 0, NULL, 0 );
	bSizer16->Add( combo_stunden, 0, wxALL, 5 );

	btn_add_taetigkeit = new wxBitmapButton( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|0 );

	btn_add_taetigkeit->SetBitmap( wxBitmap( add_xpm ) );
	bSizer16->Add( btn_add_taetigkeit, 0, wxALL, 5 );

	btn_delete_taetigkeit = new wxBitmapButton( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|0 );

	btn_delete_taetigkeit->SetBitmap( wxBitmap( delete_xpm ) );
	bSizer16->Add( btn_delete_taetigkeit, 0, wxALL, 5 );


	this->SetSizer( bSizer16 );
	this->Layout();
	bSizer16->Fit( this );

	// Connect Events
	btn_add_taetigkeit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelTaetigkeit::Onbuttonaddclicked ), NULL, this );
	btn_delete_taetigkeit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelTaetigkeit::Onbuttondeleteclicked ), NULL, this );
}

PanelTaetigkeit::~PanelTaetigkeit()
{
	// Disconnect Events
	btn_add_taetigkeit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelTaetigkeit::Onbuttonaddclicked ), NULL, this );
	btn_delete_taetigkeit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelTaetigkeit::Onbuttondeleteclicked ), NULL, this );

}

PanelListe::PanelListe( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxVERTICAL );

	m_staticText9 = new wxStaticText( this, wxID_ANY, wxT("Vorhandene Berichte"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	m_staticText9->SetFont( wxFont( 14, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true, wxT("Caladea") ) );

	bSizer18->Add( m_staticText9, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_listBox1 = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer18->Add( m_listBox1, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxHORIZONTAL );

	m_button1 = new wxButton( this, wxID_ANY, wxT("Neu"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer19->Add( m_button1, 0, wxALL, 5 );

	m_button2 = new wxButton( this, wxID_ANY, wxT("Öffnen"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer19->Add( m_button2, 0, wxALL, 5 );


	bSizer18->Add( bSizer19, 0, wxALIGN_CENTER_HORIZONTAL, 5 );


	bSizer17->Add( bSizer18, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer17 );
	this->Layout();
}

PanelListe::~PanelListe()
{
}

DialogAbteilungAnlegen::DialogAbteilungAnlegen( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer34;
	bSizer34 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer35;
	bSizer35 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText16 = new wxStaticText( this, wxID_ANY, wxT("Abteilung"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	bSizer35->Add( m_staticText16, 0, wxALL, 5 );

	eingabe_abteilung = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer35->Add( eingabe_abteilung, 0, wxALL, 5 );


	bSizer34->Add( bSizer35, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer36;
	bSizer36 = new wxBoxSizer( wxHORIZONTAL );

	m_button5 = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer36->Add( m_button5, 0, wxALL, 5 );

	m_button6 = new wxButton( this, wxID_CANCEL, wxT("Abbrechen"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer36->Add( m_button6, 0, wxALL, 5 );


	bSizer34->Add( bSizer36, 1, wxALIGN_CENTER_HORIZONTAL, 5 );


	this->SetSizer( bSizer34 );
	this->Layout();
	bSizer34->Fit( this );

	this->Centre( wxBOTH );
}

DialogAbteilungAnlegen::~DialogAbteilungAnlegen()
{
}
