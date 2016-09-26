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

        TEST_METHOD(divisionZeroConstructeurZFraction)
        {
            Logger::WriteMessage("divisionZeroConstructeurZFraction");
            wchar_t message[200];
            try
            {
                // Should raise an exception:
                ZFraction *pA = nullptr;
                ZFraction b(1, 2);
                ZFraction a(5, 0);
                _swprintf(message, L"Pas d'exception generee");
                Assert::Fail(message, LINE_INFO());
            }
            catch (std::domain_error ex)
            {
            }
            catch (...)
            {
                _swprintf(message, L"Mauvaise exception generee");
                Assert::Fail(message, LINE_INFO());
            }
        }
    };
}