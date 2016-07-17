#pragma once
#include <iostream>
#include <string>
#include "ZFraction.h"

class Membre
{
public:
    enum operation { aucune, addition, soustraction, multiplication, division };

    Membre();
    Membre(int);
    Membre(int, int);
    Membre(double);
    Membre(ZFraction);
    Membre(Membre, operation, Membre);
    Membre(int, int, operation, int, int);
    Membre(int, operation, int);
    // Surcharger la copie (pour gerer les pointeurs)
    Membre(Membre const &);					// Constructeur de copie
    Membre& operator=(Membre const &);		// L'opérateur d'affectation
    ~Membre();
    void vider();


    void operator_simple(const Membre& a, const operation oper);
    void operator_halfComplex(const Membre& a, const operation oper);
    void operator_complex(const Membre& a, const operation oper);
    Membre& operator+=(const Membre& a);
    Membre& operator-=(const Membre& a);
    Membre& operator/=(const Membre& a);
    Membre& operator*=(const Membre& a);

public:

    ZFraction getResultat() const;
    void afficher(std::ostream &) const;
    std::string afficherPlainText(void) const;
    std::string afficherHTML(void) const;
    void afficherOperation(std::ostream &) const;
    std::string afficherOperationPlainText(void) const;
    std::string afficherOperationHTML(void) const;
    static std::string afficherOperationPlainText(operation);
    static std::string afficherOperationHTML(operation);
    // Retourne vrai si le membre ne contient pas d'operation, mais seulement un nombre.
    bool isEmpty() const;
    bool isSimple() const;
    bool isHalfComplex() const;
    bool isComplex() const;
    // Appelle m_membre1/2->simplifier() et si m_membre1/2->isSimple() sont vrais alors enregistre m_nombre=m_operation->getResultat() libere m_operation/m_membre1/m_membre2.
    bool simplifier();
    void proteger();
    void deproteger();
    void setAfficherFraction(bool =true);
    bool getAfficherFraction(void) const;

    // Surcharger les operation +-*/
    // Surcharger les operation += -= *= /=

protected:
    bool parenthese_;
    bool afficherFraction_;
    Membre *membre1_;
    operation operation_;
    Membre *membre2_;
    ZFraction *nombre_;
};

std::ostream& operator<<(std::ostream&, Membre const&);
Membre operator-(Membre const& a); // operateur "moins unaire" (exemple : a= -b)
Membre operator+(Membre const& a, Membre const& b);
Membre operator-(Membre const& a, Membre const& b);
Membre operator/(Membre const& a, Membre const& b);
Membre operator*(Membre const& a, Membre const& b);
