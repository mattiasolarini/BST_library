// Esercitazione (circa 45 minuti): classi, oggetti e puntatori - il Cinema
// Classe 4C - Nome/Codice: ______________________
//
// Completa le tre classi scrivendo i costruttori e i metodi indicati nei TODO.
// I nomi dei metodi sono quelli scritti qui sotto e usati da main.cpp: decidi tu
// parametri e tipo restituito, guardando anche come li usa main.cpp.
// NON modificare main.cpp. Consegna SOLO questo file (cinema.cpp).
// Se un metodo non riesci a scriverlo, lascia almeno una versione vuota
// (che restituisce un valore qualsiasi) per far compilare il programma.

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

// =====================================================================
// PARTE A - la classe Film (circa 10 minuti)
// =====================================================================

class Film {
private:
    string titolo;
    int durata;         // in minuti
    int spettatori;     // biglietti venduti per questo film

public:
    // TODO 1 - costruttore Film
    //          Riceve titolo e durata (in quest'ordine). All'inizio gli spettatori sono 0.
    Film(string titolo_f, int durata_f)
    {
        titolo = titolo_f;
        durata = durata_f;
        spettatori = 0;     
    }

    // TODO 2 - getTitolo, getDurata, getSpettatori
    //          Tre metodi che restituiscono il valore del corrispondente attributo privato.
    string getTitolo()
    {
        return titolo;
    }

    int getDurata()
    {
        return durata;
    }

    int getSpettatori()
    {
        return spettatori;
    }


    // TODO 3 - registraSpettatori
    //          Aggiunge n spettatori al film. Un n minore o uguale a 0 non cambia nulla.
    void registraSpettatori(int n)
    {
        if(n <= 0)
        {
            return;
        }
        spettatori = spettatori + n;
    }
};

// =====================================================================
// PARTE B - la classe Sala (circa 12 minuti)
// Una Sala non possiede il Film: ne conosce soltanto l'indirizzo.
// Se nessun film e' in programmazione, il puntatore vale nullptr.
// =====================================================================

class Sala {
private:
    int numero;
    int posti;          // capienza totale
    int occupati;       // posti gia' venduti
    Film* film;         // film in programmazione, oppure nullptr

public:
    // TODO 4 - costruttore Sala
    //          Riceve numero e posti (in quest'ordine). All'inizio nessun posto e'
    //          occupato e nessun film e' in programmazione.
    Sala(int numero_s, int posti_s)
    {
        numero = numero_s;
        posti = posti_s;
        occupati = 0,
        film = nullptr;
    }

    // TODO 5 - getNumero, getPosti, postiLiberi, getFilm
    //          getNumero e getPosti restituiscono gli attributi; postiLiberi calcola
    //          quanti posti non sono ancora occupati; getFilm restituisce il puntatore
    //          al film in programmazione (nullptr se non c'e').
    int getNumero()
    {
        return numero;
    }

    int getPosti()
    {
        return posti;
    }

    int postiLiberi()
    {
        return (posti - occupati);
    }

    Film* getFilm()
    {
        return film;
    }

    // TODO 6 - assegnaFilm
    //          Riceve il puntatore a un Film e lo mette in programmazione nella sala.
    //          Inizia una nuova proiezione: i posti occupati tornano a 0.
    //          Va bene anche nullptr (la sala resta senza film). Il Film NON va copiato.
    void assegnaFilm(Film* f)
    {
        film = f;
        occupati = 0;
    }


    // TODO 7 - vendiBiglietti
    //          Vende n biglietti e dice se la vendita e' riuscita. Non cambia nulla se
    //          non c'e' nessun film in programmazione, se n e' minore o uguale a 0 o se
    //          i posti liberi non bastano. Se riesce, occupa i posti e registra gli n
    //          spettatori sul Film in programmazione (quello originale, non una copia).
    bool vendiBiglietti(int n)
    {
        
        if(film == nullptr || n <= 0 || postiLiberi() < n)
        {
            return false;
        }
        occupati = occupati + n;
        film->registraSpettatori(n);
        return true;
    }
};

// =====================================================================
// PARTE C - la classe Cinema (circa 23 minuti)
// Il Cinema crea con new tutti i Film e le Sale e li tiene in due vector di
// puntatori: e' lui a doverli distruggere con delete.
// =====================================================================

class Cinema {
private:
    string nome;
    double prezzoBiglietto;
    double incasso;
    vector<Film*> elencoFilm;
    vector<Sala*> elencoSale;

public:
    // ESEMPIO (gia' scritto) - costruttore: i parametri hanno un nome diverso
    // dagli attributi, cosi' si capisce chi e' chi
    Cinema(string n, double prezzo) {
        nome = n;
        prezzoBiglietto = prezzo;
        incasso = 0.0;
    }

    // ESEMPIO (gia' scritti) - metodi di sola lettura
    string getNome() const { return nome; }
    double getIncasso() const { return incasso; }
    int numeroFilm() const { return (int)elencoFilm.size(); }
    int numeroSale() const { return (int)elencoSale.size(); }
    Film* getFilm(int i) const {            // i-esimo film, nullptr se l'indice non esiste
        if (i < 0 || i >= numeroFilm()) return nullptr;
        return elencoFilm[i];
    }
    Sala* getSala(int i) const {            // i-esima sala, nullptr se l'indice non esiste
        if (i < 0 || i >= numeroSale()) return nullptr;
        return elencoSale[i];
    }

