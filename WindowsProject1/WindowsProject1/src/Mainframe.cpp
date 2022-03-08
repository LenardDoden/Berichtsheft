#include "Mainframe.h"

#include <wx/stdpaths.h>
#include <wx/log.h>
#include <wx/filefn.h>
#include <wx/filepicker.h>
#include <wx/mimetype.h>
#include <wx/dir.h>

#include <sstream>

#include "FrameBerichtshefteintrag.h"

#include "../../BerichtsheftStructs/Abteilung.h" 
#include "../../BerichtsheftStructs/Art.h" 
#include "../../BerichtsheftStructs/Azubi.h" 
#include "../../BerichtsheftStructs/Berichtsheft.h" 
#include "../../BerichtsheftStructs/Tätigkeit.h" 
#include "../../BerichtsheftStructs/Woche.h" 

Mainframe::Mainframe(wxWindow *parent)
   :
   Mainframebase(parent)
{
   const auto userdirectory = wxStandardPaths::Get().GetUserDataDir() + ".db";
   wxLogDebug(__FUNCTION__ " Benutzer Datenbankpfad: %s", userdirectory);

   const bool exist = wxFileExists(userdirectory);
   _db = std::make_unique<mk::sqlite::database>(userdirectory.ToStdString());

   if (!exist) {
      NeueDatenbank();
   }

   ResetWocheListe();
}

void Mainframe::ResetWocheListe () 
{
   auto woche_tabelle = WocheTabelle{*_db};
   const auto woche_liste = woche_tabelle.List();

   wxArrayString list;
   for (const auto& i : woche_liste) {
      std::stringstream beschreibung;
      beschreibung << i.beginn << "- " << i.ende <<  ", " << i.ausbildungsjahr;
      list.Add(beschreibung.str());
   }

   _listBoxWoche->Clear();

   if (!list.empty()) {
      _listBoxWoche->InsertItems(list, 0);
   }
}

void Mainframe::OnWocheUpdated (wxCommandEvent& /*event*/) 
{
   wxLogDebug(__FUNCTION__ " Bericht wurde aktualisiert");
   ResetWocheListe();
}

void Mainframe::OnButtonNeu(wxCommandEvent & /*event*/) 
{ 
   auto eintrag = new FrameBerichtshefteintrag(this, *_db);
   eintrag->Show();
 
   eintrag->Bind(FrameBerichtshefteintrag_Updated, &Mainframe::OnWocheUpdated, this);
}

void Mainframe::NeueDatenbank () 
{
   wxLogDebug(__FUNCTION__ " erzeuge neue Datenbank");

   BerichtsheftTabelle{*_db}.provision();
   ArtTabelle{*_db}.provision();
   AzubiTabelle{*_db}.provision();
   TaetigkeitTabelle{*_db}.provision();
   WocheTabelle{*_db}.provision();
   AbteilungTabelle{*_db}.provision();
}
