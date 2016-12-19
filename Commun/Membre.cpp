#include "Membre.h"

using namespace std;

Membre::Membre()
{
}


Membre::Membre(int n, int d)
    : Membre(ZFraction(n, d))
{
}

Membre::Membre(double d)
    : Membre(ZFraction(d))
{
}

Membre::Membre(ZFraction n)
    : nombre_(new ZFraction(n))
{
}

Membre::Membre(Membre m1, operation oper, Membre m2)
    : membre1_(new Membre(m1)), operation_(oper), membre2_(new Membre(m2))
{
}

Membre::Membre(int i1, operation oper, int i2) : Membre(i1, 1, oper, i2, 1)
{
}

Membre::Membre(int n1, int d1, operation oper, int n2, int d2) : membre1_(new Membre(n1, d1)), operation_(oper), membre2_(new Membre(n2, d2))
{
}

Membre::Membre(Membre const &membreACopier)
    : nombre_(nullptr != membreACopier.nombre_ ? new ZFraction(*(membreACopier.nombre_)) : nullptr),
    membre1_(nullptr != membreACopier.membre1_ ? new Membre(*(membreACopier.membre1_)) : nullptr),
    operation_(membreACopier.operation_),
    membre2_(nullptr != membreACopier.membre2_ ? new Membre(*(membreACopier.membre2_)) : nullptr),
    parenthese_(membreACopier.parenthese_),
    afficherFraction_(membreACopier.afficherFraction_)
{
}

Membre & Membre::operator=(Membre const &membreACopier)
{
    //On vérifie que l'objet n'est pas le même que celui reçu en argument
    if (this != &membreACopier)
    {
        delete nombre_;
        nombre_ = nullptr;
        if (nullptr != membreACopier.nombre_)
        {
            nombre_ = new ZFraction(*(membreACopier.nombre_));
        }

        if (nullptr != membreACopier.membre1_)
        {
            //nullptr == membre1_ ? membre1_ = new Membre(*(membreACopier.membre1_)) : *membre1_ = *membreACopier.membre1_;
            if (nullptr != membre1_)
            {
                delete membre1_;
            }
            membre1_ = new Membre(*membreACopier.membre1_);
        }
        else if (nullptr != membre1_)
        {
            delete membre1_;
            membre1_ = nullptr;
        }

        operation_ = membreACopier.operation_;

        delete membre2_;
        membre2_ = nullptr;
        if (nullptr != membreACopier.membre2_)
        {
            membre2_ = new Membre(*(membreACopier.membre2_));
        }

        parenthese_ = membreACopier.parenthese_;
        afficherFraction_ = membreACopier.afficherFraction_;
    }
    return *this; //On renvoie l'objet lui-même
}

Membre::~Membre()
{
    delete nombre_; nombre_ = nullptr;
    delete membre1_; membre1_ = nullptr;
    delete membre2_; membre2_ = nullptr;
}

// libere toute les allocations.
void Membre::vider()
{
    delete nombre_; nombre_ = nullptr;
    delete membre1_; membre1_ = nullptr;
    operation_ = operation_Aucune;
    delete membre2_; membre2_ = nullptr;
    parenthese_ = parenthese_Aucune;
    afficherFraction_ = true;
}

bool Membre::operator_generic(const Membre & a, const operation oper, const bool enreg)
{
    // Indique si le Membre est ENRegistre
    bool menr(false);

    if (isValueless())
    {
        // Le membre est vide ==> il devient simple
        menr = operator_valueless(a, oper);
    }
    else if (isSimple())
    {
        // Le membre est simple ==> il devient complexe
        menr = operator_simple(a, oper);
    }
    else if (isHalfComplex())
    {
        // Le membre est semi-complexe ==> Remplir l'autre membre
        menr = operator_halfComplex(a, oper, enreg);
    }
    else if (isComplex())
    {
        // Le membre est complexe ==> Creer un nouveau membre pour traiter l'operateur
        menr = operator_complex(a, oper, enreg);
    }

    return menr;
}

bool Membre::operator_valueless(const Membre & a, const operation oper)
{
    // Indique si le Membre est ENRegistre
    bool menr(false);

    if (isValueless())
    {
        // Le membre est vide ==> il devient simple ou reste vide
        // Aucune operation autorisee si le membre est vide !
        switch (oper) {
        case operation_multiplication:
        case operation_division:
            throw std::invalid_argument("Ajout d'un operateur inattendu.");
            break;
        case operation_Aucune:
        case operation_addition:        // Interprete comme un signe
            membre1_ = new Membre(a);
            menr = true;
            break;
        case operation_soustraction:    // Interprete comme un signe
            membre1_ = new Membre(-a);
            menr = true;
            break;
        }
    }
    return menr;
}

bool Membre::operator_simple(const Membre & a, const operation oper)
{
    // Indique si le Membre est ENRegistre
    bool menr(false);

    if (isSimple() && operation_Aucune != oper)
    {
        // Le membre est simple ==> il devient complexe
        Membre *copie = new Membre(*this);
        vider();
        membre1_ = copie;
        if (parenthese_ouverte == copie->parenthese_)
        {
            // Remonter la parenthese ouvrante au niveau de l'operation
            parenthese_ = copie->parenthese_;
            membre1_->parenthese_ = parenthese_Aucune;
        }
        operation_ = oper;
        membre2_ = new Membre(a);
        menr = true;
    }
    return menr;
}

