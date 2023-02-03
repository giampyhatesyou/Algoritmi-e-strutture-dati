/****************************************/
/* PROVA DI ESAME DI LABORATOTIO DI ASD */
/****************************************/

// Descrizione:
// In questo laboratorio si considera il tipo di dato multi-insieme implementato con la struttura dati lista di puntatori
// Un multi-insieme e' sostanzialmente un insieme dove le ripetizioni di elementi sono ammesse
// Si differenzia dal tipo di dato Lista principalmente perche' l'ordine non conta
// Es. [1,1,1,3,2]


// scrivere sotto Nome, Cognome e Matricola:
// NOME: Andrea
// COGNOME: Giampietro
// MATRICOLA: S5208458

#include <iostream>
#include <iostream>

using namespace std;

// Implementa 'multiset' con strutture collegate mediante puntatori e tipo base Elem dotato di ordinamento

namespace multiset {

  /**************************** Codici di errore ********************************************/
  enum Error {OK, FAIL, EMPTY, FULL};

  /**************************** Tipi e costanti *********************************************/

  typedef int Elem;      // tipo base 
  struct cell;
  typedef cell *MultiSet;
  const int FINEINPUT = -1000000;
  const MultiSet emptySet = nullptr;

  void createEmpty(MultiSet&);                     /* crea il multiset vuoto */
  void insertElemS(const Elem, MultiSet&);	       /* inserisce un elemento nel multiset, restituisce FAIL in caso di errore */
  int multiplicity(const Elem, const MultiSet&);   /* calcola la molteplicita' di un elemento */
  bool equals(const MultiSet&, const MultiSet&);   /* controlla se due multi-set sono uguali */
}

using namespace multiset;

struct multiset::cell {
    Elem	elem;
    cell	*next;
};

/****************************************************************/
/* 		  funzioni ausiliarie                                   */
/****************************************************************/

// INSERIRE QUI EVENTUALI FUNZIONI AUSILIARIE

bool isEmpty(multiset::MultiSet s){
    return (s == emptySet);
}


int size(multiset::MultiSet s){
    int counter = 0;
    for(multiset::MultiSet cur = s; cur != emptySet; cur = cur->next)
        counter++;
    return counter;
}


/****************************************************************/
/* 		  operazioni                                            */
/****************************************************************/

void multiset::createEmpty(MultiSet& s) {
   s = emptySet;
}


/****************************************************************/
void multiset::insertElemS(const Elem x, MultiSet& s) {
    cell *aux;
    aux = new cell; 
    aux->elem=x;
    aux->next=s;
    s = aux;
}

/****************************************************************/
/* DESCRIZIONE FUNZIONI DA IMPLEMENTARE

/* Sviluppare le due seguenti funzioni C/C++ 

   1) multiplicity() che restituisce la molteplicita' dell'elemento 'x' nel multi-insieme 's'. 
      La molteplicita' di un elemento, chiamata anche frequenza assoluta, e' il numero di occorrenze (ovvero quante volte occorre/ricorre) di 'x' in s. 
      Ad esempio la molteplicita' dell'elemento 1 nel multi-insieme [1, 1 , 1 , 2 , 2 , 3] e' 3
      
   2) equals() restituisce true se i due multi-insiemi sono uguali, false altrimenti. 
      Due multi-insiemi sono uguali se hanno gli stessi elementi anche se gli elementi sono in posizioni diversa
      Ad esempio i due seguenti multi-insiemi sono uguali: [2, 4, 5, 4] e [4, 4, 5, 2]
*/

// multiplicity restituisce la molteplicita' dell'elemento 'x' nel multi-insieme 's'.  
int multiset::multiplicity(const Elem e, const MultiSet& s){
    int counter = 0;
    for(multiset::MultiSet cur = s; cur != multiset::emptySet; cur = cur->next){
        if(cur->elem == e)
            counter++;
    }
    return counter;
}

// equals restituisce true se i due multi-insiemi sono uguali, false altrimenti. 
bool multiset::equals(const MultiSet& s1, const MultiSet& s2) {
    if(size(s1) != size(s2)) return false;
    //so che hanno stessa size, quindi posso ciclarli insieme
    for(multiset::MultiSet cur = s1; cur != emptySet; cur = cur->next){
        if(multiplicity(cur->elem, s1) != multiplicity(cur->elem, s2))
            return false;
    }
    return true;
}


int main(int argc, char *argv[]) {
    MultiSet m1, m2, m3;
    createEmpty(m1); createEmpty(m2); createEmpty(m3);
    
    // inserimneto degli elementi nel multiset m1
    insertElemS(2, m1); insertElemS(4, m1); insertElemS(5, m1); insertElemS(4, m1); insertElemS(1, m1);
    // inserimneto degli elementi nel multiset m2
    insertElemS(4, m2); insertElemS(2, m2); insertElemS(5, m2); insertElemS(1, m2); insertElemS(4, m2);
    
    if (multiplicity(4, m1)==2) 
        cout << "TEST PASSATO" << endl;
    else
        cout << "TEST FALLITO" << endl;
    
    if (equals(m1, m2)) 
        cout << "TEST PASSATO" << endl;
    else
        cout << "TEST FALLITO" << endl;
        
    if (equals(m1, m3)) 
        cout << "TEST FALLITO" << endl;
    else
        cout << "TEST PASSATO" << endl;
    
    return 0;
}