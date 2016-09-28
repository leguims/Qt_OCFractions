//#include "stdafx.h"
#include "CppUnitTest.h"
//#include "../Commun/Membre.h"
#include "../Commun/ZFraction.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ZFractionTests
{
    TEST_CLASS(ZFractionTests)
    {
    public:

        TEST_METHOD(ZFraction_divisionZeroConstructeur1)
        {
            Logger::WriteMessage("\nZFraction_divisionZeroConstructeur1");
            wchar_t message[200];
            try
            {
                Logger::WriteMessage("\tZFraction a(5, 0);");
                // Should raise an exception:
                ZFraction a(5, 0);
                swprintf_s(message, L"Pas d'exception generee");
                Assert::Fail(message, LINE_INFO());
            }
            catch (std::domain_error ex)
            {
                Logger::WriteMessage("\tException attendue => OK !");
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ZFraction_divisionZeroConstructeur2)
        {
            Logger::WriteMessage("\nZFraction_divisionZeroConstructeur2");
            wchar_t message[200];
            try
            {
                Logger::WriteMessage("\ta=4/1 ; b=0/3 ; c=a/b ...");
                // Should raise an exception:
                ZFraction a(4, 1), b(0, 3), c;
                c = a / b;
                swprintf_s(message, L"Pas d'exception generee");
                Assert::Fail(message, LINE_INFO());
            }
            catch (std::domain_error ex)
            {
                Logger::WriteMessage("\tException attendue => OK !");
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ZFraction_divisionZeroConstructeur3)
        {
            Logger::WriteMessage("\nZFraction_divisionZeroConstructeur3");
            wchar_t message[200];
            try
            {
                Logger::WriteMessage("\ta=3/7 ; b=0 ; c=a/b ...");
                // Should raise an exception:
                ZFraction a(3, 7), c;
                int b(0);
                c = a / b;
                swprintf_s(message, L"Pas d'exception generee");
                Assert::Fail(message, LINE_INFO());
            }
            catch (std::domain_error ex)
            {
                Logger::WriteMessage("\tException attendue => OK !");
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ZFraction_conversionNumerateurReel1)
        {
            Logger::WriteMessage("\nZFraction_conversionNumerateurReel1");
            wchar_t message[200];
            try
            {
                Logger::WriteMessage("\ta=1.05 ...");
                ZFraction a(1.05);
                Logger::WriteMessage("\tPas d'exception => OK !");
            }
            catch (std::domain_error ex)
            {
                Logger::WriteMessage("\tException inattendue !");
                swprintf_s(message, L"Exception inattendue !");
                Assert::Fail(message, LINE_INFO());
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ZFraction_conversionNumerateurReel2)
        {
            Logger::WriteMessage("\nZFraction_conversionNumerateurReel2");
            wchar_t message[200];
            try
            {
                Logger::WriteMessage("\ta=0.0005 ...");
                ZFraction a(0.0005);
                Logger::WriteMessage("\tPas d'exception => OK !");
            }
            catch (std::domain_error ex)
            {
                Logger::WriteMessage("\tException inattendue !");
                swprintf_s(message, L"Exception inattendue !");
                Assert::Fail(message, LINE_INFO());
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ZFraction_conversionNumerateurReel3)
        {
            Logger::WriteMessage("\nZFraction_conversionNumerateurReel3");
            wchar_t message[200];
            try
            {
                Logger::WriteMessage("\ta=0.00000005 ...");
                ZFraction a(0.00000005);
                swprintf_s(message, L"Pas d'exception generee");
                Assert::Fail(message, LINE_INFO());
            }
            catch (std::domain_error ex)
            {
                Logger::WriteMessage("\tException attendue => OK !");
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ZFraction_conversionNumerateurReel4)
        {
            Logger::WriteMessage("\nZFraction_conversionNumerateurReel4");
            wchar_t message[200];
            try
            {
                Logger::WriteMessage("\ta=123456.0000005 ...");
                ZFraction a(123456.0000005);
                swprintf_s(message, L"Pas d'exception generee");
                Assert::Fail(message, LINE_INFO());
            }
            catch (std::domain_error ex)
            {
                Logger::WriteMessage("\tException attendue => OK !");
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ZFraction_getNumerateurDenominateur)
        {
            Logger::WriteMessage("ZFraction_getNumerateurDenominateur");
            wchar_t message[200];
            try
            {
                {
                    Logger::WriteMessage("\ta=1/5 ...");
                    ZFraction a(1, 5);
                    Assert::AreEqual<long int>(1, a.getNumerateur());
                    Assert::AreEqual<long int>(5, a.getDenominateur());
                    Logger::WriteMessage(" OK !");
                }

                {
                    Logger::WriteMessage("\ta=(-1)/5 ...");
                    ZFraction a(-1, 5);
                    Assert::AreEqual<long int>(-1, a.getNumerateur());
                    Assert::AreEqual<long int>(5, a.getDenominateur());
                    Logger::WriteMessage(" OK !");
                }

                {
                    Logger::WriteMessage("\ta=1/(-5) ...");
                    ZFraction a(1, -5);
                    Assert::AreEqual<long int>(-1, a.getNumerateur());
                    Assert::AreEqual<long int>(5, a.getDenominateur());
                    Logger::WriteMessage(" OK !");
                }

                {
                    Logger::WriteMessage("\tb=8/2 ...");
                    ZFraction b(8, 2);
                    Assert::AreEqual<long int>(4, b.getNumerateur());
                    Assert::AreEqual<long int>(1, b.getDenominateur());
                    Logger::WriteMessage(" OK !");
                }

                {
                    Logger::WriteMessage("\tb=(-8)/2 ...");
                    ZFraction b(-8, 2);
                    Assert::AreEqual<long int>(-4, b.getNumerateur());
                    Assert::AreEqual<long int>(1, b.getDenominateur());
                    Logger::WriteMessage(" OK !");
                }

                {
                    Logger::WriteMessage("\tb=8/(-2) ...");
                    ZFraction b(8, -2);
                    Assert::AreEqual<long int>(-4, b.getNumerateur());
                    Assert::AreEqual<long int>(1, b.getDenominateur());
                    Logger::WriteMessage(" OK !");
                }

                {
                    Logger::WriteMessage("\tc=1.5 ...");
                    ZFraction c(1.5);
                    Assert::AreEqual<long int>(3, c.getNumerateur());
                    Assert::AreEqual<long int>(2, c.getDenominateur());
                    Logger::WriteMessage(" OK !");
                }

                {
                    Logger::WriteMessage("\tc=-1.5 ...");
                    ZFraction c(-1.5);
                    Assert::AreEqual<long int>(-3, c.getNumerateur());
                    Assert::AreEqual<long int>(2, c.getDenominateur());
                    Logger::WriteMessage(" OK !");
                }
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ZFraction_getDouble)
        {
            Logger::WriteMessage("ZFraction_getDouble");
            wchar_t message[200];
            try
            {
                {
                    Logger::WriteMessage("\ta=1/5 ...");
                    ZFraction a(1, 5);
                    Assert::AreEqual(1. / 5, a.getDouble());
                    Logger::WriteMessage(" OK !");
                }
                {
                    Logger::WriteMessage("\ta=(-1)/5 ...");
                    ZFraction a(-1, 5);
                    Assert::AreEqual((-1.) / 5, a.getDouble());
                    Logger::WriteMessage(" OK !");
                }
                {
                    Logger::WriteMessage("\ta=1/(-5) ...");
                    ZFraction a(1, -5);
                    Assert::AreEqual(1. / (-5), a.getDouble());
                    Logger::WriteMessage(" OK !");
                }

                {
                    Logger::WriteMessage("\tb=8/2 ...");
                    ZFraction b(8, 2);
                    Assert::AreEqual(8. / 2, b.getDouble());
                    Logger::WriteMessage(" OK !");
                }
                {
                    Logger::WriteMessage("\tb=(-8)/2 ...");
                    ZFraction b(-8, 2);
                    Assert::AreEqual((-8.) / 2, b.getDouble());
                    Logger::WriteMessage(" OK !");
                }
                {
                    Logger::WriteMessage("\tb=8/(-2) ...");
                    ZFraction b(8, -2);
                    Assert::AreEqual(8. / (-2), b.getDouble());
                    Logger::WriteMessage(" OK !");
                }

                {
                    Logger::WriteMessage("\tc=1.5 ...");
                    ZFraction c(1.5);
                    Assert::AreEqual(1.5, c.getDouble());
                    Logger::WriteMessage(" OK !");
                }
                {
                    Logger::WriteMessage("\tc=-1.5 ...");
                    ZFraction c(-1.5);
                    Assert::AreEqual(-1.5, c.getDouble());
                    Logger::WriteMessage(" OK !");
                }
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ZFraction_getSetAfficherFraction)
        {
            Logger::WriteMessage("ZFraction_getSetAfficherFraction");
            wchar_t message[200];
            try
            {
                {
                    Logger::WriteMessage("\ta=1/5 ...");
                    ZFraction a(1, 5);
                    Assert::AreEqual<bool>(true, a.getAfficherFraction());
                    a.setAfficherFraction(false);
                    Assert::AreEqual<bool>(false, a.getAfficherFraction());
                    a.setAfficherFraction(true);
                    Assert::AreEqual<bool>(true, a.getAfficherFraction());
                    a.setAfficherFraction(false);
                    Assert::AreEqual<bool>(false, a.getAfficherFraction());
                    a.setAfficherFraction(200); // Bad type => true if != 0
                    Assert::AreEqual<bool>(true, a.getAfficherFraction());
                    Logger::WriteMessage(" OK !");
                }
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ZFraction_operatorMINUSunit)
        {
            Logger::WriteMessage("ZFraction_operatorMINUSunit");
            wchar_t message[200];
            try
            {
                {
                    Logger::WriteMessage("\ta=1/5 ; b=(-1)/5 ; c=1/(-5) ; d=(-1)/(-5) ...");
                    ZFraction a(1, 5);
                    ZFraction b(-1, 5);
                    ZFraction c(1, -5);
                    ZFraction d(-1, -5);
                    Assert::IsTrue((-a) == b);
                    Logger::WriteMessage(" (-a) == b ... OK !");
                    Assert::IsTrue((-a) == c);
                    Logger::WriteMessage(" (-a) == c ... OK !");
                    Assert::IsTrue((-a) == -d);
                    Logger::WriteMessage(" (-a) == -d ... OK !");
                    Assert::IsTrue((-b) == a);
                    Logger::WriteMessage(" (-b) == a ... OK !");
                    Assert::IsTrue((-b) == -c);
                    Logger::WriteMessage(" (-b) == -c ... OK !");
                    Assert::IsTrue((-b) == d);
                    Logger::WriteMessage(" (-b) == d ... OK !");
                    Assert::IsTrue((-c) == a);
                    Logger::WriteMessage(" (-c) == a ... OK !");
                    Assert::IsTrue((-c) == -b);
                    Logger::WriteMessage(" (-c) == -b ... OK !");
                    Assert::IsTrue((-c) == d);
                    Logger::WriteMessage(" (-c) == d ... OK !");
                    Assert::IsTrue((-d) == -a);
                    Logger::WriteMessage(" (-d) == -a ... OK !");
                    Assert::IsTrue((-d) == b);
                    Logger::WriteMessage(" (-d) == b ... OK !");
                    Assert::IsTrue((-d) == c);
                    Logger::WriteMessage(" (-d) == c ... OK !");
                }

                //{
                //    Logger::WriteMessage("\t8/2 ; (-8)/2 ; 8/(-2) ; (-8)/(-2) ...");
                //    ZFraction a(8, 2);
                //    ZFraction b(-8, 2);
                //    ZFraction c(8, -2);
                //    ZFraction d(-8, -2);
                //    Assert::AreEqual<ZFraction>(-a, b);
                //    Assert::AreEqual<ZFraction>(-a, c);
                //    Assert::AreEqual<ZFraction>(-a, -d);
                //    Assert::AreEqual<ZFraction>(-b, a);
                //    Assert::AreEqual<ZFraction>(-b, -c);
                //    Assert::AreEqual<ZFraction>(-b, d);
                //    Assert::AreEqual<ZFraction>(-c, a);
                //    Assert::AreEqual<ZFraction>(-c, -b);
                //    Assert::AreEqual<ZFraction>(-c, d);
                //    Assert::AreEqual<ZFraction>(-d, -a);
                //    Assert::AreEqual<ZFraction>(-d, b);
                //    Assert::AreEqual<ZFraction>(-d, c);
                //    Logger::WriteMessage(" OK !");
                //}

                //{
                //    Logger::WriteMessage("\t1.5 ; -1.5 ...");
                //    ZFraction a(1.5);
                //    ZFraction b(-1.5);
                //    Assert::AreEqual<ZFraction>(-a, b);
                //    Assert::AreEqual<ZFraction>(-b, a);
                //    Logger::WriteMessage(" OK !");
                //}
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ZFraction_operatorPLUS)
        {
            Logger::WriteMessage("ZFraction_operatorPLUS");
            wchar_t message[200];
            try
            {
                {
                    Logger::WriteMessage("** ECRIRE LE TEST **");
                    swprintf_s(message, L"** ECRIRE LE TEST **");
                    Assert::Fail(message, LINE_INFO());
                }
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ZFraction_operatorMINUS)
        {
            Logger::WriteMessage("ZFraction_operatorMINUS");
            wchar_t message[200];
            try
            {
                {
                    Logger::WriteMessage("** ECRIRE LE TEST **");
                    swprintf_s(message, L"** ECRIRE LE TEST **");
                    Assert::Fail(message, LINE_INFO());
                }
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ZFraction_operatorMULTIPLY)
        {
            Logger::WriteMessage("ZFraction_operatorMULTIPLY");
            wchar_t message[200];
            try
            {
                {
                    Logger::WriteMessage("** ECRIRE LE TEST **");
                    swprintf_s(message, L"** ECRIRE LE TEST **");
                    Assert::Fail(message, LINE_INFO());
                }
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ZFraction_operatorDIVIDE)
        {
            Logger::WriteMessage("ZFraction_operatorDIVIDE");
            wchar_t message[200];
            try
            {
                {
                    Logger::WriteMessage("** ECRIRE LE TEST **");
                    swprintf_s(message, L"** ECRIRE LE TEST **");
                    Assert::Fail(message, LINE_INFO());
                }
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ZFraction_operatorINFERIOR)
        {
            Logger::WriteMessage("ZFraction_operatorINFERIOR");
            wchar_t message[200];
            try
            {
                {
                    Logger::WriteMessage("** ECRIRE LE TEST **");
                    swprintf_s(message, L"** ECRIRE LE TEST **");
                    Assert::Fail(message, LINE_INFO());
                }
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ZFraction_operatorINFERIORorEQUAL)
        {
            Logger::WriteMessage("ZFraction_operatorINFERIORorEQUAL");
            wchar_t message[200];
            try
            {
                {
                    Logger::WriteMessage("** ECRIRE LE TEST **");
                    swprintf_s(message, L"** ECRIRE LE TEST **");
                    Assert::Fail(message, LINE_INFO());
                }
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ZFraction_operatorSUPERIOR)
        {
            Logger::WriteMessage("ZFraction_operatorSUPERIOR");
            wchar_t message[200];
            try
            {
                {
                    Logger::WriteMessage("** ECRIRE LE TEST **");
                    swprintf_s(message, L"** ECRIRE LE TEST **");
                    Assert::Fail(message, LINE_INFO());
                }
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ZFraction_operatorSUPERIORorEQUAL)
        {
            Logger::WriteMessage("ZFraction_operatorSUPERIORorEQUAL");
            wchar_t message[200];
            try
            {
                {
                    Logger::WriteMessage("** ECRIRE LE TEST **");
                    swprintf_s(message, L"** ECRIRE LE TEST **");
                    Assert::Fail(message, LINE_INFO());
                }
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ZFraction_operatorEQUAL)
        {
            Logger::WriteMessage("ZFraction_operatorEQUAL");
            wchar_t message[200];
            try
            {
                {
                    Logger::WriteMessage("** ECRIRE LE TEST **");
                    swprintf_s(message, L"** ECRIRE LE TEST **");
                    Assert::Fail(message, LINE_INFO());
                }
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ZFraction_operatorUNEQUAL)
        {
            Logger::WriteMessage("ZFraction_operatorUNEQUAL");
            wchar_t message[200];
            try
            {
                {
                    Logger::WriteMessage("** ECRIRE LE TEST **");
                    swprintf_s(message, L"** ECRIRE LE TEST **");
                    Assert::Fail(message, LINE_INFO());
                }
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ZFraction_afficher)
        {
            Logger::WriteMessage("ZFraction_afficher");
            wchar_t message[200];
            try
            {
                {
                    Logger::WriteMessage("** ECRIRE LE TEST **");
                    swprintf_s(message, L"** ECRIRE LE TEST **");
                    Assert::Fail(message, LINE_INFO());
                }
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ZFraction_afficherPlainText)
        {
            Logger::WriteMessage("ZFraction_afficherPlainText");
            wchar_t message[200];
            try
            {
                {
                    Logger::WriteMessage("\ta=1/5 ...");
                    ZFraction a(1, 5);
                    Assert::AreEqual<std::string>("1/5", a.afficherPlainText());
                    Logger::WriteMessage(" OK !");
                }
                {
                    Logger::WriteMessage("\ta=(-1)/5 ...");
                    ZFraction a(-1, 5);
                    Assert::AreEqual<std::string>("-1/5", a.afficherPlainText());
                    Logger::WriteMessage(" OK !");
                }
                {
                    Logger::WriteMessage("\ta=1/(-5) ...");
                    ZFraction a(1, -5);
                    Assert::AreEqual<std::string>("-1/5", a.afficherPlainText());
                    Logger::WriteMessage(" OK !");
                }

                {
                    Logger::WriteMessage("\tb=8/2 ...");
                    ZFraction b(8, 2);
                    Assert::AreEqual<std::string>("4", b.afficherPlainText());
                    Logger::WriteMessage(" OK !");
                }
                {
                    Logger::WriteMessage("\tb=(-8)/2 ...");
                    ZFraction b(-8, 2);
                    Assert::AreEqual<std::string>("-4", b.afficherPlainText());
                    Logger::WriteMessage(" OK !");
                }
                {
                    Logger::WriteMessage("\tb=8/(-2) ...");
                    ZFraction b(8, -2);
                    Assert::AreEqual<std::string>("-4", b.afficherPlainText());
                    Logger::WriteMessage(" OK !");
                }

                {
                    Logger::WriteMessage("\tc=1.5 ...");
                    ZFraction c(1.5);
                    Assert::AreEqual<std::string>("3/2", c.afficherPlainText());
                    Logger::WriteMessage(" OK !");
                }
                {
                    Logger::WriteMessage("\tc=-1.5 ...");
                    ZFraction c(-1.5);
                    Assert::AreEqual<std::string>("-3/2", c.afficherPlainText());
                    Logger::WriteMessage(" OK !");
                }
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ZFraction_afficherHTML)
        {
            Logger::WriteMessage("ZFraction_afficherHTML");
            wchar_t message[200];
            try
            {
                {
                    Logger::WriteMessage("** ECRIRE LE TEST **");
                    swprintf_s(message, L"** ECRIRE LE TEST **");
                    Assert::Fail(message, LINE_INFO());
                }
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }
    };
}