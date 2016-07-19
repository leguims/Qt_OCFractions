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
    : Membre(ZFraction(n,d))
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
    : 	parenthese_(membreACopier.parenthese_),
      afficherFraction_(membreACopier.afficherFraction_),
      membre1_(nullptr!=membreACopier.membre1_ ? new Membre(*(membreACopier.membre1_)) : nullptr),
      operation_(membreACopier.operation_),
      membre2_(nullptr!=membreACopier.membre2_ ? new Membre(*(membreACopier.membre2_)) : nullptr),
      nombre_(nullptr!=membreACopier.nombre_ ? new ZFraction(*(membreACopier.nombre_)) : nullptr)
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

void Membre::operator_simple(const Membre & a, const operation oper)
{
    if (isSimple())
    {
        // Le membre est simple ==> il devient complexe
        membre1_ = new Membre(*nombre_);
        delete nombre_; nombre_ = nullptr;
        operation_ = oper;
        membre2_ = new Membre(a);
    }
}

void Membre::operator_halfComplex(const Membre & a, const operation oper)
{
    if (isHalfComplex())
    {
        // Le membre est semi-complexe ==> il devient complexe
        if (nullptr == membre1_)
        {
            // Nouveau membre toujours dans "membre2_" => copie membre2_ dans membre1_.
            membre1_ = membre2_;
            membre2_ = nullptr;
        }

        if(membre1_->isSimple())
        {
            // membre1_ est simple => Ajout de l'operation sans priorite
            membre2_ = new Membre(a);
            operation_ = oper;
        }
        else
        {
            // membre1_ n'est pas simple => gerer les priorites
            switch(oper)
            {
            case operation_multiplication:
                // Operation en cours est une operation prioritaire ==> appliquer sur le membre1_
                *this->membre1_ *= a;
                break;
            case operation_division:
                // Operation en cours est une operation prioritaire ==> appliquer sur le membre1_
                *this->membre1_ /= a;
                break;
            case operation_addition:
            case operation_soustraction:
            case operation_Aucune:
                // L'operation en cours n'est pas prioritaire ==> pas de priorite a gerer
                // Pas d'operation en cours ==> pas de priorite a gerer
                // Le membre est semi-complexe ==> il devient complexe
                membre2_ = new Membre(a);
                operation_ = oper;
                break;
            }
        }
    }
}

void Membre::operator_complex(const Membre & a, const operation oper)
{
    if (isComplex())
    {
        if(parenthese_ == parenthese_fermee)
        {
            // Parenthese sur l'operation precedente ==> pas de priorite a gerer
            // Le membre est complexe ==> Creer un nouveau membre pour traiter l'operateur
            Membre *copie = new Membre(*this);
            delete membre1_; membre1_ = copie;
            delete membre2_; membre2_ = nullptr;
            operation_ = oper;
            membre2_ = new Membre(a);
        }
        else
        {
            // Aucune parenthese sur l'operation precedente
            switch(oper)
            {
            case operation_multiplication:
                // Operation en cours est une operation prioritaire ==> appliquer sur le membre2_
                *this->membre2_ *= a;
                break;
            case operation_division:
                // Operation en cours est une operation prioritaire ==> appliquer sur le membre2_
                *this->membre2_ /= a;
                break;
            case operation_addition:
            case operation_soustraction:
            case operation_Aucune:
                // L'operation en cours n'est pas prioritaire ==> pas de priorite a gerer
                // Pas d'operation en cours ==> pas de priorite a gerer
                // Le membre est complexe ==> Creer un nouveau membre pour traiter l'operateur
                Membre *copie = new Membre(*this);
                delete membre1_; membre1_ = copie;
                delete membre2_; membre2_ = nullptr;
                operation_ = oper;
                membre2_ = new Membre(a);
                break;
            }
        }
    }
}

Membre & Membre::operator+=(const Membre & a)
{
    if (isEmpty())
    {
        // Le membre est vide ==> il devient simple
        membre1_ = new Membre(a);
    }
    else if (isSimple())
    {
        // Le membre est simple ==> il devient complexe
        operator_simple(a, operation_addition);
    }
    else if(isHalfComplex())
    {
        // Le membre est semi-complexe ==> Remplir l'autre membre (complexe)
        operator_halfComplex(a, operation_addition);
    }
    else if(isComplex())
    {
        // Le membre est complexe ==> Creer un nouveau membre pour traiter l'operateur
        operator_complex(a, operation_addition);
    }

    return *this;
}

