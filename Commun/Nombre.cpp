#include "Nombre.h"



using namespace std;

Nombre::Nombre() : m_fraction(0)
{
}

Nombre::~Nombre()
{
}

Nombre::Nombre(int entier) : m_fraction(entier)
{
}

Nombre::Nombre(int numerateur, int denominateur) : m_fraction(numerateur, denominateur)
{
}

Nombre::Nombre(double decimal) : m_fraction(decimal)
{
}

double Nombre::getNombre() const
{
	return m_fraction.getDouble();
}

void Nombre::afficher(std::ostream &out) const
{
	out << m_fraction << flush;
}

bool Nombre::isSimple() const
{
	return !m_fraction.getAfficherFraction();
}

void Nombre::simplifier()
{
	if(!isSimple())
	{
		m_fraction.setAfficherFraction(false);
	}
}

Nombre& Nombre::operator+=(const Nombre& a)
{
	m_fraction = m_fraction + a.m_fraction;
	return *this;
}

Nombre& Nombre::operator-=(const Nombre& a)
{
	m_fraction = m_fraction - a.m_fraction;
	return *this;
}

Nombre& Nombre::operator/=(const Nombre& a)
{
	m_fraction = m_fraction / a.m_fraction;
	return *this;
}

Nombre& Nombre::operator*=(const Nombre& a)
{
	m_fraction = m_fraction * a.m_fraction;
	return *this;
}

std::ostream & operator<<(std::ostream &out, Nombre const &nombre)
{
	nombre.afficher(out);
	return out;
}

Nombre operator+(Nombre const& a, Nombre const& b)
{
	Nombre copie(a);	//On utilise le constructeur de copie de la classe Duree !
	copie += b;			//On appelle la méthode d'addition qui modifie l'objet 'copie'
	return copie;		//Et on renvoie le résultat. Ni a ni b n'ont changé.
}

Nombre operator-(Nombre const& a, Nombre const& b)
{
	Nombre copie(a);
	copie -= b;
	return copie;
}

Nombre operator*(Nombre const& a, Nombre const& b)
{
	Nombre copie(a);
	copie *= b;
	return copie;
}

Nombre operator/(Nombre const& a, Nombre const& b)
{
	Nombre copie(a);
	copie /= b;
	return copie;
}


