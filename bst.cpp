// Esercitazione (90 minuti): refactoring di un BST, da struct a classi - classe 4C
// Nome/Codice: ______________________
//
// Trasforma la libreria del Binary Search Tree: la struct Node diventa una classe con
// attributi privati e le funzioni libere diventano metodi di una nuova classe BST.
// I nomi dei metodi sono quelli scritti qui sotto e usati da main.cpp: decidi tu
// parametri e tipo restituito, guardando anche come li usa main.cpp.
// NON modificare main.cpp. Consegna SOLO questo file (bst.cpp).
// Se un metodo non riesci a scriverlo, lascia almeno una versione vuota
// (che restituisce un valore qualsiasi) per far compilare il programma.

#include <iostream>
using namespace std;

// =====================================================================
// PARTE A - la classe Node (circa 15 minuti)
// =====================================================================

class Node {
private:
    // TODO 1 - gli attributi: la chiave (int) e i puntatori ai due figli.
    //          Usa gli stessi nomi della struct originale: data, left, right.
    int data;
    Node* left;
    Node* right;

public:
    // TODO 1 - costruttore Node
    //          Riceve la chiave. All'inizio il nodo non ha figli (entrambi i puntatori valgono nullptr).
    //          Dai al parametro un nome diverso da quello dell'attributo.
    Node(int data_d)
    {
        data = data_d;
        right = nullptr;
        left = nullptr;
    }

    // TODO 2 - getData, getLeft, getRight
    //          Restituiscono la chiave, il figlio sinistro e il figlio destro.
    int getData()
    {
        return data;
    }

    Node* getRight()
    {
        return right;
    }

    Node* getLeft()
    {
        return left;
    }

    // TODO 3 - setData, setLeft, setRight
    //          Modificano la chiave e collegano il figlio sinistro e il figlio destro.
    //          setLeft e setRight ricevono l'indirizzo di un nodo (o nullptr per scollegare).

    void setData(int key)
    {
        data = key;
    }

    void setLeft(Node* leftx)
    {
        left = leftx;
    }

       void setRight(Node* rightx)
    {
        right = rightx;
    }


    // TODO 4 - isLeaf
    //          Dice se il nodo e' una foglia, cioe' se non ha nessun figlio.

    bool isLeaf()
    {
        if(left == nullptr && right == nullptr)
        {
            return true;
        }
        return false;
    }


};

// =====================================================================
// PARTE B - la classe BST: struttura, inserimento, ricerca, visita (circa 30 minuti)
// L'albero conosce solo la radice e il numero di nodi: da fuori non si vede nessun Node.
// =====================================================================

class BST {
private:
    Node* root;         // radice dell'albero, nullptr se l'albero e' vuoto
    int numNodi;        // numero di chiavi presenti

    // Qui puoi aggiungere funzioni di appoggio private (per esempio quelle ricorsive,
    // che hanno bisogno di ricevere un nodo come argomento).
    void inOrderR(Node* current)
    {
        if(current == nullptr)
        {
            return;
        }

        inOrderR(current->getLeft());
        cout << current->getData() << " ";
        inOrderR(current->getRight());
    }

    int heightR(Node* current)
    {
        if(current == nullptr)
        {
            return 0;
        }

        int heightLeft = heightR(current->getLeft());
        int heightRight = heightR(current->getRight());


        if(heightLeft > heightRight)
        {
            return 1 + heightLeft;
        }
        else
        {
            return 1 + heightRight;
        }
    }

    void svuotaR(Node* current)
    {
        if(current == nullptr)
        {
            return;
        }

        svuotaR(current->getLeft());
        svuotaR(current->getRight());

        delete current;
    }


    int contaFoglieR(Node* current)
    {
        if(current == nullptr)
        {
            return 0;
        }

        if(current->isLeaf())
        {
            return 1;
        }

        return contaFoglieR(current->getLeft()) + contaFoglieR(current->getRight());
    }

    int contaIntervalloR(Node* current, int low, int high)
    {
        if(current == nullptr)
        {
            return 0;
        }
        int data = current->getData();

        if(data > high)
        {
            return contaIntervalloR(current->getLeft(), low, high);
        }

        if(data < low)
        {
            return contaIntervalloR(current->getRight(), low, high);
        }

        return 1 + contaIntervalloR(current->getLeft(), low,high) + contaIntervalloR(current->getRight(), low,high);

    }


    Node* insertR(Node* current, int key, bool &inserito)
    {
        if(current == nullptr)
        {   
            numNodi++;
            inserito = true;           
            return new Node(key);
        }

        if(key< current->getData())
        {
            current->setLeft(insertR(current->getLeft(), key, inserito));   
        }
        else if (key > current->getData())
        {
            current->setRight(insertR(current->getRight(), key, inserito));
        }
        else
        {
            inserito = false;
        }

        return current;
    }

