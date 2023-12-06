#B - Thread-parallele Ausführung von Conways Game-of-Life

## Aufgabenstellung

Implementieren Sie eine thread-parallele Variante von Conways "Game-of-Life" mit periodic boundary conditions. Nutzen Sie dazu OpenMP Compiler-Direktiven. Benutzen Sie double buffering um Abhängigkeiten aufzulösen.

- Beschreiben Sie Ihren Ansatz und gehen Sie sicher, dass die Arbeit thread-parallel ausgeführt wird.
- Messen und Vergleichen Sie die Ausführungszeiten für 1,2,4,8,16 und 32 Threads, für den GCC, als auch den Intel Compiler bei Feldgrößen von 128x128, 512x512, 2048x2048, 8192x8192 und 32768x32768.
- Nutzen Sie für die Berechnung eine geeignete Anzahl an Schleifendurchläufen (Zyklen des Spiels), sodass der genutzte Timer genau genug ist.
- Nutzen Sie dafür die "romeo" Partition von taurus.
- Achten Sie darauf, dass benachbarte Threads möglichst nah einander gescheduled sind.
- Testen Sie für die Feldgröße 128x128, welchen Einfluss die OpenMP Schleifenschedulingverfahren haben (OMP_SCHEDULE), indem Sie für die Ausführung mit 32-Threads des mit Intel kompilierten Benchmarks die Verfahren static, dynamic, guided, und auto bei default chunk size vergleichen
- Führen Sie jeweils 20 Messungen durch und analysieren Sie die Ergebnisse mit geeigneten statistischen Mitteln.
