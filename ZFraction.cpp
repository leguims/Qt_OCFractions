#include "ZFraction.h"
#include <algorithm>
#include <cmath>

using namespace std;

ZFraction::ZFraction(int numerateur, int denominateur) : numerateur_(numerateur), denominateur_(denominateur), afficherFraction_(true)
{
	simplifier();
}


ZFraction::ZFraction(long int numerateur, long int denominateur) : numerateur_(numerateur), denominateur_(denominateur), afficherFraction_(true)
{
	simplifier();
}


ZFraction::ZFraction(double numerateur): denominateur_(1), afficherFraction_(true)
{
	long int	entier(0);
	
	// elimine les decimales de 'numerateur'
	entier = numerateur;
	while (entier != numerateur)
	{
		numerateur *= 10;
		denominateur_ *= 10;
		entier = numerateur;
	}
	numerateur_ = numerateur;

	simplifier();
}


ZFraction::ZFraction(ZFraction const& a) : numerateur_(a.numerateur_), denominateur_(a.denominateur_), afficherFraction_(true)
{
	simplifier();
}


ZFraction::~ZFraction()
{
}


void ZFraction::afficher(ostream &out) const
{
	if (afficherFraction_)
	{
		out << numerateur_;
		if (denominateur_ != 1)
		{
			out << "/" << denominateur_;
		}
	}
	else
	{
		out << getDouble();
	}
}

 std::string ZFraction::afficherPlainText(void) const
{
	std::string out;
	if (afficherFraction_)
	{
		out += std::to_string(numerateur_);
		if (denominateur_ != 1)
		{
			out += "/" + std::to_string(denominateur_);
		}
	}
	else
	{
		out += std::to_string(getDouble());
	}
	return out;
}

 std::string ZFraction::afficherHTML(void) const
{
	std::string out;
	if (afficherFraction_)
	{
		out += std::to_string(numerateur_);
		if (denominateur_ != 1)
		{
			out += "/" + std::to_string(denominateur_);
		}
	}
	else
	{
		out += std::to_string(getDouble());
	}
	return out;
}

long int ZFraction::getNumerateur(void) const
{
	return numerateur_;
}

long int ZFraction::getDenominateur(void) const
{
	return denominateur_;
}

double ZFraction::getDouble(void) const
{
	return 1.0*numerateur_/ denominateur_;
}

void ZFraction::setAfficherFraction(bool cmd)
{
	afficherFraction_ = cmd;
}

bool ZFraction::getAfficherFraction(void) const
{
	return afficherFraction_;
}


bool ZFraction::estEgal(ZFraction a) const
{
	return ((numerateur_==a.numerateur_) && (denominateur_==a.denominateur_));
}


bool ZFraction::estSuperieur(ZFraction a) const
{
	return ( ((double)numerateur_/denominateur_) > ((double)a.numerateur_/a.denominateur_) );
}


ZFraction& ZFraction::operator+=(const ZFraction& a)
{
	numerateur_ = numerateur_ * a.denominateur_ + a.numerateur_ * denominateur_;
	denominateur_ *= a.denominateur_;
	simplifier();
	return *this;
}


ZFraction& ZFraction::operator-=(const ZFraction& a)
{
	numerateur_ = numerateur_ * a.denominateur_ - a.numerateur_ * denominateur_;
	denominateur_ *= a.denominateur_;
	simplifier();
	return *this;
}


ZFraction& ZFraction::operator/=(const ZFraction& a)
{
	numerateur_ *= a.denominateur_;
	denominateur_ *= a.numerateur_;
	simplifier();
	return *this;
}


ZFraction& ZFraction::operator*=(const ZFraction& a)
{
	numerateur_ *= a.numerateur_;
	denominateur_ *= a.denominateur_;
	simplifier();
	return *this;
}


ZFraction& ZFraction::operator+=(const long int& numerateur)
{
	numerateur_ = numerateur_ * 1 + numerateur * denominateur_;
	denominateur_ *= 1;
	simplifier();
	return *this;
}


