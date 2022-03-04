#include "FrameBerichtshefteintrag.h"
#include "DialogNameAnlegen.h"

#include <sstream>

#include "../../BerichtsheftStructs/Azubi.h"

wxDEFINE_EVENT(FrameBerichtshefteintrag_Updated, wxCommandEvent);


FrameBerichtshefteintrag::FrameBerichtshefteintrag( wxWindow* parent, mk::sqlite::database db )
:
FrameBerichtshefteintragbase( parent )
,_db(db)
{

   ResetNameChoice();
}


void FrameBerichtshefteintrag::ResetNameChoice () 
{
   _choiceName->Clear();

   auto azubi_tabelle = AzubiTabelle{_db};

   for (const auto& i : azubi_tabelle.List()) {
      std::stringstream beschreibung;
      beschreibung << i.vorname << " " << i.nachname;
      _choiceName->Insert(beschreibung.str(), 0);
   }

}

void FrameBerichtshefteintrag::OnButtonNeuName(wxCommandEvent & /*event*/) 
{
   DialogNameAnlegen dlg(this);
   if (dlg.ShowModal() == wxID_OK) {
      // TODO: Neuen namen speichern
      auto azubi = Azubi{};
      azubi.vorname = dlg._eingabe_vorname->GetValue();
      azubi.nachname = dlg._eingabe_nachname->GetValue();

      auto azubi_tabelle = AzubiTabelle{_db};
      azubi_tabelle.Save(azubi);

      ResetNameChoice();
   }
}

void FrameBerichtshefteintrag::OnButtonSpeichern(wxCommandEvent & /*event*/) {
   // TODO: speichern
   wxCommandEvent updateEvent(FrameBerichtshefteintrag_Updated);
   wxPostEvent(this, updateEvent);
}
