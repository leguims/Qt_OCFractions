//#include "stdafx.h"
#include "CppUnitTest.h"
//#include "../Commun/Membre.h"
#include "../OperationArithmetique/guicalulatrice.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GUICalculatriceTests
{
    TEST_CLASS(GUICalculatriceTests)
    {
    public:


        TEST_METHOD(GUICalculatriceTests_saisiePlainText_01)
        {
            Logger::WriteMessage("\n GUICalculatriceTests_saisiePlainText_01");
            wchar_t message[200];
            try
            {
                {
                    Logger::WriteMessage("98.9876 + 666");

                    GUICalulatrice	calcul;

                    calcul.plainText(true);

                    calcul.on_bouton_chiffre_9_clicked();
                    calcul.on_bouton_chiffre_8_clicked();
                    calcul.on_bouton_virgule_clicked();
                    calcul.on_bouton_chiffre_9_clicked();
                    calcul.on_bouton_chiffre_8_clicked();
                    calcul.on_bouton_chiffre_7_clicked();
                    calcul.on_bouton_chiffre_6_clicked();

                    calcul.on_bouton_addition_clicked();

                    calcul.on_bouton_chiffre_6_clicked();
                    calcul.on_bouton_chiffre_6_clicked();
                    calcul.on_bouton_chiffre_6_clicked();

                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_fraction_clicked();
                    calcul.on_bouton_resultat_clicked();

                    ZFraction correction(98.9876); correction += 666;
                    Assert::IsTrue(calcul.getResultat() == correction);
                    Logger::WriteMessage("\t ... ok !");
                }
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(GUICalculatriceTests_saisiePlainText_011)
        {
            Logger::WriteMessage("\n GUICalculatriceTests_saisiePlainText_011");
            wchar_t message[200];
            try
            {
                {
                    Logger::WriteMessage("2 + 2 (dedicace Pimousse)");

                    GUICalulatrice	calcul;

                    calcul.plainText(true);

                    calcul.on_bouton_chiffre_2_clicked();

                    calcul.on_bouton_addition_clicked();

                    calcul.on_bouton_chiffre_2_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();

                    ZFraction correction(4);
                    Assert::IsTrue(calcul.getResultat() == correction);
                    Logger::WriteMessage("\t ... ok !");
                }
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(GUICalculatriceTests_saisiePlainText_020)
        {
            Logger::WriteMessage("\n GUICalculatriceTests_saisiePlainText_020");
            wchar_t message[200];
            try
            {
                {
                    Logger::WriteMessage("1+2/3*4");

                    GUICalulatrice	calcul;

                    calcul.plainText(true);

                    calcul.on_bouton_chiffre_1_clicked();
                    calcul.on_bouton_addition_clicked();

                    calcul.on_bouton_chiffre_2_clicked();
                    calcul.on_bouton_division_clicked();

                    calcul.on_bouton_chiffre_3_clicked();
                    calcul.on_bouton_multiplication_clicked();

                    calcul.on_bouton_chiffre_4_clicked();


                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();

                    ZFraction correction(11, 3);
                    Assert::IsTrue(calcul.getResultat() == correction);
                    Logger::WriteMessage("\t ... ok !");
                }
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(GUICalculatriceTests_saisiePlainText_021)
        {
            Logger::WriteMessage("\n GUICalculatriceTests_saisiePlainText_021");
            wchar_t message[200];
            try
            {
                {
                    Logger::WriteMessage("1+2/(3*4)");

                    GUICalulatrice	calcul;

                    calcul.plainText(true);

                    calcul.on_bouton_chiffre_1_clicked();
                    calcul.on_bouton_addition_clicked();

                    calcul.on_bouton_chiffre_2_clicked();
                    calcul.on_bouton_division_clicked();

                    calcul.on_bouton_parenthese_ouvrante_clicked();
                    calcul.on_bouton_chiffre_3_clicked();
                    calcul.on_bouton_multiplication_clicked();
                    calcul.on_bouton_chiffre_4_clicked();
                    calcul.on_bouton_parenthese_fermante_clicked();


                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();

                    ZFraction correction(14, 12);
                    Assert::IsTrue(calcul.getResultat() == correction);
                    Logger::WriteMessage("\t ... ok !");
                }
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(GUICalculatriceTests_saisiePlainText_022)
        {
            Logger::WriteMessage("\n GUICalculatriceTests_saisiePlainText_022");
            wchar_t message[200];
            try
            {
                //for (int i = 0; i < 1'000; ++i)
                //{
                {
                    Logger::WriteMessage("1+(2/3)*4");

                    GUICalulatrice	calcul;

                    calcul.plainText(true);

                    calcul.on_bouton_chiffre_1_clicked();
                    calcul.on_bouton_addition_clicked();

                    calcul.on_bouton_parenthese_ouvrante_clicked();
                    calcul.on_bouton_chiffre_2_clicked();
                    calcul.on_bouton_division_clicked();

                    calcul.on_bouton_chiffre_3_clicked();
                    calcul.on_bouton_parenthese_fermante_clicked();

                    calcul.on_bouton_multiplication_clicked();
                    calcul.on_bouton_chiffre_4_clicked();


                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();

                    ZFraction correction(11, 3);
                    Assert::IsTrue(calcul.getResultat() == correction);
                    Logger::WriteMessage("\t ... ok !");
                }
                //}
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(GUICalculatriceTests_saisiePlainText_040)
        {
            Logger::WriteMessage("\n GUICalculatriceTests_saisiePlainText_040");
            wchar_t message[200];
            try
            {
                {
                    Logger::WriteMessage("( (1+2)*3 -4*5*6 ) *7");

                    GUICalulatrice	calcul;

                    calcul.plainText(true);

                    calcul.on_bouton_parenthese_ouvrante_clicked();

                    calcul.on_bouton_parenthese_ouvrante_clicked();
                    calcul.on_bouton_chiffre_1_clicked();
                    calcul.on_bouton_addition_clicked();
                    calcul.on_bouton_chiffre_2_clicked();
                    calcul.on_bouton_parenthese_fermante_clicked();

                    calcul.on_bouton_multiplication_clicked();
                    calcul.on_bouton_chiffre_3_clicked();

                    calcul.on_bouton_soustraction_clicked();
                    calcul.on_bouton_chiffre_4_clicked();
                    calcul.on_bouton_multiplication_clicked();
                    calcul.on_bouton_chiffre_5_clicked();
                    calcul.on_bouton_multiplication_clicked();
                    calcul.on_bouton_chiffre_6_clicked();
                    calcul.on_bouton_parenthese_fermante_clicked();

                    calcul.on_bouton_multiplication_clicked();
                    calcul.on_bouton_chiffre_7_clicked();


                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();

                    ZFraction correction(((1 + 2) * 3 - 4 * 5 * 6) * 7);
                    Assert::IsTrue(calcul.getResultat() == correction);
                    Logger::WriteMessage("\t ... ok !");
                }
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(GUICalculatriceTests_saisiePlainText_041)
        {
            Logger::WriteMessage("\n GUICalculatriceTests_saisiePlainText_041");
            wchar_t message[200];
            try
            {
                //for (int i = 0; i < 1'000; ++i)
                //{
                {
                    Logger::WriteMessage("1+2*(3-4*5*6*7)");

                    GUICalulatrice	calcul;

                    calcul.plainText(true);

                    calcul.on_bouton_chiffre_1_clicked();
                    calcul.on_bouton_addition_clicked();

                    calcul.on_bouton_chiffre_2_clicked();
                    calcul.on_bouton_multiplication_clicked();

                    calcul.on_bouton_parenthese_ouvrante_clicked();
                    calcul.on_bouton_chiffre_3_clicked();
                    calcul.on_bouton_soustraction_clicked();
                    calcul.on_bouton_chiffre_4_clicked();
                    calcul.on_bouton_multiplication_clicked();
                    calcul.on_bouton_chiffre_5_clicked();
                    calcul.on_bouton_multiplication_clicked();
                    calcul.on_bouton_chiffre_6_clicked();
                    calcul.on_bouton_multiplication_clicked();
                    calcul.on_bouton_chiffre_7_clicked();
                    calcul.on_bouton_parenthese_fermante_clicked();

                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();

                    ZFraction correction(1 + 2 * (3 - 4 * 5 * 6 * 7));
                    Assert::IsTrue(calcul.getResultat() == correction);
                    Logger::WriteMessage("\t ... ok !");
                }
                //}
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(GUICalculatriceTests_saisiePlainText_05)
        {
            Logger::WriteMessage("\n GUICalculatriceTests_saisiePlainText_05");
            wchar_t message[200];
            try
            {
                //for (int i = 0; i < 5'000; ++i)
                //{
                {
                    Logger::WriteMessage("( ( (1+2)-5 ) -4 ) /7");

                    GUICalulatrice	calcul;

                    calcul.plainText(true);

                    calcul.on_bouton_parenthese_ouvrante_clicked();
                    calcul.on_bouton_parenthese_ouvrante_clicked();

                    calcul.on_bouton_parenthese_ouvrante_clicked();
                    calcul.on_bouton_chiffre_1_clicked();
                    calcul.on_bouton_addition_clicked();
                    calcul.on_bouton_chiffre_2_clicked();
                    calcul.on_bouton_parenthese_fermante_clicked();

                    calcul.on_bouton_soustraction_clicked();
                    calcul.on_bouton_chiffre_5_clicked();
                    calcul.on_bouton_parenthese_fermante_clicked();

                    calcul.on_bouton_soustraction_clicked();
                    calcul.on_bouton_chiffre_4_clicked();
                    calcul.on_bouton_parenthese_fermante_clicked();

                    calcul.on_bouton_division_clicked();
                    calcul.on_bouton_chiffre_7_clicked();


                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();

                    ZFraction correction((((1 + 2) - 5) - 4)); correction /= 7;
                    Assert::IsTrue(calcul.getResultat() == correction);
                    Logger::WriteMessage("\t ... ok !");
                }
                //}
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(GUICalculatriceTests_saisiePlainText_06)
        {
            Logger::WriteMessage("\n GUICalculatriceTests_saisiePlainText_06");
            wchar_t message[200];
            try
            {
                {
                    Logger::WriteMessage("1+1+1+1+1+ 1+1+1+1+1+ 1+1+1+1+1");

                    GUICalulatrice	calcul;

                    calcul.plainText(false);

                    calcul.on_bouton_chiffre_1_clicked();
                    calcul.on_bouton_addition_clicked();

                    calcul.on_bouton_chiffre_1_clicked();
                    calcul.on_bouton_addition_clicked();

                    calcul.on_bouton_chiffre_1_clicked();
                    calcul.on_bouton_addition_clicked();

                    calcul.on_bouton_chiffre_1_clicked();
                    calcul.on_bouton_addition_clicked();

                    calcul.on_bouton_chiffre_1_clicked();
                    calcul.on_bouton_addition_clicked();

                    calcul.on_bouton_chiffre_1_clicked();
                    calcul.on_bouton_addition_clicked();

                    calcul.on_bouton_chiffre_1_clicked();
                    calcul.on_bouton_addition_clicked();

                    calcul.on_bouton_chiffre_1_clicked();
                    calcul.on_bouton_addition_clicked();

                    calcul.on_bouton_chiffre_1_clicked();
                    calcul.on_bouton_addition_clicked();

                    calcul.on_bouton_chiffre_1_clicked();
                    calcul.on_bouton_addition_clicked();

                    calcul.on_bouton_chiffre_1_clicked();
                    calcul.on_bouton_addition_clicked();

                    calcul.on_bouton_chiffre_1_clicked();
                    calcul.on_bouton_addition_clicked();

                    calcul.on_bouton_chiffre_1_clicked();
                    calcul.on_bouton_addition_clicked();

                    calcul.on_bouton_chiffre_1_clicked();
                    calcul.on_bouton_addition_clicked();

                    calcul.on_bouton_chiffre_1_clicked();

                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();

                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();

                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();

                    calcul.on_bouton_resultat_clicked();

                    ZFraction correction(15);
                    Assert::IsTrue(calcul.getResultat() == correction);
                    Logger::WriteMessage("\t ... ok !");
                }
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(GUICalculatriceTests_saisiePlainText_07)
        {
            Logger::WriteMessage("\n GUICalculatriceTests_saisiePlainText_07");
            wchar_t message[200];
            try
            {
                //for (int i = 0; i < 1'000; ++i)
                //{
                {
                    Logger::WriteMessage("1+ (2+ ( (1/3)/ (4-(3x2)) ) )");
                    int i(0);

                    GUICalulatrice	calcul;

                    calcul.plainText(false);

                    calcul.on_bouton_chiffre_1_clicked();
                    calcul.on_bouton_addition_clicked();
                    Logger::WriteMessage((std::to_string(++i)+std::string(" : ")+ calcul.afficherMembrePlainText()).c_str());

                    calcul.on_bouton_parenthese_ouvrante_clicked();
                    calcul.on_bouton_chiffre_2_clicked();
                    calcul.on_bouton_addition_clicked();

                    calcul.on_bouton_parenthese_ouvrante_clicked();
                    Logger::WriteMessage((std::to_string(++i) + std::string(" : ") + calcul.afficherMembrePlainText()).c_str());

                    calcul.on_bouton_parenthese_ouvrante_clicked();
                    calcul.on_bouton_chiffre_1_clicked();
                    calcul.on_bouton_division_clicked();
                    calcul.on_bouton_chiffre_3_clicked();
                    calcul.on_bouton_parenthese_fermante_clicked();

                    calcul.on_bouton_division_clicked();
                    Logger::WriteMessage((std::to_string(++i) + std::string(" : ") + calcul.afficherMembrePlainText()).c_str());

                    calcul.on_bouton_parenthese_ouvrante_clicked();
                    Logger::WriteMessage((std::to_string(++i) + std::string(" : ") + calcul.afficherMembrePlainText()).c_str());
                    calcul.on_bouton_chiffre_4_clicked();
                    Logger::WriteMessage((std::to_string(++i) + std::string(" : ") + calcul.afficherMembrePlainText()).c_str());
                    calcul.on_bouton_soustraction_clicked();
                    Logger::WriteMessage((std::to_string(++i) + std::string(" : ") + calcul.afficherMembrePlainText()).c_str());

                    calcul.on_bouton_parenthese_ouvrante_clicked();
                    Logger::WriteMessage((std::to_string(++i) + std::string(" : ") + calcul.afficherMembrePlainText()).c_str());
                    calcul.on_bouton_chiffre_3_clicked();
                    calcul.on_bouton_multiplication_clicked();
                    calcul.on_bouton_chiffre_2_clicked();
                    calcul.on_bouton_parenthese_fermante_clicked();
                    calcul.on_bouton_parenthese_fermante_clicked();
                    Logger::WriteMessage((std::to_string(++i) + std::string(" : ") + calcul.afficherMembrePlainText()).c_str());

                    calcul.on_bouton_parenthese_fermante_clicked();

                    calcul.on_bouton_parenthese_fermante_clicked();
                    Logger::WriteMessage((std::to_string(++i) + std::string(" : ") + calcul.afficherMembrePlainText()).c_str());

                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();
                    calcul.on_bouton_resultat_clicked();

                    calcul.on_bouton_resultat_clicked();

                    ZFraction correction(17, 6);
                    Assert::IsTrue(calcul.getResultat() == correction);
                    Logger::WriteMessage("\t ... ok !");
                }
                //}
            }
            catch (...)
            {
                swprintf_s(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(GUICalculatriceTests_aduADUadu)
        {
            Logger::WriteMessage("\n GUICalculatriceTests_aduADUadu");
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