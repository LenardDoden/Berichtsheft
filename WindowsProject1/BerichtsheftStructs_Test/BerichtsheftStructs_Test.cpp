#include "pch.h"
#include "CppUnitTest.h"

#include "../BerichtsheftStructs/Abteilung.h"
#include "../BerichtsheftStructs/Azubi.h"
#include "../BerichtsheftStructs/T?tigkeit.h"
#include "../BerichtsheftStructs/Woche.h"
#include "../BerichtsheftStructs/Berichtsheft.h"
#include "../BerichtsheftStructs/Art.h"
#include "../BerichtsheftStructs/ValidationUtility.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {

			template<> inline std::wstring ToString<long long>(const long long& t) { RETURN_WIDE_STRING(t); }


			template<> inline std::wstring ToString<Abteilung>(const Abteilung& t) { return ToString(t.id) + L" " + ToString(t.name); }
			template<> inline std::wstring ToString<Azubi>(const Azubi& t) { return ToString(t.id) + L" " + ToString(t.vorname) + L" " + ToString(t.nachname); }
			template<> inline std::wstring ToString<Taetigkeit>(const Taetigkeit& t) { return ToString(t.id) + L" " + ToString(t.beschreibung); }
			template<> inline std::wstring ToString<Woche>(const Woche& t) { return ToString(t.id) + L" " + ToString(t.beginn) + L" " + ToString(t.ende) + L" " + ToString(t.ausbildungsjahr) + L" " + ToString(t.abteilung_fk); }
			template<> inline std::wstring ToString<Berichtsheft>(const Berichtsheft& t) { return ToString(t.id) + L" " + ToString(t.minuten) + L" " + ToString(t.woche_fk) + L" " + ToString(t.taetigkeit_fk) + L" " + L" " + ToString(t.azubi_fk); }
			template<> inline std::wstring ToString<Art>(const Art& t) { return ToString(t.id) + L" " + ToString(t.name); }
			//template<> inline std::wstring ToString<validationUtility::FailureState>(const validationUtility::FailureState& t) { return ToString(static_cast<int>(t)); }
	}
}}



namespace BerichtsheftStructsTest 
{
	
	TEST_CLASS(TestValidationUtility)
	{
	public:

		TEST_METHOD(IDO_Date_Format_Valid)
		{
			Assert::AreEqual(true, validationUtility::isFormatValid("2022-02-25"));
		}
		

		TEST_METHOD(ISO_Date_Empty)
		{
			Assert::AreEqual(false, validationUtility::isEmpty("2021-02-25"));
		}

		TEST_METHOD(ISODate_In_Range)
		{
			Assert::AreEqual(true, validationUtility::isInRange("2022-12-31"));
		}

		TEST_METHOD(ISODate_LeapYear)
		{
			Assert::AreEqual(true, validationUtility::isLeapYear("2016-05-14"));
		}

		TEST_METHOD(ISODate_InvalidDay_WayToLarge)
		{
			Assert::AreEqual(true, validationUtility::isDayWayToLarge("2016-05-34"));
		}


		TEST_METHOD(ISODate_InvalidMonth_WayToLarge)
		{
			Assert::AreEqual(true, validationUtility::isMonthWayToLarge("2022-15-25"));
		}

		/*
		TEST_METHOD(Random_Invalid)
		{
		}
		*/

	};



