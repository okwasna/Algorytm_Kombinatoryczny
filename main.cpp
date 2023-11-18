
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <set>

class GrafSkierowany {
private:
    int liczbaWierzcholkow = 0;
    int liczbaKrawedzi = 0;
    std::vector<std::vector<int> >listaSasiedztwa;

public:
    void wczytajZPliku(const std::string &nazwaPliku) {
        std::ifstream plik(nazwaPliku);

        if (!plik.is_open()) {
            std::cerr << "Nie można otworzyć pliku!" << std::endl;
            return;
        }

        plik >> liczbaWierzcholkow >> liczbaKrawedzi;

        listaSasiedztwa.resize(liczbaWierzcholkow + 1);

        for (int i = 0; i < liczbaKrawedzi; i++) {
            int z, docelowy;
            plik >> z >> docelowy;
            listaSasiedztwa[z].push_back(docelowy);
        }

        plik.close();
    }

    std::vector<int> pobierzNastepnikow(int wierzcholek) const {
        return listaSasiedztwa[wierzcholek];
    }

    bool jestSprzezony() const {
        for (int i = 1; i <= liczbaWierzcholkow; ++i) {
            std::vector<int> nastepniki_i = pobierzNastepnikow(i);


            std::sort(nastepniki_i.begin(), nastepniki_i.end());
            if (std::adjacent_find(nastepniki_i.begin(), nastepniki_i.end()) != nastepniki_i.end()) {
                std::cout << "Nie jest 1 grafem, bo istnieja wielokrotne krawędzie.\n";
                return false;
            }

            for (int j = i + 1; j <= liczbaWierzcholkow; ++j) {
                std::vector<int> nastepniki_j = pobierzNastepnikow(j);
                std::sort(nastepniki_j.begin(), nastepniki_j.end());

                if (nastepniki_i != nastepniki_j) {
                    std::vector<int> wspolneNastepniki;
                    std::set_intersection(nastepniki_i.begin(), nastepniki_i.end(),
                                          nastepniki_j.begin(), nastepniki_j.end(),
                                          std::back_inserter(wspolneNastepniki));

                    if (!wspolneNastepniki.empty()) {
                        std::cout << "Znaleziono przynajmniej jeden wspolny nastepnik, wykluczajac sprzezonosc\n";
                        return false;
                    }
                }
            }
        }
        return true;
    }
    bool strukturatrzecia() const {
        for (int v = 1; v <= liczbaWierzcholkow; ++v) {
            const auto& nastepniki_v = pobierzNastepnikow(v);

            if (std::find(nastepniki_v.begin(), nastepniki_v.end(), v) == nastepniki_v.end()) {
                continue;
            }

            for (int nastepnik : nastepniki_v) {
                if (nastepnik != v) {
                    const auto& nastepniki_nastepnika = pobierzNastepnikow(nastepnik);

                    if (std::find(nastepniki_nastepnika.begin(), nastepniki_nastepnika.end(), nastepnik) == nastepniki_nastepnika.end()) {
                        continue;
                    }

                    if (std::find(nastepniki_nastepnika.begin(), nastepniki_nastepnika.end(), v) != nastepniki_nastepnika.end()) {
                        std::cout << "struktura3.\n";
                        return true;
                    }
                }
            }
        }

        return false;
    }


    bool strukturadruga() const {
        for (int v = 1; v <= liczbaWierzcholkow; ++v) {
            const auto& nastepniki_v = pobierzNastepnikow(v);

            if (nastepniki_v.size() < 2) {
                continue;
            }

            for (int nastepnik : nastepniki_v) {
                if (nastepnik == v) continue;

                const auto& nastepniki_nastepnika = pobierzNastepnikow(nastepnik);


                if (std::find(nastepniki_nastepnika.begin(), nastepniki_nastepnika.end(), v) != nastepniki_nastepnika.end()) {
                    for (int inny_nastepnik : nastepniki_v) {
                        if (inny_nastepnik == v || inny_nastepnik == nastepnik) continue;

                        const auto& nastepniki_innego_nastepnika = pobierzNastepnikow(inny_nastepnik);


                        if (std::find(nastepniki_innego_nastepnika.begin(), nastepniki_innego_nastepnika.end(), v) != nastepniki_innego_nastepnika.end()) {
                            std::cout << "struktura2.\n"; return true;
                        }
                    }
                }
            }
        }

        return false;
    }




