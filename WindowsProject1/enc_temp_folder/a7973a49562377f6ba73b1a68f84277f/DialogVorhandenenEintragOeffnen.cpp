#include "DialogVorhandenenEintragOeffnen.h"
#include "../wx/log.h"

DialogVorhandenenEintragOeffnen::DialogVorhandenenEintragOeffnen( wxWindow* parent )
:
DialogVorhandenenEintragOeffnenBase( parent )
{

}

void DialogVorhandenenEintragOeffnen::OnButtonJaVorhandenenBerichtOeffnen( wxCommandEvent& event )
{
// TODO: Implement OnButtonJaVorhandenenBerichtOeffnen
	
	wxLogMessage("Ja geklickt");
	EndModal(1);
}

void DialogVorhandenenEintragOeffnen::OnButtonNeinVorhandenenBErichtNichtOeffnen( wxCommandEvent& event )
{
// TODO: Implement OnButtonNeinVorhandenenBErichtNichtOeffnen
	wxLogMessage("Nein gegklickt");
	EndModal(1);
}
