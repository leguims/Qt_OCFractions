#pragma once
#include <iostream>
#include <string>

class ZFraction
{
public:
    ZFraction(int numerateur, int denominateur = 1);
    ZFraction(long int numerateur = 0, long int denominateur = 1);
    ZFraction(double numerateur);
    ZFraction(ZFraction const&);
    ~ZFraction();
    void afficher(std::ostream &out) const;
    std::string afficherPlainText(void) const;
    std::string afficherHTML(void) const;
    long int getNumerateur(void) const;
    long int getDenominateur(void) const;
    double getDouble(void) const;
    void setAfficherFraction(bool);
    bool getAfficherFraction(void) const;

    template <typename T = long int>
    bool estEgal(const T numerateur) const
    {
        return ( _numerateur == numerateur*_denominateur );
    }
    template <>
    bool estEgal<ZFraction>(const ZFraction a) const
    {
        return (_numerateur*a._denominateur == a._numerateur*_denominateur);
    }


    template <typename T = long int>
    bool estSuperieur(const T numerateur) const
    {
        return ( getDouble() > static_cast<double>(numerateur) );
    }
    template <>
    bool estSuperieur<ZFraction>(const ZFraction a) const
    {
        return ( getDouble() > a.getDouble() );
    }


    template <typename T = long int>
    ZFraction& operator+=(const T& numerateur)
    {
        _numerateur = _numerateur + numerateur * _denominateur;
        simplifier();
        return *this;
    }
    template <>
    ZFraction& operator+=<ZFraction>(const ZFraction& a)
    {
        _numerateur = _numerateur * a._denominateur + a._numerateur * _denominateur;
        _denominateur *= a._denominateur;
        simplifier();
        return *this;
    }
    template <>
    ZFraction& operator+=<double>(const double& numerateur)
    {
        ZFraction tmp( getDouble() + numerateur);

        // INFO : Pour 10'000'000 iterations: methode1=6.7s, methode2=7.2s

        // Methode 1
        *this = tmp;

        // Methode 2
        //_numerateur = tmp.getNumerateur();
        //_denominateur = tmp.getDenominateur();

        return *this;
    }


    template <typename T = long int>
    ZFraction& operator-=(const T& numerateur)
    {
        _numerateur = _numerateur - numerateur * _denominateur;
        simplifier();
        return *this;
    }
    template <>
    ZFraction& operator-=<ZFraction>(const ZFraction& a)
    {
        _numerateur = _numerateur * a._denominateur - a._numerateur * _denominateur;
        _denominateur *= a._denominateur;
        simplifier();
        return *this;
    }
    template <>
    ZFraction& operator-=<double>(const double& numerateur)
    {
        ZFraction tmp( getDouble() - numerateur);
        *this = tmp;
        return *this;
    }


    template <typename T = long int>
    ZFraction& operator/=(const T& numerateur)
    {
        _denominateur *= numerateur;
        verifierDenominateur();
        simplifier();
        return *this;
    }
    template <>
    ZFraction& operator/=<ZFraction>(const ZFraction& a)
    {
        _numerateur *= a._denominateur;
        _denominateur *= a._numerateur;
        verifierDenominateur();
        simplifier();
        return *this;
    }
    template <>
    ZFraction& operator/=<double>(const double& numerateur)
    {
        if (0. == numerateur)
        {
            // division par zero !
            throw std::domain_error("Division par zero (" + std::to_string(_numerateur) + "/" + std::to_string(numerateur * _denominateur) + ")");
        }
        else
        {
            ZFraction tmp(_numerateur / (numerateur * _denominateur));
            *this = tmp;
        }
        return *this;
    }


    template <typename T = long int>
    ZFraction& operator*=(const T& numerateur)
    {
        _numerateur *= numerateur;
        simplifier();
        return *this;
    }
    template <>
    ZFraction& operator*=<ZFraction>(const ZFraction& a)
    {
        _numerateur *= a._numerateur;
        _denominateur *= a._denominateur;
        simplifier();
        return *this;
    }
    template <>
    ZFraction& operator*=<double>(const double& numerateur)
    {
        ZFraction tmp( (_numerateur * numerateur) / _denominateur);
        *this = tmp;
        return *this;
    }


private:
    //Type d'affichage : fraction(true) ou reel(false)
    long int _numerateur = 0;   //Numerateur
    long int _denominateur = 1; //Denominateur
    bool _afficherFraction = true;
private:
    std::string afficherPlainText1(void) const;
    std::string afficherHTML1(void) const;
    long int getPGCD(long int, long int) const;
    void simplifier();
    void verifierDenominateur() const;
};

// OPERATEURS ##########################################################################
std::ostream& operator<<(std::ostream& , ZFraction const& );
ZFraction operator-(ZFraction const& a); // opérateur « moins unaire » (exemple : a= -b)

//template <typename T = long int> ... ABANDON, conflit avec Qt
bool operator==(ZFraction const& a, ZFraction const& b);
bool operator==(ZFraction const& a, long int const& b);

//template <typename T = long int> ... ABANDON, conflit avec Qt
bool operator!=(ZFraction const& a, ZFraction const& b);
bool operator!=(ZFraction const& a, long int const& b);



template <typename T = long int>
ZFraction operator+(ZFraction const& a, T const& b)
{
    ZFraction copie(a);	//On utilise le constructeur de copie de la classe Duree !
    copie += b;			//On appelle la méthode d'addition qui modifie l'objet 'copie'
    return copie;		//Et on renvoie le résultat. Ni a ni b n'ont changé.
}

template <typename T = long int>
ZFraction operator-(ZFraction const& a, T const& b)
{
    ZFraction copie(a);
    copie -= b;
    return copie;
}

template <typename T = long int>
ZFraction operator/(ZFraction const& a, T const& b)
{
    ZFraction copie(a);
    copie /= b;
    return copie;
}

template <typename T = long int>
ZFraction operator*(ZFraction const& a, T const& b)
{
    ZFraction copie(a);
    copie *= b;
    return copie;
}


template <typename T = long int>
bool operator<(ZFraction const& a, T const& b) // Astuce : a<b <==> !(a>b || a==b)
{
    return !( a.estSuperieur(b) || a.estEgal(b) );
}


template <typename T = long int>
bool operator<=(ZFraction const& a, T const& b) // Astuce : a<=b <==> !(a>b)
{
    return !a.estSuperieur(b);
}


template <typename T = long int>
bool operator>(ZFraction const& a, T const& b)
{
    return a.estSuperieur(b);
}


template <typename T = long int>
bool operator>=(ZFraction const& a, T const& b) // Astuce : a>=b <==> a>b || a==b
{
    return a.estSuperieur(b) || a.estEgal(b);
}

