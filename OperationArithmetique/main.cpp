#include "..\Commun\Membre.h"
#include <iostream>
#include <string>
#include "guicalulatrice.h"

using namespace std;

void test_cout(void);
void test_setAfficherFraction(void);
void test_afficherHTML(void);

static int nbBug = 0;

void main()
{
    //int n(1), d(5);
    //for (int i = 0; i < 1'000'000; ++i)
    //{
    //    double re(0.);
    //    re = static_cast<double>(n) / d;
    //}
    //cout << "Loop1 " << endl;

    //for (int i = 0; i < 1'000'000; ++i)
    //{
    //    double re(0.);
    //    re = 1. * n / d;
    //}
    //cout << "Loop2 " << endl;

    try
    {
        // genere dans ZFractionTests : 
        test_cout();
        test_setAfficherFraction();
        //test_afficherHTML();

        cout << endl << endl << "**** Nombre total de bugs : " << nbBug << endl;
    }
    catch (exception const& e) //On rattrape les exceptions standard de tous types
    {
        cerr << "ERREUR : " << e.what() << endl; //On affiche la description de l'erreur
    }
}

void test_cout(void)
{
    cout << endl << endl << "### test_cout :" << endl;
    Membre m0;
    Membre m1(1);
    Membre m2(2, 3);
    Membre m3(m1, Membre::operation::operation_addition, m2);
    Membre m4(m3, Membre::operation::operation_addition, Membre(1, 3));

    cout << m0 << endl;
    cout << m1 << endl;
    cout << m2 << endl;
    cout << m3 << endl;
    cout << m4 << endl;
}

void test_setAfficherFraction(void)
{
    cout << endl << endl << "### test_setAfficherFraction :" << endl;
    Membre m0, m1(1), m2(2, 3);
    Membre m3(m1, Membre::operation::operation_addition, m2);
    Membre m6(Membre(Membre(1), Membre::operation::operation_addition, Membre(2, 3)), Membre::operation::operation_addition, Membre(1, 3));
    Membre m7(1, Membre::operation::operation_addition, 2);
    Membre m8(1, 2, Membre::operation::operation_addition, 2, 3);
    Membre m9(1);

    cout << endl;

    m6.setAfficherFraction();
    cout << "m6 = " << endl;
    do
    {
        cout << m6 << endl;
    } while (m6.simplifier());
    if (m6.getResultat() != ZFraction(2))
    {
        cout << "!! BUG !! ==> Correction : m6 = 2" << endl; nbBug++;
    }

    cout << endl;

    m7.setAfficherFraction();
    cout << "m7 = " << endl;
    do
    {
        cout << m7 << endl;
    } while (m7.simplifier());
    if (m7.getResultat() != ZFraction(3))
    {
        cout << "!! BUG !! ==> Correction : m7 = 3" << endl; nbBug++;
    }

    cout << endl;

    m8.setAfficherFraction();
    cout << "m8 = " << endl;
    do
    {
        cout << m8 << endl;
    } while (m8.simplifier());
    if (m8.getResultat() != ZFraction(7, 6))
    {
        cout << "!! BUG !! ==> Correction : m8 = 7/6" << endl; nbBug++;
    }

    cout << endl;

    m9 += 2;
    m9 += ZFraction(1, 3);
    m9 /= 4;
    m9 -= ZFraction(9, 3);
    m9 *= ZFraction(4, 2);
    m9.setAfficherFraction();
    cout << "m9 = 1 + 2 + 1/3 /4 - 9/3 *4/2" << endl;
    do
    {
        cout << m9 << endl;
    } while (m9.simplifier());
    if (m9.getResultat() != ZFraction(-35, 12))
    {
        cout << "!! BUG !! ==> Correction : m9 = -35/12" << endl; nbBug++;
    }

    cout << endl;
}

void test_afficherHTML(void)
{
    cout << endl << endl << "### test_afficherHTML :" << endl;

    Membre m0, m1(1), m2(2, 3);
    cout << "m1 = " << m1 << endl;
    cout << "m2 = " << m2 << endl;

    Membre m24(m1 * m2 * 7);
    m24 = m1 * m2 * 7;
    cout << "afficherHTML()" << endl;
    cout << "m1 * m2 *7 = " << m24.afficherHTML().c_str() << endl << endl;
    m24.simplifier();
    cout << " simplifie = " << m24.afficherHTML().c_str() << endl << endl;
    m24.simplifier();
    cout << " simplifie = " << m24.afficherHTML().c_str() << endl << endl;

    ZFraction correction(14, 3);
    if (m24.getResultat() != correction)
    {
        cout << "!! BUG !! ==> Correction : " << correction << endl; nbBug++;
    }
}

