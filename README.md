# Pažymių vidurkio skaičiuoklė

Programa yra skirta apskaičiuoti pažymių vidurkį ir/arba medianą.

## Veikimo principas

> Paleidus programą, prašome sekti komandinėje eilutėje nurodytas instrukcijas.

Paleidus programą komandinėje eilutėje yra prašoma pasirinkti, ar duomenis skaityti **iš failo**, ar **suvesti ranka**.

Pasirinkus duomenų nuskaitymą iš failo, programa ieško `*.txt` failų `./data/` direktorijoje. Aptikus kelis failus, programa siūlo pasirinkti, kurį failą nuskaityti:

```bash
-> (y)Read grades from file; (n)Enter grades manaully: (y/n): y
Folder "./data/" contains multiple files. Please select one:
1: kursiokai.txt
2: studentai1000000.txt
3: studentai10000000.txt
-> Please select a file: (1-3): 1
Reading data from "./data/kursiokai.txt"
```

Pasirinkus galimybę duomenis suvesti rankiniu būdų, programa siūlo sekančius pasirinkimus:

- Įvesti vardą ir pavardę,
- Įvesti namų darbų įvertinimus bei egzamino balą.
- Po duomenų suvedimo yra apskaičiuojamas įvertinimų vidurkis arba medianas.

> Programa suteikia galimybę generuoti atsitiktinius namų darbų rezultatus bei egzamino balą, bei suvesti daugiau nei vieno studento duomenis.

Vienas iš rankiniu būdu suvestos informacijos programos eigos variantų gali būti toks:

```shell
-> (y)Read grades from file; (n)Enter grades manaully: (y/n): n
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

## Programos diegimas ir paleidimas

- Atsisiųskite programos versiją iš [Releases](https://github.com/rendertom/VU-OP-Task-2-Pazymiu-skaiciuokle/releases) aplanko ir ją išsiarchyvuokite,
- Komandinėje eilutėje įvykdykite sekančius veiksmus:

```shell
cd nuoroda_į_programos_aplanką
g++ -std=c++11 include/*.cpp 'main.cpp' -o 'main' && './main'
./main
```