	TEST_CLASS(AbteilungTest)
	{
	public:

		AbteilungTabelle Create() {
			auto db = mk::sqlite::database{ ":memory:" };
			AbteilungTabelle abteilung_tabelle(db);
			abteilung_tabelle.provision();
			return abteilung_tabelle;
		}

		
		TEST_METHOD(List_empty)
		{
			auto abteilung_tabelle = Create();
			Assert::AreEqual(size_t{ 0 }, abteilung_tabelle.List().size());
		}

		TEST_METHOD(Insert)
		{
			auto abteilung_tabelle = Create();

			Abteilung abteilung;
			abteilung.name = "Entwicklung";
			Assert::AreEqual(0LL, abteilung.id); // keine id markierung

			abteilung.id = abteilung_tabelle.Save(abteilung);

			Assert::AreNotEqual(0LL, abteilung.id);
			const auto liste = abteilung_tabelle.List();
			Assert::AreEqual(size_t{ 1 }, liste.size());
			Assert::AreEqual(abteilung, liste.at(0));
		}

		TEST_METHOD(Update)
		{
			auto abteilung_tabelle = Create();

			Abteilung abteilungEntwicklung;
			abteilungEntwicklung.name = "Entwicklung";
			abteilungEntwicklung.id = abteilung_tabelle.Save(abteilungEntwicklung);

			Abteilung abteilungSupport;
			abteilungSupport.name = "S?pp?rt";
			abteilungSupport.id = abteilung_tabelle.Save(abteilungSupport);

			abteilungSupport.name = "Support";
			abteilung_tabelle.Save(abteilungSupport);

			const auto liste = abteilung_tabelle.List();
			Assert::AreEqual(size_t{ 2 }, liste.size());
			Assert::AreEqual(abteilungEntwicklung, liste.at(0));
			Assert::AreEqual(abteilungSupport, liste.at(1));

			Assert::AreEqual(abteilungSupport.name, std::string{ "Support" });
		}
	};

	TEST_CLASS(TaetigkeitTest)
	{
	public:

		TaetigkeitTabelle Create() {
			auto db = mk::sqlite::database{ ":memory:" };
			TaetigkeitTabelle taetigkeit_tabelle(db);
			taetigkeit_tabelle.provision();
			return taetigkeit_tabelle;
		}


		TEST_METHOD(List_empty)
		{
			auto taetigkeit_tabelle = Create();
			Assert::AreEqual(size_t{ 0 }, taetigkeit_tabelle.List().size());
		}

		TEST_METHOD(Insert)
		{
			auto taetigkeit_tabelle = Create();

			Taetigkeit taetigkeit;
			taetigkeit.beschreibung = "BerichtsheftStructs testen";
			Assert::AreEqual(0LL, taetigkeit.id); // keine id markierung

			taetigkeit.id = taetigkeit_tabelle.Save(taetigkeit);

			Assert::AreNotEqual(0LL, taetigkeit.id);
			const auto liste = taetigkeit_tabelle.List();
			Assert::AreEqual(size_t{ 1 }, liste.size());
			Assert::AreEqual(taetigkeit, liste.at(0));
		}

		TEST_METHOD(Update)
		{
			auto taetigkeit_tabelle = Create();

			Taetigkeit taetigkeitEntwicklung;
			taetigkeitEntwicklung.beschreibung = "BerichtsheftStructs testen";
			taetigkeitEntwicklung.art_fk = 5;
			taetigkeitEntwicklung.id = taetigkeit_tabelle.Save(taetigkeitEntwicklung);

			Taetigkeit taetigkeitSupport;
			taetigkeitSupport.beschreibung = "Testss schreiben";
			taetigkeitSupport.id = taetigkeit_tabelle.Save(taetigkeitSupport);

			taetigkeitSupport.beschreibung = "Tests schreiben";
			taetigkeit_tabelle.Save(taetigkeitSupport);

			taetigkeitEntwicklung.art_fk = 6;
			taetigkeit_tabelle.Save(taetigkeitEntwicklung);

			const auto liste = taetigkeit_tabelle.List();
			Assert::AreEqual(size_t{ 2 }, liste.size());
			Assert::AreEqual(taetigkeitEntwicklung, liste.at(0));
			Assert::AreEqual(taetigkeitSupport, liste.at(1));
		}

	};


