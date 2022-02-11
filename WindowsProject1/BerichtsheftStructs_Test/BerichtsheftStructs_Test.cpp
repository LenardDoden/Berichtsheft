#include "pch.h"
#include "CppUnitTest.h"

#include "../BerichtsheftStructs/Abteilung.h"
#include "../BerichtsheftStructs/Azubi.h"
#include "../BerichtsheftStructs/Tätigkeit.h"
#include "../BerichtsheftStructs/Woche.h"
#include "../BerichtsheftStructs/Berichtsheft.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {

			template<> inline std::wstring ToString<long long>(const long long& t) { RETURN_WIDE_STRING(t); }


			template<> inline std::wstring ToString<Abteilung>(const Abteilung& t) { return ToString(t.id) + L" " + ToString(t.name); }
			template<> inline std::wstring ToString<Azubi>(const Azubi& t) { return ToString(t.id) + L" " + ToString(t.vorname) + L" " + ToString(t.nachname); }
			template<> inline std::wstring ToString<Taetigkeit>(const Taetigkeit& t) { return ToString(t.id) + L" " + ToString(t.beschreibung); }
			template<> inline std::wstring ToString<Woche>(const Woche& t) { return ToString(t.id) + L" " + ToString(t.beginn) + L" " + ToString(t.ende) + L" " + ToString(t.ausbildungsjahr) + L" " + ToString(t.abteilung_fk); }
			template<> inline std::wstring ToString<Berichtsheft>(const Berichtsheft& t) { return ToString(t.id) + L" " + ToString(t.minuten) + L" " + ToString(t.woche_fk) + L" " + ToString(t.taetigkeit_fk) + L" " + ToString(t.abteilung_fk) + L" " + ToString(t.azubi_fk); }
	}
}}

namespace BerichtsheftStructsTest 
{
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
			abteilungSupport.name = "Süppört";
			abteilungSupport.id = abteilung_tabelle.Save(abteilungSupport);

			abteilungSupport.name = "Support";
			abteilung_tabelle.Save(abteilungSupport);

			const auto liste = abteilung_tabelle.List();
			Assert::AreEqual(size_t{ 2 }, liste.size());
			Assert::AreEqual(abteilungEntwicklung, liste.at(0));
			Assert::AreEqual(abteilungSupport, liste.at(1));
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
			taetigkeitEntwicklung.id = taetigkeit_tabelle.Save(taetigkeitEntwicklung);

			Taetigkeit taetigkeitSupport;
			taetigkeitSupport.beschreibung = "Testss schreiben";
			taetigkeitSupport.id = taetigkeit_tabelle.Save(taetigkeitSupport);

			taetigkeitSupport.beschreibung = "Tests schreiben";
			taetigkeit_tabelle.Save(taetigkeitSupport);

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
			woche.ausbildungsjahr = 1995;
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

			Woche wocheEntwicklung;
			wocheEntwicklung.beginn = "2022-02-07";
			wocheEntwicklung.id = woche_tabelle.Save(wocheEntwicklung);

			Woche wocheSupport;
			wocheSupport.beginn = "2022-09-09";
			wocheSupport.id = woche_tabelle.Save(wocheSupport);

			wocheSupport.beginn = "2022-02-07";
			woche_tabelle.Save(wocheSupport);

			const auto liste = woche_tabelle.List();
			Assert::AreEqual(size_t{ 2 }, liste.size());
			Assert::AreEqual(wocheEntwicklung, liste.at(0));
			Assert::AreEqual(wocheSupport, liste.at(1));
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

			Berichtsheft berichtsheftEntwicklung;
			berichtsheftEntwicklung.minuten = 22;
			berichtsheftEntwicklung.id = berichtsheft_tabelle.Save(berichtsheftEntwicklung);

			Berichtsheft berichtsheftSupport;
			berichtsheftSupport.minuten = 9;
			berichtsheftSupport.id = berichtsheft_tabelle.Save(berichtsheftSupport);

			berichtsheftSupport.minuten = 2022;
			berichtsheft_tabelle.Save(berichtsheftSupport);

			const auto liste = berichtsheft_tabelle.List();
			Assert::AreEqual(size_t{ 2 }, liste.size());
			Assert::AreEqual(berichtsheftEntwicklung, liste.at(0));
			Assert::AreEqual(berichtsheftSupport, liste.at(1));
		}


	};


}
