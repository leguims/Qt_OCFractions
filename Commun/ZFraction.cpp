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
    return 1.0*_numerateur/_denominateur;
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

std::ostream& operator<<(std::ostream& out, ZFraction const& fraction)
{
    fraction.afficher(out);
    return out;
}



