#include "..\Commun\Membre.h"
#include <iostream>
#include <string>
#include "guicalulatrice.h"

using namespace std;

void test_constructeurCopie(void);
void test_isSimple(void);
void test_simplifier(void);
void test_getResultat(void);
void test_cout(void);
void test_setAfficherFraction(void);
void test_constructeurOperator(void);
void test_afficherPlainText(void);
void test_afficherHTML(void);
void test_saisieCalculatrice_PlainText_01(void);

void main()
{
	Membre m0, m1(1), m2(2, 3);
	Membre m3(m1, Membre::operation::operation_addition, m2);
	Membre m4(m3, Membre::operation::operation_addition, Membre(1, 3));
	Membre m5(m4);
	Membre m6(Membre(Membre(1), Membre::operation::operation_addition, Membre(2, 3)), Membre::operation::operation_addition, Membre(1, 3));
	Membre m7(1, Membre::operation::operation_addition, 2);
	Membre m8(1, 2, Membre::operation::operation_addition, 2, 3);
	Membre m9(1);

	test_constructeurCopie();
	//test_isSimple();
	//test_simplifier();
	//test_getResultat();
	test_cout();
	test_setAfficherFraction();
	test_constructeurOperator();
	test_afficherPlainText();
	//test_afficherHTML();
	test_saisieCalculatrice_PlainText_01();
}

void test_constructeurCopie(void)
{
	cout << endl << endl << "### test_constructeurCopie :" << endl;
	Membre m0;

	cout << "Membre m0; ..." << endl;
	cout << "m0 = " << m0 << endl;
	cout << "... m0 = 1 ..." << endl; m0 = 1;
	cout << "m0 = " << m0 << endl << endl;
}

void test_isSimple(void)
{
	cout << endl << endl << "### test_isSimple :" << endl;
	Membre m0;
	Membre m1(1);
	Membre m2(2, 3);
	Membre m3(m1, Membre::operation::operation_addition, m2);
	Membre m4(m3, Membre::operation::operation_addition, Membre(1, 3));

	m0.isSimple();
	m1.isSimple();
	m2.isSimple();
	m3.isSimple();
	m4.isSimple();
}

void test_simplifier(void)
{
	cout << endl << endl << "### test_simplifier :" << endl;
	Membre m0;
	Membre m1(1);
	Membre m2(2, 3);
	Membre m3(m1, Membre::operation::operation_addition, m2);
	Membre m4(m3, Membre::operation::operation_addition, Membre(1, 3));

	m0.simplifier();
	m1.simplifier();
	m2.simplifier();
	m3.simplifier();
	m4.simplifier();
}

void test_getResultat(void)
{
	cout << endl << endl << "### test_getResultat :" << endl;
	Membre m0;
	Membre m1(1);
	Membre m2(2, 3);
	Membre m3(m1, Membre::operation::operation_addition, m2);
	Membre m4(m3, Membre::operation::operation_addition, Membre(1, 3));

	m0.getResultat();
	m1.getResultat();
	m2.getResultat();
	m3.getResultat();
	m4.getResultat();
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
	Membre m4(m3, Membre::operation::operation_addition, Membre(1, 3));
	Membre m5(m4);
	Membre m6(Membre(Membre(1), Membre::operation::operation_addition, Membre(2, 3)), Membre::operation::operation_addition, Membre(1, 3));
	Membre m7(1, Membre::operation::operation_addition, 2);
	Membre m8(1, 2, Membre::operation::operation_addition, 2, 3);
	Membre m9(1);

	m4.setAfficherFraction(false);
	cout << "m4 = " << endl;
	do
	{
		cout << m4 << endl;
	} while (m4.simplifier());

	cout << endl;

	m5.setAfficherFraction();
	cout << "m5 = " << endl;
	do
	{
		cout << m5 << endl;
	} while (m5.simplifier());

	cout << endl;

	m6.setAfficherFraction();
	cout << "m6 = " << endl;
	do
	{
		cout << m6 << endl;
	} while (m6.simplifier());

	cout << endl;

	m7.setAfficherFraction();
	cout << "m7 = " << endl;
	do
	{
		cout << m7 << endl;
	} while (m7.simplifier());

	cout << endl;

	m8.setAfficherFraction();
	cout << "m8 = " << endl;
	do
	{
		cout << m8 << endl;
	} while (m8.simplifier());

	cout << endl;

	m9 += 2;
	m9 += ZFraction(1, 3);
	m9 /= 4;
	m9 -= ZFraction(9, 3);
	m9 *= ZFraction(4, 2);
	m9.setAfficherFraction();
	cout << "m9 = " << endl;
	do
	{
		cout << m9 << endl;
	} while (m9.simplifier());

	cout << endl;
}

void test_constructeurOperator(void)
{
	cout << endl << endl << "### test_constructeurOperator :" << endl;

	Membre m0, m1(1), m2(2, 3);
	cout << "m1 = " << m1 << endl;
	cout << "m2 = " << m2 << endl;

	Membre m20(m1 + m2);
	cout << "m1 + m2 = " << m20;
	m20.simplifier();
	cout << " simplifie = " << m20 << endl;

	Membre m21(m1 - m2);
	cout << "m1 - m2 = " << m21;
	m21.simplifier();
	cout << " simplifie = " << m21 << endl;

	Membre m22(m1 / m2);
	cout << "m1 / m2 = " << m22;
	m22.simplifier();
	cout << " simplifie = " << m22 << endl;

	Membre m23(m1 * m2 * 7);
	cout << "m1 * m2 *7 = " << m23;
	m23.simplifier();
	cout << " simplifie = " << m23 << endl;
	m23.simplifier();
	cout << " simplifie = " << m23 << endl;

}

void test_afficherPlainText(void)
{
	cout << endl << endl << "### test_afficherPlainText :" << endl;

	Membre m0, m1(1), m2(2, 3);
	cout << "m1 = " << m1 << endl;
	cout << "m2 = " << m2 << endl;

	Membre m24(m1 * m2 * 7);
	cout << "afficherPlainText()" << endl;
	cout << "m1 * m2 *7 = " << m24.afficherPlainText().c_str();
	m24.simplifier();
	cout << " simplifie = " << m24.afficherPlainText().c_str() << endl;
	m24.simplifier();
	cout << " simplifie = " << m24.afficherPlainText().c_str() << endl;
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
}

void test_saisieCalculatrice_PlainText_01(void)
{
	cout << endl << endl << "### test_saisieCalculatrice_PlainText_01 : 98.9876 + 666 = = = FRACTION = " << endl;

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
}