ZFraction& ZFraction::operator-=(const long int& numerateur)
{
	numerateur_ = numerateur_ * 1 - numerateur * denominateur_;
	denominateur_ *= 1;
	simplifier();
	return *this;
}


ZFraction& ZFraction::operator/=(const long int& numerateur)
{
	numerateur_ *= 1;
	denominateur_ *= numerateur;
	simplifier();
	return *this;
}


ZFraction& ZFraction::operator*=(const long int& numerateur)
{
	numerateur_ *= numerateur;
	denominateur_ *= 1;
	simplifier();
	return *this;
}



void ZFraction::simplifier()
{
	// Reduire la fraction au maximum : 2/4 devient 1/2
	// Selectionner le minimum entre numerateur et denominateur
	// Verifier pour toutes les valeurs [2;min(numerateur;denomiteur)] s'il y a un facteur commun
	for (long int i(2); i <= min( std::abs(numerateur_), std::abs(denominateur_) ); i++)
	{
		if ((0 == numerateur_ % i) && (0 == denominateur_ % i))
		{
			numerateur_ /= i;
			denominateur_ /= i;
			i = 1;
		}
	}

	// Mettre le signe de la fraction au numérateur
	if ((numerateur_ > 0 && denominateur_ < 0) || (numerateur_<0 && denominateur_<0))
	{
		numerateur_ *= -1;
		denominateur_ *= -1;
	}
}



// OPERATEURS ##########################################################################

ostream& operator<<(ostream& out, ZFraction const& fraction)
{
	fraction.afficher(out);
	return out;
}

ZFraction operator-(ZFraction const& a)
{
	ZFraction copie(a);
	copie *= -1;
	return copie;
}


ZFraction operator+(ZFraction const& a, ZFraction const& b)
{
	ZFraction copie(a);	//On utilise le constructeur de copie de la classe Duree !
	copie += b;			//On appelle la méthode d'addition qui modifie l'objet 'copie'
	return copie;		//Et on renvoie le résultat. Ni a ni b n'ont changé.
}


ZFraction operator-(ZFraction const& a, ZFraction const& b)
{
	ZFraction copie(a);
	copie -= b;
	return copie;
}


ZFraction operator*(ZFraction const& a, ZFraction const& b)
{
	ZFraction copie(a);
	copie *= b;
	return copie;
}


ZFraction operator/(ZFraction const& a, ZFraction const& b)
{
	ZFraction copie(a);
	copie /= b;
	return copie;
}


ZFraction operator+(ZFraction const& a, long int const& b)
{
	ZFraction copie(a);	//On utilise le constructeur de copie de la classe Duree !
	copie += b;			//On appelle la méthode d'addition qui modifie l'objet 'copie'
	return copie;		//Et on renvoie le résultat. Ni a ni b n'ont changé.
}


ZFraction operator-(ZFraction const& a, long int const& b)
{
	ZFraction copie(a);
	copie -= b;
	return copie;
}


ZFraction operator*(ZFraction const& a, long int const& b)
{
	ZFraction copie(a);
	copie *= b;
	return copie;
}


ZFraction operator/(ZFraction const& a, long int const& b)
{
	ZFraction copie(a);
	copie /= b;
	return copie;
}


bool operator==(ZFraction const& a, ZFraction const& b)
{
	return a.estEgal(b);
}


bool operator!=(ZFraction const& a, ZFraction const& b)
{
	return !a.estEgal(b);
}


bool operator<(ZFraction const& a, ZFraction const& b) // Astuce : a<b <==> b>a
{
	return b.estSuperieur(a);
}


bool operator<=(ZFraction const& a, ZFraction const& b) // Astuce : a<=b <==> !(a>b)
{
	return !a.estSuperieur(b);
}


bool operator>(ZFraction const& a, ZFraction const& b)
{
	return a.estSuperieur(b);
}


bool operator>=(ZFraction const& a, ZFraction const& b) // Astuce : a>=b <==> !(a<b) <==> !(b>a)
{
	return !b.estSuperieur(a);
}


