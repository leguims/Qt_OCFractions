#include "Membre.h"

using namespace std;

Membre::Membre()
    : parenthese_(parenthese_Aucune), afficherFraction_(true), membre1_(nullptr), operation_(operation_Aucune), membre2_(nullptr), nombre_(nullptr)
{
}


Membre::Membre(int i)
    : Membre(i, 1)
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
    : parenthese_(parenthese_Aucune), afficherFraction_(true), membre1_(nullptr), operation_(operation_Aucune), membre2_(nullptr), nombre_(new ZFraction(n))
{
}

Membre::Membre(Membre m1, operation oper, Membre m2)
    : parenthese_(parenthese_Aucune), afficherFraction_(true), membre1_(new Membre(m1)), operation_(oper), membre2_(new Membre(m2)), nombre_(nullptr)
{
}

Membre::Membre(int i1, operation oper, int i2) : Membre(i1, 1, oper, i2, 1)
{
}

Membre::Membre(int n1, int d1, operation oper, int n2, int d2) : parenthese_(parenthese_Aucune), afficherFraction_(true), membre1_(new Membre(n1, d1)), operation_(oper), membre2_(new Membre(n2, d2)), nombre_(nullptr)
{
}

Membre::Membre(Membre const &membreACopier)
    : parenthese_(membreACopier.parenthese_),
      afficherFraction_(membreACopier.afficherFraction_),
      membre1_(nullptr != membreACopier.membre1_ ? new Membre(*(membreACopier.membre1_)) : nullptr),
      operation_(membreACopier.operation_),
      membre2_(nullptr != membreACopier.membre2_ ? new Membre(*(membreACopier.membre2_)) : nullptr),
      nombre_(nullptr != membreACopier.nombre_ ? new ZFraction(*(membreACopier.nombre_)) : nullptr)
{
}

Membre & Membre::operator=(Membre const &membreACopier)
{
    //On vérifie que l'objet n'est pas le même que celui reçu en argument
    if (this != &membreACopier)
    {
        parenthese_ = membreACopier.parenthese_;
        afficherFraction_ = membreACopier.afficherFraction_;

        delete membre1_;
        membre1_ = nullptr;
        if (nullptr != membreACopier.membre1_)
        {
            membre1_ = new Membre(*(membreACopier.membre1_));
        }

        operation_ = membreACopier.operation_;

        delete membre2_;
        membre2_ = nullptr;
        if (nullptr != membreACopier.membre2_)
        {
            membre2_ = new Membre(*(membreACopier.membre2_));
        }

        delete nombre_;
        nombre_ = nullptr;
        if (nullptr != membreACopier.nombre_)
        {
            nombre_ = new ZFraction(*(membreACopier.nombre_));
        }
    }
    return *this; //On renvoie l'objet lui-même
}

Membre::~Membre()
{
    delete membre1_; membre1_ = nullptr;
    delete membre2_; membre2_ = nullptr;
    delete nombre_; nombre_ = nullptr;
}

