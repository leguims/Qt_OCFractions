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
    bool estEgal(ZFraction a) const;
    bool estSuperieur(ZFraction a) const;
    ZFraction& operator+=(const ZFraction& a);
    ZFraction& operator-=(const ZFraction& a);
    ZFraction& operator/=(const ZFraction& a);
    ZFraction& operator*=(const ZFraction& a);
    ZFraction& operator+=(const long int& a);
    ZFraction& operator-=(const long int& a);
    ZFraction& operator/=(const long int& a);
    ZFraction& operator*=(const long int& a);
private:
    //Type d'affichage : fraction(true) ou reel(false)
    bool _afficherFraction = true;  
    long int _numerateur = 0;   //Numerateur
    long int _denominateur = 1; //Denominateur
private:
    void simplifier();
    void verifierDenominateur() const;
};

std::ostream& operator<<(std::ostream& , ZFraction const& );
ZFraction operator-(ZFraction const& a); // opérateur « moins unaire » (exemple : a= -b)

ZFraction operator+(ZFraction const& a, ZFraction const& b);
ZFraction operator-(ZFraction const& a, ZFraction const& b);
ZFraction operator/(ZFraction const& a, ZFraction const& b);
ZFraction operator*(ZFraction const& a, ZFraction const& b);

ZFraction operator+(ZFraction const& a, long int const& b);
ZFraction operator-(ZFraction const& a, long int const& b);
ZFraction operator/(ZFraction const& a, long int const& b);
ZFraction operator*(ZFraction const& a, long int const& b);

bool operator==(ZFraction const& a, ZFraction const& b);
bool operator!=(ZFraction const& a, ZFraction const& b);
bool operator<(ZFraction const& a, ZFraction const& b);
bool operator<=(ZFraction const& a, ZFraction const& b);
bool operator>(ZFraction const& a, ZFraction const& b);
bool operator>=(ZFraction const& a, ZFraction const& b);