// Si enreg == true => La methode doit enregistrer l'operation
bool Membre::operator_halfComplex(const Membre & a, const operation oper, const bool enreg)
{
    // Indique si le Membre est ENRegistre
    bool menr(false);

    if (isHalfComplex())
    {
        // Phase 1 (cf. Membre::operator_complex)
        if (parenthese_ == parenthese_fermee && enreg && operation_Aucune != oper)
        {
            if (nullptr == membre1_)
            {
                // copie membre2_ dans membre1_ pour le move
                membre1_ = membre2_;
                membre2_ = nullptr;
            }

            // Si les parentheses sont fermees => appliquer l'operation a un nouveau membre
            moveThisToMembre1();

            operation_ = oper;
            membre2_ = new Membre(a);

            return true;
        }
        // Aucune operation et 'this->parenthese_' == fermee => ERREUR !!!
        else if (parenthese_ == parenthese_fermee && enreg && operation_Aucune == oper)
        {
            throw std::invalid_argument("Necessite une parenthese ouvrante");
        }
        // 'this->parenthese_' == fermee => retour sans enregistrement (return 'menr'=false)
        else if (parenthese_ == parenthese_fermee && !enreg)
        {
            return false;
        }


        // Phase 2 (cf. Membre::operator_complex)
        if (operation_Aucune == oper)
        {
            if (nullptr != membre2_)
            {
                menr = membre2_->operator_generic(a, oper, false);
            }
            if (!menr && nullptr != membre1_)
            {
                menr = membre1_->operator_generic(a, oper, false);
                if (!menr)
                    throw std::invalid_argument("Necessite une parenthese ouvrante");
            }
            return menr;
        }


        // Phase 3 (cf. Membre::operator_complex)
        if (operation_Aucune != oper)
        {
            if (nullptr != membre2_ && (membre2_->isHalfComplex() || membre2_->isComplex()))
            {
                menr = membre2_->operator_generic(a, oper, false);
            }
            else if(nullptr != membre1_ && (membre1_->isHalfComplex() || membre1_->isComplex()))
            {
                menr = membre1_->operator_generic(a, oper, false);
            }
            if (menr)
                return menr;
        }


        // Phase 4 (cf. Membre::operator_complex)
        // Phase 5 (cf. Membre::operator_complex)
        if (!menr)
        {
            if (nullptr == membre1_)
            {
                // copie membre2_ dans membre1_ pour ajouter l'operation
                membre1_ = membre2_;
                membre2_ = nullptr;
            }
            operation_ = oper;
            membre2_ = new Membre(a);

            return true;
        }
    }

    return menr;
}

