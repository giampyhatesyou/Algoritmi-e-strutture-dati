/****************************************************/
/* PROVA DI ESAME DI LABORATORIO DI ASD             */
/****************************************************/
// TRE DOMANDE

// scrivere sotto Nome, Cognome e Matricola:
// NOME: Andrea
// COGNOME: Giampietro
// MATRICOLA: S5208458

// DESCRIZIONE:
// In questo laboratorio si considera il tipo di dato Albero binario dove i nodi sono numeri interi positivi.
// Un'albero binario e' un albero con radice dove ogni nodo ha al piu' due figli


/****************************************************************/
/* DESCRIZIONE FUNZIONI DA IMPLEMENTARE */

/* Sviluppare le tre seguenti funzioni C/C++ la cui specifica è data sotto forma di commento prima delle rispettive funzioni:

   1) int getNumPari(const Tree& t)
      
   2) Label trovaPadre(Label questo, const Tree& t);
   
   3) int sommaProfondita(int k, const Tree& t);
      
*/
    
#include <iostream>
#include <string>

using namespace std;

// Implementa Albero binario con strutture collegate (Nodo) mediante puntatori e Label dotata di ordinamento
namespace tree {

    typedef int Label;
    struct Nodo;
    typedef Nodo* Tree; // un albero e' identificato dal puntatore alla sua radice
    const Tree alberoVuoto = nullptr;
    const Label emptyLabel =-1000000;
    // Costruisce albero vuoto
    Tree creaAlberoVuoto();
    // Restituisce true se l'albero t e' vuoto (oppure se il puntatore punta a NULL), false altrimenti
    bool vuoto(const Tree& t);
    // Aggiunge nodo radice, fallisce se l'albero e' non vuoto
    bool inserisciRadice(const Label l, Tree& t);
    // Aggiunge nuovo nodo sinistro di un nodo esistente. Ritorna false se non esiste il nodo "questo" nell'albero o se la label "nome_figlio_sx" e' gia' presente nell'albero
    bool inserisciFiglioSX(Label questo, Label nome_figlio_sx, Tree& t);
    // Aggiunge nuovo nodo destro di un nodo esistente. Ritorna false se non esiste il nodo "questo" nell'albero o se la label "nome_figlio_dx" e' gia' presente nell'albero
    bool inserisciFiglioDX(Label questo, Label nome_figlio_dx, Tree& t);
    // Restituisce il numero di etichette pari presenti nell'albero. Se l'albero e` vuoto restituisce 0
    int getNumPari(const Tree& t);
    // Restituisce l'etichetta del padre del nodo con etichetta "questo" se il nodo esiste nell'albero (o sottoalbero) t e se il padre esiste. Restituisce la costante emptyLabel altrimenti
    Label trovaPadre(Label questo, const Tree& t);
    // Restituisce la somma dei valori associati ai nodi che si trovano a profondita' maggiore o uguale a k. 
    // Se non esistono nodi a profondita' maggiore o uguale a k, oppure in caso di albero vuoto, l'algoritmo deve restituire 0. 
    // Ricordiamo che la radice si trova a profondita' zero.
    int sommaProfondita(int k, const Tree& t);
}

using namespace tree;

// il nodo di un albero e' caratterizzato dall'etichetta (in questo caso un intero),
// il puntatore al figlio sinistro e il puntatore al figlio destro
struct tree::Nodo {
    Label label;
    Nodo *sinistro;
    Nodo *destro;
};

/*******************************************************************************************************/
// Funzioni ausiliarie
/*******************************************************************************************************/

// Data un'etichetta l crea il nodo con quella etichetta e ne restituisce il puntatore
Nodo* createNode(const Label l) {
    Nodo* t = new Nodo;
    t->label = l;
    t->sinistro = t->destro = NULL;
    return t;
}

// Data un'etichetta l e un albero t (ovvero, un albero la cui radice
// e' il nodo puntato da t), restituisce il puntatore al nodo dell'albero t che ha quell'etichetta
// (NULL se nessun nodo ha quell'etichetta)
Nodo* getNode(const Label l, const Tree& t) {
    // se l'albero e' vuoto restituisco il nodo vuoto
    if (vuoto(t))
        return alberoVuoto;
    // se l'etichetta dell'albero e' quella cercata, restituisco t
    if (t->label == l)
        return t; 
    // cerca nei figli
    Nodo* aux = alberoVuoto;
    if (!vuoto(t->sinistro)) aux = getNode(l, t->sinistro);
    if (!vuoto(aux)) return aux;
    if (!vuoto(t->destro)) aux = getNode(l, t->destro);
    if (!vuoto(aux)) return aux;
    // non trovato!
    return NULL;
}

/*******************************************************************************************************/
// Funzioni relative all'albero binario
/*******************************************************************************************************/

// Costruisce l'albero vuoto
Tree tree::creaAlberoVuoto() {
   return alberoVuoto;
}

// Restituisce true se l'albero t e' vuoto (oppure se il puntatore punta a NULL), false altrimenti
bool tree::vuoto(const Tree& t) {
   return (t==alberoVuoto);
}

// Aggiunge il nodo radice, fallisce se l'albero e' non vuoto o se l'etichetta e` minore di zero
bool tree::inserisciRadice(const Label l, Tree& t) {
    if(l<0 || !vuoto(t)) 
        return false;

    Tree aux = new Nodo;
    aux->label = l;
    t = aux;
    return true;
}

