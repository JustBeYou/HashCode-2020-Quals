#include <stdio.h>
#include <stdint.h>
#include <bits/stdc++.h>

using namespace std;
const int MAX = 10e5;

struct library {
    int bookCount;
    int signupTime;
    int booksPerDay;
    int* bookID;
};

int bookScore[MAX];
library lib[MAX];

int libScore[MAX];
int dp[100005];
bool taken[100005][10005];
//int howmany[100005];
int howmany;
bool path[100005];

int main () {
    freopen ("d.txt", "r", stdin);

    int bookTotal, libTotal, dayTotal;
    scanf ("%d %d %d ", &bookTotal, &libTotal, &dayTotal);

    for (int i = 0; i < bookTotal; i++) {
        scanf ("%d ", &bookScore[i]);
    }

    int m = 0;
    for (int i = 0; i < libTotal; i++) {
        int bookCount, signupTime, booksPerDay;
        scanf ("%d %d %d ", &bookCount, &signupTime, &booksPerDay);

        lib[i].bookCount = bookCount;
        lib[i].signupTime = signupTime;
        lib[i].booksPerDay = booksPerDay;
        lib[i].bookID = new int[bookCount];

        for (int k = 0; k < bookCount; k++) {
            scanf ("%d ", &lib[i].bookID[k]);
            libScore[i] += bookScore[lib[i].bookID[k]];
        }

        //printf("%d %lld\n", i, libScore[i]);
        //m = max(libScore[i], m);
    }
    //printf("%lld\n", m);
    for (int i = 0; i < libTotal; i++) {
        for (int j = 100000 - 1 - lib[i].signupTime; j >= 0; j--) {
            if (dp[j + lib[i].signupTime] <= dp[j] + libScore[i]) {
               dp[j + lib[i].signupTime] = dp[j] + libScore[i];
                taken[i][j + lib[i].signupTime] = true;
//               howmany[j + lib[i].signupTime] = 1 + howmany[j];
            } else {
                taken[i][j + lib[i].signupTime] = false;
            }
        }
    }

    int current = 0;
    int maxval = 0;
    int index = 0;
    for (int i = 0; i < 100000 - 1; i++) {
        if (dp[i] > maxval) {
            maxval = dp[i];
            index = i;
        }
    }
    //printf("%d %d\n", current, maxval);

    int j = 100000 - 1;

    //int howmany = 0;
    for (int i = bookTotal; i >= 0; i--) {
        if (taken[i][j]) {
            path[i] = true;
            howmany++;
        }
        j = j - lib[i].signupTime;
    } 
    printf("%d\n", howmany);
    for (int i = 0; i < 100005; i++ ) {
        if (path[i]) {
            printf("%d %d\n", i, lib[i].bookCount);
            for (int j = 0; j < lib[i].bookCount; j++) {
                printf("%d ", lib[i].bookID[j]);
            }
            printf("\n");
        }
    }

    // TEST

    /*for (int i = 0; i < libTotal; i++) {
        printf ("%d %d %d\n", lib[i].bookCount, lib[i].signupTime, lib[i].booksPerDay);

        for (int k = 0; k < lib[i].bookCount; k++) {
            printf ("%d ", lib[i].bookID[k]);
        }

        printf ("\n");
    }*/
}