	TEST_CLASS(AzubiTest)
	{
	public:

		AzubiTabelle Create() {
			auto db = mk::sqlite::database{ ":memory:" };
			AzubiTabelle azubi_tabelle(db);
			azubi_tabelle.provision();
			return azubi_tabelle;
		}


		TEST_METHOD(List_empty)
		{
			auto azubi_tabelle = Create();
			Assert::AreEqual(size_t{ 0 }, azubi_tabelle.List().size());
		}

		TEST_METHOD(Insert)
		{
			auto azubi_tabelle = Create();

			Azubi azubi;
			azubi.vorname = "Lenard";
			azubi.nachname = "Doden";
			Assert::AreEqual(0LL, azubi.id);

			azubi.id = azubi_tabelle.Save(azubi);

			Assert::AreNotEqual(0LL, azubi.id);
			const auto liste = azubi_tabelle.List();
			Assert::AreEqual(size_t{ 1 }, liste.size());
			Assert::AreEqual(azubi, liste.at(0));
		}

		TEST_METHOD(Update)
		{
			auto azubi_tabelle = Create();

			Azubi azubiEntwicklung;
			azubiEntwicklung.vorname = "Lenard";
			azubiEntwicklung.id = azubi_tabelle.Save(azubiEntwicklung);

			Azubi azubiSupport;
			azubiSupport.vorname = "Test";
			azubiSupport.id = azubi_tabelle.Save(azubiSupport);

			azubiSupport.vorname = "Max";
			azubi_tabelle.Save(azubiSupport);

			const auto liste = azubi_tabelle.List();
			Assert::AreEqual(size_t{ 2 }, liste.size());
			Assert::AreEqual(azubiEntwicklung, liste.at(0));
			Assert::AreEqual(azubiSupport, liste.at(1));
		}
	};


	TEST_CLASS(WocheTest)
	{
	public:

		WocheTabelle Create() {
			auto db = mk::sqlite::database{ ":memory:" };
			WocheTabelle woche_tabelle(db);
			woche_tabelle.provision();
			return woche_tabelle;
		}


		TEST_METHOD(List_empty)
		{
			auto woche_tabelle = Create();
			Assert::AreEqual(size_t{ 0 }, woche_tabelle.List().size());
		}

		TEST_METHOD(Insert)
		{
			auto woche_tabelle = Create();

			Woche woche;
			woche.beginn = "2022-02-07";
			Assert::AreEqual(0LL, woche.id);

			
			woche.ende = "2022-10-05";
			Assert::AreEqual(0LL, woche.id);
			
			woche.ausbildungsjahr = "2022";
			Assert::AreEqual(0LL, woche.id);

			woche.abteilung_fk = 1;
			Assert::AreEqual(0LL, woche.id);

			woche.id = woche_tabelle.Save(woche);

			Assert::AreNotEqual(0LL, woche.id);
			const auto liste = woche_tabelle.List();
			Assert::AreEqual(size_t{ 1 }, liste.size());
			Assert::AreEqual(woche, liste.at(0));

		}

		TEST_METHOD(Update)
		{
			auto woche_tabelle = Create();

			
			Woche woche1;
			woche1.beginn = "2022-02-07";
			woche1.id = woche_tabelle.Save(woche1);
			

			Woche woche2;
			woche2.beginn = "2022-09-09";
			woche2.ende = "2022-10-05";
			woche2.ausbildungsjahr = "2022";
			woche2.abteilung_fk = 1;
			woche2.id = woche_tabelle.Save(woche2);

			woche2.beginn = "2022-02-07";
			woche2.ende = "2022-11-05";
			woche2.ausbildungsjahr = "2021";
			woche2.abteilung_fk = 2;
			woche_tabelle.Save(woche2);

			const auto liste = woche_tabelle.List();
			Assert::AreEqual(size_t{ 2 }, liste.size());
			Assert::AreEqual(woche1, liste.at(0));
			Assert::AreEqual(woche2, liste.at(1));
		}
	};

