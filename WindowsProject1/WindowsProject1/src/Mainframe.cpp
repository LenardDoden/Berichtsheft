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


Mainframe::Mainframe( wxWindow* parent )
:
Mainframebase( parent )
{
	auto standardpaths = wxStandardPaths::Get();

	auto userdirectory = standardpaths.GetUserDataDir();
	
	//TODO: File Extension hinzufügen
	

	//wxFileName name (userdirectory);
	//wxFileTypeInfo info (userdirectory);
	
	//auto filetype = wxFileTypeInfo(info);
	//filetype.AddExtension(".db");


	//std::cout << userdirectory;

	wxLogMessage("%s", userdirectory);


	//m_staticText9->SetLabelText(test);

	bool test = wxDirExists(userdirectory);
	//TODO: Wenn Datei schon existiert gibts ne exception

	if (test == true)
	{
		wxLogMessage("%s", "existiert");
	}

	

	if (test == false)
	{
		auto userdirectorystdstring = userdirectory.ToStdString();

		wxLogMessage("%s", "existiert nicht");
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

		wxString namevompath = wxFileNameFromPath(userdirectory);
		auto dateiname = wxFileName(namevompath);
		dateiname.SetName("Test");
		dateiname.SetExt(".db");

		dateiname.SetFullName("Test.db");

		auto getname = dateiname.GetName();
		wxLogMessage(getname);

		//wxLogMessage("%s", namevompath);


		//auto name = wxFileName(namevompath);
		/*
		name.SetExt(".db");
		//wxLogMessage("%s", namevompath);

		auto fileinfo = wxFileTypeInfo("Berichtsheft");
		fileinfo.AddExtension(".db");
		
		wxFileName name = wxFileName::DirName(userdirectory);
		name.SetName("Test");
		name.SetExt(".db");

		*/
		
		

	}
}
