/************
Autors: Iļja Gubins, ig11075
I uzdevums: Dzīves spēle (Conway’s ‘Game of Life’)

Divi noteikumi:
1) ja dzīvai šūnai ir 2 vai 3 dzīvi kaimiņi, tā turpina dzīvot,
pretējā gadījumā tā mirst no "vientulības" vai "pārapdzīvotības";

2) Tukša (mirusi) šūna, kam ir tieši 3 dzīvi kaimiņi, atdzīvojas.

************/
#include <iostream> //std input/output
#include <cstdlib> //lai varetu izmantot rand/srand
#include <ctime> //lai izmantotu time funkciju
#include <windows.h> //lai izmantotu Sleep(milisekundes)
using namespace std;

int i,j,k,kaimini; //koordinati
int arraySize, steps, clear, steptime; //vertibas kuras lietotajs ievada
int square[35][35]; //ists masivs ar vertibas
int squareTemp[35][35]; //starpmasivs

void createMap(){
        for (i = 0; i < arraySize; i++) {
                for (j = 0; j < arraySize; j++) {
                        square[i][j] = rand()%2;
                        squareTemp[i][j] = 0;
                }
        }
}

void checkMap() {
    int iMin,iPlus,jMin,jPlus;

    for (i = 0; i < arraySize; i++) {
        for (j = 0; j < arraySize; j++) {
            if (i == 0){ iMin = arraySize; } else {iMin = i-1;}
            if (i == arraySize){ iPlus = 0;} else {iPlus = i+1;}
            if (j == 0){ jMin = arraySize; } else {jMin = j-1;}
            if (j == arraySize){ jPlus = 0;} else {jPlus = j+1;}

            kaimini = square[iMin][jMin]+
                square[i][jMin]+
                square[iPlus][jMin]+
                square[iMin][j]+
                square[iPlus][j]+
                square[iMin][jPlus]+
                square[i][jPlus]+
                square[iPlus][jPlus];

            if (kaimini < 2){
                squareTemp[i][j] = 0;
            }
            else if (kaimini > 3){
                squareTemp[i][j] = 0;
            }
            else if (kaimini == 3){
                squareTemp[i][j] = 1;
            }
            else if (kaimini == 2){
                squareTemp[i][j] = square[i][j];
            }
        }
    }
    //tagad no squareTemp uz istu square masivu
    for (i = 0; i < arraySize; i++) {
        for (j = 0; j < arraySize; j++) {
            square[i][j] = squareTemp[i][j];
        }
    }
}

void printMap(){
    if (clear) system("CLS");
    else cout << "\n";

    for (i = 0; i < arraySize; i++) {
        for (j = 0; j < arraySize; j++) {
            if (square[i][j] == 0) {
                cout << "..";}
            else {
                cout << "[]";
            }
        }
        cout << "\n";
    }
}

int main () {
    do {
        cout << "Enter size of the field (1 - 35): ";
        cin >> arraySize;
        if(arraySize<1 || arraySize>35) cout << "Error: too big or too small grid size!\n";
    }while(arraySize<1 || arraySize>35);
    do {
        cout << "Enter the number of the steps: ";
        cin >> steps;
        if(steps<1) cout << "Error: number of steps <1!\n";
    }while(steps<1);
    do {
        cout << "How much time between steps (in seconds): ";
        cin >> steptime;
        if(steptime<1) cout << "Error: time between steps must be greater than 1 second!\n";
    }while(steptime<1);
    do {
        cout << "Clear the screen between steps? (1/0): ";
        cin >> clear;
        if(clear<0 || clear>1) cout << "Error: clear the screen value must be 1 or 0!\n";
    }while(clear<0 || clear>1);

    srand((unsigned)(time(0)));
    createMap();
    for (k=0; k<steps; k++) {
        checkMap();
        printMap();
        Sleep(steptime*1000); //reiz 1000, jo Sleep(milisekundes)
    }
    cout << "Done!\n";
    cout << "Enter any key to exit.";
    cin.get();
    return 0;
}
