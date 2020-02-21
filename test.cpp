#include <stdio.h>
#include <algorithm>

using namespace std;

int bookTotal, libTotal, dayTotal;
const int MAX = 10e5;

struct library {
    int bookCount;
    int signupTime;
    int booksPerDay;
    int* bookID;
    int score;
    int libID;
};

int bookScore[MAX];
library lib[MAX];

bool sortLib (library lib1, library lib2) {
    if (lib1.booksPerDay == lib2.booksPerDay) {
        return lib1.signupTime < lib2.signupTime;
    } 
    return lib1.booksPerDay > lib2.booksPerDay;
}

bool sortBook (int bookID1, int bookID2) {
    return bookScore[bookID1] > bookScore[bookID2];
}

int out[MAX];
int outCnt;

int bookOut[MAX];
int bookOutCnt = 0;

void printLibs () {
    for (int i = 0; i < libTotal; i++) {
        printf ("%d %d %d\n", lib[i].bookCount, lib[i].signupTime, lib[i].booksPerDay);

        for (int k = 0; k < lib[i].bookCount; k++) {
            printf ("%d ", lib[i].bookID[k]);
        }

        printf ("\n");
    }
}

int main () {
    freopen ("f.txt", "r", stdin);
    freopen ("out.txt", "w", stdout);

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
            lib[i].score+= bookScore[lib[i].bookID[k]];
        }

        sort (lib[i].bookID, lib[i].bookID + lib[i].bookCount, sortBook);
    }

    sort (lib, lib + libTotal, sortLib);

    //printLibs ();

    int day = 0;
    for (int i = 0; i < libTotal; i++) {
        day += lib[i].signupTime;
        if (day >= dayTotal)
            break;

        out[outCnt++] = i;
    }

    printf ("%d\n", outCnt);

    for (int i = 0; i < outCnt; i++) {
        library ourLib = lib[out[i]];
        bookOutCnt = 0;

        for (int k = 0; k < ourLib.bookCount; k++) {
            if (bookScore[ourLib.bookID[k]] != -1) {
                bookOut[bookOutCnt++] = ourLib.bookID[k];
                //bookScore[ourLib.bookID[k]] = -1;
            }
        }

        printf ("%d %d\n", ourLib.libID, bookOutCnt);
        for (int k = 0; k < bookOutCnt; k++)
            printf ("%d ", bookOut[k]);

        printf ("\n");
    }
}