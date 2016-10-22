#include "guicalulatrice.h"
#include <iostream>

GUICalulatrice::GUICalulatrice() :
	membre_()
{
}

//
// Mode d'affichage
//
void GUICalulatrice::on_bouton_fraction_clicked(void)
{
	membre_.setAfficherFraction(!membre_.getAfficherFraction());
}


//
// Operation liant avec le nombre suivant
//
void GUICalulatrice::on_bouton_addition_clicked(void)
{
	// Enregistrer la saisie realisee dans membre_
	enregistrerNombre();
	
	// Enregistrer la prochaine operation
	oper_ = Membre::operation_addition;

	afficherMembre();
}

void GUICalulatrice::on_bouton_soustraction_clicked()
{
	// Enregistrer la saisie realisee dans membre_
	enregistrerNombre();

	// Enregistrer la prochaine operation
	oper_ = Membre::operation_soustraction;

	afficherMembre();
}

void GUICalulatrice::on_bouton_multiplication_clicked()
{
	// Enregistrer la saisie realisee dans membre_
	enregistrerNombre();

	// Enregistrer la prochaine operation
	oper_ = Membre::operation_multiplication;

	afficherMembre();
}

void GUICalulatrice::on_bouton_division_clicked()
{
	// Enregistrer la saisie realisee dans membre_
	enregistrerNombre();

	// Enregistrer la prochaine operation
	oper_ = Membre::operation_division;

	afficherMembre();
}

void GUICalulatrice::on_bouton_parenthese_ouvrante_clicked()
{
	// Enregistrer parenthese ouvrante
	membre_.ouvrirParenthese(oper_);

	// Reinitialise la saisie des decimales et du nombre
	oper_ = Membre::operation_Aucune;
	saisieNumerateur_ = 0;
	saisieDenominateur_ = 1;
	saisieDecimales_ = false;
	saisieVide_ = true;

	afficherMembre();
}

void GUICalulatrice::on_bouton_parenthese_fermante_clicked()
{
	// Enregistrer la saisie realisee dans membre_
	enregistrerNombre();

	// Enregistrer parenthese ouvrante
	membre_.fermerParenthese();

	// Reinitialise la saisie des decimales et du nombre
	oper_ = Membre::operation_Aucune;
	saisieNumerateur_ = 0;
	saisieDenominateur_ = 1;
	saisieDecimales_ = false;
	saisieVide_ = true;

	afficherMembre();
}


//
// Fin de l'operation : resultat
//
void GUICalulatrice::on_bouton_resultat_clicked()
{
	if (Membre::operation_Aucune != oper_)
	{
		// Enregistrer la saisie realisee dans membre_
		enregistrerNombre();
		// Enregistrer la prochaine operation
		oper_ = Membre::operation_Aucune;

		// Afficher l'operation complete a resoudre
		std::cout << membre_ << std::endl;
		afficherResultat();
	}
	else
	{
		// Resoudre l'operation
		membre_.simplifier();

		afficherResultat();
	}
}


//
// Saisie du nombre courant
//
void GUICalulatrice::on_bouton_inverse_clicked()
{
}

void GUICalulatrice::on_bouton_effacer_clicked()
{
	membre_.vider();
	oper_ = Membre::operation_Aucune;
	saisieNumerateur_ = 0;
	saisieDenominateur_ = 1;
	saisieDecimales_ = false;
	saisieVide_ = true;
}

void GUICalulatrice::on_bouton_oppose_clicked()
{
}

void GUICalulatrice::on_bouton_virgule_clicked()
{
	if (!saisieDecimales_)
	{
		saisieDecimales_ = true;
	}
}