bool Membre::operator_complex(const Membre & a, const operation oper, const bool enreg)
{
    // Indique si le Membre est ENRegistre
    bool menr(false);

    if (isComplex())
    {
        // Phase 1
        // 'this->parenthese_' == fermee + obligation enregistrement => copie 'this' dans 'membre1_' avec parenthese et opération sur 'membre2_' (gere le cas d'une parenthese sur membre du sommet)
        // 'this->parenthese_' == fermee et Aucune operation => ERREUR !!!
        // 'this->parenthese_' == fermee + sans obligation => retour sans enregistrement (return 'menr'=false)

        // Phase 2
        // 'this->parenthese_' != fermee  ==> Traitement ci-dessous
        // 'oper' absente => IDEE GLOBALE : Chercher 'membre2_' le plus profond "sans valeur avec parenthese ouvrante". Si echec, tester 'membre1_'. Si echec membre 1 remonter d'un cran.
        // 'oper' absente => Appliquer traitement à 'this->membre2_'. Si retour false, appliquer à 'this->membre1_'. Si retour false, retour sans enregistrement (return 'menr'=false).
        // 'oper' absente => Aucun membre "sans valeur avec parenthese ouvrante" => ERREUR !!!

        // Phase 3
        // 'oper' presente => Traitement ci-dessous
        // IDEE GLOBALE : Toujours commencer les traitements par les 'membre2_' les plus profonds.
        // 'this->membre2_->isHalfComplex || this->membre2_->isComplex' => Appliquer traitement à 'this->membre2_'. Si retour false, poursuivre le traitement.

        // Phase 4
        // Retour false ou membre2_->isSimple/Valueless => Traitement ci-dessous
        // Note : membre2_->isSimple signifie que le traitement dépend de l'operation qui lie 'membre1_' et 'membre2_', donc la décision est à prendre ici et surtout pas à sous-traiter à 'membre2_'
        // 'this->operation_' prioritaire (mul/div) ==> Deplacer le membre "prioritaire" en place (=this) sur 'membre1_' et copier le nouveau membre sur 'membre2_'. Maintenir la parenthese ouvrante sur le noeud (=this) malgres le deplacement qui le descend d'un etage.

        // Phase 5
        // 'this->operation_' non prioritaire (add/sub) ==> Traitement ci-dessous
        // 'oper' non prioritaire (add/sub) ==> Meme traitement que "'this->operation_' prioritaire (mul/div)" ci-dessus
        // 'oper' prioritaire (mul/div) ==> Allouer un nouveau 'membre2_' initialisé avec : 'membre1_' = ancien 'membre2_', 'operation_'='oper' et 'membre2_' = nouveau membre.

        // REGLE NOUVELLE : Ouvrir parenthese sur 'this->membre2_' uniquement
        // REGLE NOUVELLE : Deplacer 'this->membre2_' sur 'this->membre1_' si 'this->membre2_->parenthese==fermee' et 'membre1_' vide.


        // Phase 1
        // 'this->parenthese_' == fermee + obligation enregistrement => copie 'this' dans 'membre1_' avec parenthese et opération sur 'membre2_' (gere le cas d'une parenthese sur membre du sommet)
        if (parenthese_ == parenthese_fermee && enreg && operation_Aucune != oper)
        {
            // Si les parentheses sont fermees => appliquer l'operation a un nouveau membre
            moveThisToMembre1();

            operation_ = oper;
            membre2_ = new Membre(a);

            return true;
        }
        // Aucune operation et 'this->parenthese_' == fermee => ERREUR !!!
        else if (parenthese_ == parenthese_fermee && enreg && operation_Aucune == oper)
        {
            throw std::invalid_argument("Necessite une parenthese ouvrante");
        }
        // 'this->parenthese_' == fermee => retour sans enregistrement (return 'menr'=false)
        else if (parenthese_ == parenthese_fermee && !enreg)
        {
            return false;
        }


        // Phase 2
        // 'this->parenthese_' != fermee  ==> Traitement ci-dessous
        // 'oper' absente => IDEE GLOBALE : Chercher 'membre2_' le plus profond "sans valeur avec parenthese ouvrante". Si echec, tester 'membre1_'. Si echec membre 1 remonter d'un cran.
        // 'oper' absente => Appliquer traitement à 'this->membre2_'. Si retour false, appliquer à 'this->membre1_'. Si retour false, retour sans enregistrement (return 'menr'=false).
        // 'oper' absente => Aucun membre "sans valeur avec parenthese ouvrante" => ERREUR !!!
        if (operation_Aucune == oper)
        {
            if (nullptr != membre2_)
            {
                menr = membre2_->operator_generic(a, oper, false);
                if (!menr && nullptr != membre1_)
                {
                    menr = membre1_->operator_generic(a, oper, false);
                    if (!menr)
                        throw std::invalid_argument("Necessite une parenthese ouvrante");
                }
            }
            return menr;
        }


        // Phase 3
        // 'oper' presente => Traitement ci-dessous
        // IDEE GLOBALE : Toujours commencer les traitements par les 'membre2_' les plus profonds.
        // 'this->membre2_->isHalfComplex || this->membre2_->isComplex' => Appliquer traitement à 'this->membre2_'. Si retour false, poursuivre le traitement.
        if (operation_Aucune != oper)
        {
            if (nullptr != membre2_ && (membre2_->isHalfComplex() || membre2_->isComplex()))
            {
                menr = membre2_->operator_generic(a, oper, false);
            }
            if (menr)
                return menr;
        }


        // Phase 4
        // Retour false ou membre2_->isSimple/Valueless => Traitement ci-dessous
        // Note : membre2_->isSimple signifie que le traitement dépend de l'operation qui lie 'membre1_' et 'membre2_', donc la décision est à prendre ici et surtout pas à sous-traiter à 'membre2_'
        // 'this->operation_' prioritaire (mul/div) ==> Deplacer le membre "prioritaire" en place (=this) sur 'membre1_' et copier le nouveau membre sur 'membre2_'. Maintenir la parenthese ouvrante sur le noeud (=this) malgres le deplacement qui le descend d'un etage.
        if (operation_multiplication == operation_ || operation_division == operation_  // Phase 4
            || operation_addition == oper || operation_soustraction == oper)            // debut Phase 5
        {
            Membre::parenthese copie = parenthese_;
            moveThisToMembre1();

            operation_ = oper;
            membre2_ = new Membre(a);

            // Remonter la parenthese ouvrante au niveau de l'operation
            if (parenthese_ouverte == copie)
            {
                parenthese_ = copie;
                membre1_->parenthese_ = parenthese_Aucune;
            }

            return true;
        }


        // Phase 5
        // 'this->operation_' non prioritaire (add/sub) ==> Traitement ci-dessous
        // 'oper' non prioritaire (add/sub) ==> Meme traitement que "'this->operation_' prioritaire (mul/div)" ci-dessus (=> Phase 4)
        // 'oper' prioritaire (mul/div) ==> Allouer un nouveau 'membre2_' initialisé avec : 'membre1_' = ancien 'membre2_', 'operation_'='oper' et 'membre2_' = nouveau membre.
        if (operation_multiplication == oper || operation_division == oper)
        {
            Membre *copie = membre2_;
            membre2_ = new Membre();
            membre2_->membre1_ = copie;
            membre2_->operation_ = oper;
            membre2_->membre2_ = new Membre(a);

            return true;
        }
    }

    return menr;
}

void Membre::moveThisToMembre1(void)
{
    //Membre *copie = new Membre(*this);
    //vider();
    //membre1_ = copie;


    // Optimisation à vérifier => legerement plus rapide, presque equivalent. :(
    // Deplacement du contenu de 'this' dans un nouveau 'this->membre1_'
    Membre *copie = membre1_;
    membre1_ = new Membre();
    membre1_->nombre_ = nombre_;
    membre1_->membre1_ = copie;
    membre1_->operation_ = operation_;
    membre1_->membre2_ = membre2_;
    membre1_->parenthese_ = parenthese_;
    membre1_->afficherFraction_ = afficherFraction_;

    Membre vide;
    nombre_ = vide.nombre_;
    // 'membre1_' = 'new' ci-dessus
    operation_ = vide.operation_;
    membre2_ = vide.membre2_;
    parenthese_ = vide.parenthese_;
    afficherFraction_ = vide.afficherFraction_;
}