Membre & Membre::operator-=(const Membre & a)
{
    if (isEmpty())
    {
        // Le membre est vide ==> il devient simple
        membre1_ = new Membre(-a);
    }
    else if (isSimple())
    {
        // Le membre est simple ==> il devient complexe
        operator_simple(a, operation_soustraction);
    }
    else if (isHalfComplex())
    {
        // Le membre est semi-complexe ==> Remplir l'autre membre
        operator_halfComplex(a, operation_soustraction);
    }
    else if (isComplex())
    {
        // Le membre est complexe ==> Creer un nouveau membre pour traiter l'operateur
        operator_complex(a, operation_soustraction);
    }

    return *this;
}

Membre & Membre::operator/=(const Membre & a)
{
    // Cas "if (isEmpty())" ignoré

    if (isSimple())
    {
        // Le membre est simple ==> il devient complexe
        operator_simple(a, operation_division);
    }
    else if (isHalfComplex())
    {
        // Pour la division, veiller à ce que membre1_ soit occupé
        if (nullptr == membre1_)
        {
            membre1_ = membre2_;
            membre2_ = nullptr;
        }
        // Le membre est semi-complexe ==> Remplir l'autre membre
        operator_halfComplex(a, operation_division);
    }
    else if (isComplex())
    {
        // Le membre est complexe ==> Creer un nouveau membre pour traiter l'operateur
        operator_complex(a, operation_division);
    }

    return *this;
}

Membre & Membre::operator*=(const Membre & a)
{
    // Cas "if (isEmpty())" ignoré

    if (isSimple())
    {
        // Le membre est simple ==> il devient complexe
        operator_simple(a, operation_multiplication);
    }
    else if (isHalfComplex())
    {
        // Le membre est semi-complexe ==> Remplir l'autre membre
        operator_halfComplex(a, operation_multiplication);
    }
    else if (isComplex())
    {
        // Le membre est complexe ==> Creer un nouveau membre pour traiter l'operateur
        operator_complex(a, operation_multiplication);
    }

    return *this;
}


ZFraction Membre::getResultat() const
{
    // Traiter l'erreur si "m_nombre == nullptr"
    return isSimple()?*nombre_:0;
}

void Membre::afficher(std::ostream &out) const
{
    if(parenthese_ != parenthese_Aucune)
    {
        out << "(";
    }

    if (isEmpty())
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

        out << *membre2_ ;
    }
    else
    {
        // Erreur
        out << "Erreur : Membre vide";
    }

    if(parenthese_ == parenthese_fermee)
    {
        out << ")";
    }

    out << flush;
}

std::string Membre::afficherPlainText(void) const
{
    std::string out;
    if(parenthese_ != parenthese_Aucune)
    {
        out += "(";
    }

    if (isEmpty())
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
        out += "Erreur : Membre vide";
    }

    if(parenthese_ == parenthese_fermee)
    {
        out += ")";
    }

    return out;
}

