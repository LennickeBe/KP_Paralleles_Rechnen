# D - MPI-parallele Ausführung von Conways Game-of-Life

## Aufgabenstellung
Implementieren Sie eine MPI-parallele Variante von Conways "Game-of-Life" mit periodic boundary conditions. Nutzen Sie für die Synchronisierung zwischen den einzelnen Ranks asynchrone Kommunikation (z.B. MPI_Isend). Benutzen Sie double buffering um Abhängigkeiten aufzulösen.

- Beschreiben Sie Ihren Ansatz und gehen Sie sicher, dass die der Datenaustausch effizient ausgeführt wird.
- Teilen Sie die Sie die Felder nach den Schemas blockweise (Blöcke von Zeilen) und chessboard (block/block) auf die ranks auf.
- Messen und vergleichen Sie die Ausführungszeiten für 1,4,16,64,128 und 256 ranks bei Feldgrößen von 2048x2048, 8192x8192, 32768x32768, 131072x131072 (nur ab 64 ranks ), wobei die gesamten Felder auf die ranks aufgeteilt werden.
- Nutzen Sie für die Berechnung eine geeignete Anzahl an Schleifendurchläufen (Zyklen des Spiels), sodass der genutzte Timer genau genug ist.
- Achten Sie darauf, dass benachbarte Ranks möglichst nah beieinander gescheduled sind.
- Nutzen Sie dafür die "romeo" Partition von taurus.
- Führen Sie jeweils 20 Messungen durch und analysieren Sie die Ergebnisse mit geeigneten statistischen Mitteln.

