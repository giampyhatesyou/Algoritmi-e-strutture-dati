/****************************************************/
/*          ESAME DI LABORATORIO DI ASD             */
/****************************************************/

// Descrizione:
// In questo esame consideriamo grafi rappresentati tramite matrici di adiacenza. Il grafo viene utilizzato per rappresentare persone e i loro incontri (o contatti) 
// nell'arco dell'ultima ora (pensate alla questione Covid).
// Di conseguenza, il grafo e' non orientato e ogni arco e' etichettato con il numero di minuti le persone sono state in contatto tra loro. 
//
// Per esempio, supponiamo di avere il grafo seguente:
// 0 1 0
// 1 0 3
// 0 3 0
//
// Questo grafo contiene 3 persone, dove Persona 0 e' stata in contatto con Persona 1 per 1 minuto, Persona 1 e' stata in contatto con Persona 0 per 1 minuto e 
// Persona 2 per 3 minuti. Infine Persona 2 è stata in contatto con Persona 1 per 3 minuti.


#include <iostream>

using namespace std;

/****************************************************************/
// Definizione Lista semplice ausiliaria (utile successivamente)
/****************************************************************/

struct Cella {
    int id;
    Cella* prossimo;
};

typedef Cella* Lista; // definiamo lista come un puntatore a cella

Lista lista_vuota = nullptr; // la lista vuota corrisponde a nullptr
int elemento_vuoto = -1;     // questo elemento viene ritornato quando la lista è vuota e si prova a rimuovere un elemento da essa

// funzione che crea la lista vuota
void creaLista(Lista& lista) {
    lista = lista_vuota;
}

// funzione che aggiunge elemento alla lista (aggiunge in coda)
void aggiungiElemento(Lista& lista, int id) {
    if(lista == lista_vuota) {
        lista = new Cella();
        lista->id = id;
        lista->prossimo = lista_vuota;
    }
    else {
        Lista aux = lista;
        while(aux->prossimo != lista_vuota) {
            aux = aux->prossimo;
        }
        aux->prossimo = new Cella();
        aux->prossimo->id = id;
        aux->prossimo->prossimo = lista_vuota;
    }
}

// funzione che rimuove elemento dalla lista (rimuove in testa)
int rimuoviElemento(Lista& lista) {
    if(lista == lista_vuota) {
        return elemento_vuoto;
    }
    int elemento = lista->id;
    Lista aux = lista;
    lista = lista->prossimo;
    delete aux;
    return elemento;
}

// funzione che stampa a video la lista
void printLista(Lista lista) {
    cout << "[";
    while(lista != lista_vuota) {
        cout << " Persona " << lista->id;
        lista = lista->prossimo;
        if(lista != lista_vuota) cout << ",";
    }
    cout << " ]" << endl;
}

/****************************************************************/
// Definizione Grafo con matrice di adiacenza
/****************************************************************/

typedef int Tempo; // usato per esprimere la durata del contatto

const int max_persone = 10; // massimo numero di persone che il grafo puo' contenere

struct Grafo {
    int n_persone;                            // numero corrente di persone nel grafo
    Tempo contatti[max_persone][max_persone]; // matrice di adiacenza dei contatti tra le persone
};

// funzione che inizializza il grafo con n persone (variabile n_persone)
void inizializzaGrafo(Grafo& grafo, int n_persone) {
    if(n_persone > max_persone) {
        return;
    }
    grafo.n_persone = n_persone;
    for(int i = 0; i < grafo.n_persone; i++) {
        for(int j = 0; j < grafo.n_persone; j++) {
            grafo.contatti[i][j] = 0;
        }
    }
}

// funzione che stampa a video il grafo
void printGrafo(Grafo grafo) {
    for(int i = 0; i < grafo.n_persone; i++) {
        cout << "Persona " << i << " e' stata in contatto con: ";
        bool contatto = false;
        for(int j = 0; j < grafo.n_persone; j++) {
            if(grafo.contatti[i][j] > 0) {
                cout << "- Persona " << j << " per " << grafo.contatti[i][j] << (grafo.contatti[i][j] > 1 ? " minuti; " : " minuto; ");
                contatto = true;
            }
        }
        if(!contatto) {
            cout << "Nessuno";
        }
        cout << endl;
    }
}

