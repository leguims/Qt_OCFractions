#include "ZFraction.h"
#include <algorithm>
#include <cmath>

using namespace std;

ZFraction::ZFraction(int numerateur, int denominateur) : m_numerateur(numerateur), m_denominateur(denominateur)
{
	simplifier();
}


ZFraction::ZFraction(long int numerateur, long int denominateur) : m_numerateur(numerateur), m_denominateur(denominateur)
{
	simplifier();
}


ZFraction::ZFraction(double numerateur): m_denominateur(1)
{
	long int	entier(0);
	
	// elimine les decimales de 'numerateur'
	entier = numerateur;
	while (entier != numerateur)
	{
		numerateur *= 10;
		m_denominateur *= 10;
		entier = numerateur;
	}
	m_numerateur = numerateur;

	simplifier();
}


ZFraction::ZFraction(ZFraction const& a) : m_numerateur(a.m_numerateur), m_denominateur(a.m_denominateur)
{
	simplifier();
}


ZFraction::~ZFraction()
{
}


void ZFraction::afficher(ostream &out) const
{
	out << m_numerateur;
	if (m_denominateur != 1)
	{
		out << "/" << m_denominateur;
	}
}

long int ZFraction::getNumerateur(void) const
{
	return m_numerateur;
}

long int ZFraction::getDenominateur(void) const
{
	return m_denominateur;
}

double ZFraction::getDouble(void) const
{
	return 1.0*m_numerateur/ m_denominateur;
}


bool ZFraction::estEgal(ZFraction a) const
{
	return ((m_numerateur==a.m_numerateur) && (m_denominateur==a.m_denominateur));
}


bool ZFraction::estSuperieur(ZFraction a) const
{
	return ( ((double)m_numerateur/m_denominateur) > ((double)a.m_numerateur/a.m_denominateur) );
}


ZFraction& ZFraction::operator+=(const ZFraction& a)
{
	m_numerateur = m_numerateur * a.m_denominateur + a.m_numerateur * m_denominateur;
	m_denominateur *= a.m_denominateur;
	simplifier();
	return *this;
}


ZFraction& ZFraction::operator-=(const ZFraction& a)
{
	m_numerateur = m_numerateur * a.m_denominateur - a.m_numerateur * m_denominateur;
	m_denominateur *= a.m_denominateur;
	simplifier();
	return *this;
}


ZFraction& ZFraction::operator/=(const ZFraction& a)
{
	m_numerateur *= a.m_denominateur;
	m_denominateur *= a.m_numerateur;
	simplifier();
	return *this;
}


ZFraction& ZFraction::operator*=(const ZFraction& a)
{
	m_numerateur *= a.m_numerateur;
	m_denominateur *= a.m_denominateur;
	simplifier();
	return *this;
}


ZFraction& ZFraction::operator+=(const long int& numerateur)
{
	m_numerateur = m_numerateur * 1 + numerateur * m_denominateur;
	m_denominateur *= 1;
	simplifier();
	return *this;
}


ZFraction& ZFraction::operator-=(const long int& numerateur)
{
	m_numerateur = m_numerateur * 1 - numerateur * m_denominateur;
	m_denominateur *= 1;
	simplifier();
	return *this;
}


ZFraction& ZFraction::operator/=(const long int& numerateur)
{
	m_numerateur *= 1;
	m_denominateur *= numerateur;
	simplifier();
	return *this;
}


ZFraction& ZFraction::operator*=(const long int& numerateur)
{
	m_numerateur *= numerateur;
	m_denominateur *= 1;
	simplifier();
	return *this;
}



void ZFraction::simplifier()
{
	// Reduire la fraction au maximum : 2/4 devient 1/2
	// Selectionner le minimum entre numerateur et denominateur
	// Verifier pour toutes les valeurs [2;min(numerateur;denomiteur)] s'il y a un facteur commun
	for (long int i(2); i <= min( std::abs(m_numerateur), std::abs(m_denominateur) ); i++)
	{
		if ((0 == m_numerateur % i) && (0 == m_denominateur % i))
		{
			m_numerateur /= i;
			m_denominateur /= i;
			i = 1;
		}
	}

	// Mettre le signe de la fraction au numérateur
	if ((m_numerateur > 0 && m_denominateur < 0) || (m_numerateur<0 && m_denominateur<0))
	{
		m_numerateur *= -1;
		m_denominateur *= -1;
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


