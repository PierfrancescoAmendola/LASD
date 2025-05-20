ESERCIZIO 1
- VETTORI, LISTE E INSIEMI ORDINATI DI DATI GENERICI -
F. MOGAVERO
Implementare tre librerie in Linguaggio C++ per la gestione di strutture dati dinamiche di
tipo vettore, lista e insieme ordinato contenenti dati generici, ovvero interi, stringhe, ecc.
In particolare, per l’ultima struttura dovranno essere sviluppate due diverse implementazioni
concrete basate su (a) vettori con efficiente ridimensionamento automatico dello spazio
allocato e (b) liste.
Le funzionalit` a da realizzare sono di seguito elencate:
(1) costruzione e distruzione di una struttura dati;
(2) operazioni di assegnamento e confronto tra istanze diverse della specifica struttura dati;
(3) operazioni comuni ai tre tipi di strutture dati: test di vuotezza; lettura della dimensione;
svuotamento della struttura; accesso non distruttivo all’elemento iniziale, finale o
avente uno specifico indice; controllo di esistenza di un dato valore; operazioni di
attraversamento e accumulazione di un valore (funzioni traverse e fold);
(4) operazioni comuni a vettori e liste: operazioni di applicazione di una funzione a tutti
gli elementi (funzioni map);
(5) funzioni specifiche dei vettori: ridimensionamento del vettore;
(6) funzioni specifiche delle liste: inserimento, rimozione e rimozione con lettura di un
dato valore in testa o coda;
(7) operazioni specifiche degli insiemi: inserimento/eliminazione di un dato elemen-
to; rimozione, rimozione con lettura e lettura non distruttiva dell’elemento mini-
mo/massimo o del predecessore/successore di un dato elemento.
Al fine di poter testare adeguatamente il funzionamento delle librerie sopra descritte, si richiede
di definire (esternamente alle stesse, in un opportuno file di test richiamato dal “main”) un
insieme di procedure di test unitario. In aggiunta a questo, ` e necessario prevedere l’accesso
alla funzionalit` a di test prevista dal docente.
Il codice sorgente prodotto dovr` a seguire pedissequamente (sia nei nomi delle funzioni di libreria,
sia nella strutturazione, gerarchia di classi e nei nomi delle diverse directory e file “.cpp” e
“.hpp”) la forma riportata nel template Exercise1.zip associato al presente esercizio.
Per lo sviluppo delle librerie, in aggiunta alle spiegazioni del docente e al diagramma delle classi
reperibile sul sito docenti d’ateneo, si faccia riferimento alla sezione 13.6 di [1] e alle sezioni
4.1 e 4.4 di [2].
RIFERIMENTI BIBLIOGRAFICI
[1] Bjarne Stroustrup. The C++ Programming Language, Addison-Wesley, 4th Edition, 2013.
[2] Clifford A. Shaffer. Data Structures and Algorithm Analysis, Edition 3.2 (C++ Version), 2013.
