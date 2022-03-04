#include "Mainframe.h"
#include <wx/stdpaths.h>
#include <wx/log.h>
#include <wx/filefn.h>


#include "../../BerichtsheftStructs/Abteilung.h" 
#include "../../BerichtsheftStructs/Art.h" 
#include "../../BerichtsheftStructs/Azubi.h" 
#include "../../BerichtsheftStructs/Berichtsheft.h" 
#include "../../BerichtsheftStructs/Tätigkeit.h" 
#include "../../BerichtsheftStructs/Woche.h" 
#include "wx/filepicker.h"
#include "wx/mimetype.h"
#include "wx/dir.h"


Mainframe::Mainframe(wxWindow* parent)
	:
	Mainframebase(parent)
{

	try {
		auto standardpaths = wxStandardPaths::Get();
		auto userdirectory = standardpaths.GetUserDataDir() + ".db";

		wxLogMessage("%s", userdirectory);

		//wxFileName directory_name_ohne_ordner = userdirectory;
		
		//directory_name_ohne_ordner.AppendDir("\\berichtsheft");
		


		bool test = wxFileExists(userdirectory);
		

		//name = wxFileName::DirName(userdirectory);
		//name.SetName("test");
		//name.SetName("Test");


		if (test == true)
		{
			wxLogMessage("%s", "Datei existiert");
		}


		if (test == false)
		{
			auto userdirectorystdstring = userdirectory.ToStdString();
		
			wxLogMessage( "%s", "Der Pfad ist: " + userdirectorystdstring );

			//wxLogMessage("%s", "Datei existiert nicht");
			auto db = mk::sqlite::database{ userdirectorystdstring };

			BerichtsheftTabelle berichtsheft_tabelle(db);
			berichtsheft_tabelle.provision();

			ArtTabelle art_tabelle(db);
			art_tabelle.provision();

			AzubiTabelle azubi_tabelle(db);
			azubi_tabelle.provision();

			TaetigkeitTabelle taetigkeit_tabelle(db);
			taetigkeit_tabelle.provision();

			WocheTabelle woche_tabelle(db);
			woche_tabelle.provision();

			AbteilungTabelle abteilung_tabelle(db);
			abteilung_tabelle.provision();

		}
	}


	catch (std::exception e)
	{
		wxLogMessage(e.what());
	}

}

/*
wxString namevompath = wxFileNameFromPath(userdirectory);
			auto dateiname = wxFileName(namevompath);
			dateiname.SetName("Test");
			dateiname.SetExt(".db");

			dateiname.SetFullName("Test.db");

			auto getname = dateiname.GetName();

*/