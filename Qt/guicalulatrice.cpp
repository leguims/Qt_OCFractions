#include "guicalulatrice.h"
#include "ui_guicalulatrice.h"

GUICalulatrice::GUICalulatrice(QWidget *parent) :
    QDialog(parent),
    membre_(),
    oper_(Membre::operation_Aucune),
    saisieNumerateur_(0),
    saisieDenominateur_(1),
    saisieDecimales_(false),
    saisieVide_(true),
    plainText_(true),
    ui(new Ui::GUICalulatrice)
{
    ui->setupUi(this);
}

//
// Mode d'affichage
//
void GUICalulatrice::on_bouton_fraction_clicked(void)
{
    membre_.setAfficherFraction(!membre_.getAfficherFraction());

    if(membre_.getAfficherFraction())
    {
        ui->bouton_fraction->setText("x/y");
        ui->formatAffichageNombreReel->setText("Fraction");
        //ui->affichageResultat->setText("Fraction");
    }
    else
    {
        ui->bouton_fraction->setText("x.yz");
        ui->formatAffichageNombreReel->setText("Virgule");
        //ui->affichageResultat->setText("Virgule");
    }
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

    //ui->affichageResultat->setText("addition");
    //ui->affichageResultat->insertPlainText("+");
    afficherMembre();
}

void GUICalulatrice::on_bouton_soustraction_clicked()
{
    // Enregistrer la saisie realisee dans membre_
    enregistrerNombre();

    // Enregistrer la prochaine operation
    oper_ = Membre::operation_soustraction;

    //ui->affichageResultat->insertPlainText("-");
    afficherMembre();
}

void GUICalulatrice::on_bouton_multiplication_clicked()
{
    // Enregistrer la saisie realisee dans membre_
    enregistrerNombre();

    // Enregistrer la prochaine operation
    oper_ = Membre::operation_multiplication;

    //ui->affichageResultat->insertPlainText("*");
    afficherMembre();
}

void GUICalulatrice::on_bouton_division_clicked()
{
    // Enregistrer la saisie realisee dans membre_
    enregistrerNombre();

    // Enregistrer la prochaine operation
    oper_ = Membre::operation_division;

    //ui->affichageResultat->insertPlainText("/");
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

    //ui->affichageResultat->insertPlainText("(");
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

    //ui->affichageResultat->insertPlainText(")");
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

        //ui->affichageResultat->setText("resultat");
        //afficherMembre();
        afficherResultat();
    }
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
    //ui->affichageResultat->setText("effacer");
    ui->affichageResultat->clear();

    membre_.vider();
    oper_ = Membre::operation_Aucune;
    saisieNumerateur_ = 0;
    saisieDenominateur_ = 1;
    saisieDecimales_ = false;
    saisieVide_ = true;
}

void GUICalulatrice::on_bouton_oppose_clicked()
{
    ui->affichageResultat->setText("oppose");
}

void GUICalulatrice::on_bouton_virgule_clicked()
{
    if (!saisieDecimales_)
    {
        saisieDecimales_ = true;
    }

    ui->affichageResultat->setText("virgule");
}

