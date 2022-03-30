#ifndef __DialogAbteilungAnlegen__
#define __DialogAbteilungAnlegen__

/**
@file
Subclass of DialogAbteilungAnlegenBase, which is generated by wxFormBuilder.
*/

#include "Berichtsheft.h"

//// end generated include

/** Implementing DialogAbteilungAnlegenBase */
class DialogAbteilungAnlegen : public DialogAbteilungAnlegenBase
{
	protected:
		// Handlers for DialogNameAnlegenbase events.
		void OnOKClicked(wxCommandEvent& event);
		void OnUebernehmenClicked(wxCommandEvent& event);
		void OnTextAbteilungChanged(wxCommandEvent& event);
		
	public:
		/** Constructor */
		DialogAbteilungAnlegen(wxWindow* parent);
	//// end generated class members
	private:
	
};

#endif // __DialogAbteilungAnlegen__