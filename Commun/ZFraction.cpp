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


ZFraction::ZFraction(double nbReel)
{
    if ((-1. / std::numeric_limits<long int>::max() < nbReel)
        && (nbReel < 1. / std::numeric_limits<long int>::max()))
    {
        _numerateur = 0;
        _denominateur = 1;
        return;
    }

    if (nbReel < -std::numeric_limits<long int>::max())
    {
        _numerateur = -std::numeric_limits<long int>::max();
        _denominateur = 1;
        return;
    }

    if (std::numeric_limits<long int>::max() < nbReel)
    {
        _numerateur = std::numeric_limits<long int>::max();
        _denominateur = 1;
        return;
    }

    double pd_ = nbReel - std::floor(nbReel); // Partie decimale
    const long int precision_ = pow(10, std::floor(std::log10(std::numeric_limits<long int>::max()) - std::log10(nbReel < 1 ? 1 : nbReel))); //Precision
    //const long int precision_ = 1'000'000'000 / (pow(10, std::ceil(1 + std::log10(std::abs(nbReel))))); //Precision ; C++14 Digital Separator; std::numeric_limits<long int>::max()
    long int pgcd_ = getPGCD(std::round(pd_ * precision_), precision_);

    _numerateur = round(pd_ * precision_) / pgcd_ + std::floor(nbReel)*precision_ / pgcd_;
    _denominateur = precision_ / pgcd_;

    if (std::trunc(nbReel) != std::trunc(_numerateur / _denominateur))
    {
        // nbReel reel perdu !
        throw std::domain_error("Numerateur reel (" + std::to_string(nbReel) + ") impossible a convertir en fraction");
    }
}


ZFraction::ZFraction(ZFraction const& a) : _numerateur(a._numerateur), _denominateur(a._denominateur)
{
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

int ZFraction::getHauteur() const
{
    int hauteur = 1;

    if (_denominateur != 1)
    {
        hauteur = 3;
    }

    return hauteur;
}

int ZFraction::getLargeur() const
{
    int largeur = 1;

    return largeur;
}

std::string ZFraction::afficherPlainText(void) const
{
    return ZFraction::afficherPlainText1();
}

std::string ZFraction::afficherPlainText1(void) const
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
    return ZFraction::afficherHTML2();
}

std::string ZFraction::afficherHTML1(void) const
{
    std::string out;
    if (_afficherFraction)
    {
        if (_denominateur != 1)
        {
            out += "\n<table style=\"border-collapse:collapse;\">   <tr>      <td style=\"text-align:center;vertical-align:middle;\">"
                + std::to_string(_numerateur)
                + "</td>"
                + "   </tr>"
                + "   <tr>"     // Barre de fraction + Denominateur
                + "      <td style=\"text-align:center;vertical-align:middle;\">"
                + "         <hr />" + std::to_string(_denominateur)
                + "      </td>"
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

std::string ZFraction::afficherHTML2(void) const
{
    std::string out;
    if (_afficherFraction)
    {
        if (_denominateur != 1)
        {
            out += "\n<table style=\"border-collapse:collapse;text-align:center;\">   <tr>      <td>"
                + std::to_string(_numerateur)
                + "</td>"
                + "   </tr>"
                + "   <tr>"     // Barre de fraction + Denominateur
                + "      <td>"
                + "         <hr />" + std::to_string(_denominateur)
                + "      </td>"
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
    // INFO : Pour 1'000'000'000 iterations: methode1=7.6s, methode2=9.4s

    // Methode 1
    return static_cast<double>(_numerateur) / _denominateur;

    // Methode 2
    // return 1.* _numerateur / _denominateur;
}

void ZFraction::setAfficherFraction(bool cmd)
{
    //_afficherFraction = cmd;
    cmd == false ? _afficherFraction = false : _afficherFraction = true;
}

bool ZFraction::getAfficherFraction(void) const
{
    return _afficherFraction;
}


long int ZFraction::getPGCD(long int a, long int b) const
{
    if (a == 0)
        return b;
    else if (b == 0)
        return a;

    if (a < 0)   a = std::abs(a);
    if (b < 0)   b = std::abs(b);

    if (a < b)
        return getPGCD(a, b % a);
    else
        return getPGCD(b, a % b);
}

void ZFraction::simplifier()
{
    // Reduire la fraction au maximum : 2/4 devient 1/2
    long int pgcd_ = getPGCD(_numerateur, _denominateur);
    _numerateur /= pgcd_;
    _denominateur /= pgcd_;

    // Mettre le signe de la fraction au numérateur
    if ((_numerateur > 0 && _denominateur < 0) || (_numerateur < 0 && _denominateur < 0))
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

std::ostream& operator<<(std::ostream& out, ZFraction const& fraction)
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

//template <typename T = long int>
bool operator==(ZFraction const& a, ZFraction const& b)
{
    return a.estEgal(b);
}
bool operator==(ZFraction const& a, long int const& b)
{
    return a.estEgal(b);
}


//template <typename T = long int>
bool operator!=(ZFraction const& a, ZFraction const& b) // Astuce : a!=b <==> !(a==b)
{
    return !a.estEgal(b);
}
bool operator!=(ZFraction const& a, long int const& b) // Astuce : a!=b <==> !(a==b)
{
    return !a.estEgal(b);
}

