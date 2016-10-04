#pragma once
#include <iostream>
#include <string>
#include "ZFraction.h"

class Membre
{
public:
    // Operation : Aucune, addition, soustration, multiplication ou division
    enum operation { operation_Aucune, operation_addition, operation_soustraction, operation_multiplication, operation_division };
    // Parenthese : Aucune, ouverte (ouvrante seulement) ou fermee (ouvrante et fermante)
    enum parenthese { parenthese_Aucune, parenthese_ouverte, parenthese_fermee };

    Membre();
    Membre(int, int = 1);
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

    // Surcharger les operation +-*/
    // Surcharger les operation += -= *= /=

    Membre& operator+=(const Membre& a);
    Membre& operator-=(const Membre& a);
    Membre& operator/=(const Membre& a);
    Membre& operator*=(const Membre& a);
private:
    bool operator_generic(const Membre& a, const operation oper, const bool =false);
    bool operator_valueless(const Membre& a, const operation oper);
    bool operator_simple(const Membre& a, const operation oper);
    bool operator_halfComplex(const Membre& a, const operation oper, const bool =false);
    bool operator_complex(const Membre& a, const operation oper, const bool =false);

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
    // Retourne vrai si le membre ne contient rien (pas d'operation, pas de nombre et pas de parenthese)
    bool isEmpty() const;
    // Idem Empty, mais indifferent aux parentheses
    bool isValueless() const;
    bool isSimple() const;
    bool isHalfComplex() const;
    bool isComplex() const;
    // Appelle m_membre1/2->simplifier() et si m_membre1/2->isSimple() sont vrais alors enregistre m_nombre=m_operation->getResultat() libere m_operation/m_membre1/m_membre2.
    bool simplifier();
    void ouvrirParenthese(operation =operation_Aucune);
    void operator_aucuneOperation(const Membre&);
    bool fermerParenthese();
    void setAfficherFraction(bool =true);
    bool getAfficherFraction(void) const;

private:
    void ouvrirParenthese_valueless(operation);
    void ouvrirParenthese_simple(operation);
    void ouvrirParenthese_halfComplex(operation);
    void ouvrirParenthese_complex(operation);
    bool fermerParenthese_valueless();
    bool fermerParenthese_simple();
    bool fermerParenthese_halfComplex();
    bool fermerParenthese_complex();


protected:
    ZFraction *nombre_ = nullptr; // Pointeur sur le nombre
    Membre *membre1_ = nullptr; //Pointeur sur le 1er membre de l'operation
    operation operation_ = operation_Aucune; // Operation du membre
    Membre *membre2_ = nullptr; //Pointeur sur le 2ond membre de l'operation
    parenthese parenthese_ = parenthese_Aucune; // Etat des parentheses
    //Type d'affichage : fraction(true) ou reel(false)
    bool afficherFraction_ = true;
};

std::ostream& operator<<(std::ostream&, Membre const&);
Membre operator-(Membre const& a); // operateur "moins unaire" (exemple : a= -b)
Membre operator+(Membre const& a, Membre const& b);
Membre operator-(Membre const& a, Membre const& b);
Membre operator/(Membre const& a, Membre const& b);
Membre operator*(Membre const& a, Membre const& b);
