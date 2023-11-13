# Oryginalny Graf Sprzężony - Projekt Bioinformatyki


## Opis Projektu
Projekt dotyczy poszukiwania oryginalnego grafu sprzężonego. Realizacja odbywa się w ramach klasy `GrafSkierowany`, z kodem podzielonym na funkcje spełniające różne zadania. Graf jest reprezentowany za pomocą listy sąsiedztwa.

## Funkcjonalności

### Wczytanie Grafu z Pliku
- Wczytanie danych grafu z pliku tekstowego.
- Plik zawiera informacje o liczbie wierzchołków i krawędzi oraz pary liczb reprezentujące krawędzie.

### Sprawdzenie Sprzężoności Grafu
- Analiza, czy wczytany graf jest grafem sprzężonym.
- Sprawdzenie, czy graf jest 1-grafem bez krawędzi wielokrotnych.

### Sprawdzenie Liniowości Grafu Sprzężonego
- Wykluczenie struktur uniemożliwiających liniowość grafu:
  1. Wierzchołki z wspólnymi następnikami.
  2. Wierzchołki z cyklicznymi następnikami.
  3. Wierzchołki z wzajemnymi pętlami.

### Transformacja Grafu Sprzężonego w Graf Oryginalny
- Implementacja transformacji grafu sprzężonego w graf oryginalny za pomocą dwuwymiarowej tablicy dynamicznej.

## Zapisanie Grafu Wynikowego
- Zapis przetransformowanego grafu do nowego pliku tekstowego w tym samym formacie.

## Technologie
- C++

