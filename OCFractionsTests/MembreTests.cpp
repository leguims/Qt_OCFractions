//#include "stdafx.h"
#include "CppUnitTest.h"
//#include "../Commun/Membre.h"
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

        TEST_METHOD(Membre_isHalfComplex)
        {
            Logger::WriteMessage("\n Membre_isHalfComplex");
            wchar_t message[200];
            try
            {
                Logger::WriteMessage("** ECRIRE LE TEST **");
                swprintf_s(message, L"** ECRIRE LE TEST **");
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
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(Membre_aduaduadu)
        {
            Logger::WriteMessage("\n Membre_aduaduadu");
            wchar_t message[200];
            try
            {
                Logger::WriteMessage("** ECRIRE LE TEST **");
                swprintf_s(message, L"** ECRIRE LE TEST **");
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