<h1>PHILOSOPERS</h1>
<h1>Dining Philosophers Problem 🍝</h1>
Problema di sincronizzazione concorrente introdotto da Dijkstra. Cinque filosofi siedono attorno a un tavolo rotondo, ognuno con un piatto di spaghetti e una forchetta tra ogni coppia di piatti. Per mangiare servono due forchette: quella a sinistra e quella a destra. I filosofi alternano due stati: pensare e mangiare.

<h2>Vincoli principali🔒</h2>
Un filosofo può mangiare solo se ha entrambe le forchette.
Le forchette sono condivise con i vicini.
Nessun filosofo sa in anticipo cosa faranno gli altri.
<h2>⚠Problemi:⚠️</h2>
Deadlock: ogni filosofo prende la forchetta a sinistra e attende la destra, bloccando il sistema.
Starvation: un filosofo può non riuscire mai a mangiare se gli altri lo impediscono continuamente.
Livelock: i filosofi continuano a cambiare stato senza mai mangiare.

<p>La sfida:</p>
- Evitare **deadlock**
- Prevenire **race conditions**
- Garantire che nessuno **muoia di fame**
- Assicurare una terminazione ordinata della simulazione
