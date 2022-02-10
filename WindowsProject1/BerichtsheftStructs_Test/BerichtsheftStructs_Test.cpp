#include "pch.h"
#include "CppUnitTest.h"

#include "../BerichtsheftStructs/Abteilung.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {

			template<> inline std::wstring ToString<long long>(const long long& t) { RETURN_WIDE_STRING(t); }


			template<> inline std::wstring ToString<Abteilung>(const Abteilung& t) { return ToString(t.id) + L" " + ToString(t.name); }
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
}