// Aggiunge nuovo nodo sinistro di un nodo esistente
// Ritorna false se non esiste il nodo "questo" nell'albero, se la label "nome_figlio_sx" e' gia' presente nell'albero o se e` minore di zero
bool tree::inserisciFiglioSX(Label questo, Label nome_figlio_sx, Tree& t) {
    Tree from = getNode(questo, t);
    if(vuoto(from))
        return false;
    
    if(!vuoto(getNode(nome_figlio_sx, t)) || nome_figlio_sx<0)
        return false;
    //ora che ho fatto tutti i controlli di dovere, inserisco il figlio
    Tree aux = new Nodo;
    aux->label = nome_figlio_sx;
    from->sinistro = aux;
    return true;
}

// Aggiunge nuovo nodo destro di un nodo esistente
// Ritorna false se non esiste il nodo "questo" nell'albero, se la label "nome_figlio_dx" e' gia' presente nell'albero o se e` minore di zero
bool tree::inserisciFiglioDX(Label questo, Label nome_figlio_dx, Tree& t) {
    Tree from = getNode(questo, t);
    if(vuoto(from))
        return false;
    
    if(!vuoto(getNode(nome_figlio_dx, t)) || nome_figlio_dx<0)
        return false;
    //ora che ho fatto tutti i controlli di dovere, inserisco il figlio
    Tree aux = new Nodo;
    aux->label = nome_figlio_dx;
    from->destro = aux;
    return true;
}

// Restituisce il numero di etichette pari presenti nell'albero. Se l'albero e` vuoto restituisce 0
int tree::getNumPari(const Tree& t) {
    if(vuoto(t)) return 0;
    if(t->label%2 == 0)
        return(1+getNumPari(t->sinistro)+getNumPari(t->destro));
    else    
        return(getNumPari(t->sinistro)+getNumPari(t->destro));
}

// Restituisce l'etichetta del padre del nodo con etichetta "questo" se il nodo esiste nell'albero (o sottoalbero) t e se il padre esiste. Restituisce la costante emptyLabel altrimenti
Label tree::trovaPadre(Label questo, const Tree& t) {
    /*if(vuoto(t)) return emptyLabel;
    //controllo se è il padre
    if(!vuoto(t->sinistro)){ //evito segm fault
       if(t->sinistro->label == questo) return t->label;  
    }
    if(!vuoto(t->destro)){
        if(t->destro->label == questo) return t->label;
    }

    //variabili per chiamate ricorsive
    if(!vuoto(t->destro) && !vuoto(t->sinistro)){ //se esistono entrambi i figli
        trovaPadre(questo, t->sinistro);
        trovaPadre(questo, t->destro);
    }
    else if(!vuoto(t->sinistro) && vuoto(t->destro)) //se ho solo figlio sinistro
        trovaPadre(questo, t->sinistro);

    else if(vuoto(t->sinistro) && !vuoto(t->destro)) //se ho solo figlio destro
        trovaPadre(questo, t->destro);
    else
        return emptyLabel;*/
   
   
    //MODO PIU' CARINO?

    if(vuoto(t)) return emptyLabel;
    Label aux = emptyLabel;
    if(!vuoto(t->sinistro)){
        if(t->sinistro->label == questo) return t->label;
        else   
            aux = trovaPadre(questo, t->sinistro);
    }
    if(aux != emptyLabel) return aux;
    
    if(!vuoto(t->destro)){
        if(t->destro->label == questo) return t->label;
        else
            aux = trovaPadre(questo, t->destro);
    }
    return aux;
}



// Restituisce la somma dei valori associati ai nodi che si trovano a profondita' maggiore o uguale a k. 
// Se non esistono nodi a profondita' maggiore o uguale a k, oppure in caso di albero vuoto, l'algoritmo deve restituire 0. 
// Ricordiamo che la radice si trova a profondita' zero.
int tree::sommaProfondita(int k, const Tree& t) {
    int somma = 0;
    if(vuoto(t)) return 0;
    if(k<=0){ //faccio le operazioni, altrimenti richiamo scendendo di un livello
        somma+=t->label;
    }
    return(somma+sommaProfondita(k-1, t->sinistro) + sommaProfondita(k-1, t->destro));
}

int main() {
    // creazione albero binario
    Tree t = creaAlberoVuoto();
    // inserimento di nodi in un albero binario
    inserisciRadice(10, t); // inseriamo la radice
    inserisciFiglioSX(10, 8, t);
    inserisciFiglioDX(10, 7, t);
    inserisciFiglioSX(8, 3, t);
    inserisciFiglioDX(8, 5, t);
    inserisciFiglioSX(7, 1, t);
    
    cout << "***** PROVA DI ESAME DI LABORATORIO DI ASD (traccia 1)" << endl;
    cout << "*** PRIMA FUNZIONE *** " << endl;
    if(getNumPari(t) == 2)
        cout << "TEST PASSATO" << endl;
    else
        cout << "TEST FALLITO" << endl;
	cout << endl;
	
    cout << "*** SECONDA FUNZIONE *** " << endl;
    if ((trovaPadre(1, t))==7 && (trovaPadre(4, t))==emptyLabel)
    	cout << "TEST PASSATO" << endl;
    else
        cout << "TEST FALLITO" << endl;
    cout << endl;
    
    cout << "*** TERZA FUNZIONE *** " << endl;
     if (sommaProfondita(2, t)==9)
    	cout << "TEST PASSATO" << endl;
    else
        cout << "TEST FALLITO" << endl;
        
    cout << endl;
}