    // TODO 8 - cercaFilm, cercaSala
    //          cercaFilm riceve un titolo, cercaSala un numero. Restituiscono il puntatore
    //          al Film o alla Sala trovati (quelli originali, non copie) oppure nullptr
    //          se non esistono.
    Film* cercaFilm(string titolo)
    {
        for(int i = 0; elencoFilm.size() < i; i++)
        {
            if(elencoFilm[i]->getTitolo() == titolo)
            {
                return elencoFilm[i];
            }
        }
        return nullptr;
    }

    Sala* cercaSala(int numero)
    {
        for(int i = 0; elencoSale.size() < i; i++)
        {
            if(numero == elencoSale[i]->getNumero())
            {
                return elencoSale[i];
            }
        }
        return nullptr;
    }

    // TODO 9 - aggiungiFilm
    //          Riceve titolo e durata. Crea un nuovo Film con new, lo aggiunge al cinema
    //          e restituisce il suo puntatore. Se esiste gia' un film con quel titolo o
    //          se la durata e' minore o uguale a 0 non aggiunge nulla e restituisce nullptr.
    Film* aggiungiFilm(string titolo, int durata)
    {

        if(durata <= 0 || cercaFilm(titolo) !=nullptr)
        {
            return nullptr;
        }

        Film* newfilm = new Film(titolo, durata);

        elencoFilm.push_back(newfilm);

        return newfilm;
        }

    // TODO 10 - aggiungiSala
    //          Riceve numero e posti. Crea una nuova Sala con new, la aggiunge al cinema
    //          e restituisce il suo puntatore. Se esiste gia' una sala con quel numero o
    //          se i posti sono minori o uguali a 0 non aggiunge nulla e restituisce nullptr.

    Sala* aggiungiSala(int numero, int posti)
    {
        if(posti <= 0 || cercaSala(numero)!= nullptr)
        {
            return nullptr;
        }

        Sala* newsala = new Sala(numero,posti);

        elencoSale.push_back(newsala);

        return newsala;
    }

    // TODO 11 - programma
    //          Riceve il numero di una sala e il titolo di un film e mette il film in
    //          programmazione in quella sala. Restituisce true se ci riesce, false se la
    //          sala o il film non esistono (in tal caso non cambia nulla).
    bool programma(int numero, string titolo)
    {
        Sala* s = cercaSala(numero);
        Film* f = cercaFilm(titolo);

        if(s == nullptr || f == nullptr)
        {
            return false;
        }

        s->assegnaFilm(f);
        return true;
    }

    // TODO 12 - vendi
    //          Riceve il numero di una sala e quanti biglietti vendere. Usa la sala per la
    //          vendita; se riesce, aggiunge all'incasso (biglietti * prezzoBiglietto) e
    //          restituisce true. Altrimenti (sala inesistente o vendita impossibile)
    //          restituisce false e l'incasso non cambia.

    bool vendi(int numero, int biglietti)
    {
        Sala* s = cercaSala(numero);

        if(s == nullptr || biglietti <= 0)
        {
            return false;
        }

        if(s->vendiBiglietti(biglietti))

        {
        incasso = incasso + (biglietti * prezzoBiglietto);       
        return true;
        }

        return false;
        
    }

    // TODO 13 - salaPiuLibera
    //          Restituisce la sala che ha piu' posti liberi tra quelle con un film in
    //          programmazione (a parita' la prima inserita). Se nessuna sala ha un film
    //          restituisce nullptr.
    Sala* salaPiuLibera()
    {
        Sala* salaMax = nullptr;

        for(int i = 0; i < elencoSale.size(); i++)
        {

            if(elencoSale[i]->getFilm()!= nullptr)
            {
                if(salaMax == nullptr || elencoSale[i]->postiLiberi()> salaMax->postiLiberi())
                {
                    salaMax = elencoSale[i];
                }
            }
        }
        return salaMax;
    }

    // TODO 14 - svuota
    //          Libera con delete tutti i Film e tutte le Sale creati e riporta il cinema
    //          allo stato vuoto (0 film, 0 sale). Deve poter essere chiamato anche due
    //          volte di fila senza danni. L'incasso non viene toccato.

    void svuota()
    {
        for(int i = 0; i < elencoFilm.size(); i++)
        {
            delete elencoFilm[i];
        }
        for(int i = 0; i < elencoSale.size(); i++)
        {
            delete elencoSale[i];
        }
        elencoFilm.clear();
        elencoSale.clear();
    }

    // BONUS TODO 15 - filmPiuVisto
    //          Restituisce il film con piu' spettatori (a parita' il primo inserito),
    //          nullptr se non ci sono film.
    Film* filmPiuVisto()
    {
        Film* filmMax = nullptr;

        for(int i = 0; i < elencoFilm.size(); i++)
        {
            if(filmMax == nullptr|| elencoFilm[i]->getSpettatori() > filmMax->getSpettatori())
            {
                filmMax = elencoFilm[i];
            }
        }
        return filmMax;
    }





    // BONUS TODO 16 - rimuoviFilm
    //          Elimina dal cinema il film con quel titolo (delete) e dice se esisteva.
    //          Attenzione: se una sala lo ha in programmazione, quella sala deve restare
    //          senza film (altrimenti conserverebbe un puntatore a memoria liberata).

    bool rimuoviFilm(string titolo)
    {
        Film* f = cercaFilm(titolo);

        if(f== nullptr)
        {
            return false;
        }

        for(int i = 0; i < elencoSale.size(); i++)
        {
            if(elencoSale[i]->getFilm() == f)
            {
                elencoSale[i]->assegnaFilm(nullptr);
            }
        } 

        delete f;

        return true;
 
    }
};