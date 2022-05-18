#ifndef __FrameBerichtshefteintrag__
#define __FrameBerichtshefteintrag__

/**
@file
Subclass of FrameBerichtshefteintragbase, which is generated by wxFormBuilder.
*/

#include "Berichtsheft.h"
#include "../../mk_sqlite/database.h"
#include "wx/log.h"


//// end generated include


wxDECLARE_EVENT(FrameBerichtshefteintrag_Updated, wxCommandEvent);

/** Implementing FrameBerichtshefteintragbase */
class FrameBerichtshefteintrag : public FrameBerichtshefteintragbase
{
   mk::sqlite::database _db;

   void ResetNameChoice();
   void ResetAbteilungChoice();
   void ResetTaetigkeitBetriebChoice();
   void ResetTaetigkeitSchuleChoice();


   void OnButtonNeuName(wxCommandEvent& event)override;
   void OnButtonNeuAbteilung( wxCommandEvent& event )override;
   void OnCalendarVonChanged(wxCalendarEvent& event)override;
   void OnCalendarBisChanged(wxCalendarEvent& event)override;
   void OnButtonSpeichern(wxCommandEvent& event)override;
   void OnButtonDrucken( wxCommandEvent& event )override;
   void OnButtonLoeschen(wxCommandEvent & event) override;
   void OnButtonUpdaten(wxCommandEvent & event) override;

	public:
		/** Constructor */
		void LoadDataForFrameOeffnen(int64_t id_woche);

		void OnTaetigkeitEntfernen(wxCommandEvent & event);

		void panelbetriebstaetigkeiterstellen();
		void panelschultaetigkeiterstellen();
	
		FrameBerichtshefteintrag(wxWindow* parent, mk::sqlite::database db);
		
	//// end generated class members

		virtual void OnBetriebTaetigkeitErstellen(wxCommandEvent& event);
		virtual void OnBetriebTaetigkeitLoeschen(wxCommandEvent& event);
		virtual void OnSchuleTaetigkeitErstellen(wxCommandEvent& event);
		virtual void OnSchuleTaetigkeitLoeschen(wxCommandEvent& event);


};

#endif // __FrameBerichtshefteintrag__

