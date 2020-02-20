#include <stdio.h>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

const int MAX = 10e5;

struct library {
    int libID;
    int bookCount;
    int signupTime;
    int booksPerDay;
    int* bookID;
    int score;
};

int bookScore[MAX];
library lib[MAX];

bool sortLib (library lib1, library lib2) {
    if (lib1.signupTime == lib2.signupTime) {
        return lib1.score > lib2.score;
    } else {
        return lib1.signupTime < lib2.signupTime;
    }
}

int out[MAX];
int outCnt;

int main () {
    freopen ("f.txt", "r", stdin);
    freopen ("outf.txt", "w", stdout);

    int bookTotal, libTotal, dayTotal;
    scanf ("%d %d %d ", &bookTotal, &libTotal, &dayTotal);

    for (int i = 0; i < bookTotal; i++) {
        scanf ("%d ", &bookScore[i]);
    }

    for (int i = 0; i < libTotal; i++) {
        int bookCount, signupTime, booksPerDay;
        scanf ("%d %d %d ", &bookCount, &signupTime, &booksPerDay);

        lib[i].libID = i;
        lib[i].bookCount = bookCount;
        lib[i].signupTime = signupTime;
        lib[i].booksPerDay = booksPerDay;
        lib[i].bookID = new int[bookCount];

        for (int k = 0; k < bookCount; k++) {
            scanf ("%d ", &lib[i].bookID[k]);
            lib[i].score += lib[i].bookID[k]; 
        }
    }

    vector<library> output;
    int usedDays = 0; 
    while (usedDays <= dayTotal) {
        sort (lib, lib + libTotal, sortLib);

        swap(lib[0], lib[libTotal - 1]);
        libTotal--;

        output.push_back(lib[libTotal]);
        usedDays += lib[libTotal].signupTime;

        for (int i = 0; i < lib[libTotal].bookCount; i++) {
            bookScore[lib[libTotal].bookID[i]] = 0;
        }
    
    for (int i = 0; i < libTotal; i++) {
        lib[i].score = 0;
        for (int k = 0; k < lib[i].bookCount; k++) {
            lib[i].score += lib[i].bookID[k]; 
        }
    }
    
    }

    printf("%d\n", output.size()); 

    /*
    for (int i = 0; i < libTotal; i++) {
        printf ("%d %d %d\n", lib[i].bookCount, lib[i].signupTime, lib[i].booksPerDay);

        for (int k = 0; k < lib[i].bookCount; k++) {
            printf ("%d ", lib[i].bookID[k]);
        }

        printf ("\n");
    }*/

    /*int day = 0;
    for (int i = 0; i < libTotal; i++) {
        day += lib[i].signupTime;
        if (day >= dayTotal)
            break;

        out[outCnt++] = lib[i].libID;
    }*/

    //printf ("%d\n", outCnt);
    for (int i = 0; i < output.size(); i++) {
        printf ("%d %d\n", output[i].libID, output[i].bookCount);
        for (int k = 0; k < output[i].bookCount; k++) {
            printf ("%d ", output[i].bookID[k]);
        }
        printf ("\n");
    }
}