Membre & Membre::operator+=(const Membre & a)
{
    operator_generic(a, operation_addition, true);

    return *this;
}

Membre & Membre::operator-=(const Membre & a)
{
    operator_generic(a, operation_soustraction, true);

    return *this;
}

Membre & Membre::operator/=(const Membre & a)
{
    operator_generic(a, operation_division, true);

    return *this;
}

Membre & Membre::operator*=(const Membre & a)
{
    operator_generic(a, operation_multiplication, true);

    return *this;
}

void Membre::operator_aucuneOperation(const Membre& a)
{
    // 1er nombre d'une parenthese, donc sans operation
    operator_generic(a, operation_Aucune, true);
}

ZFraction Membre::getResultat() const
{
    // Traiter l'erreur si "m_nombre == nullptr"
    return isSimple() ? *nombre_ : 0;
}

void Membre::afficher(std::ostream &out) const
{
    if (parenthese_ != parenthese_Aucune)
    {
        out << "(";
    }

    if (isEmpty() || isValueless())
    {
        out << " ";
    }
    else if (isSimple())
    {
        //out << m_nombre->getNombre();
        out << *nombre_;
    }
    else if (isHalfComplex())
    {
        if (nullptr != membre1_)
        {
            out << *membre1_;
        }

        if (nullptr != membre2_)
        {
            out << *membre2_;
        }
    }
    else if (isComplex())
    {
        out << *membre1_;

        afficherOperation(out);

        out << *membre2_;
    }
    else
    {
        // Erreur
        out << "Erreur : Membre vide1";
    }

    if (parenthese_ == parenthese_fermee)
    {
        out << ")";
    }

    out << flush;
}

std::string Membre::afficherPlainText(void) const
{
    return Membre::afficherPlainText1();
}

std::string Membre::afficherPlainText1(void) const
{
    std::string out;
    if (parenthese_ != parenthese_Aucune)
    {
        out += "(";
    }

    if (isEmpty() || isValueless())
    {
        out += " ";
    }
    else if (isSimple())
    {
        //out << m_nombre->getNombre();
        out += nombre_->afficherPlainText();
    }
    else if (isHalfComplex())
    {
        if (nullptr != membre1_)
        {
            out += membre1_->afficherPlainText();
        }

        if (nullptr != membre2_)
        {
            out += membre2_->afficherPlainText();
        }
    }
    else if (isComplex())
    {
        out += membre1_->afficherPlainText();

        out += afficherOperationPlainText();

        out += membre2_->afficherPlainText();
    }
    else
    {
        // Erreur
        out += "Erreur : Membre vide2";
    }

    if (parenthese_ == parenthese_fermee)
    {
        out += ")";
    }

    return out;
}

std::string Membre::afficherHTML(bool racine) const
{
    return Membre::afficherHTML1(racine);
    //return Membre::afficherHTML2(racine);
}