// Enregistrer la saisie realisee dans membre_
void GUICalulatrice::enregistrerNombre()
{
    if( 0!=saisieNumerateur_ || !saisieVide_)
    {
        // Appliquer l'attribut "oper" comme operation sur le membre
        // Si "oper==operation_Aucune", initialiser le membre avec la saisie
        switch (oper_)
        {
        case Membre::operation_Aucune:
            membre_ = ZFraction(saisieNumerateur_, saisieDenominateur_);
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
    if(plainText_)
    {
        ui->affichageResultat->setText( QString::fromUtf8( membre_.afficherPlainText().data(), membre_.afficherPlainText().size() ) );

        // Move cursor into end of line
        QTextCursor cursor = ui->affichageResultat->textCursor();
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->affichageResultat->setTextCursor(cursor);

        ui->affichageResultat->insertPlainText( QString::fromUtf8( Membre::afficherOperationPlainText(oper_).data(), Membre::afficherOperationPlainText(oper_).size() ) );
        //ui->affichageResultat->append( QString::fromUtf8( Membre::afficherOperationPlainText(oper_).data(), Membre::afficherOperationPlainText(oper_).size() ) );
    }
    else
    {
        ui->affichageResultat->setHtml( QString::fromUtf8( membre_.afficherHTML().data(), membre_.afficherHTML().size() ) );

        // Move cursor into end of line
        QTextCursor cursor = ui->affichageResultat->textCursor();
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->affichageResultat->setTextCursor(cursor);

        ui->affichageResultat->insertHtml( QString::fromUtf8( Membre::afficherOperationHTML(oper_).data(), Membre::afficherOperationHTML(oper_).size() ) );
        //ui->affichageResultat->append( QString::fromUtf8( Membre::afficherOperationHTML(oper_).data(), Membre::afficherOperationHTML(oper_).size() ) );
    }
}

void GUICalulatrice::afficherResultat()
{
    if(plainText_)
    {
        ui->affichageResultat->append( "\n" + QString::fromUtf8( membre_.afficherPlainText().data(), membre_.afficherPlainText().size() ) );
    }
    else
    {
        ui->affichageResultat->append( "<br/>\n" + QString::fromUtf8( membre_.afficherHTML().data(), membre_.afficherHTML().size() ) );
    }
}

void GUICalulatrice::on_bouton_chiffre_9_clicked()
{
    saisieNumerateur_ *= 10;
    saisieNumerateur_ += 9;
    if(saisieDecimales_)
    {
        saisieDenominateur_ *= 10;
    }

    ui->affichageResultat->insertPlainText("9");
}

void GUICalulatrice::on_bouton_chiffre_8_clicked()
{
    saisieNumerateur_ *= 10;
    saisieNumerateur_ += 8;
    saisieDecimales_ && (saisieDenominateur_ *= 10);

    ui->affichageResultat->insertPlainText("8");
}

void GUICalulatrice::on_bouton_chiffre_7_clicked()
{
    saisieNumerateur_ *= 10;
    saisieNumerateur_ += 7;
    saisieDecimales_ && (saisieDenominateur_*=10);

    ui->affichageResultat->insertPlainText("7");
}

void GUICalulatrice::on_bouton_chiffre_6_clicked()
{
    saisieNumerateur_ *= 10;
    saisieNumerateur_ += 6;
    saisieDecimales_ && (saisieDenominateur_ *= 10);

    ui->affichageResultat->insertPlainText("6");
}

void GUICalulatrice::on_bouton_chiffre_5_clicked()
{
    saisieNumerateur_ *= 10;
    saisieNumerateur_ += 5;
    saisieDecimales_ && (saisieDenominateur_ *= 10);

    ui->affichageResultat->insertPlainText("5");
}

void GUICalulatrice::on_bouton_chiffre_4_clicked()
{
    saisieNumerateur_ *= 10;
    saisieNumerateur_ += 4;
    saisieDecimales_ && (saisieDenominateur_ *= 10);

    ui->affichageResultat->insertPlainText("4");
}

void GUICalulatrice::on_bouton_chiffre_3_clicked()
{
    saisieNumerateur_ *= 10;
    saisieNumerateur_ += 3;
    saisieDecimales_ && (saisieDenominateur_ *= 10);

    ui->affichageResultat->insertPlainText("3");
}

void GUICalulatrice::on_bouton_chiffre_2_clicked()
{
    saisieNumerateur_ *= 10;
    saisieNumerateur_ += 2;
    saisieDecimales_ && (saisieDenominateur_ *= 10);

    ui->affichageResultat->insertPlainText("2");
}

void GUICalulatrice::on_bouton_chiffre_1_clicked()
{
    saisieNumerateur_ *= 10;
    saisieNumerateur_ += 1;
    saisieDecimales_ && (saisieDenominateur_ *= 10);

    ui->affichageResultat->insertPlainText("1");
}

void GUICalulatrice::on_bouton_chiffre_0_clicked()
{
    // Pour detecter le cas particulier d'operation sans nombre
    // Absence de saisie : "Numerateur==0 && saisieVide"
    saisieVide_ = false;

    saisieNumerateur_ *= 10;
    saisieNumerateur_ += 0;
    saisieDecimales_ && (saisieDenominateur_ *= 10);

    ui->affichageResultat->insertPlainText("0");
}


GUICalulatrice::~GUICalulatrice()
{
    delete ui;
}
