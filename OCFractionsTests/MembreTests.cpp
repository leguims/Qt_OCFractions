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
        TEST_METHOD(Membre_aduaduadu)
        {
            Logger::WriteMessage("\nMembre_aduaduadu");
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