// Méthode historique avec affichage propre (sauf centrage vertical).
// Crée de nombreuses "<table>...</table>" qui provoque de gros ralentissements sur Qt.
std::string Membre::afficherHTML1(bool racine) const
{
    std::string out;

    if (isEmpty() || isValueless())
    {
        switch (parenthese_)
        {
        case parenthese_Aucune:
            out += " ";
            break;
        case parenthese_ouverte:
            out += "( ";
            break;
        case parenthese_fermee:
            out += "( )";
            break;
        }
    }
    else if (isSimple())
    {
        switch (parenthese_)
        {
        case parenthese_Aucune:
            out += nombre_->afficherHTML();
            break;
        case parenthese_ouverte:
            out += "\n<table style=\"border-collapse:collapse;\">   <tr style=\"text-align:center;vertical-align:middle;\">      <td>(</td><td>"
                + nombre_->afficherHTML() + "</td>"
                + "   </tr>"
                + "</table>";
            break;
        case parenthese_fermee:
            out += "\n<table style=\"border-collapse:collapse;\">   <tr style=\"text-align:center;vertical-align:middle;\">      <td>(</td><td>"
                + nombre_->afficherHTML() + "</td><td>)</td>"
                + "   </tr>"
                + "</table>";
            break;
        }
    }
    else if (isHalfComplex())
    {
        Membre *m = nullptr;
        if (nullptr != membre1_) { m = membre1_; }
        if (nullptr != membre2_) { m = membre2_; }

        if (nullptr != m)
        {
            switch (parenthese_)
            {
            case parenthese_Aucune:
                out += m->afficherHTML();
                break;
            case parenthese_ouverte:
                out += "\n<table style=\"border-collapse:collapse;\">   <tr style=\"text-align:center;vertical-align:middle;\">      <td>(</td><td>"
                    + m->afficherHTML() + "</td>"
                    + "   </tr>"
                    + "</table>";
                break;
            case parenthese_fermee:
                out += "\n<table style=\"border-collapse:collapse;\">   <tr style=\"text-align:center;vertical-align:middle;\">      <td>(</td><td>"
                    + m->afficherHTML() + "</td><td>)</td>"
                    + "   </tr>"
                    + "</table>";
                break;
            }
        }
    }
    else if (isComplex())
    {
        switch (operation_)
        {
        case operation_addition:
        case operation_soustraction:
        case operation_multiplication:
        case operation_Aucune:
            switch (parenthese_)
            {
            case parenthese_Aucune:
                out += "\n<table style=\"border-collapse:collapse;\">   <tr style=\"text-align:center;vertical-align:middle;\">      <td>"
                    + membre1_->afficherHTML() + "</td>"
                    + "      <td>" + afficherOperationHTML() + "</td>"
                    + "      <td>" + membre2_->afficherHTML() + "</td>"
                    + "   </tr>"
                    + "</table>";
                break;
            case parenthese_ouverte:
                out += "\n<table style=\"border-collapse:collapse;\">   <tr style=\"text-align:center;vertical-align:middle;\">      <td>(</td><td>"
                    + membre1_->afficherHTML() + "</td>"
                    + "      <td>" + afficherOperationHTML() + "</td>"
                    + "      <td>" + membre2_->afficherHTML() + "</td>"
                    + "   </tr>"
                    + "</table>";
                break;
            case parenthese_fermee:
                out += "\n<table style=\"border-collapse:collapse;\">   <tr style=\"text-align:center;vertical-align:middle;\">      <td>(</td><td>"
                    + membre1_->afficherHTML() + "</td>"
                    + "      <td>" + afficherOperationHTML() + "</td>"
                    + "      <td>" + membre2_->afficherHTML() + "</td><td>)</td>"
                    + "   </tr>"
                    + "</table>";
                break;
            }
            break;
        case operation_division:
            switch (parenthese_)
            {
            case parenthese_Aucune:
                out += "\n<table style=\"border-collapse:collapse;\">   <tr style=\"vertical-align:middle;\">      <td style=\"text-align:center;\">"
                    + membre1_->afficherHTML()
                    + "<hr /></td>"     // Barre de fraction
                    + "   </tr>"
                    + "   <tr style=\"vertical-align:middle;\">"
                    + "      <td style=\"text-align:center;\">" + membre2_->afficherHTML() + "</td>"
                    + "   </tr>"
                    + "</table>";
                break;
            case parenthese_ouverte:
                out += "\n<table style=\"border-collapse:collapse;\">   <tr style=\"vertical-align:middle;\">      <td rowspan=\"2\" style=\"font-size:20px;\">(</td><td style=\"text-align:center;\">"
                    + membre1_->afficherHTML()
                    + "<hr /></td>"     // Barre de fraction
                    + "   </tr>"
                    + "   <tr style=\"vertical-align:middle;\">"
                    + "      <td style=\"text-align:center;\">" + membre2_->afficherHTML() + "</td>"
                    + "   </tr>"
                    + "</table>";
                break;
            case parenthese_fermee:
                out += "\n<table style=\"border-collapse:collapse;\">   <tr style=\"vertical-align:middle;\">      <td rowspan=\"2\" style=\"font-size:20px;\">(</td><td style=\"text-align:center;\">"
                    + membre1_->afficherHTML()
                    + "<hr /></td>"     // Barre de fraction
                    + "<td rowspan=\"2\" style=\"font-size:20px;\">)</td>"
                    + "   </tr>"
                    + "   <tr style=\"vertical-align:middle;\">"
                    + "      <td style=\"text-align:center;\">" + membre2_->afficherHTML() + "</td>"
                    + "   </tr>"
                    + "</table>";
                break;
            }
            break;
        }
    }
    else
    {
        // Erreur
        out += "Erreur : Membre vide3";
    }
    return out;
}