// libere toute les allocations.
void Membre::vider()
{
    parenthese_ = parenthese_Aucune;
    afficherFraction_ = true;
    delete membre1_; membre1_ = nullptr;
    operation_ = operation_Aucune;
    delete membre2_; membre2_ = nullptr;
    delete nombre_; nombre_ = nullptr;
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
        switch (oper) {
        case operation_multiplication:
        case operation_division:
            break;
        case operation_Aucune:
            // 1er nombre apres une ouverture de parenthese.
            nombre_ = new ZFraction(a.nombre_ != nullptr ? *a.nombre_ : 0);
            menr = true;
            break;
        case operation_addition:
            membre1_ = new Membre(a);
            menr = true;
            break;
        case operation_soustraction:
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
        // Le membre est semi-complexe ==> il devient complexe
        if (nullptr == membre1_)
        {
            // Nouveau membre toujours dans "membre2_" => copie membre2_ dans membre1_.
            membre1_ = membre2_;
            membre2_ = nullptr;
        }

        if (parenthese_ == parenthese_fermee && enreg && operation_Aucune != oper)
        {
            // Si les parentheses sont fermees => appliquer l'operation a un nouveau membre
            // Pas de priorite a gerer
            Membre *copie = new Membre(*this);
            vider();
            membre1_ = copie;
            operation_ = oper;
            membre2_ = new Membre(a);
            menr = true;
        }
        else if (parenthese_fermee != parenthese_)
        {
            // Si les parentheses sont ouvertes ou absentes => Appliquer sur membre1_ puis forcer sur membre_2
            menr = membre1_->operator_generic(a, oper, false);
            if (!menr && enreg)
            {
                // membre1_ n'est pas simple => gerer les priorites
                switch (oper)
                {
                case operation_multiplication:
                case operation_division:
                    // Operation en cours est une operation prioritaire ==> appliquer sur le membre1_
                    menr = membre1_->operator_generic(a, oper, true);
                    break;
                case operation_addition:
                case operation_soustraction:
                    // L'operation en cours n'est pas prioritaire ==> pas de priorite a gerer
                    // Le membre est semi-complexe ==> il devient complexe
                    operation_ = oper;
                    membre2_ = new Membre(a);
                    menr = true;
                    break;
                case operation_Aucune:
                    // Pas d'operation en cours ==> cas non gere !
                    break;
                }
            }
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
        if (parenthese_ == parenthese_fermee && enreg && operation_Aucune != oper)
        {
            // Si les parentheses sont fermees => appliquer l'operation a un nouveau membre
            // Pas de priorite a gerer
            Membre *copie = new Membre(*this);
            vider();
            membre1_ = copie;
            operation_ = oper;
            membre2_ = new Membre(a);
            menr = true;
        }
        else if (parenthese_fermee != parenthese_)
        {
            // Si les parentheses sont ouvertes ou absentes
            // ET que l'opération du membre isComplex() n'est pas prioritaire
            // => Appliquer sur membre2_
            if (operation_ != operation_multiplication && operation_ != operation_division)
            {
                menr = membre2_->operator_generic(a, oper, false);
            }

            if (!menr && enreg)
            {
                // Si l'opération du membre isComplex() est prioritaire
                // OU
                // Si l'opération à réaliser n'est pas prioritaire
                // => Creer un nouveau membre pour traiter l'operateur
                if (operation_multiplication == operation_ || operation_division == operation_
                        || operation_addition == oper || operation_soustraction == oper)
                {
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
                else
                {
                    // Aucune parenthese ou priorité sur l'operation precedente
                    switch (oper)
                    {
                    case operation_multiplication:
                    case operation_division:
                        // Operation en cours est une operation prioritaire ==> appliquer sur le membre2_
                        menr = membre2_->operator_generic(a, oper, true);
                        break;
                    case operation_addition:
                    case operation_soustraction:
                        // Traité dans le if() ci-dessus.
                        break;
                    case operation_Aucune:
                        // Pas d'operation en cours ==> cas non gere !
                        break;
                    }
                }
            }
        }
    }
    return menr;
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

std::string Membre::afficherHTML(void) const
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
        if (nullptr != membre1_)    { m = membre1_; }
        if (nullptr != membre2_)    { m = membre2_; }

        if(nullptr != m)
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
    std::string out = afficherOperationPlainText(operation_);
    return out;
}

std::string Membre::afficherOperationHTML(void) const
{
    std::string out = afficherOperationHTML(operation_);
    return out;
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

bool Membre::isEmpty() const
{
    // Empty si membres/nombre vides.
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
    // Empty si membres/nombre vides.
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
    bool loop = !isSimple();

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
    if (isHalfComplex() && (nullptr != membre1_ && membre1_->isSimple() || nullptr != membre2_ && membre2_->isSimple()))
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

void Membre::operator_aucuneOperation(const Membre& a)
{
    // 1er nombre d'une parenthese, donc sans operation
    operator_generic(a, operation_Aucune, true);
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
            break;
        case parenthese_ouverte:
            // Deja ! Allouer un nouveau membre pour les nouvelles parentheses.
            membre1_ = new Membre();
            membre1_->ouvrirParenthese(oper);
            break;
        }
    }
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
            break;
        case parenthese_Aucune:
        case parenthese_ouverte:
            // Copie Parenthese sur membre1_ et ouvrante sur membre2_
            membre1_ = new Membre(*nombre_);
            membre1_->parenthese_ = parenthese_;
            parenthese_ = parenthese_Aucune;
            delete nombre_; nombre_ = nullptr;
            operation_ = oper;
            membre2_ = new Membre();
            membre2_->ouvrirParenthese(operation_Aucune);
            break;
        }
    }
}

