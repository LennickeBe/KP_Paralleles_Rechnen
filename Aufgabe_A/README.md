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
Die Daten werden durch ein python Programm ausgewertet. Dafür wird die Python Version 3.9.5 empfohlen und benötigt numpy (1.24.1), pandas (2.0.0) und matplotlib (3.3.4).

Das python Programm ist unter 'evaluation/evaluation.py' zu finden.
Für eine Auswertung auf "romeo" ist folgendes Setup notwendig

```
module load release/23.04
module load GCCcore/10.3.0
module load Python/3.9.5
cd <repo root directory>/evaluation
python3 -m venv .venv
source .venv/bin/activate
pip install numpy==1.24.1 pandas==2.0.0 matplotlib==3.3.4
```

Für eine lokale Auswertung muss das eigene Setup entsprechend angepasst werden, dass die Versionen eingehalten werden.

Gestartet wird die Auswertung dann mit:

```
cd <repo root directory>/evaluation
source .venv/bin/activate
python3 evaluation.py
```

