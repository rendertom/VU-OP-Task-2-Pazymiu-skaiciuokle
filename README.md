# Pažymių vidurkio skaičiuoklė

Programa yra skirta apskaičiuoti pažymių vidurkį ir/arba medianą.

## Veikimo principas

Paleidus programą komandinėje eilutėje yra prašoma atlikti keletą veiksmų:

- Pasirinkti, ar duomenis suvesti ranka, ar juos skaityti iš failo `kursiokai.txt`,
- Pasirinkus įvedimą ranka, prašoma įvesti vardą ir pavardę,
- Įvesti namų darbų įvertinimus bei egzamino balą.
- Po duomenų suvedimo yra apskaičiuojamas įvertinimų vidurkis arba medianas.

> Programa suteikia galimybę generuoti atsitiktinius namų darbų rezultatus bei egzamino balą, bei suvesti daugiau nei vieno studento duomenis.

Paleidus programą, prašome sekti komandinėje eilutėje nurodytus instrukcijas.

Vienas iš galimymų programos eigos variantų yra toks:

```shell
-> (y)Read grades from file "kursiokai.txt"; (n)Enter grades manaully: (y/n): n
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

### Changelog

- [v0.1](https://github.com/rendertom/VU-OP-Task-2-Pazymiu-skaiciuokle/releases/tag/v0.1) - Pradinė programos versija
- [v0.1.1](https://github.com/rendertom/VU-OP-Task-2-Pazymiu-skaiciuokle/releases/tag/v0.1.1)
  - pataisyta
    - Vidurkio ir Mediano skaičiavimas, kai nėra įvesta pažymių.
    - Nerodo pažymių įvedimo formos užklausos (random/manual), jei vartotojas neturi pažymių.
  - pašalinta
    - VSCode IDE nustatymai (.vscode > settings.json).
    - `std::cout` teksto spalvos nustatymai.
- [v0.2](https://github.com/rendertom/VU-OP-Task-2-Pazymiu-skaiciuokle/releases/tag/v0.2)
  - pataisyta
    - Nerodo atsitiktinės (random) pažymių įvedimo užklausos, kai pažymių skaičius yra nežinomas.
  - pašalinta
    - `C` tipo masyvo programos realizcija: pašalintas failas `main-array.cpp`, o failas `main-vector.cpp` pervadintas į `main.cpp`.
  - pridėta
    - Galimybė skaityti rezultatus iš išorinio failo.
    - Galimybė atspausdinti Vidurkį, Medianą, arba abu iš karto.
    - Spausdinamas sarašas išrikiuojamas abėcėlės tvarka pagal pavardes.
- [v0.3](https://github.com/rendertom/VU-OP-Task-2-Pazymiu-skaiciuokle/releases/tag/v0.3)
  - pakeista
    - Optimizuotas nuskaitomo failo apdorojimas, nuskaitant jo turinį į buffer'į.
    - Optimizuotas ciklo _for_ veikimas, nuskaitant masyvo dydį į kintamąjį.
    - Reorganizuota failo struktūra, suskaldant pagrindinį failą į smulkelsnius failus su antraštėm _header_. Sukurti atskiri _header_ failai: Console.hpp, Definitions.hpp, File.hpp, Math.hpp, RND.hpp, Student.hpp, Table.hpp, Timer.hpp.
  - pridėta
    - Išimčių _exceptions_ valdymas.
