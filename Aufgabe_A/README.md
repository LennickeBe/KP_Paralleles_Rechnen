#A - Stringmanipulationen mit Intrinsics

## Aufgabenstellung

Implementieren Sie eine sequentielle und eine SIMD-parallele (mittels Intrinsics für einen Prozessor, der AVX2, AVX und FMA unterstützt) Variante für folgende String-Funktionen:

/\* turns string "string" (with length len_string) to uppercase \*/
/\* returns 1 if there has been an error, 0 if there has been no error \*/\
int toUppercase(char\* string, int len_string)

/\* turns string "string" (with length len_string) to lowercase \*/
/\* returns 1 if there has been an error, 0 if there has been no error \*/\
int toLowercase(char\* string, int len_string)

/\* counts the appearences of character "c" in string "string" (with length len_string) \*/
/\* returns -1 if there has been an error, and the number of appearences if there has been no error \*/\
int countChar(char\* string, int len_string, char c)


- Beschreiben Sie für diese Funktionen die asymptotische Zeitkomplexität.
- Messen und Vergleichen Sie die Ausführungszeiten für sequentielle und SIMD-parallele Ausführung für Strings der Länge 10.000, 100.000, 1.000.000 und 100.000.000 .
- Nutzen Sie dafür die "romeo" Partition von taurus.
- Führen Sie jeweils 20 Messungen durch und analysieren Sie die Ergbenisse mit geeigneten statistischen Mitteln.

## Durchführung

### Messung
Die Messung soll auf dem "romeo" cluster der TU Dresden stattfinden.
Daher ist zunächst ein Login darauf notwendig.

```
ssh <username>@login1.romeo.hpc.tu-dresden.de
```

Anschließend das Repository an geeigneter Stelle clonen.

```
git clone https://github.com/LennickeBe/KP_Paralleles_Rechnen.git
```

Eine Messung wird mit dem sbatch script 'run.sh' im Repository unter 'Aufgabe_A/measurement' gestartet.

```
cd KP_Paralleles_Rechnen/Aufgabe_A/measurement
sbatch run.sh
```

### Auswertung
Die Daten werden durch ein python Programm ausgewertet.
