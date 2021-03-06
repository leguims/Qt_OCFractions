#ifndef GUICALULATRICE_H
#define GUICALULATRICE_H

#include <QDialog>
#include <QString>
#include "../Commun/Membre.h"

namespace Ui {
class GUICalulatrice;
}

class GUICalulatrice : public QDialog
{
    Q_OBJECT

public slots:
    // Mode d'affichage
    void on_bouton_fraction_clicked(void);

    // Operation liant avec le nombre suivant
    void on_bouton_addition_clicked(void);
    void on_bouton_soustraction_clicked(void);
    void on_bouton_multiplication_clicked(void);
    void on_bouton_division_clicked(void);
    void on_bouton_parenthese_ouvrante_clicked(void);
    void on_bouton_parenthese_fermante_clicked(void);

    // Fin de l'operation : resultat
    void on_bouton_resultat_clicked(void);

    // Saisie du nombre courant
    void on_bouton_inverse_clicked(void);
    void on_bouton_effacer_clicked(void);
    void on_bouton_oppose_clicked(void);
    void on_bouton_virgule_clicked(void);
    void on_bouton_chiffre_0_clicked(void);
    void on_bouton_chiffre_1_clicked(void);
    void on_bouton_chiffre_2_clicked(void);
    void on_bouton_chiffre_3_clicked(void);
    void on_bouton_chiffre_4_clicked(void);
    void on_bouton_chiffre_5_clicked(void);
    void on_bouton_chiffre_6_clicked(void);
    void on_bouton_chiffre_7_clicked(void);
    void on_bouton_chiffre_8_clicked(void);
    void on_bouton_chiffre_9_clicked(void);

private:
    void enregistrerNombre();
    void afficherMembre();
    void afficherResultat();

public:
    explicit GUICalulatrice(QWidget *parent = 0);
    ~GUICalulatrice();
    void plainText(bool);
    std::string  afficherMembrePlainText();     // for debug only
    std::string  afficherResultatPlainText();   // for debug only
    ZFraction getResultat() const;

private:
    Membre	membre_;
	Membre::operation oper_ = Membre::operation_Aucune;
	int		saisieNumerateur_ = 0;
	int		saisieDenominateur_ = 1;
	bool	saisieDecimales_ = false;
	bool	saisieVide_ = true;
	bool	plainText_ = false;

    Ui::GUICalulatrice *ui;
};

#endif // GUICALULATRICE_H
