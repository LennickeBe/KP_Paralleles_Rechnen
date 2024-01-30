#C - SIMD-parallele Ausführung von Conways Game-of-Life

## Aufgabenstellung

Implementieren Sie eine SIMD-parallele Variante von Conways "Game-of-Life" mit periodic boundary conditions. Nutzen Sie dazu OpenMP Compiler-Direktiven. Benutzen Sie double buffering um Abhängigkeiten aufzulösen.

- Beschreiben Sie Ihren Ansatz und gehen Sie sicher, dass die Arbeit SIMD-parallel ausgeführt wird, (beziehungsweise nicht-SIMD-parallel als Referenzmessung). Informationen dazu finden Sie in den FAQs
- Messen und Vergleichen Sie die Ausführungszeiten für aktiviertes und inaktives OpenMP, sowie den GCC, als auch den Intel Compiler bei Feldgrößen von 128x128, 512x512, 2048x2048, 8192x8192 und 32768x32768.
- Nutzen Sie für die Berechnung eine geeignete Anzahl an Schleifendurchläufen (Zyklen des Spiels), sodass der genutzte Timer genau genug ist.
- Nutzen Sie dafür die "romeo" Partition von taurus.
- Führen Sie jeweils 20 Messungen durch und analysieren Sie die Ergebnisse mit geeigneten statistischen Mitteln.

