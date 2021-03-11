# Pažymių vidurkio skaičiuoklė 🧮

Programa yra skirta apskaičiuoti pažymių vidurkį ir/arba medianą.

## 🥤 Veikimo principas

> Paleidus programą, prašome sekti komandinėje eilutėje nurodytas instrukcijas.

```bash
1. Generate new records
2. Filter records
3. Read grades from a file
4. Enter grades manually
-> Select: (1-4):
```

1. [Generate new records](#-generate-new-records)
2. [Filter records](#%EF%B8%8F-filter-records)
3. [Read grades from a file](#-read-grades-from-a-file)
4. [Enter grades manually](#%EF%B8%8F-enter-grades-manually)

### 📚 Generate new records

Šis metodas skirtas naujų failų generavimui.

```bash
-> Select: (1-4): 1
-> How many records: (1-10000000): 1000
```

Po įvedimo `./data/` direktorijoje yra sukuriamas naujas failas `Random XXX.txt`, kur `XXX` yra užklausos dydis.
Jame sugeneruojami studentų įrašai su 10 atsitiktinių namų darbų įvertinimų bei egzamino pažymiu.

```bash
Vardas     Pavarde     ND1  ND2  ND3 ... ND10  Egz.
Vardas1    Pavarde1    2    8    6       9     3
Vardas2    Pavarde2    1    2    3       7     10
...
VardasXXX  PavardeXXX  3    4    8       6     8
```

Žemiau pateikti testavimo atvejai. Laiko matavimas pateiktas sekundėmis.

| Description        | 1000    | 10.000  | 100.000 | 1.000.000 | 10.000.000 |
| :----------------- | :------ | :------ | :------ | :-------- | :--------- |
| Buffering students | 0.00344 | 0.02834 | 0.23464 | 2.27576   | 23.217     |
| Saving buffer      | 0.00049 | 0.00163 | 0.01616 | 0.13867   | 1.56499    |
| **Total**          | 0.00398 | 0.03003 | 0.25170 | 2.42024   | 24.8665    |

---

### 🌪️ Filter records

Šis metodas skirtas atskirti gerai besimokančius studentus nuo prastai besimokančių. Jei studento **vidurkis** yra didesnis arba lygus nei 5, tai jis priskiriamas prie gerai besimokančių, kitu atveju - prie besimokančių prastai.

```bash
-> Select: (1-4): 2
Folder "./data/" contains multiple files. Please select one:
1: Studentai 10.000.txt
2: Studentai 100.000.txt
3: Studentai 1000.000.txt
4: Studentai 10.000.000.txt
-> Please select a file: (1-4): 1
```

Gerai besimokinantys studentai išsaugomis faile `XXX winners.txt`, o prastai - `XXX losers.txt`, kur `XXX` yra šakninis pasirinkto failo pavadinimas.

Žemiau pateikti testavimo atvejai. Laiko matavimas pateiktas sekundėmis.

| Description                    | 10.000  | 100.000 | 1.000.000 | 10.000.000 |
| :----------------------------- | :------ | :------ | :-------- | :--------- |
| **Reading source file:**       |         |         |           |            |
| Buffering file                 | 0.01779 | 0.18051 | 0.80284   | 7.6818     |
| Processing buffer              | 0.06277 | 0.71893 | 3.57932   | 36.7005    |
| Processing students            | 0.00024 | 0.00234 | 0.03426   | 0.27276    |
| **Filtering:**                 |         |         |           |            |
| Sorting students (descending)  | 0.00076 | 0.01204 | 0.09973   | 1.02805    |
| Searching for the first loser  | 2.9e-05 | 0.00164 | 0.00378   | 0.04699    |
| Copying losers to a new vector | 0.00069 | 0.01164 | 0.07389   | 0.92133    |
| Resizing original vector       | 0.00036 | 0.01485 | 0.09852   | 1.26067    |
| **Writing losers to file:**    |         |         |           |            |
| Buffering students             | 0.01385 | 0.15100 | 0.59066   | 5.91808    |
| Writing buffer to file         | 0.00105 | 0.01275 | 0.04718   | 0.49510    |
| **Writing winners to file:**   |         |         |           |            |
| Buffering students             | 0.01886 | 0.21706 | 0.86465   | 8.9698     |
| Writing buffer to file         | 0.00181 | 0.01645 | 0.06368   | 0.68474    |
| **Total**                      | 0.11841 | 1.34499 | 6.27838   | 64.1041    |

---

### 📂 Read grades from a file

Šis metodas skirtas **vidurkio** arba **mediano** (arba jų abiejų) skaičiavimui iš pasirinkto failo.

Programa ieško `*.txt` failų `./data/` direktorijoje. Aptikus kelis failus, programa siūlo pasirinkti, kurį failą nuskaityti:

```bash
-> Select: (1-4): 3
Folder "./data/" contains multiple files. Please select one:
1: Studentai 10.000.txt
2: Studentai 100.000.txt
3: Studentai 1000.000.txt
4: Studentai 10.000.000.txt
-> Please select a file: (1-4): 1
Reading data from "./data/Studentai 10.000.txt"
-> Choose what to calculate: (1)Mean, (2)Median, (3)Both: (1-3): 3
```

Po sėkmindo skaičiavimo duomenis galima automatiškai išsaugoti į failą, arba pateikti juos į konsolę:

```bash
-> Choose what to calculate: (1)Mean, (2)Median, (3)Both: (1-3): 3
-> Print to (y)file or (n)console: (y/n): y
```

Pasirinkus išsaugojimą į failą, rezultatas atrodo taip:

```bash
Vardas     Pavarde     Galutinis Vid.  Galutinis Med.
-----------------------------------------------------
Vardas1    Pavarde1    3.43            6.00
Vardas10   Pavarde10   7.23            4.00
...
VardasXXX  PavardeXXX  6.45            7.00
```

---

### ⌨️ Enter grades manually

Metodas skirtas studento duomenims suvesti rankiniu būdų. Programa siūlo sekančius pasirinkimus:

- Įvesti vardą ir pavardę,
- Įvesti namų darbų įvertinimus bei egzamino balą.
- Po duomenų suvedimo yra apskaičiuojamas įvertinimų vidurkis arba medianas.

> Programa suteikia galimybę generuoti atsitiktinius namų darbų rezultatus bei egzamino balą, bei suvesti daugiau nei vieno studento duomenis.

Vienas iš rankiniu būdu suvestos informacijos programos eigos variantų gali būti toks:

```shell
-> Select: (1-4): 3
-> Please enter first name: Tomas
-> Please enter last name: Makaronas
-> Do you know the number of grades? (y/n): y
Enter number of grades: 5
-> Generate RANDOM grades (otherwise, enter grades MANUALLY)? (y/n): n
Enter grades: 7 8 9 9 10
Enter exam grade: 10
-> Add another student? (y/n): y
-> Please enter first name: Jurga
-> Please enter last name: Spurga
-> Do you know the number of grades? (y/n): n
-> Generate RANDOM grades (otherwise, enter grades MANUALLY)? (y/n): y
Generated 7 random grades: 8 5 3 8 2 8 5
Generated random exam grade: 4
-> Add another student? (y/n): y
-> Please enter first name: Studentas
-> Please enter last name: Nabagelis
-> Do you know the number of grades? (y/n): n
-> Generate RANDOM grades (otherwise, enter grades MANUALLY)? (y/n): n
Enter grade [0] (type -1 to quit): 7
Enter grade [1] (type -1 to quit): 8
Enter grade [2] (type -1 to quit): 9
Enter grade [3] (type -1 to quit): -1
Enter exam grade: 8
-> Add another student? (y/n): n
-> Choose what to calculate: (1)Mean, (2)Median, (3)Both: (1-3): 3
-> Print to (y)file or (n)console: (y/n): n
```

Po sėkmingo duomenų suvedimo į terminalo langą išvedami rezultatai panašia forma:

```shell
Vardas      Pavarde         Galutinis Vid. Galutinis Med.
----------------------------------------------------------
Tomas       Makaronas       9.44           9.00
Studentas   Nabagelis       8.00           8.00
Jurga       Spurga          4.63           5.00
```

Galutinis vidurkis yra apskaičiuojamas pagal formulę `galutinis = 0.4 * vidurkis + 0.6 * egzaminas`.

## 📈 Spartos analizė

Programos spartos analizė (duomenų, nuskaitymas iš failo, apdorijimas ir rūšiavimas į kategorijas) atlikta duomenis saugant į skirtingus konteinerius: `std::deque`, `std::list` ir `std::vector`.

Analizė atlikta su MacBook Pro, 2.3 GHz Dual-Core Intel Core i5, 8 GB 2133 MHz LPDDR3.

### 🧰 Duomenų apdorojimas

| Container   | 10.000  | 100.000 | 1.000.000 | 10.000.000 |
| :---------- | :------ | :------ | :-------- | :--------- |
| std::deque  | 0.06061 | 0.70649 | 3.52166   | 35.0777    |
| std::list   | 0.06191 | 0.73367 | 3.59739   | 35.95377   |
| std::vector | 0.05895 | 0.71480 | 3.52165   | 36.03642   |

---

### ⚖️ Duomenų rūšiavimas

| Container   | 10.000  | 100.000 | 1.000.000 | 10.000.000 |
| :---------- | :------ | :------ | :-------- | :--------- |
| std::deque  | 0.0024  | 0.03438 | 0.31071   | 3.44917    |
| std::list   | 0.00338 | 0.0919  | 1.1708    | 16.56225   |
| std::vector | 0.00202 | 0.03528 | 0.29249   | 3.30253    |

---

## 🚀 Programos diegimas ir paleidimas

- Atsisiųskite programos versiją iš [Releases](https://github.com/rendertom/VU-OP-Task-2-Pazymiu-skaiciuokle/releases) aplanko ir ją išsiarchyvuokite,
- Komandinėje eilutėje įvykdykite sekančius veiksmus:

```shell
cd nuoroda_į_programos_aplanką
g++ -std=c++11 include/*.cpp 'main.cpp' -o 'main' && './main'
./main
```