// Méthode qui limite la création de tables, mais l'affichage est dégradé.
// Disparition des ralentissements sur Qt.
std::string Membre::afficherHTML2(bool racine) const
{
    std::string out;

    // Membre racine donc debut de la table
    if (racine)
    {
        out += "\n<table style=\"border-collapse:collapse;\">\n<tr style=\"text-align:center;vertical-align:middle;\"> <td>";
    }

    if (isEmpty() || isValueless())
    {
        switch (parenthese_)
        {
        case parenthese_Aucune:
            out += " ";
            break;
        case parenthese_ouverte:
            out += "( ";
            break;
        case parenthese_fermee:
            out += "( )";
            break;
        }
    }
    else if (isSimple())
    {
        switch (parenthese_)
        {
        case parenthese_Aucune:
            out += nombre_->afficherHTML();
            break;
        case parenthese_ouverte:
            out += "(</td><td>"
                + nombre_->afficherHTML() + "</td><td>";
            break;
        case parenthese_fermee:
            out += "(</td><td>"
                + nombre_->afficherHTML() + "</td><td>)</td><td>";
            break;
        }
    }
    else if (isHalfComplex())
    {
        Membre *m = nullptr;
        if (nullptr != membre1_) { m = membre1_; }
        if (nullptr != membre2_) { m = membre2_; }

        if (nullptr != m)
        {
            switch (parenthese_)
            {
            case parenthese_Aucune:
                out += m->afficherHTML();
                break;
            case parenthese_ouverte:
                out += "(</td><td>"
                    + m->afficherHTML() + "</td><td>";
                break;
            case parenthese_fermee:
                out += "<td>(</td><td>"
                    + m->afficherHTML() + "</td><td>)</td><td>";
                break;
            }
        }
    }
    else if (isComplex())
    {
        switch (operation_)
        {
        case operation_addition:
        case operation_soustraction:
        case operation_multiplication:
        case operation_Aucune:
            switch (parenthese_)
            {
            case parenthese_Aucune:
                out += membre1_->afficherHTML() + "</td><td>"
                    + afficherOperationHTML() + "</td><td>"
                    + membre2_->afficherHTML() + "</td><td>";
                break;
            case parenthese_ouverte:
                out += "(</td><td>"
                    + membre1_->afficherHTML() + "</td><td>"
                    + afficherOperationHTML() + "</td><td>"
                    + membre2_->afficherHTML() + "</td><td>";
                break;
            case parenthese_fermee:
                out += "(</td><td>"
                    + membre1_->afficherHTML() + "</td><td>"
                    + afficherOperationHTML() + "</td><td>"
                    + membre2_->afficherHTML() + "</td><td>)</td><td>";
                break;
            }
            break;
        case operation_division:
            switch (parenthese_)
            {
            case parenthese_Aucune:
                out += "\n<table style=\"border-collapse:collapse;\">   <tr style=\"vertical-align:middle;\">      <td style=\"text-align:center;\">"
                    + membre1_->afficherHTML()
                    + "<hr /></td>"     // Barre de fraction
                    + "   </tr>"
                    + "   <tr style=\"vertical-align:middle;\">"
                    + "      <td style=\"text-align:center;\">" + membre2_->afficherHTML() + "</td>"
                    + "   </tr>"
                    + "</table>";
                break;
            case parenthese_ouverte:
                out += "\n<table style=\"border-collapse:collapse;\">   <tr style=\"vertical-align:middle;\">      <td rowspan=\"2\" style=\"font-size:20px;\">(</td><td style=\"text-align:center;\">"
                    + membre1_->afficherHTML()
                    + "<hr /></td>"     // Barre de fraction
                    + "   </tr>"
                    + "   <tr style=\"vertical-align:middle;\">"
                    + "      <td style=\"text-align:center;\">" + membre2_->afficherHTML() + "</td>"
                    + "   </tr>"
                    + "</table>";
                break;
            case parenthese_fermee:
                out += "\n<table style=\"border-collapse:collapse;\">   <tr style=\"vertical-align:middle;\">      <td rowspan=\"2\" style=\"font-size:20px;\">(</td><td style=\"text-align:center;\">"
                    + membre1_->afficherHTML()
                    + "<hr /></td>"     // Barre de fraction
                    + "<td rowspan=\"2\" style=\"font-size:20px;\">)</td>"
                    + "   </tr>"
                    + "   <tr style=\"vertical-align:middle;\">"
                    + "      <td style=\"text-align:center;\">" + membre2_->afficherHTML() + "</td>"
                    + "   </tr>"
                    + "</table>";
                break;
            }
            break;
        }
    }
    else
    {
        // Erreur
        out += "Erreur : Membre vide3";
    }

    // Membre racine donc fin de la table
    if (racine)
    {
        out += "</td></tr>\n</table>";
    }

    return out;
}

void Membre::afficherOperation(std::ostream &out) const
{
    switch (operation_)
    {
    case operation_addition:
        out << "+";
        break;
    case operation_soustraction:
        out << "-";
        break;
    case operation_multiplication:
        out << "x";
        break;
    case operation_division:
        out << "/";
        break;
    case operation_Aucune:
        //	default:
        out << " ";
        break;
    }
}

std::string Membre::afficherOperationPlainText(void) const
{
    return afficherOperationPlainText(operation_);
}

std::string Membre::afficherOperationHTML(void) const
{
    return afficherOperationHTML(operation_);
}

std::string Membre::afficherOperationPlainText(operation oper)
{
    std::string out;
    switch (oper)
    {
    case operation_addition:
        out += "+";
        break;
    case operation_soustraction:
        out += "-";
        break;
    case operation_multiplication:
        out += "x";
        break;
    case operation_division:
        out += "/";
        break;
    case operation_Aucune:
        //    default:
        out += " ";
        break;
    }
    return out;
}

std::string Membre::afficherOperationHTML(operation oper)
{
    return afficherOperationPlainText(oper);
}

