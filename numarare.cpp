#include <fstream>
#include <iostream>
#include <vector>

#define nmax 100005
#define MOD 1000000007

using namespace std;

// dp[i] nr de lanturi de la 1 la i
int dp[nmax];
// liste de adiacenta cu muchiile comune
vector<int> com[nmax];

int main() {
    ifstream fin("numarare.in");
    ofstream fout("numarare.out");

    int n, m, u, v;
    fin >> n >> m;

    // matricea de adiacenta a primului graf alocata dinamic
    // int a[nmax][nmax];
    int **a = new int *[nmax];

    for (int i = 0; i < nmax; ++i) {
        a[i] = new int[nmax];
    }

    // a e primul graf
    for (int i = 0; i < m; ++i) {
        fin >> u >> v;
        a[u][v] = 1;
    }

    // com e cel comun
    for (int i = 0; i < m; ++i) {
        fin >> u >> v;
        if (a[u][v]) {
            com[u].push_back(v);
        }
    }
    fin.close();

    // setam cazul de baza
    dp[1] = 1;

    // calculam nr de noduri din lant
    for (int i = 1; i <= n; ++i) {
        // pentru fiecare nod vecin al lui i
        for (int vecin : com[i]) {
            dp[vecin] += dp[i];
            dp[vecin] %= MOD;
        }
    }

    fout << dp[n];

    // dezalocarea memoriei pentru matricea alocata dinamic
    for (int i = 0; i < nmax; ++i) {
        delete[] a[i];
    }
    delete[] a;

    fout.close();
    return 0;
}