std::string Membre::afficherHTML(void) const
{
    std::string out;
    if (isSimple())
    {
        //out << m_nombre->getNombre();
        out += nombre_->afficherHTML();
    }
    else if (isHalfComplex())
    {
        if (nullptr != membre1_)
        {
            out += membre1_->afficherHTML();
        }

        if (nullptr != membre2_)
        {
            out += membre2_->afficherHTML();
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
                        + membre1_->afficherHTML() +"</td>"
                        + "      <td>"+ afficherOperationHTML() +"</td>"
                        + "      <td>"+ membre2_->afficherHTML() +"</td>"
                        + "   </tr>"
                        + "</table>";
                break;
            case parenthese_ouverte:
                out += "\n<table style=\"border-collapse:collapse;\">   <tr style=\"text-align:center;vertical-align:middle;\">      <td>(</td><td>"
                        + membre1_->afficherHTML() +"</td>"
                        + "      <td>"+ afficherOperationHTML() +"</td>"
                        + "      <td>"+ membre2_->afficherHTML() +"</td>"
                        + "   </tr>"
                        + "</table>";
                break;
            case parenthese_fermee:
                out += "\n<table style=\"border-collapse:collapse;\">   <tr style=\"text-align:center;vertical-align:middle;\">      <td>(</td><td>"
                        + membre1_->afficherHTML() +"</td>"
                        + "      <td>"+ afficherOperationHTML() +"</td>"
                        + "      <td>"+ membre2_->afficherHTML() +"</td><td>)</td>"
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
                        + "      <td style=\"text-align:center;\">"+ membre2_->afficherHTML() +"</td>"
                        + "   </tr>"
                        + "</table>";
                break;
            case parenthese_ouverte:
                out += "\n<table style=\"border-collapse:collapse;\">   <tr style=\"vertical-align:middle;\">      <td rowspan=\"2\" style=\"font-size:20px;\">(</td><td style=\"text-align:center;\">"
                        + membre1_->afficherHTML()
                        + "<hr /></td>"     // Barre de fraction
                        + "   </tr>"
                        + "   <tr style=\"vertical-align:middle;\">"
                        + "      <td style=\"text-align:center;\">"+ membre2_->afficherHTML() +"</td>"
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
                        + "      <td style=\"text-align:center;\">"+ membre2_->afficherHTML() +"</td>"
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
        out += "Erreur : Membre vide";
    }
    cout << out << endl;
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
    if (nullptr == nombre_ && ( (nullptr != membre1_ && nullptr == membre2_) || (nullptr == membre1_ && nullptr != membre2_) ) )
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
    if (isHalfComplex() && (membre1_->isSimple() || membre2_->isSimple()))
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
    else if ( isHalfComplex() || isComplex() )
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

    if (isEmpty())
    {
        ouvrirParenthese_empty(oper);
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

void Membre::ouvrirParenthese_empty(operation oper)
{
    // Positionner les parentheses "ouvrantes" (parenthese_ouverte)

    // isEmpty() avec operation => O_o => Ignorer ce cas
    if (isEmpty() && oper == operation_Aucune)
    {
        // Le membre est vide et aucune operation en cours
        switch (parenthese_) {
        case parenthese_Aucune:
            parenthese_ = parenthese_ouverte;
            break;
        case parenthese_fermee:
            // isEmpty() et Fermee ?! O_o => ignorer l'ordre d'ouverture de parenthese
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

    // isEmpty() avec operation => O_o => Ignorer ce cas
    // isSimple() sans operation => Probleme !
    // Une parenthese ouvrante suit TOUJOURS une operation (ou une parenthese).
    // SI le membre est simple sans operation ALORS la parenthese ouvrante suit un nombre ! :O
    // => Ignorer ce cas
    if (isSimple() && oper != operation_Aucune)
    {
        // Le membre est simple avec une operation en cours
        // Le membre est simple ==> il devient complexe
        switch (parenthese_) {
        case parenthese_Aucune:
            //parenthese_ = parenthese_Aucune;
            // Parenthese ouvrante sur membre2_
            membre1_ = new Membre(*nombre_);
            delete nombre_; nombre_ = nullptr;
            operation_ = oper;
            membre2_ = new Membre();
            membre2_->ouvrirParenthese(operation_Aucune);
            break;
        case parenthese_fermee:
            // isSimple() et Fermee ?! O_o => ignorer l'ordre d'ouverture de parenthese
            break;
        case parenthese_ouverte:
            parenthese_ = parenthese_Aucune;
            // Parenthese ouvrante sur membre1_ et ouvrante sur membre2_
            membre1_ = new Membre(*nombre_);
            membre1_->parenthese_ = parenthese_ouverte;
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

        if( (oper != operation_Aucune && operation_ == operation_Aucune)
                || (oper == operation_Aucune && operation_ != operation_Aucune) )
        {
            switch (parenthese_) {
            case parenthese_Aucune:
            case parenthese_ouverte:
                if(oper != operation_Aucune)
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
        else if(oper == operation_Aucune && operation_ == operation_Aucune && parenthese_ == parenthese_ouverte)
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

void Membre::fermerParenthese()
{
    // Positionner les parentheses "fermantes" (parenthese_fermee)

    if (isEmpty())
    {
        fermerParenthese_empty();
    }
    else if (isSimple())
    {
        fermerParenthese_simple();
    }
    else if (isHalfComplex())
    {
        fermerParenthese_halfComplex();
    }
    else if (isComplex())
    {
        fermerParenthese_complex();
    }
}

void Membre::fermerParenthese_empty()
{

}

void Membre::fermerParenthese_simple()
{

}

void Membre::fermerParenthese_halfComplex()
{

}

void Membre::fermerParenthese_complex()
{

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


