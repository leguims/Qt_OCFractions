#include "guicalulatrice.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GUICalulatrice calculette;
    calculette.show();

    return a.exec();
}

// Definir comment chainer les operateurs, les chiffres et les resultats intermédiaires.

// ************************************************************************************
// Objet Membre :
//      DESCRIPTION:
//              Liste d'operations. Version 1 : 1 operation ou 1 fraction. Version 2 : +1 inconnue.
//      ATTRIBUTS:
//              m_parenthese;   // si vrai : le membre est encadré par des parenthèses explicites (= à afficher).
//              *m_operation;
//              *m_nombre;      // Nombre = fraction (ou entier) ou decimal
//      METHODES:
//              setNombre(Nombre nombre);
//              getResultat();  // Retourne m_nombre s'il existe.
//              simplifier();   // Appelle m_operation->simplifier()
//                              //    ... et si m_operation->isSimple() est vrai alors enregistre m_nombre=m_operation->resultat() libere m_operation.
//              afficher();
//              isSimple();     // Retourne vrai si le membre ne contient pas d'operation, mais seulement un nombre.

// ************************************************************************************
// Objet Operation :
//      DESCRIPTION:
//              association de 2 membres liés par une operation. Le resultat est dépendant de l'operation.
//      ATTRIBUTS:
//              Membre *m_membre1, *m_membre2;
//              Nombre m_neutre;
//      METHODES:
//              Operation(Operation const& operationACopier);
//                    Operation::Operation(Operation const& operationACopier)
//                       :
//                    {
//                        m_membre1 = nullptr;
//                        if(nullptr == operationACopier.m_membre1)
//                        {
//                            m_membre1 = new Membre(*(operationACopier.m_membre1));
//                        }

//                        m_membre2 = nullptr;
//                        if(nullptr == operationACopier.m_membre2)
//                        {
//                            m_membre2 = new Membre(*(operationACopier.m_membre2));
//                        }
//                    }
//              Operation& operator=(Operation const& operationACopier);
//                    Operation& Operation::operator=(Operation const& operationACopier)
//                    {
//                        if(this != &operationACopier)
//                        //On vérifie que l'objet n'est pas le même que celui reçu en argument
//                        {
//                            // Apres la copie, l'attribut initial doit etre perdu.
//                            if(nullptr != m_membre1)
//                            {
//                                delete m_membre1;
//                                m_membre1 = nullptr;
//                            }
//                            // Copie de l'attribut ACopier.
//                            if(nullptr == operationACopier.m_membre1)
//                            {
//                                m_membre1 = new Membre(*(operationACopier.m_membre1));
//                            }

//                            // Apres la copie, l'attribut initial doit etre perdu.
//                            if(nullptr != m_membre2)
//                            {
//                                delete m_membre2;
//                                m_membre2 = nullptr;
//                            }
//                            // Copie de l'attribut ACopier.
//                            if(nullptr == operationACopier.m_membre2)
//                            {
//                                m_membre2 = new Membre(*(operationACopier.m_membre2));
//                            }
//                        }
//                        return *this; //On renvoie l'objet lui-même
//                    }
//              virtual Nombre getResultat() =0;   // Si m_membre1 et m_membre2 sont simples, retourne le résultat de l'opération.
//              virtual afficher() =0;
//              virtual Nombre getNombreNeutre() =0;
//              bool isSimple();      // Retourne vrai si chaque membre ne contient pas d'operation, mais seulement un nombre.
//              void simplifier();    // Appelle m_membre->simplifier() pour chaque membre non simple.

// ************************************************************************************
// Objet Addition : hérite Operation
//      DESCRIPTION:
//             Implémente l'opération d'addition entre les 2 membres de la classe mere.
//      ATTRIBUTS:
//      METHODES:
//              getResultat();
//              afficher();
//              getNombreNeutre(); // Retourne 0

// ************************************************************************************
// Objet Soustraction : hérite Operation
//      DESCRIPTION:
//             Implémente l'opération de soustraction entre les 2 membres de la classe mere.
//      ATTRIBUTS:
//      METHODES:
//              getResultat();
//              afficher();
//              getNombreNeutre(); // Retourne 0

// ************************************************************************************
// Objet Multiplication : hérite Operation
//      DESCRIPTION:
//             Implémente l'opération de multiplication entre les 2 membres de la classe mere.
//      ATTRIBUTS:
//      METHODES:
//              getResultat();
//              afficher();
//              getNombreNeutre(); // Retourne 1

// ************************************************************************************
// Objet Division : hérite Operation
//      DESCRIPTION:
//             Implémente l'opération de division entre les 2 membres de la classe mere.
//      ATTRIBUTS:
//      METHODES:
//              getResultat();
//              afficher();
//              getNombreNeutre(); // Retourne 1
