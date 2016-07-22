#pragma once
#include <iostream>
#include "ZFraction.h"

class Nombre
{
public:
	Nombre();
	~Nombre();
protected:
	ZFraction m_fraction;
public:
	Nombre(int entier);
	Nombre(int numerateur, int denominateur);
	Nombre(double decimal);
	double getNombre() const;
	void afficher(std::ostream &) const;
	bool isSimple() const;
	void simplifier();

	Nombre& Nombre::operator+=(const Nombre&);
	Nombre& Nombre::operator-=(const Nombre&);
	Nombre& Nombre::operator/=(const Nombre&);
	Nombre& Nombre::operator*=(const Nombre&);
};

std::ostream& operator<<(std::ostream&, Nombre const&);

Nombre operator+(Nombre const&, Nombre const&);
Nombre operator-(Nombre const&, Nombre const&);
Nombre operator*(Nombre const&, Nombre const&);
Nombre operator/(Nombre const&, Nombre const&);