    bool strukturapierwsza() const {
        for (int v = 1; v <= liczbaWierzcholkow; ++v) {
            std::vector<int> nastepniki = pobierzNastepnikow(v);
            std::sort(nastepniki.begin(), nastepniki.end());

            for (int i = 0; i < nastepniki.size(); ++i) {
                std::vector<int> nastepniki_i = pobierzNastepnikow(nastepniki[i]);
                std::sort(nastepniki_i.begin(), nastepniki_i.end());

                for (int j = i + 1; j < nastepniki.size(); ++j) {
                    std::vector<int> wspolnyelement;
                    std::vector<int> nastepniki_j = pobierzNastepnikow(nastepniki[j]);
                    std::sort(nastepniki_j.begin(), nastepniki_j.end());

                    std::set_intersection(nastepniki_i.begin(), nastepniki_i.end(),
                                          nastepniki_j.begin(), nastepniki_j.end(),
                                          std::back_inserter(wspolnyelement));

                    if (!wspolnyelement.empty()) {
                        std::cout << "struktura1.\n";
                        return true;
                    }
                }
            }
        }
        return false;
    }



    bool jestLiniowy() const {
        for (int v = 1; v <= liczbaWierzcholkow; ++v) {
            if (strukturadruga() || strukturapierwsza() || strukturatrzecia()) {
                return false;
            }
        }
        return true;
    }


    void drukuj(){
        std::cout << "Liczba wierzchołków: " << liczbaWierzcholkow  << ", Liczba łuków: " << liczbaKrawedzi << std::endl;
        for (int i = 1; i <= liczbaWierzcholkow; ++i) {
            for (int sasiad : listaSasiedztwa[i]) {
                std::cout << i << " -> " << sasiad << std::endl;
            }
        }
    }
    void transformacjaIZapisDoPliku(const std::string &nazwaPlikuWynikowego) {
        int v = liczbaWierzcholkow;
        int x, y, i, g, tmp, temp, tmp2;
        int **graf_oryginalny;

        graf_oryginalny = new int *[v + 1];
        for (x = 0; x <= v; x++) { //
            graf_oryginalny[x] = new int[2];
        }
        for (y = 0; y <= v; y++) {
            for (i = 0; i < 2; i++) {
                graf_oryginalny[y][i] = 0;
            }
        }


        int counter = 1;
        for (x = 1; x <= v; x++) {
            if (graf_oryginalny[x][0] == 0) {
                graf_oryginalny[x][0] = counter;
                counter++;
            }
            if (graf_oryginalny[x][1] == 0) {
                graf_oryginalny[x][1] = counter;
                counter++;
            }
            for (y = 1; y <= v; y++) {
                std::vector<int> nastepniki_y = pobierzNastepnikow(y);
                if (std::find(nastepniki_y.begin(), nastepniki_y.end(), x) != nastepniki_y.end()) {
                    graf_oryginalny[y][1] = graf_oryginalny[x][0];//poprzedniki

                }
            }


            for (int sasiad: listaSasiedztwa[x])
                graf_oryginalny[sasiad][0] = graf_oryginalny[x][1];//nastepniki


        }

        std::cout << "Wynik transformacji: " << std::endl;
        for (x = 1; x <= v; x++) {
            for (y = 0; y < 2; y++) {
                if (y == 0) {
                    std::cout << graf_oryginalny[x][y] << " -> ";
                } else {
                    std::cout << graf_oryginalny[x][y] << " ";
                }


            }
            std::cout << std::endl;

            std::set<int> unikalneWierzcholki;
            for (int x = 1; x <= liczbaWierzcholkow; x++) {
                unikalneWierzcholki.insert(graf_oryginalny[x][0]);
                unikalneWierzcholki.insert(graf_oryginalny[x][1]);
            }
            unikalneWierzcholki.erase(0);
            int aktualnaLiczbaWierzcholkow = unikalneWierzcholki.size();


            int aktualnaLiczbaKrawedzi = liczbaWierzcholkow ;


            std::ofstream plikWynikowy(nazwaPlikuWynikowego);
            if (!plikWynikowy.is_open()) {
                std::cerr << "Nie można otworzyć pliku do zapisu!" << std::endl;
                return;
            }

            plikWynikowy << aktualnaLiczbaWierzcholkow << " " << aktualnaLiczbaKrawedzi << std::endl;
            for (int i = 1; i <= liczbaWierzcholkow; i++) {
                plikWynikowy << graf_oryginalny[i][0] << " " << graf_oryginalny[i][1] << std::endl;
            }

            plikWynikowy.close();
        }
    }
};


int main() {
    GrafSkierowany graf;
    graf.wczytajZPliku("/Users/home/Desktop/akwb/start.txt");
    graf.drukuj();


    if (graf.jestSprzezony()) {
        if (graf.jestLiniowy()) {
            std::cout << "Graf jest sprzęzony i liniowy.\n";
        } else {
            std::cout << "Graf jest sprzężony, ale nie jest liniowy.\n";
        }

        graf.transformacjaIZapisDoPliku("/Users/home/Desktop/akwb/wynik.txt");


    } else {
        std::cout << "Brak grafu sprzężonego, nie sprawdzam liniowości. Wstrzymuję program.\n";
        return 1;
    }

    return 0;
}

