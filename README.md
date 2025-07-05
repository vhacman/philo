<h1>PHILOSOPERS</h1>
<h1>Dining Philosophers Problem 🍝</h1>
Problema di sincronizzazione concorrente introdotto da Dijkstra. Cinque filosofi siedono attorno a un tavolo rotondo, ognuno con un piatto di spaghetti e una forchetta tra ogni coppia di piatti. Per mangiare servono due forchette: quella a sinistra e quella a destra. I filosofi alternano due stati: pensare e mangiare.

<h2>Vincoli principali🔒</h2>
Un filosofo può mangiare solo se ha entrambe le forchette.
Le forchette sono condivise con i vicini.
Nessun filosofo sa in anticipo cosa faranno gli altri.
<h2>Problemi:⚠️</h2>
Deadlock: ogni filosofo prende la forchetta a sinistra e attende la destra, bloccando il sistema.
Starvation: un filosofo può non riuscire mai a mangiare se gli altri lo impediscono continuamente.
Livelock: i filosofi continuano a cambiare stato senza mai mangiare.

<h2>La sfida:</h2>
- Evitare **deadlock**
- Prevenire **race conditions**
- Garantire che nessuno **muoia di fame**
- Assicurare una terminazione ordinata della simulazione

<h2>⚙️ Compilazione </h2>

```bash
make
```
<h2>UTILIZZO</h2>

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [meals_required]
```

| Nome parametro               | Tipo | Descrizione                                                     |
| ---------------------------- | ---- | --------------------------------------------------------------- |
| `number_of_philosophers`     | int  | Numero di filosofi attorno al tavolo                            |
| `time_to_die`                | int  | Tempo massimo (in millisecondi) senza mangiare prima di morire  |
| `time_to_eat`                | int  | Tempo impiegato per mangiare (in millisecondi)                  |
| `time_to_sleep`              | int  | Tempo dedicato al sonno dopo il pasto (in millisecondi)         |
| `meals_required` (opzionale) | int  | Numero di pasti da consumare prima di concludere la simulazione |

Esempio
```bash
./philo 5 800 200 200
```
Crea 5 filosofi con 800ms di tolleranza prima della morte, 200ms per mangiare, 200ms per dormire.

```bash
./philo 5 800 200 200 3
```