void GUICalulatrice::enregistrerNombre()
{
	if (0 != saisieNumerateur_ || !saisieVide_)
	{
		// Appliquer l'attribut "oper" comme operation sur le membre
		// Si "oper==operation_Aucune", initialiser le membre avec la saisie
		switch (oper_)
		{
		case Membre::operation_Aucune:
			if (membre_.isEmpty())
			{
				membre_ = ZFraction(saisieNumerateur_, saisieDenominateur_);
			}
			else
			{
				// 1er nombre d'une parenthese
				membre_.operator_aucuneOperation( ZFraction(saisieNumerateur_, saisieDenominateur_) );
			}
			break;
		case Membre::operation_addition:
			membre_ += ZFraction(saisieNumerateur_, saisieDenominateur_);
			break;
		case Membre::operation_soustraction:
			membre_ -= ZFraction(saisieNumerateur_, saisieDenominateur_);
			break;
		case Membre::operation_multiplication:
			membre_ *= ZFraction(saisieNumerateur_, saisieDenominateur_);
			break;
		case Membre::operation_division:
			membre_ /= ZFraction(saisieNumerateur_, saisieDenominateur_);
			break;
			//default:
			//    break;
		}
		// Reinitialise la saisie des decimales et du nombre
		saisieDecimales_ = false;
		saisieVide_ = true;
		saisieNumerateur_ = 0;
		saisieDenominateur_ = 1;
	}
}


void GUICalulatrice::afficherMembre()
{
    if (plainText_)
    {
        std::cout << membre_.afficherPlainText();
        std::cout << Membre::afficherOperationPlainText(oper_) << std::endl;
    }
    else
    {
        std::cout << membre_.afficherHTML();
        std::cout << Membre::afficherOperationHTML(oper_) << std::endl;
    }
}

std::string GUICalulatrice::afficherMembrePlainText()
{
    std::string out;
    out = membre_.afficherPlainText();
    out += Membre::afficherOperationPlainText(oper_);
    return out;
}

void GUICalulatrice::afficherResultat()
{
    if (plainText_)
    {
        std::cout << membre_.afficherPlainText() << std::endl;
    }
    else
    {
        std::cout << membre_.afficherHTML() << std::endl;
    }
}

std::string  GUICalulatrice::afficherResultatPlainText()
{
    std::string out;
    out = membre_.afficherPlainText();
    return out;
}

void GUICalulatrice::on_bouton_chiffre_9_clicked()
{
	saisieNumerateur_ *= 10;
	saisieNumerateur_ += 9;
	if(saisieDecimales_)	{		saisieDenominateur_ *= 10;	}
}

void GUICalulatrice::on_bouton_chiffre_8_clicked()
{
	saisieNumerateur_ *= 10;
	saisieNumerateur_ += 8;
	saisieDecimales_ && (saisieDenominateur_ *= 10);
}

void GUICalulatrice::on_bouton_chiffre_7_clicked()
{
	saisieNumerateur_ *= 10;
	saisieNumerateur_ += 7;
	saisieDecimales_ && (saisieDenominateur_*=10);
}

void GUICalulatrice::on_bouton_chiffre_6_clicked()
{
	saisieNumerateur_ *= 10;
	saisieNumerateur_ += 6;
	saisieDecimales_ && (saisieDenominateur_ *= 10);
}

void GUICalulatrice::on_bouton_chiffre_5_clicked()
{
	saisieNumerateur_ *= 10;
	saisieNumerateur_ += 5;
	saisieDecimales_ && (saisieDenominateur_ *= 10);
}

void GUICalulatrice::on_bouton_chiffre_4_clicked()
{
	saisieNumerateur_ *= 10;
	saisieNumerateur_ += 4;
	saisieDecimales_ && (saisieDenominateur_ *= 10);
}

void GUICalulatrice::on_bouton_chiffre_3_clicked()
{
	saisieNumerateur_ *= 10;
	saisieNumerateur_ += 3;
	saisieDecimales_ && (saisieDenominateur_ *= 10);
}

void GUICalulatrice::on_bouton_chiffre_2_clicked()
{
	saisieNumerateur_ *= 10;
	saisieNumerateur_ += 2;
	saisieDecimales_ && (saisieDenominateur_ *= 10);
}

void GUICalulatrice::on_bouton_chiffre_1_clicked()
{
	saisieNumerateur_ *= 10;
	saisieNumerateur_ += 1;
	saisieDecimales_ && (saisieDenominateur_ *= 10);
}

void GUICalulatrice::on_bouton_chiffre_0_clicked()
{
	saisieNumerateur_ *= 10;
	saisieNumerateur_ += 0;
	saisieDecimales_ && (saisieDenominateur_ *= 10);
}


GUICalulatrice::~GUICalulatrice()
{
}

void GUICalulatrice::plainText(bool pt)
{
	plainText_ = pt;
}
