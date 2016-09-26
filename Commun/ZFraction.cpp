#include "ZFraction.h"
#include <algorithm>
#include <cmath>
#include <exception>

using namespace std;

ZFraction::ZFraction(int numerateur, int denominateur) : _numerateur(numerateur), _denominateur(denominateur)
{
    verifierDenominateur();
    simplifier();
}


ZFraction::ZFraction(long int numerateur, long int denominateur) : _numerateur(numerateur), _denominateur(denominateur)
{
    verifierDenominateur();
    simplifier();
}


ZFraction::ZFraction(double numerateur)
{
    double	    sauvegarde(numerateur);
    long int	entier(0);

    // elimine les decimales de 'numerateur'
    entier = static_cast<long int>(numerateur);
    while (entier != numerateur)
    {
        numerateur *= 10;
        _denominateur *= 10;
        entier = static_cast<long int>(numerateur);

        if (sauvegarde != numerateur/_denominateur)
        {
            // numerateur reel perdu !
            throw std::domain_error("Numerateur reel (" + std::to_string(sauvegarde) + ") impossible a convertir en fraction");
        }
    }
    _numerateur = static_cast<long int>(numerateur);

    verifierDenominateur();
    simplifier();
}


ZFraction::ZFraction(ZFraction const& a) : _afficherFraction(true), _numerateur(a._numerateur), _denominateur(a._denominateur)
{
    simplifier();
}


ZFraction::~ZFraction()
{
}


void ZFraction::afficher(ostream &out) const
{
    if (_afficherFraction)
    {
        out << _numerateur;
        if (_denominateur != 1)
        {
            out << "/" << _denominateur;
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
    if (_afficherFraction)
    {
        out += std::to_string(_numerateur);
        if (_denominateur != 1)
        {
            out += "/" + std::to_string(_denominateur);
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
    if (_afficherFraction)
    {
        if (_denominateur != 1)
        {
            out += "\n<table style=\"border-collapse:collapse;\">   <tr>      <td style=\"text-align:center;vertical-align:middle;\">"
                    + std::to_string(_numerateur)
                    + "<hr /></td>"     // Barre de fraction
                    + "   </tr>"
                    + "   <tr>"
                    + "      <td style=\"text-align:center;vertical-align:middle;\">"+ std::to_string(_denominateur) +"</td>"
                    + "   </tr>"
                    + "</table>";
        }
        else
        {
            out += std::to_string(_numerateur);
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
    return _numerateur;
}

long int ZFraction::getDenominateur(void) const
{
    return _denominateur;
}

double ZFraction::getDouble(void) const
{
    return 1.0*_numerateur/ _denominateur;
}

void ZFraction::setAfficherFraction(bool cmd)
{
    _afficherFraction = cmd;
}

bool ZFraction::getAfficherFraction(void) const
{
    return _afficherFraction;
}


bool ZFraction::estEgal(ZFraction a) const
{
    return ((_numerateur==a._numerateur) && (_denominateur==a._denominateur));
}


bool ZFraction::estSuperieur(ZFraction a) const
{
    return ( ( static_cast<double>(_numerateur)/_denominateur) > (static_cast<double>(a._numerateur)/a._denominateur) );
}


ZFraction& ZFraction::operator+=(const ZFraction& a)
{
    _numerateur = _numerateur * a._denominateur + a._numerateur * _denominateur;
    _denominateur *= a._denominateur;
    simplifier();
    return *this;
}


ZFraction& ZFraction::operator-=(const ZFraction& a)
{
    _numerateur = _numerateur * a._denominateur - a._numerateur * _denominateur;
    _denominateur *= a._denominateur;
    simplifier();
    return *this;
}


ZFraction& ZFraction::operator/=(const ZFraction& a)
{
    _numerateur *= a._denominateur;
    _denominateur *= a._numerateur;
    verifierDenominateur();
    simplifier();
    return *this;
}


ZFraction& ZFraction::operator*=(const ZFraction& a)
{
    _numerateur *= a._numerateur;
    _denominateur *= a._denominateur;
    simplifier();
    return *this;
}


ZFraction& ZFraction::operator+=(const long int& numerateur)
{
    _numerateur = _numerateur * 1 + numerateur * _denominateur;
    _denominateur *= 1;
    simplifier();
    return *this;
}


ZFraction& ZFraction::operator-=(const long int& numerateur)
{
    _numerateur = _numerateur * 1 - numerateur * _denominateur;
    _denominateur *= 1;
    simplifier();
    return *this;
}


ZFraction& ZFraction::operator/=(const long int& numerateur)
{
    _numerateur *= 1;
    _denominateur *= numerateur;
    verifierDenominateur();
    simplifier();
    return *this;
}


ZFraction& ZFraction::operator*=(const long int& numerateur)
{
    _numerateur *= numerateur;
    _denominateur *= 1;
    simplifier();
    return *this;
}



void ZFraction::simplifier()
{
    // Reduire la fraction au maximum : 2/4 devient 1/2
    // Selectionner le minimum entre numerateur et denominateur
    // Verifier pour toutes les valeurs [2;min(numerateur;denomiteur)] s'il y a un facteur commun
    for (long int i(2); i <= min( std::abs(_numerateur), std::abs(_denominateur) ); i++)
    {
        if ((0 == _numerateur % i) && (0 == _denominateur % i))
        {
            _numerateur /= i;
            _denominateur /= i;
            i = 1;
        }
    }

    // Mettre le signe de la fraction au numérateur
    if ((_numerateur > 0 && _denominateur < 0) || (_numerateur<0 && _denominateur<0))
    {
        _numerateur *= -1;
        _denominateur *= -1;
    }
}

void ZFraction::verifierDenominateur() const
{
    if (_denominateur == 0)
    {
        // division par zero !
        throw std::domain_error("Division par zero (" + std::to_string(_numerateur) + "/" + std::to_string(_denominateur) + ")");
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


