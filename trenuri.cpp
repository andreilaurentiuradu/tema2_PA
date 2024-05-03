#include <bitset>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>
#define nmax 200005
using namespace std;

ifstream fin("trenuri.in");
ofstream fout("trenuri.out");

string src, dest;
unordered_map<string, int> cod;
int ans, n;
int pas[nmax];
vector<int> graf[nmax];

// imbunatatire inlocuiesti queue cu priority_queue si faci dijkstra
void parcurgere(int start) {
    queue<int> q;
    q.push(start);
    pas[start] = 1;
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        for (int next : graf[current]) {
            if (pas[current] + 1 > pas[next]) {
                pas[next] = pas[current] + 1;
                q.push(next);
            }
        }
    }
}

int main() {
    int m;
    string u, v;
    fin >> src >> dest >> m;

    for (int i = 1; i <= m; ++i) {
        fin >> u >> v;
        if (cod[u] == 0) {
            cod[u] = ++n;
        }

        if (cod[v] == 0) {
            cod[v] = ++n;
        }

        graf[cod[u]].push_back(cod[v]);
    }
    fin.close();
    parcurgere(cod[src]);
    fout << pas[cod[dest]];
    fout.close();
    return 0;
}