	TEST_CLASS(BerichtsheftTest)
	{
	public:

		BerichtsheftTabelle Create() {
			auto db = mk::sqlite::database{ ":memory:" };
			BerichtsheftTabelle berichtsheft_tabelle(db);
			berichtsheft_tabelle.provision();
			return berichtsheft_tabelle;
		}

		TEST_METHOD(List_empty)
		{
			auto berichtsheft_tabelle = Create();
			Assert::AreEqual(size_t{ 0 }, berichtsheft_tabelle.List().size());
		}

		TEST_METHOD(Insert)
		{
			auto berichtsheft_tabelle = Create();

			Berichtsheft berichtsheft;
			berichtsheft.minuten = 22;
			
			Assert::AreEqual(0LL, berichtsheft.id);
			
			berichtsheft.id = berichtsheft_tabelle.Save(berichtsheft);

			Assert::AreNotEqual(0LL, berichtsheft.id);
			const auto liste = berichtsheft_tabelle.List();
			Assert::AreEqual(size_t{ 1 }, liste.size());
			Assert::AreEqual(berichtsheft, liste.at(0));
		}


		TEST_METHOD(Update)

		{
			auto berichtsheft_tabelle = Create();

			Berichtsheft berichtsheft1;
			berichtsheft1.minuten = 22;
			berichtsheft1.azubi_fk = 5;
			berichtsheft1.taetigkeit_fk = 5;
			berichtsheft1.woche_fk = 5;
			berichtsheft1.id = berichtsheft_tabelle.Save(berichtsheft1);

			Berichtsheft berichtsheft2;
			berichtsheft2.minuten = 9;
			berichtsheft2.id = berichtsheft_tabelle.Save(berichtsheft2);

			berichtsheft1.minuten = 25;
			berichtsheft1.azubi_fk = 4;
			berichtsheft1.taetigkeit_fk = 4;
			berichtsheft1.woche_fk = 4;
			berichtsheft_tabelle.Save(berichtsheft1);

			berichtsheft2.minuten = 2022;
			berichtsheft_tabelle.Save(berichtsheft2);

			const auto liste = berichtsheft_tabelle.List();
			Assert::AreEqual(size_t{ 2 }, liste.size());
			Assert::AreEqual(berichtsheft1, liste.at(0));
			Assert::AreEqual(berichtsheft2, liste.at(1));
		}
	};

	TEST_CLASS(ArtTest)
	{
	public:

		ArtTabelle Create() {
			auto db = mk::sqlite::database{ ":memory:" };
			ArtTabelle art_tabelle(db);
			art_tabelle.provision();
			return art_tabelle;
		}


		TEST_METHOD(List_empty)
		{
			auto art_tabelle = Create();
			Assert::AreEqual(size_t{ 0 }, art_tabelle.List().size());
		}

		TEST_METHOD(Insert)
		{
			auto art_tabelle = Create();

			Art art;
			art.name = "Entwicklung";
			Assert::AreEqual(0LL, art.id); // keine id markierung

			art.id = art_tabelle.Save(art);

			Assert::AreNotEqual(0LL, art.id);
			const auto liste = art_tabelle.List();
			Assert::AreEqual(size_t{ 1 }, liste.size());
			Assert::AreEqual(art, liste.at(0));
		}

		TEST_METHOD(Update)
		{
			auto art_tabelle = Create();

			Art artSchule;
			artSchule.name = "Entwicklung";
			artSchule.id = art_tabelle.Save(artSchule);

			Art artBetrieb;

			artBetrieb.name = "S?pp?rt";
			artBetrieb.id = art_tabelle.Save(artBetrieb);

			artBetrieb.name = "Support";
			art_tabelle.Save(artBetrieb);

			const auto liste = art_tabelle.List();
			Assert::AreEqual(size_t{ 2 }, liste.size());
			Assert::AreEqual(artSchule, liste.at(0));
			Assert::AreEqual(artBetrieb, liste.at(1));
		}
	};
}
