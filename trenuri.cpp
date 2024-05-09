#include <algorithm>
#include <bitset>
#include <fstream>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

ifstream fin("trenuri.in");
ofstream fout("trenuri.out");

// orasul de start, respectiv destinatie
string src, dest;
// mapare intre numele oraselor si numere
unordered_map<string, int> cod;
// nr de orase
int n;
const int nmax = 200005;

// graful ce retine pentru fiecare graf[i] orasele vecine cu i
// reprezentate prin coduri
vector<int> graf[nmax];

bitset<nmax> visited(false);

// sortarea topologica a nodurilor
stack<int> topo;

// cream stiva printr-un dfs
void dfs(int node) {
    visited[node] = true;
    for (int neighbor : graf[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor);
        }
    }
    topo.push(node);
}

int main() {
    int m;
    string u, v;
    fin >> src >> dest >> m;

    // asociem pentru fiecare oras nou un cod(numar intreg)
    for (int i = 0; i < m; ++i) {
        fin >> u >> v;

        if (cod[u] == 0) {
            // u este oras nou
            cod[u] = ++n;
        }

        if (cod[v] == 0) {
            // v este oras nou
            cod[v] = ++n;
        }

        // adaugam v ca fiind vecin cu u in graf
        graf[cod[u]].push_back(cod[v]);
    }
    fin.close();

    // pas[i] nr de orase pe care il putem vizita maxim pana in orasul i
    // incepand cu cel de start
    vector<int> pas(nmax, 0);

    // facem un dfs prin care cream stiva cu nodurile sortate topologic
    dfs(cod[src]);

    // initializam nr de orase vizitate pana la prin oras cu 1
    pas[cod[src]] = 1;

    // extragem nodurile din stiva(ies in ordinea sortarii topologice)
    while (!topo.empty()) {
        int node = topo.top();
        topo.pop();
        // actualizam pentru fiecare oras vecin daca am gasit o ruta cu mai
        // multe orase
        for (int neighbor : graf[node]) {
            pas[neighbor] = max(pas[neighbor], pas[node] + 1);
        }
    }

    // nr de orase maxim pe care le putem vizita de la src la dest
    fout << pas[cod[dest]];
    fout.close();
    return 0;
}