bool Membre::isEmpty() const
{
    // Empty si membres/nombre/parenthese vides.
    if (nullptr == nombre_ && nullptr == membre1_ && operation_Aucune == operation_ && nullptr == membre2_ && parenthese_Aucune == parenthese_)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Membre::isValueless() const
{
    // Valueless si membres/nombre vides, mais indifferent aux parentheses.
    if (nullptr == nombre_ && nullptr == membre1_ && operation_Aucune == operation_ && nullptr == membre2_)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Retourne vrai si le membre ne contient pas d'operation, mais seulement un nombre.
bool Membre::isSimple() const
{
    // Simple si membres vides + nombre au format demandé.
    if (nullptr != nombre_ && nullptr == membre1_ && operation_Aucune == operation_ && nullptr == membre2_)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Membre::isHalfComplex() const
{
    // Semi-complexe = 1 membre utilisé.
    if (nullptr == nombre_ && ((nullptr != membre1_ && nullptr == membre2_) || (nullptr == membre1_ && nullptr != membre2_)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Membre::isComplex() const
{
    // Complexe = 2 membres utilisés.
    if (nullptr == nombre_ && nullptr != membre1_ && operation_Aucune != operation_ && nullptr != membre2_)
    {
        return true;
    }
    else
    {
        return false;
    }
}


// Appelle m_operation->simplifier() et si m_operation->isSimple() est vrai alors enregistre m_nombre=m_operation->resultat() libere m_operation.
bool Membre::simplifier()
{
    // Pas de boucle si simple ou ou vide
    bool loop = !(isSimple() || isValueless());

    // Si les membres sont simples, realiser l'operation
    if (isComplex() && membre1_->isSimple() && membre2_->isSimple())
    {
        switch (operation_)
        {
        case operation_addition:
            nombre_ = new ZFraction(*(membre1_->nombre_) + *(membre2_->nombre_));
            break;
        case operation_soustraction:
            nombre_ = new ZFraction(*(membre1_->nombre_) - *(membre2_->nombre_));
            break;
        case operation_multiplication:
            nombre_ = new ZFraction(*(membre1_->nombre_) * *(membre2_->nombre_));
            break;
        case operation_division:
            nombre_ = new ZFraction(*(membre1_->nombre_) / *(membre2_->nombre_));
            break;
        case operation_Aucune:
            //		default:
            break;
        }
        // Definir l'affichage de fraction
        nombre_->setAfficherFraction(afficherFraction_);

        delete membre1_; membre1_ = nullptr;
        delete membre2_; membre2_ = nullptr;
        operation_ = operation_Aucune;
    }
    // Si semi-complex avec membre simple, membre devient simple
    if (isHalfComplex() && ( (nullptr != membre1_ && membre1_->isSimple()) || (nullptr != membre2_ && membre2_->isSimple())) )
    {
        if (nullptr != membre1_)
        {
            nombre_ = new ZFraction(*(membre1_->nombre_));
            delete membre1_; membre1_ = nullptr;
        }

        if (nullptr != membre2_)
        {
            nombre_ = new ZFraction(*(membre2_->nombre_));
            delete membre2_; membre2_ = nullptr;
        }

        // Definir l'affichage de fraction
        nombre_->setAfficherFraction(afficherFraction_);

        operation_ = operation_Aucune;
    }
    // Si un membre n'est pas simple, demander la simplification de chacun
    else if (isHalfComplex() || isComplex())
    {
        if (nullptr != membre1_)
        {
            membre1_->simplifier();
        }
        if (nullptr != membre2_)
        {
            membre2_->simplifier();
        }
    }
    return loop;
}

void Membre::ouvrirParenthese(operation oper)
{
    // Positionner les parentheses "ouvrantes" (parenthese_ouverte)

    if (isValueless())
    {
        ouvrirParenthese_valueless(oper);
    }
    else if (isSimple())
    {
        ouvrirParenthese_simple(oper);
    }
    else if (isHalfComplex())
    {
        ouvrirParenthese_halfComplex(oper);
    }
    else if (isComplex())
    {
        ouvrirParenthese_complex(oper);
    }
}

void Membre::ouvrirParenthese_valueless(operation oper)
{
    // Positionner les parentheses "ouvrantes" (parenthese_ouverte)

    // isValueless() avec operation => O_o => Ignorer ce cas
    if (isValueless() && oper == operation_Aucune)
    {
        // Le membre est vide et aucune operation en cours
        switch (parenthese_) {
        case parenthese_Aucune:
            parenthese_ = parenthese_ouverte;
            break;
        case parenthese_fermee:
            // isValueless() et Fermee ?! O_o => ignorer l'ordre d'ouverture de parenthese
            throw std::invalid_argument("Incoherence lors de l'ouverture de parenthese.");
            break;
        case parenthese_ouverte:
            // Deja ! Allouer un nouveau membre pour les nouvelles parentheses.
            membre2_ = new Membre();
            membre2_->ouvrirParenthese(oper);
            break;
        }
    }
    else
        throw std::invalid_argument("Ajout d'un operateur inattendu pour l'ouverture de parenthese.");
}

void Membre::ouvrirParenthese_simple(operation oper)
{
    // Positionner les parentheses "ouvrantes" (parenthese_ouverte)

    // isValueless() avec operation => O_o => Ignorer ce cas
    // isSimple() sans operation => Probleme !
    // Une parenthese ouvrante suit TOUJOURS une operation (ou une parenthese).
    // SI le membre est simple sans operation ALORS la parenthese ouvrante suit un nombre ! :O
    // => Ignorer ce cas
    if (isSimple() && oper != operation_Aucune)
    {
        // Le membre est simple avec une operation en cours
        // Le membre est simple ==> il devient complexe
        switch (parenthese_) {
        case parenthese_fermee:
            // isSimple() et Fermee ?! O_o => ignorer l'ordre d'ouverture de parenthese
            throw std::invalid_argument("Incoherence lors de l'ouverture de parenthese.");
            break;
        case parenthese_Aucune:
        case parenthese_ouverte:
            // Copie nombre_ sur membre1_ et conserve parenthese_ et ouvrante sur membre2_
            membre1_ = new Membre(*nombre_);
            delete nombre_; nombre_ = nullptr;
            operation_ = oper;
            membre2_ = new Membre();
            membre2_->ouvrirParenthese(operation_Aucune);
            break;
        }
    }
    else
        throw std::invalid_argument("Manque un operateur pour l'ouverture de parenthese.");
}

void Membre::ouvrirParenthese_halfComplex(operation oper)
{
    // Positionner les parentheses "ouvrantes" (parenthese_ouverte)

    if (isHalfComplex())
    {
        // Si les parenthese du membre en cours sont fermees => le deplacer dans un nouveau membre1_ et appliquer les parentheses au membre2_ associe
        if (Membre::parenthese_fermee == parenthese_)
        {
            moveThisToMembre1();

            operation_ = oper;
            membre2_ = new Membre;
            membre2_->ouvrirParenthese(Membre::operation_Aucune);
        }
        else if (nullptr != membre2_)
        {
            membre2_->ouvrirParenthese(oper);
        }
        else
        {
            if ( operation_Aucune != oper && operation_Aucune == operation_)
            {
                operation_ = oper;
                membre2_ = new Membre();
                membre2_->ouvrirParenthese(operation_Aucune);
            }
            else
                throw std::invalid_argument("Incoherence sur l'operateur pour l'ouverture de parenthese.");
        }
    }
}

void Membre::ouvrirParenthese_complex(operation oper)
{
    // Positionner les parentheses "ouvrantes" (parenthese_ouverte)

    if (isComplex())
    {
        // Si les parenthese du membre en cours sont fermees => le deplacer dans un nouveau membre1_ et appliquer les parentheses au membre2_ associe
        if (Membre::parenthese_fermee == parenthese_)
        {
            moveThisToMembre1();

            operation_ = oper;
            membre2_ = new Membre;
            membre2_->ouvrirParenthese(Membre::operation_Aucune);
        }
        else if (nullptr != membre2_)
            membre2_->ouvrirParenthese(oper);
        else
        {
            throw std::invalid_argument("Faux membre complex pour l'ouverture de parenthese.");
        }
    }
}

bool Membre::fermerParenthese()
{
    // Positionner les parentheses "fermantes" (parenthese_fermee)

    // Indique si la Fermeture de la Parenthese est Realisee
    bool fpr(false);

    if (isValueless())
    {
        fpr = fermerParenthese_valueless_simple();
    }
    else if (isSimple())
    {
        fpr = fermerParenthese_valueless_simple();
    }
    else if (isHalfComplex())
    {
        fpr = fermerParenthese_halfComplex_complex();
    }
    else if (isComplex())
    {
        fpr = fermerParenthese_halfComplex_complex();
    }
    return fpr;
}

bool Membre::fermerParenthese_valueless_simple()
{
    // Positionner les parentheses "fermee" (parenthese_fermee)

    // Indique si la Fermeture de la Parenthese est Realisee
    bool fpr(false);

    // isValueless() avec operation => O_o => Ignorer ce cas
    if (isValueless() || isSimple())
    {
        // Le membre est vide ==> Aucune interet d'avoir des parentheses !
        switch (parenthese_) {
        case parenthese_Aucune:
        case parenthese_fermee:
            // isValueless() et Fermee ?! O_o => des parentheses inutiles ! Supprimer les parentheses.
            break;
        case parenthese_ouverte:
            // isValueless() et Ouverte ?! O_o => des parentheses inutiles ! Supprimer les parentheses.
            fpr = true;
            break;
        }
        parenthese_ = parenthese_Aucune;
        // TODO : Il faudrait meme libérer le membre s'il est chainé !
    }
    return fpr;
}

bool Membre::fermerParenthese_halfComplex_complex()
{
    // Positionner les parentheses "fermantes" (parenthese_fermee)

    // Indique si la Fermeture de la Parenthese est Realisee
    bool fpr(false);

    if (isHalfComplex() || isComplex())
    {
        // Le membre est (semi-)complexe ==> Fermer les parentheses les plus imbriquees en priorite.
        if (nullptr != membre2_ && membre2_->fermerParenthese())
        {
            fpr = true;

            // Liberer le membre vide sans parentheses
            if (membre2_->isValueless() && membre2_->parenthese_ == parenthese_Aucune)
            {
                delete membre2_; membre2_ = nullptr;
            }

            // Deplace membre2_ avec parenthese fermees dans membre1_ => Simplifie l'arbre, car les parentheses fermees rendent le membre inalterable.
            if (nullptr == membre1_ && membre2_->parenthese_ == parenthese_fermee)
            {
                membre1_ = membre2_;
                membre2_ = nullptr;
            }
        }
        // Pas de parenthese imbriquee => verifier la parenthese courante
        else if (parenthese_ == parenthese_ouverte)
        {
            // Fermer la parenthese locale
            parenthese_ = parenthese_fermee;
            fpr = true;
        }
    }
    return fpr;
}

void Membre::setAfficherFraction(bool cmd)
{
    afficherFraction_ = cmd;
    // Diffuser la commande aux membres et nombre
    if (nullptr != membre1_)
    {
        membre1_->setAfficherFraction(cmd);
    }

    if (nullptr != membre2_)
    {
        membre2_->setAfficherFraction(cmd);
    }

    if (nullptr != nombre_)
    {
        nombre_->setAfficherFraction(cmd);
    }
}

bool Membre::getAfficherFraction(void) const
{
    return afficherFraction_;
}

std::ostream & operator<<(std::ostream &out, Membre const &membre)
{
    membre.afficher(out);
    return out;
}

Membre operator-(Membre const & a)
{
    Membre copie(a);
    copie *= -1;
    return copie;
}

Membre operator+(Membre const & a, Membre const & b)
{
    Membre copie(a);	//On utilise le constructeur de copie de la classe.
    copie += b;			//On appelle la méthode d'addition qui modifie l'objet 'copie'
    return copie;		//Et on renvoie le résultat. Ni a ni b n'ont changé.
}

Membre operator-(Membre const & a, Membre const & b)
{
    Membre copie(a);
    copie -= b;
    return copie;
}

Membre operator/(Membre const & a, Membre const & b)
{
    Membre copie(a);
    copie /= b;
    return copie;
}

Membre operator*(Membre const & a, Membre const & b)
{
    Membre copie(a);
    copie *= b;
    return copie;
}


