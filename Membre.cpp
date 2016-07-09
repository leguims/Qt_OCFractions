#include "Membre.h"

using namespace std;

Membre::Membre() 
    : parenthese_(false), afficherFraction_(true), membre1_(nullptr), operation_(aucune), membre2_(nullptr), nombre_(nullptr)
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
    : parenthese_(false), afficherFraction_(true), membre1_(nullptr), operation_(aucune), membre2_(nullptr), nombre_(new ZFraction(n))
{
}

Membre::Membre(Membre m1, operation oper, Membre m2)
    : parenthese_(false), afficherFraction_(true), membre1_(new Membre(m1)), operation_(oper), membre2_(new Membre(m2)), nombre_(nullptr)
{
}

Membre::Membre(int i1, operation oper, int i2) : Membre(i1, 1, oper, i2, 1)
{
}

Membre::Membre(int n1, int d1, operation oper, int n2, int d2) : parenthese_(false), afficherFraction_(true), membre1_(new Membre(n1, d1)), operation_(oper), membre2_(new Membre(n2, d2)), nombre_(nullptr)
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
    parenthese_ = false;
    afficherFraction_ = true;
    delete membre1_; membre1_ = nullptr;
    operation_ = aucune;
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
			membre1_ = new Membre(a);
		}
		else if (nullptr == membre2_)
		{
			membre2_ = new Membre(a);
		}
		operation_ = oper;
	}
}

void Membre::operator_complex(const Membre & a, const operation oper)
{
	if (isComplex())
	{
		// Le membre est complexe ==> Creer un nouveau membre pour traiter l'operateur
		Membre *copie = new Membre(*this);
		delete membre1_; membre1_ = copie;
		operation_ = oper;
		delete membre2_; membre2_ = new Membre(a);
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
		operator_simple(a, addition);
	}
	else if(isHalfComplex())
	{
		// Le membre est semi-complexe ==> Remplir l'autre membre (complexe)
		operator_halfComplex(a, addition);
	}
	else if(isComplex())
	{ 
		// Le membre est complexe ==> Creer un nouveau membre pour traiter l'operateur
		operator_complex(a, addition);
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
		operator_simple(a, soustraction);
	}
	else if (isHalfComplex())
	{
		// Le membre est semi-complexe ==> Remplir l'autre membre
		operator_halfComplex(a, soustraction);
	}
	else if (isComplex())
	{
		// Le membre est complexe ==> Creer un nouveau membre pour traiter l'operateur
		operator_complex(a, soustraction);
	}

	return *this;
}

Membre & Membre::operator/=(const Membre & a)
{
	// Cas "if (isEmpty())" ignoré
		
	if (isSimple())
	{
		// Le membre est simple ==> il devient complexe
		operator_simple(a, division);
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
		operator_halfComplex(a, division);
	}
	else if (isComplex())
	{
		// Le membre est complexe ==> Creer un nouveau membre pour traiter l'operateur
		operator_complex(a, division);
	}

	return *this;
}

Membre & Membre::operator*=(const Membre & a)
{
	// Cas "if (isEmpty())" ignoré

	if (isSimple())
	{
		// Le membre est simple ==> il devient complexe
		operator_simple(a, multiplication);
	}
	else if (isHalfComplex())
	{
		// Le membre est semi-complexe ==> Remplir l'autre membre
		operator_halfComplex(a, multiplication);
	}
	else if (isComplex())
	{
		// Le membre est complexe ==> Creer un nouveau membre pour traiter l'operateur
		operator_complex(a, multiplication);
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
	if (isSimple())
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
		out << "(" << *membre1_;

		afficherOperation(out);

		out << *membre2_ << ")";
	}
	else
	{
		// Erreur
		out << "Erreur : Membre vide";
	}
	out << flush;
}

std::string Membre::afficherPlainText(void) const
{
	std::string out;
	if (isSimple())
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
		out += "(" + membre1_->afficherPlainText();

		out += afficherOperationPlainText();

		out += membre2_->afficherPlainText() + ")";
	}
	else
	{
		// Erreur
		out += "Erreur : Membre vide";
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
        case addition:
        case soustraction:
        case multiplication:
        case aucune:
            out += "\n<table style=\"border-collapse:collapse;\">   <tr style=\"text-align:center;vertical-align:middle;\">      <td>(</td><td>"
                    + membre1_->afficherHTML() +"</td>"
                    + "      <td>"+ afficherOperationHTML() +"</td>"
                    + "      <td>"+ membre2_->afficherHTML() +"</td><td>)</td>"
                    + "   </tr>"
                    + "</table>";

            break;
        case division:
            out += "\n<table style=\"border-collapse:collapse;\">   <tr style=\"vertical-align:middle;\">      <td rowspan=\"2\">(</td><td style=\"text-align:center;\">"
                    + membre1_->afficherHTML()
                    + "<hr /></td>"     // Barre de fraction
                    + "<td rowspan=\"2\">)</td>"
                    + "   </tr>"
                    + "   <tr style=\"vertical-align:middle;\">"
                    + "      <td style=\"text-align:center;\">"+ membre2_->afficherHTML() +"</td>"
                    + "   </tr>"
                    + "</table>";

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
	case addition:
		out << "+";
		break;
	case soustraction:
		out << "-";
		break;
	case multiplication:
		out << "x";
		break;
	case division:
		out << "/";
		break;
	case aucune:
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
    case addition:
        out += "+";
        break;
    case soustraction:
        out += "-";
        break;
    case multiplication:
        out += "x";
        break;
    case division:
        out += "/";
        break;
    case aucune:
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
    case addition:
        out += "+";
        break;
    case soustraction:
        out += "-";
        break;
    case multiplication:
        out += "x";
        break;
    case division:
        out += "/";
        break;
    case aucune:
//    default:
        out += " ";
        break;
    }
    return out;
}

bool Membre::isEmpty() const
{
	// Empty si membres/nombre vides.
	if (nullptr == nombre_ && nullptr == membre1_ && aucune == operation_ && nullptr == membre2_)
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
	if (nullptr != nombre_ && nullptr == membre1_ && aucune == operation_ && nullptr == membre2_)
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
	if (nullptr == nombre_ && nullptr != membre1_ && aucune != operation_ && nullptr != membre2_)
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
		case addition:
			nombre_ = new ZFraction(*(membre1_->nombre_) + *(membre2_->nombre_));
			break;
		case soustraction:
			nombre_ = new ZFraction(*(membre1_->nombre_) - *(membre2_->nombre_));
			break;
		case multiplication:
			nombre_ = new ZFraction(*(membre1_->nombre_) * *(membre2_->nombre_));
			break;
		case division:
			nombre_ = new ZFraction(*(membre1_->nombre_) / *(membre2_->nombre_));
			break;
		case aucune:
//		default:
			break;
		}
		// Definir l'affichage de fraction
		nombre_->setAfficherFraction(afficherFraction_);

		delete membre1_; membre1_ = nullptr;
		delete membre2_; membre2_ = nullptr;
		operation_ = aucune;
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

		operation_ = aucune;
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

void Membre::proteger()
{
	parenthese_ = true;
}

void Membre::deproteger()
{
	parenthese_ = false;
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


