//#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Commun/Membre.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MembreTests
{
    TEST_CLASS(MembreTests)
    {
    public:

        TEST_METHOD(Membre_isEmpty)
        {
            Logger::WriteMessage("\n Membre_isEmpty");
            wchar_t message[200];
            try
            {
                Membre m0;
                Membre m1(1);
                Membre m2(2, 3);
                Membre m3(m1, Membre::operation::operation_addition, m2);
                Membre m4(m3, Membre::operation::operation_addition, Membre(1, 3));

                Assert::IsTrue(m0.isEmpty());
                m0.ouvrirParenthese();
                Assert::IsFalse(m0.isEmpty());
                m0.fermerParenthese();
                Assert::IsTrue(m0.isEmpty());

                Assert::IsFalse(m1.isEmpty());
                Assert::IsFalse(m2.isEmpty());
                Assert::IsFalse(m3.isEmpty());
                Assert::IsFalse(m4.isEmpty());

                Logger::WriteMessage("\t ... ok !");
            }
            catch (...)
            {
                Logger::WriteMessage("\t Mauvaise exception generee ... KO !");
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(Membre_isValueless)
        {
            Logger::WriteMessage("\n Membre_isValueless");
            wchar_t message[200];
            try
            {
                Membre m0;
                Membre m1(1);
                Membre m2(2, 3);
                Membre m3(m1, Membre::operation::operation_addition, m2);
                Membre m4(m3, Membre::operation::operation_addition, Membre(1, 3));

                Assert::IsTrue(m0.isValueless());
                m0.ouvrirParenthese();
                Assert::IsTrue(m0.isValueless());
                m0.fermerParenthese();
                Assert::IsTrue(m0.isValueless());
                Assert::IsFalse(m1.isValueless());
                Assert::IsFalse(m2.isValueless());
                Assert::IsFalse(m3.isValueless());
                Assert::IsFalse(m4.isValueless());

                Logger::WriteMessage("\t ... ok !");
            }
            catch (...)
            {
                Logger::WriteMessage("\t Mauvaise exception generee ... KO !");
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(Membre_isSimple)
        {
            Logger::WriteMessage("\n Membre_isSimple");
            wchar_t message[200];
            try
            {
                Membre m0;
                Membre m1(1);
                Membre m2(2, 3);
                Membre m3(m1, Membre::operation::operation_addition, m2);
                Membre m4(m3, Membre::operation::operation_addition, Membre(1, 3));

                Assert::IsFalse(m0.isSimple());
                Assert::IsTrue(m1.isSimple());
                Assert::IsTrue(m2.isSimple());
                Assert::IsFalse(m3.isSimple());
                Assert::IsFalse(m4.isSimple());

                Logger::WriteMessage("\t ... ok !");
            }
            catch (...)
            {
                Logger::WriteMessage("\t Mauvaise exception generee ... KO !");
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ABANDON_Membre_isHalfComplex)
        {
            Logger::WriteMessage("\n ABANDON_Membre_isHalfComplex");
            wchar_t message[200];
            try
            {
                Logger::WriteMessage("** Test abandonne **");
                swprintf_s(message, L"** Test abandonne **");
                Assert::Fail(message, LINE_INFO());
            }
            catch (...)
            {
                Logger::WriteMessage("\t Mauvaise exception generee ... KO !");
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(Membre_isComplex)
        {
            Logger::WriteMessage("\n Membre_isComplex");
            wchar_t message[200];
            try
            {
                Membre m0;
                Membre m1(1);
                Membre m2(2, 3);
                Membre m3(m1, Membre::operation::operation_addition, m2);
                Membre m4(m3, Membre::operation::operation_addition, Membre(1, 3));

                Assert::IsFalse(m0.isComplex());
                Assert::IsFalse(m1.isComplex());
                Assert::IsFalse(m2.isComplex());
                Assert::IsTrue(m3.isComplex());
                Assert::IsTrue(m4.isComplex());

                Logger::WriteMessage("\t ... ok !");
            }
            catch (...)
            {
                Logger::WriteMessage("\t Mauvaise exception generee ... KO !");
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(Membre_get_setAfficherFraction)
        {
            Logger::WriteMessage("\n Membre_get_setAfficherFraction");
            wchar_t message[200];
            try
            {
                Membre m0;
                Membre m1(1);
                Membre m2(2, 3);
                Membre m3(m1, Membre::operation::operation_addition, m2);
                Membre m4(m3, Membre::operation::operation_addition, Membre(1, 3));

                Assert::IsTrue(m0.getAfficherFraction());
                m0.setAfficherFraction(false);
                Assert::IsFalse(m0.getAfficherFraction());
                m0.setAfficherFraction();
                Assert::IsTrue(m0.getAfficherFraction());
                m0.setAfficherFraction(false);
                Assert::IsFalse(m0.getAfficherFraction());
                m0.setAfficherFraction(true);
                Assert::IsTrue(m0.getAfficherFraction());

                Logger::WriteMessage("\t ... ok !");
            }
            catch (...)
            {
                Logger::WriteMessage("\t Mauvaise exception generee ... KO !");
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(Membre_getResultat)
        {
            Logger::WriteMessage("\n Membre_getResultat");
            wchar_t message[200];
            try
            {
                Membre m0;
                Membre m1(1);
                Membre m2(2, 3);
                Membre m3(m1, Membre::operation::operation_addition, m2);
                Membre m4(m3, Membre::operation::operation_addition, Membre(1, 3));

                ZFraction s0(0), s1(1), s2(2,3), s3(0), s4(0);

                Assert::IsTrue(m0.getResultat() == s0);
                Assert::IsTrue(m1.getResultat() == s1);
                Assert::IsTrue(m2.getResultat() == s2);
                Assert::IsTrue(m3.getResultat() == s3);
                Assert::IsTrue(m4.getResultat() == s4);

                Logger::WriteMessage("\t ... ok !");
            }
            catch (...)
            {
                Logger::WriteMessage("\t Mauvaise exception generee ... KO !");
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(Membre_simplifier1)
        {
            Logger::WriteMessage("\n Membre_simplifier1");
            wchar_t message[200];
            try
            {
                Membre m0;
                Membre m1(1);
                Membre m2(2, 3);
                Membre m3(m1, Membre::operation::operation_addition, m2);
                Membre m4(m3, Membre::operation::operation_addition, Membre(1, 3));

                Assert::IsFalse(m0.simplifier());
                Assert::IsFalse(m1.simplifier());
                Assert::IsFalse(m2.simplifier());
                Assert::IsTrue(m3.simplifier());
                Assert::IsTrue(m4.simplifier());

                Logger::WriteMessage("\t ... ok !");
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(Membre_simplifier2)
        {
            Logger::WriteMessage("\n Membre_simplifier2");
            wchar_t message[200];
            try
            {
                Membre m1(1);
                Membre m2(2, 3);
                Membre m3(m1, Membre::operation::operation_addition, m2);
                Membre m4(m3, Membre::operation::operation_addition, Membre(1, 3));

                ZFraction s3(5, 3), s4(6, 3);

                Assert::IsTrue(m3.simplifier());
                Assert::IsTrue(m3.getResultat() == s3);
                Assert::IsFalse(m3.simplifier());

                Assert::IsTrue(m4.simplifier());
                Assert::IsTrue(m4.simplifier());
                Assert::IsTrue(m4.getResultat() == s4);
                Assert::IsFalse(m4.simplifier());

                Logger::WriteMessage("\t ... ok !");
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(Membre_simplifier3)
        {
            Logger::WriteMessage("\n Membre_simplifier3");
            wchar_t message[200];
            try
            {
                ZFraction correction;
                Membre m0, m1(1), m2(2, 3);

                Membre m20(m1 + m2);
                m20.simplifier();
                correction = ZFraction(5, 3);
                Assert::IsTrue(m20.getResultat() == correction);

                Logger::WriteMessage("\t ... ok !");
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(Membre_simplifier4)
        {
            Logger::WriteMessage("\n Membre_simplifier4");
            wchar_t message[200];
            try
            {
                ZFraction correction;
                Membre m0, m1(1), m2(2, 3);

                Membre m21(m1 - m2);
                m21.simplifier();
                correction = ZFraction(1, 3);
                Assert::IsTrue(m21.getResultat() == correction);

                Logger::WriteMessage("\t ... ok !");
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(Membre_simplifier5)
        {
            Logger::WriteMessage("\n Membre_simplifier5");
            wchar_t message[200];
            try
            {
                ZFraction correction;
                Membre m0, m1(1), m2(2, 3);

                Membre m22(m1 / m2);
                m22.simplifier();
                correction = ZFraction(3, 2);
                Assert::IsTrue(m22.getResultat() == correction);

                Logger::WriteMessage("\t ... ok !");
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(Membre_simplifier6)
        {
            Logger::WriteMessage("\n Membre_simplifier6");
            wchar_t message[200];
            try
            {
                ZFraction correction;
                Membre m0, m1(1), m2(2, 3);

                Membre m23(m1 * m2 * 7);
                m23.simplifier();
                m23.simplifier();
                correction = ZFraction(14, 3);
                Assert::IsTrue(m23.getResultat() == correction);

                Logger::WriteMessage("\t ... ok !");
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(Membre_constructorByCopy1)
        {
            Logger::WriteMessage("\n Membre_constructorByCopy1");
            wchar_t message[200];
            try
            {
                ZFraction correction;
                Membre m0, m1(1), m2(2, 3);

                Membre m23;
                m23 = m1 * m2 * 7;
                m23.simplifier();
                m23.simplifier();
                correction = ZFraction(14, 3);
                Assert::IsTrue(m23.getResultat() == correction);

                Logger::WriteMessage("\t ... ok !");
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(Membre_constructorByCopy2)
        {
            Logger::WriteMessage("\n Membre_constructorByCopy2");
            wchar_t message[200];
            try
            {
                ZFraction correction;
                Membre m0, m1(1), m2(2, 3);

                Membre m23(1.5);
                m23 = m1 * m2 * 7;
                m23.simplifier();
                m23.simplifier();
                correction = ZFraction(14, 3);
                Assert::IsTrue(m23.getResultat() == correction);

                Logger::WriteMessage("\t ... ok !");
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(Membre_constructorByCopy3)
        {
            Logger::WriteMessage("\n Membre_constructorByCopy3");
            wchar_t message[200];
            try
            {
                ZFraction correction;
                Membre m0, m1(1), m2(2, 3);

                Membre m23(m1 * m2 * 7);
                m23 = m23;
                m23.simplifier();
                m23.simplifier();
                correction = ZFraction(14, 3);
                Assert::IsTrue(m23.getResultat() == correction);

                Logger::WriteMessage("\t ... ok !");
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(Membre_constructorByCopy4)
        {
            Logger::WriteMessage("\n Membre_constructorByCopy4");
            wchar_t message[200];
            try
            {
                {
                    ZFraction correction;
                    Membre src, dst;

                    dst = src;
                    correction = ZFraction();
                    Assert::IsTrue(dst.getResultat() == correction);
                }
                {
                    ZFraction correction;
                    Membre src, dst(1);

                    dst = src;
                    correction = ZFraction();
                    Assert::IsTrue(dst.getResultat() == correction);
                }
                {
                    ZFraction correction;
                    Membre src(1), dst;

                    dst = src;
                    correction = ZFraction(1);
                    Assert::IsTrue(dst.getResultat() == correction);
                }
                {
                    ZFraction correction;
                    Membre src(1), dst(2);

                    dst = src;
                    correction = ZFraction(1);
                    Assert::IsTrue(dst.getResultat() == correction);
                }

                Logger::WriteMessage("\t ... ok !");
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }



        TEST_METHOD(Membre_operatorMINUSunit)
        {
            Logger::WriteMessage("\n Membre_operatorMINUSunit");
            wchar_t message[200];
            try
            {
                {
                    Logger::WriteMessage("\ta=1/5 ; b=(-1)/5 ; c=1/(-5) ; d=(-1)/(-5) ...");
                    Membre a(1, 5);
                    Membre b(-1, 5);
                    Membre c(1, -5);
                    Membre d(-1, -5);
                    Membre minus_a(-a); minus_a.simplifier();
                    Membre minus_b(-b); minus_b.simplifier();
                    Membre minus_c(-c); minus_c.simplifier();
                    Membre minus_d(-d); minus_d.simplifier();

                    Assert::IsTrue(minus_a.getResultat() == b.getResultat());
                    Logger::WriteMessage("\t\t(-a) == b\t... OK !");
                    Assert::IsTrue(minus_a.getResultat() == c.getResultat());
                    Logger::WriteMessage("\t\t(-a) == c\t... OK !");
                    Assert::IsTrue(minus_a.getResultat() == minus_d.getResultat());
                    Logger::WriteMessage("\t\t(-a) == -d\t... OK !");
                    Assert::IsTrue(minus_b.getResultat() == a.getResultat());
                    Logger::WriteMessage("\t\t(-b) == a\t... OK !");
                    Assert::IsTrue(minus_b.getResultat() == minus_c.getResultat());
                    Logger::WriteMessage("\t\t(-b) == -c\t... OK !");
                    Assert::IsTrue(minus_b.getResultat() == d.getResultat());
                    Logger::WriteMessage("\t\t(-b) == d\t... OK !");
                    Assert::IsTrue(minus_c.getResultat() == a.getResultat());
                    Logger::WriteMessage("\t\t(-c) == a\t... OK !");
                    Assert::IsTrue(minus_c.getResultat() == minus_b.getResultat());
                    Logger::WriteMessage("\t\t(-c) == -b\t... OK !");
                    Assert::IsTrue(minus_c.getResultat() == d.getResultat());
                    Logger::WriteMessage("\t\t(-c) == d\t... OK !");
                    Assert::IsTrue(minus_d.getResultat() == minus_a.getResultat());
                    Logger::WriteMessage("\t\t(-d) == -a\t... OK !");
                    Assert::IsTrue(minus_d.getResultat() == b.getResultat());
                    Logger::WriteMessage("\t\t(-d) == b\t... OK !");
                    Assert::IsTrue(minus_d.getResultat() == c.getResultat());
                    Logger::WriteMessage("\t\t(-d) == c\t... OK !");
                }

                {
                    Logger::WriteMessage("\ta=8/2 ; b=(-8)/2 ; c=8/(-2) ; d=(-8)/(-2) ...");
                    Membre a(8, 2);
                    Membre b(-8, 2);
                    Membre c(8, -2);
                    Membre d(-8, -2);
                    Membre minus_a(-a); minus_a.simplifier();
                    Membre minus_b(-b); minus_b.simplifier();
                    Membre minus_c(-c); minus_c.simplifier();
                    Membre minus_d(-d); minus_d.simplifier();

                    Assert::IsTrue(minus_a.getResultat() == b.getResultat());
                    Logger::WriteMessage("\t\t(-a) == b\t... OK !");
                    Assert::IsTrue(minus_a.getResultat() == c.getResultat());
                    Logger::WriteMessage("\t\t(-a) == c\t... OK !");
                    Assert::IsTrue(minus_a.getResultat() == minus_d.getResultat());
                    Logger::WriteMessage("\t\t(-a) == -d\t... OK !");
                    Assert::IsTrue(minus_b.getResultat() == a.getResultat());
                    Logger::WriteMessage("\t\t(-b) == a\t... OK !");
                    Assert::IsTrue(minus_b.getResultat() == minus_c.getResultat());
                    Logger::WriteMessage("\t\t(-b) == -c\t... OK !");
                    Assert::IsTrue(minus_b.getResultat() == d.getResultat());
                    Logger::WriteMessage("\t\t(-b) == d\t... OK !");
                    Assert::IsTrue(minus_c.getResultat() == a.getResultat());
                    Logger::WriteMessage("\t\t(-c) == a\t... OK !");
                    Assert::IsTrue(minus_c.getResultat() == minus_b.getResultat());
                    Logger::WriteMessage("\t\t(-c) == -b\t... OK !");
                    Assert::IsTrue(minus_c.getResultat() == d.getResultat());
                    Logger::WriteMessage("\t\t(-c) == d\t... OK !");
                    Assert::IsTrue(minus_d.getResultat() == minus_a.getResultat());
                    Logger::WriteMessage("\t\t(-d) == -a\t... OK !");
                    Assert::IsTrue(minus_d.getResultat() == b.getResultat());
                    Logger::WriteMessage("\t\t(-d) == b\t... OK !");
                    Assert::IsTrue(minus_d.getResultat() == c.getResultat());
                    Logger::WriteMessage("\t\t(-d) == c\t... OK !");
                }

                {
                    Logger::WriteMessage("\ta=1.5 ; b=-1.5 ...");
                    Membre a(1.5);
                    Membre b(-1.5);
                    Membre minus_a(-a); minus_a.simplifier();
                    Membre minus_b(-b); minus_b.simplifier();

                    Assert::IsTrue(minus_a.getResultat() == b.getResultat());
                    Logger::WriteMessage("\t\t(-a) == b\t... OK !");
                    Assert::IsTrue(minus_b.getResultat() == a.getResultat());
                    Logger::WriteMessage("\t\t(-b) == a\t... OK !");
                }
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(Membre_operatorPLUS)
        {
            Logger::WriteMessage("\n Membre_operatorPLUS");
            wchar_t message[200];
            try
            {
                {
                    Logger::WriteMessage("\ta=1/5 ; b=int(1) ; c=long int(1) ; d=double(1.9) ; e=double(1.1) ; f=double(0.9) ...");
                    Membre a(1, 5);
                    Membre minus_a(-a); minus_a.simplifier();
                    Membre result;
                    int b(1);
                    long int c(1);
                    double d(1.9);
                    double e(1.1);
                    double f(0.9);
                    std::string msg;

                    {
                        ZFraction correction(6, 5);
                        result = a + b; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a + b) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());

                        result = a + c; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a + c) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction correction(21, 10);
                        result = a + d; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a + d) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction correction(13, 10);
                        result = a + e; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a + e) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction correction(11, 10);
                        result = a + f; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a + f) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }
                }

                {
                    Logger::WriteMessage("\ta=10/5 ; b=int(1) ; c=long int(1) ; d=double(1.9) ; e=double(1.1) ; f=double(0.9) ...");
                    Membre a(10, 5);
                    Membre minus_a(-a); minus_a.simplifier();
                    Membre result;
                    int b(1);
                    long int c(1);
                    double d(1.9);
                    double e(1.1);
                    double f(0.9);
                    std::string msg;

                    {
                        ZFraction correction(15, 5);
                        result = a + b; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a + b) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());

                        result = a + c; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a + c) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction correction(39, 10);
                        result = a + d; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a + d) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction correction(31, 10);
                        result = a + e; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a + e) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction correction(29, 10);
                        result = a + f; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a + f) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }
                }

                {
                    Logger::WriteMessage("\ta=1.5 ; b=int(1) ; c=long int(1) ; d=double(1.9) ; e=double(1.1) ; f=double(0.9) ...");
                    Membre a(1.5);
                    Membre minus_a(-a); minus_a.simplifier();
                    Membre result;
                    int b(1);
                    long int c(1);
                    double d(1.9);
                    double e(1.1);
                    double f(0.9);
                    std::string msg;

                    {
                        ZFraction correction(5, 2);
                        result = a + b; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a + b) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());

                        result = a + c; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a + c) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction correction(34, 10);
                        result = a + d; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a + d) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction correction(26, 10);
                        result = a + e; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a + e) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction correction(24, 10);
                        result = a + f; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
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

        TEST_METHOD(Membre_operatorMINUS)
        {
            Logger::WriteMessage("\n Membre_operatorMINUS");
            wchar_t message[200];
            try
            {
                {
                    Logger::WriteMessage("\ta=1/5 ; b=int(1) ; c=long int(1) ; d=double(1.9) ; e=double(1.1) ; f=double(0.9) ...");
                    Membre a(1, 5);
                    Membre minus_a(-a); minus_a.simplifier();
                    Membre result;
                    int b(1);
                    long int c(1);
                    double d(1.9);
                    double e(1.1);
                    double f(0.9);
                    std::string msg;

                    {
                        ZFraction correction(-4, 5);
                        result = a - b; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a - b) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());

                        result = (a - c); result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a - c) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction correction(-17, 10);
                        result = (a - d); result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a - d) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction correction(-9, 10);
                        result = (a - e); result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a - e) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction correction(-7, 10);
                        result = (a - f); result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a - f) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }
                }

                {
                    Logger::WriteMessage("\ta=10/5 ; b=int(1) ; c=long int(1) ; d=double(1.9) ; e=double(1.1) ; f=double(0.9) ...");
                    Membre a(10, 5);
                    Membre minus_a(-a); minus_a.simplifier();
                    Membre result;
                    int b(1);
                    long int c(1);
                    double d(1.9);
                    double e(1.1);
                    double f(0.9);
                    std::string msg;

                    {
                        ZFraction correction(1, 1);
                        result = (a - b); result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a - b) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());

                        result = (a - c); result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a - c) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction correction(1, 10);
                        result = (a - d); result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a - d) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction correction(9, 10);
                        result = (a - e); result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a - e) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction correction(11, 10);
                        result = (a - f); result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a - f) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }
                }

                {
                    Logger::WriteMessage("\ta=1.5 ; b=int(1) ; c=long int(1) ; d=double(1.9) ; e=double(1.1) ; f=double(0.9) ...");
                    Membre a(1.5);
                    Membre minus_a(-a); minus_a.simplifier();
                    Membre result;
                    int b(1);
                    long int c(1);
                    double d(1.9);
                    double e(1.1);
                    double f(0.9);
                    std::string msg;

                    {
                        ZFraction correction(1, 2);
                        result = (a - b); result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a - b) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());

                        result = (a - c); result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a - c) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction correction(-4, 10);
                        result = (a - d); result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a - d) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction correction(4, 10);
                        result = (a - e); result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a - e) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction correction(6, 10);
                        result = (a - f); result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a - f) == " + result.afficherPlainText() + "\t... OK !";
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

        TEST_METHOD(Membre_operatorMULTIPLY)
        {
            Logger::WriteMessage("\n Membre_operatorMULTIPLY");
            wchar_t message[200];
            try
            {
                {
                    Logger::WriteMessage("\ta=1/5 ; b=int(1) ; c=long int(1) ; d=double(1.9) ; e=double(1.1) ; f=double(0.9) ...");
                    Membre a(1, 5);
                    Membre minus_a(-a); minus_a.simplifier();
                    Membre result;
                    int b(1);
                    long int c(1);
                    double d(1.9);
                    double e(1.1);
                    double f(0.9);
                    std::string msg;

                    {
                        ZFraction correction(1, 5);
                        result = a * b; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a * b) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());

                        result = a * c; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a * c) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction correction(38, 100);
                        result = a * d; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a * d) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction correction(22, 100);
                        result = a * e; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a * e) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction correction(18, 100);
                        result = a * f; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a * f) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }
                }

                {
                    Logger::WriteMessage("\ta=10/5 ; b=int(1) ; c=long int(1) ; d=double(1.9) ; e=double(1.1) ; f=double(0.9) ...");
                    Membre a(10, 5);
                    Membre minus_a(-a); minus_a.simplifier();
                    Membre result;
                    int b(1);
                    long int c(1);
                    double d(1.9);
                    double e(1.1);
                    double f(0.9);
                    std::string msg;

                    {
                        ZFraction correction(2, 1);
                        result = a * b; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a * b) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());

                        result = a * c; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a * c) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction correction(38, 10);
                        result = a * d; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a * d) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction correction(22, 10);
                        result = a * e; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a * e) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction correction(18, 10);
                        result = a * f; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a * f) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }
                }

                {
                    Logger::WriteMessage("\ta=1.5 ; b=int(1) ; c=long int(1) ; d=double(1.9) ; e=double(1.1) ; f=double(0.9) ...");
                    Membre a(1.5);
                    Membre minus_a(-a); minus_a.simplifier();
                    Membre result;
                    int b(1);
                    long int c(1);
                    double d(1.9);
                    double e(1.1);
                    double f(0.9);
                    std::string msg;

                    {
                        ZFraction correction(3, 2);
                        result = a * b; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a * b) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());

                        result = a * c; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a * c) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction correction(285, 100);
                        result = a * d; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a * d) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction correction(165, 100);
                        result = a * e; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a * e) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction correction(135, 100);
                        result = a * f; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a * f) == " + result.afficherPlainText() + "\t... OK !";
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

        TEST_METHOD(Membre_operatorDIVIDE)
        {
            Logger::WriteMessage("\n Membre_operatorDIVIDE");
            wchar_t message[200];
            try
            {
                {
                    Logger::WriteMessage("\ta=1/5 ; b=int(1) ; c=long int(1) ; d=double(2.) ; e=double(0.5) ...");
                    Membre a(1, 5);
                    Membre minus_a(-a); minus_a.simplifier();
                    Membre result;
                    int b(1);
                    long int c(1);
                    double d(2.);
                    double e(0.5);
                    std::string msg;

                    {
                        ZFraction correction(1, 5);
                        result = a / b; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a / b) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());

                        result = a / c; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a / c) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction correction(10, 100);
                        result = a / d; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a / d) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction correction(40, 100);
                        result = a / e; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a / e) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }
                }

                {
                    Logger::WriteMessage("\ta=10/5 ; b=int(1) ; c=long int(1) ; d=double(2.) ; e=double(0.5) ...");
                    Membre a(10, 5);
                    Membre minus_a(-a); minus_a.simplifier();
                    Membre result;
                    int b(1);
                    long int c(1);
                    double d(2.);
                    double e(0.5);
                    std::string msg;

                    {
                        ZFraction correction(2, 1);
                        result = a / b; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a / b) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());

                        result = a / c; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a / c) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction correction(10, 10);
                        result = a / d; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a / d) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction correction(40, 10);
                        result = a / e; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a / e) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }
                }

                {
                    Logger::WriteMessage("\ta=1.5 ; b=int(1) ; c=long int(1) ; d=double(2.) ; e=double(0.5) ...");
                    Membre a(1.5);
                    Membre minus_a(-a); minus_a.simplifier();
                    Membre result;
                    int b(1);
                    long int c(1);
                    double d(2.);
                    double e(0.5);
                    std::string msg;

                    {
                        ZFraction correction(3, 2);
                        result = a / b; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a / b) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());

                        result = a / c; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a / c) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction correction(75, 100);
                        result = a / d; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a / d) == " + result.afficherPlainText() + "\t... OK !";
                        Logger::WriteMessage(msg.c_str());
                    }

                    {
                        ZFraction correction(3, 1);
                        result = a / e; result.simplifier();
                        Assert::IsTrue(result.getResultat() == correction);
                        msg = "\t\t(a / e) == " + result.afficherPlainText() + "\t... OK !";
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

        TEST_METHOD(ABANDON_Membre_afficher)
        {
            Logger::WriteMessage("\n ABANDON_Membre_afficher");
            wchar_t message[200];
            try
            {
                Logger::WriteMessage("** Test abandonne **");
                swprintf_s(message, L"** Test abandonne **");
                Assert::Fail(message, LINE_INFO());
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }


        TEST_METHOD(Membre_afficherPlainText)
        {
            Logger::WriteMessage("\n Membre_afficherPlainText");
            wchar_t message[200];
            try
            {
                {
                    Membre a(1, 5);
                    Assert::AreEqual<std::string>("1/5", a.afficherPlainText());
                    Logger::WriteMessage("\ta=1/5\t... OK !");
                }
                {
                    Membre a(-1, 5);
                    Assert::AreEqual<std::string>("-1/5", a.afficherPlainText());
                    Logger::WriteMessage("\ta=(-1)/5\t... OK !");
                }
                {
                    Membre a(1, -5);
                    Assert::AreEqual<std::string>("-1/5", a.afficherPlainText());
                    Logger::WriteMessage("\ta=1/(-5)\t... OK !");
                }

                {
                    Membre b(8, 2);
                    Assert::AreEqual<std::string>("4", b.afficherPlainText());
                    Logger::WriteMessage("\tb=8/2\t... OK !");
                }
                {
                    Membre b(-8, 2);
                    Assert::AreEqual<std::string>("-4", b.afficherPlainText());
                    Logger::WriteMessage("\tb=(-8)/2\t... OK !");
                }
                {
                    Membre b(8, -2);
                    Assert::AreEqual<std::string>("-4", b.afficherPlainText());
                    Logger::WriteMessage("\tb=8/(-2)\t... OK !");
                }

                {
                    Membre c(1.5);
                    Assert::AreEqual<std::string>("3/2", c.afficherPlainText());
                    Logger::WriteMessage("\tc=1.5\t... OK !");
                }
                {
                    Membre c(-1.5);
                    Assert::AreEqual<std::string>("-3/2", c.afficherPlainText());
                    Logger::WriteMessage("\tc=-1.5\t... OK !");
                }
                {
                    Membre a, b(1), c(2, 3);
                    Membre d(b * c * 7);
                    Assert::AreEqual<std::string>(" ", a.afficherPlainText());
                    Assert::AreEqual<std::string>("1", b.afficherPlainText());
                    Assert::AreEqual<std::string>("2/3", c.afficherPlainText());
                    Assert::AreEqual<std::string>("1x2/3x7", d.afficherPlainText());
                    Logger::WriteMessage("\ta=vide ; b=1 ; c=2/3 ; d=b*c*7\t... OK !");
                }
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }


        TEST_METHOD(ABANDON_Membre_afficherHTML)
        {
            Logger::WriteMessage("\n ABANDON_Membre_afficherHTML");
            wchar_t message[200];
            try
            {
                Logger::WriteMessage("** Test abandonne **");
                swprintf_s(message, L"** Test abandonne **");
                Assert::Fail(message, LINE_INFO());
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ABANDON_Membre_afficherOperation)
        {
            Logger::WriteMessage("\n ABANDON_Membre_afficherOperation");
            wchar_t message[200];
            try
            {
                Logger::WriteMessage("** Test abandonne **");
                swprintf_s(message, L"** Test abandonne **");
                Assert::Fail(message, LINE_INFO());
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(Membre_afficherOperationPlainText)
        {
            Logger::WriteMessage("\n Membre_afficherOperationPlainText");
            wchar_t message[200];
            try
            {
                {
                    Assert::AreEqual<std::string>(" ", Membre::afficherOperationPlainText(Membre::operation_Aucune));
                    Logger::WriteMessage("\tvide\t... OK !");
                }
                {
                    Assert::AreEqual<std::string>("+", Membre::afficherOperationPlainText(Membre::operation_addition));
                    Logger::WriteMessage("\t+\t... OK !");
                }
                {
                    Assert::AreEqual<std::string>("-", Membre::afficherOperationPlainText(Membre::operation_soustraction));
                    Logger::WriteMessage("\t-\t... OK !");
                }
                {
                    Assert::AreEqual<std::string>("x", Membre::afficherOperationPlainText(Membre::operation_multiplication));
                    Logger::WriteMessage("\t/\t... OK !");
                }

                {
                    Assert::AreEqual<std::string>("/", Membre::afficherOperationPlainText(Membre::operation_division));
                    Logger::WriteMessage("\tx\t... OK !");
                }
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }


        TEST_METHOD(ABANDON_Membre_afficherOperationHTML)
        {
            Logger::WriteMessage("\n ABANDON_Membre_afficherOperationHTML");
            wchar_t message[200];
            try
            {
                Logger::WriteMessage("** Test abandonne **");
                swprintf_s(message, L"** Test abandonne **");
                Assert::Fail(message, LINE_INFO());
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ABANDON_Membre_ouvrirParenthese)
        {
            Logger::WriteMessage("\n ABANDON_Membre_ouvrirParenthese");
            wchar_t message[200];
            try
            {
                Logger::WriteMessage("** Test abandonne **");
                swprintf_s(message, L"** Test abandonne **");
                Assert::Fail(message, LINE_INFO());
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ABANDON_Membre_fermerParenthese)
        {
            Logger::WriteMessage("\n ABANDON_Membre_fermerParenthese");
            wchar_t message[200];
            try
            {
                Logger::WriteMessage("** Test abandonne **");
                swprintf_s(message, L"** Test abandonne **");
                Assert::Fail(message, LINE_INFO());
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ABANDON_Membre_operator_aucuneOperation)
        {
            Logger::WriteMessage("\n ABANDON_Membre_operator_aucuneOperation");
            wchar_t message[200];
            try
            {
                Logger::WriteMessage("** Test abandonne **");
                swprintf_s(message, L"** Test abandonne **");
                Assert::Fail(message, LINE_INFO());
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ABANDON_Membre_operator_generic)
        {
            Logger::WriteMessage("\n ABANDON_Membre_operator_generic");
            wchar_t message[200];
            try
            {
                Logger::WriteMessage("** Test abandonne **");
                swprintf_s(message, L"** Test abandonne **");
                Assert::Fail(message, LINE_INFO());
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

    };
}