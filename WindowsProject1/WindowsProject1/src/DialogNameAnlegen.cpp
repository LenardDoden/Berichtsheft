#include "DialogNameAnlegen.h"
#include <wx/log.h>


DialogNameAnlegen::DialogNameAnlegen( wxWindow* parent )
:
DialogNameAnlegenbase( parent )
{

}

void DialogNameAnlegen::OnOKClicked( wxCommandEvent& event )
{
   bool succes = true;

   const auto nachname = _eingabe_nachname->GetValue();

 

   if (nachname.empty() || nachname.size() > 100) {
      wxLogMessage("%s", "Bitte geben Sie einen gültigen Nachnamen (kleiner 100 Zeichen) ein.");
      succes = false;
   }

   const auto vorname = _eingabe_vorname->GetValue();
   if (vorname.empty() || vorname.size() > 100) {
      wxLogMessage("%s", "Bitte geben Sie einen gültigen Vornamen (kleiner 100 Zeichen) ein.");
      succes = false;
   }

  

   if (succes) {
      event.Skip();
   }
}
