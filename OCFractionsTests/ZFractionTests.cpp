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
            Logger::WriteMessage("ZFraction_divisionZeroConstructeur1\n");
            wchar_t message[200];
            try
            {
                Logger::WriteMessage("\tZFraction a(5, 0);\n");
                // Should raise an exception:
                ZFraction a(5, 0);
                _swprintf(message, L"Pas d'exception generee");
                Assert::Fail(message, LINE_INFO());
            }
            catch (std::domain_error ex)
            {
                Logger::WriteMessage("\tException attendue => OK !\n");
            }
            catch (...)
            {
                _swprintf(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ZFraction_divisionZeroConstructeur2)
        {
            Logger::WriteMessage("ZFraction_divisionZeroConstructeur2\n");
            wchar_t message[200];
            try
            {
                Logger::WriteMessage("\ta=4/1 ; b=0/3 ; c=a/b ...\n");
                // Should raise an exception:
                ZFraction a(4, 1), b(0, 3), c;
                c = a / b;
                _swprintf(message, L"Pas d'exception generee");
                Assert::Fail(message, LINE_INFO());
            }
            catch (std::domain_error ex)
            {
                Logger::WriteMessage("\tException attendue => OK !\n");
            }
            catch (...)
            {
                _swprintf(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ZFraction_divisionZeroConstructeur3)
        {
            Logger::WriteMessage("ZFraction_divisionZeroConstructeur3\n");
            wchar_t message[200];
            try
            {
                Logger::WriteMessage("\ta=3/7 ; b=0 ; c=a/b ...\n");
                // Should raise an exception:
                ZFraction a(3, 7), c;
                int b(0);
                c = a / b;
                _swprintf(message, L"Pas d'exception generee");
                Assert::Fail(message, LINE_INFO());
            }
            catch (std::domain_error ex)
            {
                Logger::WriteMessage("\tException attendue => OK !\n");
            }
            catch (...)
            {
                _swprintf(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ZFraction_conversionNumerateurReel1)
        {
            Logger::WriteMessage("ZFraction_conversionNumerateurReel1\n");
            wchar_t message[200];
            try
            {
                Logger::WriteMessage("\ta=1.05 ...\n");
                ZFraction a(1.05);
            }
            catch (std::domain_error ex)
            {
                Logger::WriteMessage("\tException inattendue !\n");
                _swprintf(message, L"Exception inattendue !");
                Assert::Fail(message, LINE_INFO());
            }
            catch (...)
            {
                _swprintf(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ZFraction_conversionNumerateurReel2)
        {
            Logger::WriteMessage("ZFraction_conversionNumerateurReel2\n");
            wchar_t message[200];
            try
            {
                Logger::WriteMessage("\ta=0.0005 ...\n");
                ZFraction a(0.0005);
            }
            catch (std::domain_error ex)
            {
                Logger::WriteMessage("\tException inattendue !\n");
                _swprintf(message, L"Exception inattendue !");
                Assert::Fail(message, LINE_INFO());
            }
            catch (...)
            {
                _swprintf(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ZFraction_conversionNumerateurReel3)
        {
            Logger::WriteMessage("ZFraction_conversionNumerateurReel3\n");
            wchar_t message[200];
            try
            {
                Logger::WriteMessage("\ta=0.00000005 ...\n");
                ZFraction a(0.00000005);
                _swprintf(message, L"Pas d'exception generee");
                Assert::Fail(message, LINE_INFO());
            }
            catch (std::domain_error ex)
            {
                Logger::WriteMessage("\tException attendue => OK !\n");
            }
            catch (...)
            {
                _swprintf(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }

        TEST_METHOD(ZFraction_conversionNumerateurReel4)
        {
            Logger::WriteMessage("ZFraction_conversionNumerateurReel4\n");
            wchar_t message[200];
            try
            {
                Logger::WriteMessage("\ta=123456.0000005 ...\n");
                ZFraction a(123456.0000005);
                _swprintf(message, L"Pas d'exception generee");
                Assert::Fail(message, LINE_INFO());
            }
            catch (std::domain_error ex)
            {
                Logger::WriteMessage("\tException attendue => OK !\n");
            }
            catch (...)
            {
                _swprintf(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }
    };
}