// funzione che registra un contatto diretto tra persona id_persona1 e persona id_persona2 
// Tale contatto diretto e' rappresentato dalla variabile durata_contatto
void registraContatto(Grafo& grafo, int id_persona1, int id_persona2, Tempo durata_contatto) {
    // DA IMPLEMENTARE
    grafo.contatti[id_persona1][id_persona2] = durata_contatto;
    grafo.contatti[id_persona2][id_persona1] = durata_contatto;
}

// funzione che ritorna la lista di persone che potrebbero essere state infettate con contatto diretto dalla persona id_persona
// (supponiamo che questo avvenga se il contatto è durato almeno 3 minuti, se il contatto è durato meno si suppone che l'infezione non sia avvenuta) 
// Usare le operazioni della lista fornita
Lista possibiliInfettiContattoDiretto(Grafo grafo, int id_infetto) {
    // DA IMPLEMENTARE
    Lista infetti = lista_vuota;
    for(int i=0; i<grafo.n_persone; ++i){
        if(grafo.contatti[id_infetto][i] >= 3 && grafo.contatti[i][id_infetto] >= 3){
            aggiungiElemento(infetti, i);
        }
    }
    return infetti;
}

// funzione che controlla se la catena di infezioni data in input è corretta (ovvero è una sequenza di persone che possono infettarsi fra loro)
// Esempio con catena di infezioni [1,2,3,4] 
// La funzione ritorna vero se 1 ha avuto contatto con 2 per almeno 3 minuti, e se 2 ha avuto contatto con 3 per almeno 3 minuti,
// e se 3 ha avuto contatto con 4 per almeno 3 minuti. Intuitivamente, questa catena rappresenta una sequenza di infezioni assumendo che la prima persona sia infetta.
bool catenaDiInfezioni(Grafo grafo, Lista catena) {
    // DA IMPLEMENTARE
    if(catena == lista_vuota)
        return false;
    while(catena->prossimo != lista_vuota){
        if(grafo.contatti[catena->id][catena->prossimo->id] < 3)
            return false; //caso che interromperebbe la streak di concatenazioni corrette
        catena = catena->prossimo;
    } //se non sono stato interrotto è tutto corretto e posso ritornoare true
    return true;
}

//FUNZIONI AUSILIARI PER L'ULTIMA FUNZIONE
bool is_in(Lista l1, int id){
    while (l1 != lista_vuota){
        if(l1->id == id)
            return true; //posso interrompermi perchè so che è presente
        l1 = l1->prossimo; //avanzo
    }
    return false; //se non sono stato interrotto vuol dire che non era presente
}

Lista mix(Lista l1, Lista l2){ //funzione ausiliare che fonde due liste senza duplicare elementi
    //scorro l2
    while(l2 != lista_vuota){
        if(!is_in(l1, l2->id))  //se l2->id non è già in l1
            aggiungiElemento(l1, l2->id); //inserisco
        l2 = l2->prossimo; //avanzo
    }
    return l1;
}

// funzione che ritorna una lista contenente tutte le persone infettabili (direttamete e indirettamente) da id_infetto (la lista ritornata non deve contenere id_infetto)
// questa lista rappresenta una possibile catena di infezioni a partire dalla persona id_infetto
Lista possibiliInfetti(Grafo grafo, int id_infetto) {
    // DA IMPLEMENTARE
    Lista infetti = new Cella;
    //inserisco id_infetto nella prima cella in modo da non inserirla nuovamente grazie ai miei controlli
    //e rimuoverlo più facilmente successivamente
    infetti->id = id_infetto;
    for(int i=0; i<grafo.n_persone; ++i){
        if(grafo.contatti[id_infetto][i] >= 3){ //possibile infetto
            //aggiungo tutti i contatti diretti di i
            Lista aux = possibiliInfettiContattoDiretto(grafo, i); //prendo tutti gli elementi possibili di i
            infetti = mix(infetti, aux); 
        } //altrimenti non faccio niente
    }//rumuovo id_infetto
    Lista aux = infetti;
    infetti = infetti->prossimo;
    delete aux; //deallocazione
    return infetti;
}

