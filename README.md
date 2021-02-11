# Pažymių vidurkio skaičiuoklė

Programa yra skirta apskaičiuoti pažymių vidurkį ir/arba medianą.

## Veikimo principas

Paleidus programą komandinėje eilutėje yra prašoma atlikti keletą veiksmų:

- Įvesti vardą ir pavardę,
- Įvesti namų darbų įvertinimus bei egzamino balą.
- Po duomenų suvedimo yra apskaičiuojamas įvertinimų vidurkis arba medianas.

> Programa suteikia galimybę generuoti atsitiktinius namų darbų rezultatus bei egzamino balą, bei suvesti daugiau nei vieno studento duomenis.

Paleidus programą, prašome sekti komandinėje eilutėje nurodytus instrukcijas. Vienas iš galimymų programos eigos variantų yra toks:

```shell
Please enter first name: Tomas
Please enter last name: Makaronas
-> Do you know the number of grades? (y/n): y
Enter number of grades: 5
-> Generate RANDOM grades (otherwise, enter grades MANUALLY)? (y/n): n
Enter grades: 7 8 9 9 10
Enter exam grade: 10
-> Add another student? (y/n): y
Please enter first name: Jurga
Please enter last name: Spurga
-> Do you know the number of grades? (y/n): n
-> Generate RANDOM grades (otherwise, enter grades MANUALLY)? (y/n): y
Generated 13 random grades: 6 1 10 9 3 10 4 9 8 4 8 8 7
Generated random exam grade: 3
-> Add another student? (y/n): y
Please enter first name: Studentas
Please enter last name: Nabagėlis
-> Do you know the number of grades? (y/n): n
-> Generate RANDOM grades (otherwise, enter grades MANUALLY)? (y/n): n
Enter grade [0] (type -1 to quit): 7
Enter grade [1] (type -1 to quit): 8
Enter grade [2] (type -1 to quit): 9
Enter grade [3] (type -1 to quit): -1
Enter exam grade: 8
-> Add another student? (y/n): n
-> Calculate MEAN (otherwise, calculate MEDIAN)? (y/n): y
```

Po sėkmingo duomenų suvedimo į terminalo langą išvedami rezultatai panašia forma:

```shell
Vardas    Pavardė        Galutinis Vid.
---------------------------------------
Tomas     Makaronas      9.44
Jurga     Spurga         4.48
Studentas Nabagėlis      8.00
```

Galutinis vidurkis yra apskaičiuojamas pagal formulę `galutinis = 0.4 * vidurkis + 0.6 * egzaminas`.

Programa yra realizuota dviem būdais, kur rezultatai yra saugomi į `C` tipo masyvą (failas `main-array.cpp`), arba į `std::vector` tipo konteinerį (failas `main-vector.cpp`).

## Programos diegimas ir paleidimas

- Atsisiųskite programos versiją iš [Releases](https://github.com/rendertom/VU-Objektinis-Programavimas/releases) aplanko ir ją išsiarchyvuokite,
- Komandinėje eilutėje įvykdykite sekančius veiksmus:

```shell
cd nuoroda_į_programos_aplanką
g++ 'main-vector.cpp' -o 'main'
./main
```