    bool searchR(Node* current, int key)
    {
        if(current == nullptr)
        {
            return false;
        }

        if(key == current->getData())
        {
            return true;
        }

        if(key < current->getData())
        {
            return searchR(current->getLeft(), key);    
        }

        else
        {
            return searchR(current->getRight(), key);
        }

    }

Node* removeR(Node* current, int key, bool& found) {
    if (current == nullptr) 
    {
        found = false;
        return nullptr;
    }

    if (key < current->getData())
    {
        current->setLeft(removeR(current->getLeft(), key, found));
    }

    else if (key > current->getData()) 
    {
        current->setRight(removeR(current->getRight(), key, found));
    }

    else
    {
        found = true;

   
        if (current->getLeft() == nullptr) 
        {
            Node* temp = current->getRight();
            delete current;
            numNodi--;
            return temp;
        }

        else if (current->getRight() == nullptr) 
        {
            Node* temp = current->getLeft();
            delete current;
            numNodi--;
            return temp;
        }

        Node* successor = current->getRight();
        while (successor->getLeft() != nullptr) 
        {
            successor = successor->getLeft();
        }

        current->setData(successor->getData());

        bool tmp = false;
        current->setRight(removeR(current->getRight(), successor->getData(), tmp));
    }

    return current;
}

public:
    // TODO 5 - costruttore BST, isEmpty, size
    //          Il costruttore crea un albero vuoto. isEmpty dice se l'albero e' vuoto,
    //          size restituisce quante chiavi contiene.
    BST()
    {
        root = nullptr;
        numNodi = 0;
    }

    bool isEmpty()
    {
        if(root == nullptr)
        {
            return true;
        }
        return false;
    }

    int size()
    {
        return numNodi;
    }

    // TODO 6 - insert
    //          Riceve una chiave e la inserisce al posto giusto creando un nuovo Node con new.
    //          Niente duplicati: se la chiave e' gia' presente non fa nulla.
    //          Dice se la chiave e' stata inserita.

    bool insert(int key)
    {
        bool inserito = false;
        root = insertR(root, key, inserito);
        return inserito;
    }


    // TODO 7 - search
    //          Dice se una chiave e' presente nell'albero (non modifica l'albero).

    bool search(int key)
    {
        return searchR(root,key);
    }

    // TODO 8 - inOrder
    //          Stampa su cout tutte le chiavi in ordine crescente (visita inorder),
    //          ciascuna seguita da uno spazio. Se l'albero e' vuoto non stampa nulla.
    //          Non va a capo: ci pensa il main.

    void inOrder()
    {
        inOrderR(root);
    }

    // TODO 9 - height
    //          Restituisce l'altezza dell'albero, cioe' il numero di nodi del cammino piu' lungo
    //          dalla radice a una foglia. Albero vuoto: 0.

    int height()
    {
        return heightR(root);
    }

    // TODO 10 - minimo, massimo
    //          Restituiscono la chiave piu' piccola e quella piu' grande.
    //          Per un albero vuoto restituiscono -1 (nell'esercizio le chiavi sono sempre positive).

    int minimo()
    {
        if(root == nullptr)
        {
            return - 1;
        }

        Node* current = root;

        while (current->getLeft()!= nullptr)
        {
            current = current->getLeft();
        }
        return current->getData();    
    }

      int massimo()
    {
        if(root == nullptr)
        {
            return - 1;
        }

        Node* current = root;

        while (current->getRight()!= nullptr)
        {
            current = current->getRight();
        }
        return current->getData();    
    }

    // =================================================================
    // PARTE C - cancellazione e memoria (circa 30 minuti)
    // =================================================================

    // TODO 11 - remove
    //          Elimina una chiave dall'albero e dice se esisteva. Gestisci i tre casi:
    //          nodo senza figli, con un figlio, con due figli (si sostituisce la chiave con
    //          quella del successore). Ogni nodo tolto va liberato con delete.

    bool remove(int key)
    {
        bool found = false;
        root = removeR(root,key,found);
        return found;
    }
    
    // TODO 12 - svuota
    //          Libera con delete tutti i nodi e riporta l'albero allo stato vuoto.
    //          Deve poter essere chiamata anche due volte di fila senza danni.

    void svuota()
    {
        svuotaR(root);
        root = nullptr;
        numNodi = 0;
    }

    // TODO 13 - contaFoglie
    //          Restituisce quante foglie ha l'albero (usa isLeaf). Albero vuoto: 0.

    int contaFoglie()
    {
        return contaFoglieR(root);
    }

    // BONUS TODO 14 - contaIntervallo
    //          Riceve due chiavi low e high e restituisce quante chiavi dell'albero sono comprese
    //          tra low e high (estremi inclusi). Sfrutta la proprieta' del BST: non serve
    //          visitare i sottoalberi che non possono contenere chiavi dell'intervallo.

    int contaIntervallo(int low,int high)
    {
        return contaIntervalloR(root,low,high);
    }
};

// =====================================================================
// PARTE D - domande e controllo finale (circa 15 minuti)
// Rispondi qui sotto, in due o tre righe ciascuna.
// =====================================================================
//
// 1) Perche' gli attributi di Node sono private? Cosa si guadagna rispetto alla struct,
//    in cui qualunque funzione poteva scrivere in data, left e right?
//    Risposta: gli attributi di Node sono private cosi non possono essere modificati al di fuori della definizione del Nodo,
//    l'utente è costretto a usare i metodi cosi non rischia di causare danni modificando direttamente gli attributi 
//
// 2) Nella struct la radice veniva passata come argomento a ogni funzione; nella classe
//    BST la radice e' un attributo. Cosa cambia per chi usa l'albero (guarda il main)?
//    Risposta: i metodi vengono chiamati direttamente dall'oggetto senza passare parametri
//
// 3) Perche' di solito un metodo ricorsivo come insert o inOrder ha bisogno di una funzione di appoggio
//    privata che riceve un nodo, e non puo' essere scritto direttamente come metodo pubblico?
//    Risposta: perche gli attributi di root non sono visibili all'interno della classe BST, e un metodo pubblico viene chiamato
//    nel main senza argomenti
//
// 4) Chi e' responsabile di liberare i nodi creati con new? In quale momento lo si fa,
//    e cosa succederebbe se ci si dimenticasse?
//    Risposta: la classe BST, che ha il compito di allocare e deallocare la memoria