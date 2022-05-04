#include "DialogVorhandenenEintragOeffnen.h"
#include "../wx/log.h"
#include "FrameBerichtshefteintrag.h"
#include <wx/stdpaths.h>
#include "../../mk_sqlite/database.h"
#include "Berichtsheft.h"

DialogVorhandenenEintragOeffnen::DialogVorhandenenEintragOeffnen( wxWindow* parent, int64_t id)
:
DialogVorhandenenEintragOeffnenBase( parent )

{
	//auto test = id;
}

void DialogVorhandenenEintragOeffnen::OnButtonJaVorhandenenBerichtOeffnen(wxCommandEvent& event)
	
{
// TODO: Implement OnButtonJaVorhandenenBerichtOeffnen
	
	wxLogMessage("Ja geklickt");
	EndModal(1);

	FrameBerichtshefteintrag::maskemitvorhandenemberichtfuellen();

	FrameBerichtshefteintrag::LoadDataForFrameOeffnen()


}

void DialogVorhandenenEintragOeffnen::OnButtonNeinVorhandenenBErichtNichtOeffnen( wxCommandEvent& event )
{
// TODO: Implement OnButtonNeinVorhandenenBErichtNichtOeffnen
	
	wxLogMessage("Nein gegklickt");
	EndModal(1);
}
