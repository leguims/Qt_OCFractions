#include "guicalulatrice.h"
#include "ui_guicalulatrice.h"

GUICalulatrice::GUICalulatrice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GUICalulatrice)
{
    ui->setupUi(this);
}

//
// Mode d'affichage
//
void GUICalulatrice::on_bouton_fraction_clicked(void)
{
    if(true == m_afficherFraction)
    {
        m_afficherFraction = false;
        ui->formatAffichageNombreReel->setText("Virgule");
        ui->affichageResultat->setText("Virgule");
    }
    else
    {
        m_afficherFraction = true;
        ui->formatAffichageNombreReel->setText("Fraction");
        ui->affichageResultat->setText("Fraction");
    }
}


//
// Operation liant avec le nombre suivant
//
void GUICalulatrice::on_bouton_addition_clicked(void)
{
    ui->affichageResultat->setText("addition");
}

void GUICalulatrice::on_bouton_soustraction_clicked()
{
    ui->affichageResultat->setText("soustraction");
}

void GUICalulatrice::on_bouton_multiplication_clicked()
{
    ui->affichageResultat->setText("multiplication");
}

void GUICalulatrice::on_bouton_division_clicked()
{
    ui->affichageResultat->setText("division");
}

void GUICalulatrice::on_bouton_parenthese_ouvrante_clicked()
{
    ui->affichageResultat->setText("parenthese ouvrante");
}

void GUICalulatrice::on_bouton_parenthese_fermante_clicked()
{
    ui->affichageResultat->setText("parenthese fermante");
}


//
// Fin de l'operation : resultat
//
void GUICalulatrice::on_bouton_resultat_clicked()
{
    ui->affichageResultat->setText("resultat");
}


//
// Saisie du nombre courant
//
void GUICalulatrice::on_bouton_inverse_clicked()
{
    ui->affichageResultat->setText("inverse");
}

void GUICalulatrice::on_bouton_effacer_clicked()
{
    ui->affichageResultat->setText("effacer");
}

void GUICalulatrice::on_bouton_oppose_clicked()
{
    ui->affichageResultat->setText("oppose");
}

void GUICalulatrice::on_bouton_virgule_clicked()
{
    ui->affichageResultat->setText("virgule");
}

void GUICalulatrice::on_bouton_chiffre_9_clicked()
{
    ui->affichageResultat->setText("chiffre_9");
}

void GUICalulatrice::on_bouton_chiffre_8_clicked()
{
    ui->affichageResultat->setText("chiffre_8");
}

void GUICalulatrice::on_bouton_chiffre_7_clicked()
{
    ui->affichageResultat->setText("chiffre_7");
}

void GUICalulatrice::on_bouton_chiffre_6_clicked()
{
    ui->affichageResultat->setText("chiffre_6");
}

void GUICalulatrice::on_bouton_chiffre_5_clicked()
{
    ui->affichageResultat->setText("chiffre_5");
}

void GUICalulatrice::on_bouton_chiffre_4_clicked()
{
    ui->affichageResultat->setText("chiffre_4");
}

void GUICalulatrice::on_bouton_chiffre_3_clicked()
{
    ui->affichageResultat->setText("chiffre_3");
}

void GUICalulatrice::on_bouton_chiffre_2_clicked()
{
    ui->affichageResultat->setText("chiffre_2");
}

void GUICalulatrice::on_bouton_chiffre_1_clicked()
{
    ui->affichageResultat->setText("chiffre_1");
}

void GUICalulatrice::on_bouton_chiffre_0_clicked()
{
    ui->affichageResultat->setText("chiffre_0");
}


GUICalulatrice::~GUICalulatrice()
{
    delete ui;
}