void Membre::ouvrirParenthese_halfComplex(operation oper)
{
    // Positionner les parentheses "ouvrantes" (parenthese_ouverte)

    if (isHalfComplex())
    {
        // Le membre est semi-complexe ==> l'autre membre ouvre ses parentheses
        if (nullptr == membre1_)
        {
            // Nouveau membre toujours dans "membre2_" => copie membre2_ dans membre1_.
            membre1_ = membre2_;
            membre2_ = nullptr;
        }

        if ((oper != operation_Aucune && operation_ == operation_Aucune)
                || (oper == operation_Aucune && operation_ != operation_Aucune))
        {
            switch (parenthese_) {
            case parenthese_Aucune:
            case parenthese_ouverte:
                if (oper != operation_Aucune)
                {
                    operation_ = oper;
                }
                // membre2_ est alloue avec des parentheses ouvrantes
                membre2_ = new Membre();
                membre2_->ouvrirParenthese(operation_Aucune);
                break;
            case parenthese_fermee:
                // isHalfComplex() et Fermee ?! O_o => ignorer l'ordre d'ouverture de parenthese
                break;
            }
        }
        // isHalfComplex() sans operation avec parenthese ouverte => parentheses imbriquees
        else if (oper == operation_Aucune && operation_ == operation_Aucune && parenthese_ == parenthese_ouverte)
        {
            membre1_->ouvrirParenthese(oper);
        }
    }
}

void Membre::ouvrirParenthese_complex(operation oper)
{
    // Positionner les parentheses "ouvrantes" (parenthese_ouverte)

    if (isComplex())
    {
        if (oper != operation_Aucune)
        {
            // Le membre est complexe ==> Creer un nouveau membre pour ouvrir les parentheses
            Membre *copie = new Membre(*this);
            vider();
            membre1_ = copie;
            operation_ = oper;
            membre2_ = new Membre();
            membre2_->ouvrirParenthese(operation_Aucune);
        }
        // isComplex() sans operation => parentheses imbriquees
        else
        {
            membre2_->ouvrirParenthese(oper);
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
        fpr = fermerParenthese_valueless();
    }
    else if (isSimple())
    {
        fpr = fermerParenthese_simple();
    }
    else if (isHalfComplex())
    {
        fpr = fermerParenthese_halfComplex();
    }
    else if (isComplex())
    {
        fpr = fermerParenthese_complex();
    }
    return fpr;
}

bool Membre::fermerParenthese_valueless()
{
    // Positionner les parentheses "fermee" (parenthese_fermee)

    // Indique si la Fermeture de la Parenthese est Realisee
    bool fpr(false);

    // isValueless() avec operation => O_o => Ignorer ce cas
    if (isValueless())
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

bool Membre::fermerParenthese_simple()
{
    // Positionner les parentheses "fermantes" (parenthese_fermee)

    // Indique si la Fermeture de la Parenthese est Realisee
    bool fpr(false);

    if (isSimple())
    {
        // Le membre est simple ==> Aucune interet d'avoir des parentheses !
        switch (parenthese_) {
        case parenthese_Aucune:
        case parenthese_fermee:
            break;
        case parenthese_ouverte:
            fpr = true;
            break;
        }
        parenthese_ = parenthese_Aucune;
    }
    return fpr;
}

bool Membre::fermerParenthese_halfComplex()
{
    // Positionner les parentheses "fermantes" (parenthese_fermee)

    // Indique si la Fermeture de la Parenthese est Realisee
    bool fpr(false);

    if (isHalfComplex())
    {
        if (nullptr == membre1_)
        {
            // Nouveau membre toujours dans "membre2_" => copie membre2_ dans membre1_.
            membre1_ = membre2_;
            membre2_ = nullptr;
        }

        // Le membre est semi-complexe ==> Fermer les parentheses les plus imbriquees en priorite.
        if (membre1_->fermerParenthese())
        {
            fpr = true;
            if (membre1_->isValueless() && membre1_->parenthese_ == parenthese_Aucune)
            {
                // Liberer tous les membres vides sans parentheses
                delete membre1_; membre1_ = nullptr;
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

bool Membre::fermerParenthese_complex()
{
    // Positionner les parentheses "fermantes" (parenthese_fermee)

    // Indique si la Fermeture de la Parenthese est Realisee
    bool fpr(false);

    if (isComplex())
    {
        // Le membre est complexe ==> Fermer les parentheses les plus imbriquees en priorite.
        if (membre2_->fermerParenthese())
        {
            fpr = true;
            if (membre2_->isValueless() && membre2_->parenthese_ == parenthese_Aucune)
            {
                // Liberer tous les membres vides sans parentheses
                delete membre2_; membre2_ = nullptr;
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


