#include "..\Commun\Membre.h"
#include <iostream>
#include <string>
#include "guicalulatrice.h"

using namespace std;

void main()
{
	Membre m0;
	Membre m1(1);
	Membre m2(2,3);
	Membre m3(m1, Membre::operation::operation_addition, m2);
	Membre m4(m3, Membre::operation::operation_addition, Membre(1,3));
	Membre m5(m4);
	Membre m6(Membre(Membre(1), Membre::operation::operation_addition, Membre(2, 3)), Membre::operation::operation_addition, Membre(1, 3));
	Membre m7(1, Membre::operation::operation_addition, 2);
	Membre m8(1, 2, Membre::operation::operation_addition, 2, 3);
	Membre m9(1);

	cout << "m0 = " << endl << m0 << endl << endl;
	m0 = 1;
	cout << "m0 = " << endl << m0 << endl << endl;

	//m0.isSimple();
	//m1.isSimple();
	//m2.isSimple();
	//m3.isSimple();

	//m0.simplifier();
	//m1.simplifier();
	//m2.simplifier();
	//m3.simplifier();
	//m4.simplifier();

	//m0.getResultat();
	//m1.getResultat();
	//m2.getResultat();
	//m3.getResultat();
	//m4.getResultat();

	//cout << m0 << endl;
	//cout << m1 << endl;
	//cout << m2 << endl;
	//cout << m3 << endl;
	//cout << m4 << endl;

	m4.setAfficherFraction(false);
	cout << "m4 = " << endl;
	do
	{
		cout << m4 << endl;
	}while (m4.simplifier());

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

	Membre m24(m1 * m2 * 7);
	cout << "afficherPlainText()" << endl;
	cout << "m1 * m2 *7 = " << m24.afficherPlainText().c_str();
	m24.simplifier();
	cout << " simplifie = " << m24.afficherPlainText().c_str() << endl;
	m24.simplifier();
	cout << " simplifie = " << m24.afficherPlainText().c_str() << endl;

	m24  =m1 * m2 * 7;
	cout << "afficherHTML()" << endl;
	cout << "m1 * m2 *7 = " << m24.afficherHTML().c_str();
	m24.simplifier();
	cout << " simplifie = " << m24.afficherHTML().c_str() << endl;
	m24.simplifier();
	cout << " simplifie = " << m24.afficherHTML().c_str() << endl;


	cout << endl;

	GUICalulatrice	calcul;
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