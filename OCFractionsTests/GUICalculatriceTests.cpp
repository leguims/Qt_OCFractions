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