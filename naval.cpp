/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <cmath>
using namespace std;
class Okret {
public:
    string nazwa;
    int id, moc, szybkosc, zaloga, celnosc, hp;
    Okret(int identifier, string name, int power, int speed, int crew, int accuracy, int hitpoints) {
        nazwa = name;
        moc = power;
        szybkosc = speed;
        zaloga = crew;
        celnosc = accuracy;
        id = identifier;
        hp = hitpoints;
    }
    Okret() {}
    void get() {
        cout << "***************\nID: " << id << "\nNAZWA: " << nazwa << "\nMOC : " << moc << "\nSZYBKOSC: " << szybkosc << "\nHP: " << hp << "\nZALOGA: " << zaloga << "\nCELNOSC: " << celnosc << "\n\n";
    }
};
class Krazownik : public Okret {
public:
    int iloscDzial, zasieg;
    Krazownik(int identifier, string name, int power, int speed, int crew, int accuracy, int hitpoints, int cannonCount, int range) : Okret(identifier, name, power, speed, crew, accuracy, hitpoints) {
        iloscDzial = cannonCount;
        zasieg = range;
    }
    Krazownik() {}
    void get() {
        Okret::get();
        cout << "ILOSC DZIAL: " << iloscDzial << "\nZASIEG: " << zasieg << "\n\n";
    }
};
class LodzPodwodna : public Krazownik {
public:
    int glebokosc;
    bool czyAtom;
    LodzPodwodna(int identifier, string name, int power, int speed, int crew, int accuracy, int hitpoints, int cannonCount, int range, int depth, bool isAtomic) : Krazownik(identifier, name, power, speed, crew, accuracy, hitpoints, cannonCount, range) {
        glebokosc = depth;
        czyAtom = isAtomic;
    }
    LodzPodwodna() {}
    void get() {
        Krazownik::get();
        cout << "GLEBOKOSC: " << glebokosc << "\nATOM: " << czyAtom << "\n\n";
    }
};
class Flota {
public:
    Okret** okrety;
    Krazownik** krazowniki;
    LodzPodwodna** lpodwodne;
    int identifier = 0;
    int ships[3];
    Flota(int iloscOkretow, int iloscKrazownikow, int iloscLodziPodwodnych) {
        ships[0] = iloscOkretow;
        ships[1] = iloscKrazownikow;
        ships[2] = iloscLodziPodwodnych;
        okrety = new Okret * [ships[0]];
        krazowniki = new Krazownik * [ships[1]];
        lpodwodne = new LodzPodwodna * [ships[2]];
        string name[2][10] = { {"HMS", "LA", "OZM", "ZLB", "SHW", "CHM", "KTR", "RJ45", "FFK", "REP"}, {"Danietz", "Magda", "Patrycja", "MOSiR", "JTFolio", "Pandziak", "Morcinek", "Fentanyl", "Robercia", "Malpa"} }, typy[3] = { "Okrety:", "Krazowniki:", "Lodzie podw.:" };
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < ships[i]; j++) {
                string tname = name[0][rand() % 10] + ' ' + name[1][rand() % 10];
                switch (i) {
                case 0:
                    okrety[j] = new Okret(identifier, tname, rand() % 11 + 15, rand() % 201 + 200, rand() % 4 + 1, rand() % 16 + 60, rand() % 100 + 300);
                    break;
                case 1:
                    krazowniki[j] = new Krazownik(identifier, tname, rand() % 21 + 40, rand() % 176 + 200, rand() % 21 + 10, rand() % 31 + 45, rand() % 500 + 750, rand() % 3 + 1, rand() % 76 + 75);
                    break;
                case 2:
                    lpodwodne[j] = new LodzPodwodna(identifier, tname, rand() % 11 + 35, rand() % 301 + 150, rand() % 3 + 2, rand() % 11 + 75, rand() % 250 + 600, 2, rand() % 101 + 150, rand() % 301 + 150, (rand() % 2 == 0) ? true : false);
                    break;
                }
                identifier++;
            }
        cout << "=== FLOTA ===\nOkretow: " << iloscOkretow << "\nKrazownikow: " << iloscKrazownikow << "\nLodzi podwodnych: " << iloscLodziPodwodnych << "\n=============\n";
        for (int i = 0; i < ships[0]; i++)
            okrety[i]->get();
        for (int i = 0; i < ships[1]; i++)
            krazowniki[i]->get();
        for (int i = 0; i < ships[2]; i++)
            lpodwodne[i]->get();
    }
};
bool checkVictory(int hp1, int hp2, string nazwa1, string nazwa2, int id1, int id2) {
    if (hp1 <= 0 && hp2 <= 0) {
        cout << "[REMIS] Oba '" << nazwa1 << "' oraz '" << nazwa2 << "' leza na dnie basenu! (OVERKILL: " << hp1 << " hp i " << hp2 << " hp)!\n";
        return true;
    }
    if (hp1 <= 0) {
        cout << "[WYGRANA] '" << nazwa2 << " " << id2 << "' zwyciezyl '" << nazwa1 << " " << id2 << "' (OVERKILL: " << hp1 << " hp)!\n";
        return true;
    }
    if (hp2 <= 0) {
        cout << "[WYGRANA] '" << nazwa1 << " " << id1 << "' zwyciezyl '" << nazwa2 << " " << id1 << "' (OVERKILL: " << hp2 << " hp)!\n";
        return true;
    }
    return false;
}
int rem(LodzPodwodna* statek1, LodzPodwodna* statek2) {
    LodzPodwodna* statek[2] = { statek1, statek2 };
    for (int i = 0; i < 2; i++) {
        if (rand() % 101 <= statek[0 + i]->celnosc) {
            statek[1 - i]->hp -= statek[0 + i]->moc * statek[0 + i]->iloscDzial - statek[1 - i]->glebokosc / 30;
            cout << "'" << statek[0 + i]->nazwa << " " << statek[0 + i]->id << "' godzi '" << statek[1 - i]->nazwa << "' (" << statek[0 + i]->moc * statek[0 + i]->iloscDzial - statek[1 - i]->glebokosc / 30 << " hp)! ";
            if (statek[1 - i]->hp > 0)
                cout << "Pozostalo " << statek[1 - i]->hp << " hp.";
            else if (statek[1 - i]->czyAtom) {
                cout << "\n[BOMBA] Awaryjna orpeda atomowa zostala wystrzelona! ";
                if (rand() % 101 < 13) {
                    statek[0 + i]->hp -= 9999;
                    cout << "Niezneutralizowana na czas, obraca cel w proch!";
                }
                else
                    cout << "Nie trafia!";
            }
            cout << "\n";
            if (checkVictory(statek[0]->hp, statek[1]->hp, statek[0]->nazwa, statek[1]->nazwa, statek[0]->id, statek[1]->id))
                return 0;
        }
        else
            cout << "'" << statek[0 + i]->nazwa << "' chybił!\n";
    }
    return 0;
}
void walka(Flota* flota1, Flota* flota2) {
    char dummy;
    while (1) {
        cout << "Oczekiwanie...\n>> ";
        cin >> dummy;
        Flota* args[2] = { flota1, flota2 };
        int total = flota1->ships[0] + flota1->ships[1] + flota1->ships[2], tura = 1;
        vector<vector<LodzPodwodna*>> floty(2, vector<LodzPodwodna*>(total));
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < args[i]->ships[0]; j++) {
                Okret* okret = args[i]->okrety[j];
                floty[i][j] = new LodzPodwodna(okret->id, okret->nazwa, okret->moc, okret->celnosc, okret->zaloga, okret->celnosc, okret->hp, 1, 130, 1, false);
            }
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < args[i]->ships[1]; j++) {
                Krazownik* krazownik = args[i]->krazowniki[j];
                floty[i][j + flota1->ships[0]] = new LodzPodwodna(krazownik->id, krazownik->nazwa, krazownik->moc, krazownik->celnosc, krazownik->zaloga, krazownik->celnosc, krazownik->hp, krazownik->iloscDzial, krazownik->zasieg, 1, false);
            }
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < args[i]->ships[2]; j++)
                floty[i][j + +flota1->ships[0] + flota1->ships[1]] = args[i]->lpodwodne[j];
        cout << "\n######################\n        WALKA\n######################\n";
        bool hasEnded = false;
        while (!hasEnded) {
            hasEnded = true;
            cout << "\n--- TURA " << tura;
            for (int i = 0; i < total; i++) {
                cout << "\n";
                if (checkVictory(floty[0][i]->hp, floty[1][i]->hp, floty[0][i]->nazwa, floty[1][i]->nazwa, floty[0][i]->id, floty[1][i]->id))
                    continue;
                if (floty[0][i]->szybkosc >= floty[1][i]->szybkosc)
                    rem(floty[0][i], floty[1][i]);
                else
                    rem(floty[1][i], floty[0][i]);
                hasEnded = false;
            }
            tura++;
        }
        cout << "\n--- KONIEC\n\n";
    }
}
int main()
{
    srand(time(NULL));
    int input[3] = { 0 };
    cout << "Podaj wielkosc floty, kamracie!\nIN>>OKR>>KRZ>>LPD>> ";
    cin >> input[0] >> input[1] >> input[2];
    Flota flota1(input[0], input[1], input[2]);
    Flota flota2(input[0], input[1], input[2]);
    walka(&flota1, &flota2);
    return 0;
}