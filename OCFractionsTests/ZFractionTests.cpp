//#include "stdafx.h"
#include "CppUnitTest.h"
//#include "../Commun/Membre.h"
#include "../Commun/ZFraction.h"
#include <string>

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
                    ZFraction a(1, 5);
                    Assert::AreEqual<long int>(1, a.getNumerateur());
                    Assert::AreEqual<long int>(5, a.getDenominateur());
                    Logger::WriteMessage("\ta=1/5\t... OK !");
                }

                {
                    ZFraction a(-1, 5);
                    Assert::AreEqual<long int>(-1, a.getNumerateur());
                    Assert::AreEqual<long int>(5, a.getDenominateur());
                    Logger::WriteMessage("\ta=(-1)/5\t... OK !");
                }

                {
                    ZFraction a(1, -5);
                    Assert::AreEqual<long int>(-1, a.getNumerateur());
                    Assert::AreEqual<long int>(5, a.getDenominateur());
                    Logger::WriteMessage("\ta=1/(-5)\t... OK !");
                }

                {
                    ZFraction b(8, 2);
                    Assert::AreEqual<long int>(4, b.getNumerateur());
                    Assert::AreEqual<long int>(1, b.getDenominateur());
                    Logger::WriteMessage("\tb=8/2\t... OK !");
                }

                {
                    ZFraction b(-8, 2);
                    Assert::AreEqual<long int>(-4, b.getNumerateur());
                    Assert::AreEqual<long int>(1, b.getDenominateur());
                    Logger::WriteMessage("\tb=(-8)/2\t... OK !");
                }

                {
                    ZFraction b(8, -2);
                    Assert::AreEqual<long int>(-4, b.getNumerateur());
                    Assert::AreEqual<long int>(1, b.getDenominateur());
                    Logger::WriteMessage("\tb=8/(-2)\t... OK !");
                }

                {
                    ZFraction c(1.5);
                    Assert::AreEqual<long int>(3, c.getNumerateur());
                    Assert::AreEqual<long int>(2, c.getDenominateur());
                    Logger::WriteMessage("\tc=1.5\t... OK !");
                }

                {
                    ZFraction c(-1.5);
                    Assert::AreEqual<long int>(-3, c.getNumerateur());
                    Assert::AreEqual<long int>(2, c.getDenominateur());
                    Logger::WriteMessage("\tc=-1.5\t... OK !");
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
                    ZFraction a(1, 5);
                    Assert::AreEqual(1. / 5, a.getDouble());
                    Logger::WriteMessage("\ta=1/5\t... OK !");
                }
                {
                    ZFraction a(-1, 5);
                    Assert::AreEqual((-1.) / 5, a.getDouble());
                    Logger::WriteMessage("\ta=(-1)/5\t... OK !");
                }
                {
                    ZFraction a(1, -5);
                    Assert::AreEqual(1. / (-5), a.getDouble());
                    Logger::WriteMessage("\ta=1/(-5)\t... OK !");
                }

                {
                    ZFraction b(8, 2);
                    Assert::AreEqual(8. / 2, b.getDouble());
                    Logger::WriteMessage("\tb=8/2\t... OK !");
                }
                {
                    ZFraction b(-8, 2);
                    Assert::AreEqual((-8.) / 2, b.getDouble());
                    Logger::WriteMessage("\tb=(-8)/2\t... OK !");
                }
                {
                    ZFraction b(8, -2);
                    Assert::AreEqual(8. / (-2), b.getDouble());
                    Logger::WriteMessage("\tb=8/(-2)\t... OK !");
                }

                {
                    ZFraction c(1.5);
                    Assert::AreEqual(1.5, c.getDouble());
                    Logger::WriteMessage("\tc=1.5\t... OK !");
                }
                {
                    ZFraction c(-1.5);
                    Assert::AreEqual(-1.5, c.getDouble());
                    Logger::WriteMessage("\tc=-1.5\t... OK !");
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
                    Logger::WriteMessage("\t\t(-a) == b\t... OK !");
                    Assert::IsTrue((-a) == c);
                    Logger::WriteMessage("\t\t(-a) == c\t... OK !");
                    Assert::IsTrue((-a) == -d);
                    Logger::WriteMessage("\t\t(-a) == -d\t... OK !");
                    Assert::IsTrue((-b) == a);
                    Logger::WriteMessage("\t\t(-b) == a\t... OK !");
                    Assert::IsTrue((-b) == -c);
                    Logger::WriteMessage("\t\t(-b) == -c\t... OK !");
                    Assert::IsTrue((-b) == d);
                    Logger::WriteMessage("\t\t(-b) == d\t... OK !");
                    Assert::IsTrue((-c) == a);
                    Logger::WriteMessage("\t\t(-c) == a\t... OK !");
                    Assert::IsTrue((-c) == -b);
                    Logger::WriteMessage("\t\t(-c) == -b\t... OK !");
                    Assert::IsTrue((-c) == d);
                    Logger::WriteMessage("\t\t(-c) == d\t... OK !");
                    Assert::IsTrue((-d) == -a);
                    Logger::WriteMessage("\t\t(-d) == -a\t... OK !");
                    Assert::IsTrue((-d) == b);
                    Logger::WriteMessage("\t\t(-d) == b\t... OK !");
                    Assert::IsTrue((-d) == c);
                    Logger::WriteMessage("\t\t(-d) == c\t... OK !");
                }

                {
                    Logger::WriteMessage("\ta=8/2 ; b=(-8)/2 ; c=8/(-2) ; d=(-8)/(-2) ...");
                    ZFraction a(8, 2);
                    ZFraction b(-8, 2);
                    ZFraction c(8, -2);
                    ZFraction d(-8, -2);
                    Assert::IsTrue((-a) == b);
                    Logger::WriteMessage("\t\t(-a) == b\t... OK !");
                    Assert::IsTrue((-a) == c);
                    Logger::WriteMessage("\t\t(-a) == c\t... OK !");
                    Assert::IsTrue((-a) == -d);
                    Logger::WriteMessage("\t\t(-a) == -d\t... OK !");
                    Assert::IsTrue((-b) == a);
                    Logger::WriteMessage("\t\t(-b) == a\t... OK !");
                    Assert::IsTrue((-b) == -c);
                    Logger::WriteMessage("\t\t(-b) == -c\t... OK !");
                    Assert::IsTrue((-b) == d);
                    Logger::WriteMessage("\t\t(-b) == d\t... OK !");
                    Assert::IsTrue((-c) == a);
                    Logger::WriteMessage("\t\t(-c) == a\t... OK !");
                    Assert::IsTrue((-c) == -b);
                    Logger::WriteMessage("\t\t(-c) == -b\t... OK !");
                    Assert::IsTrue((-c) == d);
                    Logger::WriteMessage("\t\t(-c) == d\t... OK !");
                    Assert::IsTrue((-d) == -a);
                    Logger::WriteMessage("\t\t(-d) == -a\t... OK !");
                    Assert::IsTrue((-d) == b);
                    Logger::WriteMessage("\t\t(-d) == b\t... OK !");
                    Assert::IsTrue((-d) == c);
                    Logger::WriteMessage("\t\t(-d) == c\t... OK !");
                }

                {
                    Logger::WriteMessage("\ta=1.5 ; b=-1.5 ...");
                    ZFraction a(1.5);
                    ZFraction b(-1.5);
                    Assert::IsTrue((-a) == b);
                    Logger::WriteMessage("\t\t(-a) == b\t... OK !");
                    Assert::IsTrue((-b) == a);
                    Logger::WriteMessage("\t\t(-b) == a\t... OK !");
                }
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
                    Logger::WriteMessage("\ta=1/5 ; b=int(1) ; c=long int(1) ; d=double(1.9) ; e=double(1.1) ; f=double(0.9) ...");
                    ZFraction a(1, 5);
                    int b(1);
                    long int c(1);
                    double d(1.9);
                    double e(1.1);
                    double f(0.9);
                    std::string msg;

                    {
                        ZFraction result(6, 5);
                        Assert::IsTrue((a + b) == result);
                        msg = "\t\t(a + b) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());

                        Assert::IsTrue((a + c) == result);
                        msg = "\t\t(a + c) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction result(21, 10);
                        Assert::IsTrue((a + d) == result);
                        msg = "\t\t(a + d) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction result(13, 10);
                        Assert::IsTrue((a + e) == result);
                        msg = "\t\t(a + e) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction result(11, 10);
                        Assert::IsTrue((a + f) == result);
                        msg = "\t\t(a + f) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }
                }

                {
                    Logger::WriteMessage("\ta=10/5 ; b=int(1) ; c=long int(1) ; d=double(1.9) ; e=double(1.1) ; f=double(0.9) ...");
                    ZFraction a(10, 5);
                    int b(1);
                    long int c(1);
                    double d(1.9);
                    double e(1.1);
                    double f(0.9);
                    std::string msg;

                    {
                        ZFraction result(15, 5);
                        Assert::IsTrue((a + b) == result);
                        msg = "\t\t(a + b) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());

                        Assert::IsTrue((a + c) == result);
                        msg = "\t\t(a + c) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction result(39, 10);
                        Assert::IsTrue((a + d) == result);
                        msg = "\t\t(a + d) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction result(31, 10);
                        Assert::IsTrue((a + e) == result);
                        msg = "\t\t(a + e) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction result(29, 10);
                        Assert::IsTrue((a + f) == result);
                        msg = "\t\t(a + f) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }
                }

                {
                    Logger::WriteMessage("\ta=1.5 ; b=int(1) ; c=long int(1) ; d=double(1.9) ; e=double(1.1) ; f=double(0.9) ...");
                    ZFraction a(1.5);
                    int b(1);
                    long int c(1);
                    double d(1.9);
                    double e(1.1);
                    double f(0.9);
                    std::string msg;

                    {
                        ZFraction result(5, 2);
                        Assert::IsTrue((a + b) == result);
                        msg = "\t\t(a + b) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());

                        Assert::IsTrue((a + c) == result);
                        msg = "\t\t(a + c) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction result(34, 10);
                        Assert::IsTrue((a + d) == result);
                        msg = "\t\t(a + d) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction result(26, 10);
                        Assert::IsTrue((a + e) == result);
                        msg = "\t\t(a + e) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction result(24, 10);
                        Assert::IsTrue((a + f) == result);
                        msg = "\t\t(a + f) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }
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
                    ZFraction a(1, 5);
                    Assert::AreEqual<std::string>("1/5", a.afficherPlainText());
                    Logger::WriteMessage("\ta=1/5\t... OK !");
                }
                {
                    ZFraction a(-1, 5);
                    Assert::AreEqual<std::string>("-1/5", a.afficherPlainText());
                    Logger::WriteMessage("\ta=(-1)/5\t... OK !");
                }
                {
                    ZFraction a(1, -5);
                    Assert::AreEqual<std::string>("-1/5", a.afficherPlainText());
                    Logger::WriteMessage("\ta=1/(-5)\t... OK !");
                }

                {
                    ZFraction b(8, 2);
                    Assert::AreEqual<std::string>("4", b.afficherPlainText());
                    Logger::WriteMessage("\tb=8/2\t... OK !");
                }
                {
                    ZFraction b(-8, 2);
                    Assert::AreEqual<std::string>("-4", b.afficherPlainText());
                    Logger::WriteMessage("\tb=(-8)/2\t... OK !");
                }
                {
                    ZFraction b(8, -2);
                    Assert::AreEqual<std::string>("-4", b.afficherPlainText());
                    Logger::WriteMessage("\tb=8/(-2)\t... OK !");
                }

                {
                    ZFraction c(1.5);
                    Assert::AreEqual<std::string>("3/2", c.afficherPlainText());
                    Logger::WriteMessage("\tc=1.5\t... OK !");
                }
                {
                    ZFraction c(-1.5);
                    Assert::AreEqual<std::string>("-3/2", c.afficherPlainText());
                    Logger::WriteMessage("\tc=-1.5\t... OK !");
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