/****************************************************************/
// MAIN con casi di test
/****************************************************************/
int main() {
    int n_persone = 5; // inizializziamo grafo con 5 persone
    Grafo grafo;
    inizializzaGrafo(grafo, n_persone);

    cout << "****** ESECUZIONE  ****** " << endl << endl;
	cout << "*** FUNZIONE 1 *** " << endl;
    registraContatto(grafo, 0, 1, 2); // registriamo contatto diretto tra Persona 0 e Persona 1 per 2 minuti
    registraContatto(grafo, 0, 2, 1); // registriamo contatto diretto tra Persona 0 e Persona 2 per 1 minuto
    registraContatto(grafo, 1, 2, 3); // registriamo contatto diretto tra Persona 1 e Persona 2 per 3 minuti
    registraContatto(grafo, 1, 3, 5); // registriamo contatto diretto tra Persona 1 e Persona 3 per 5 minuti
    cout << "CONTATTI OSSERVATI:" << endl;
    printGrafo(grafo); // stampa il grafo a video
    cout << endl;
    cout << "La tua funzione e' corretta se sopra ha stampato (dopo CONTATTI OSSERVATI):" << endl;
    cout << "Persona 0 e' stata in contatto con: - Persona 1 per 2 minuti; - Persona 2 per 1 minuto;" << endl;
    cout << "Persona 1 e' stata in contatto con: - Persona 0 per 2 minuti; - Persona 2 per 3 minuti; - Persona 3 per 5 minuti;" << endl;
    cout << "Persona 2 e' stata in contatto con: - Persona 0 per 1 minuto; - Persona 1 per 3 minuti;" << endl;
    cout << "Persona 3 e' stata in contatto con: - Persona 1 per 5 minuti;" << endl;
    cout << "Persona 4 e' stata in contatto con: Nessuno;" << endl << endl;

    cout << endl << "*** FUNZIONE 2 *** " << endl;
    cout << "Possibili persone infette causa contatto diretto con Persona 1: ";
    printLista(possibiliInfettiContattoDiretto(grafo, 1)); // stampiamo a video i possibili contatti diretti di Persona 1 che potrebbero quindi essere stati infettati
    cout << endl;
    cout << "La tua funzione e' corretta se sopra ha stampato (l'ordine degli elementi stampati non ha importanza):" << endl;
    cout << "Possibili persone infette causa contatto diretto con Persona 1: [ Persona 2, Persona 3]" << endl;

    cout << endl << "*** FUNZIONE 3 *** " << endl;
    registraContatto(grafo, 2, 3, 6); // registriamo contatto diretto tra Persona 2 e Persona 3 per 6 minuti
    Lista catena;
    creaLista(catena);
    aggiungiElemento(catena, 1);
    aggiungiElemento(catena, 2);
    aggiungiElemento(catena, 3);
    cout << "TEST catena di infezioni: " << (catenaDiInfezioni(grafo, catena) ? "PASSATO" : "FALLITO") << endl;

    cout << endl << "*** FUNZIONE 4 *** " << endl;
    registraContatto(grafo, 3, 4, 5); // registriamo contatto diretto tra Persona 3 e Persona 4 per 6 minuti
    cout << "Possibili infetti diretti e indiretti da Persona 1: ";
    printLista(possibiliInfetti(grafo, 1));
    cout << endl;
    cout << "La tua funzione e' corretta se sopra ha stampato: (l'ordine degli elementi stampati non ha importanza)" << endl;
    cout << "Possibili infetti diretti e indiretti da Persona 1: [ Persona 2, Persona 3, Persona 4 ]" << endl;
}
