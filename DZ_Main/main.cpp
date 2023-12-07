#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <chrono>
#include <ctime>
#include <algorithm>

using namespace std;
using namespace chrono;

// ��������� ����� �����
struct Edge {
    int start_p;
    int end_p;
    int weight;
};

// ���������� ��������� ������ ��� �����
ostream& operator << (ostream& out_s, Edge ed) {
    return out_s << "start " << ed.start_p << " end " << ed.end_p << " weight " << ed.weight << endl;
}

istream& operator >> (istream& in, Edge& ed) {
    int start_p;
    int end_p;
    int weight;

    in >> start_p >> end_p >> weight;
    ed = { start_p, end_p, weight };

    return in;
}

//�������� �����
void Prim(int n, vector <Edge> graph, string file_name) {
    ofstream fout;
    set <int> visited_p = { 1 };
    vector <Edge> path = {};
    int edges_in = 0;
    int active_p = 1;
    int min_weight;
    int v_p;
    Edge v_ed;
    int sum_weight = 0;

    auto start_Func = system_clock::now();

    while (edges_in != n - 1) {
        min_weight = 9999;
        for (int point : visited_p) {
            for (Edge ed : graph) {
                if (((ed.start_p == point && visited_p.count(ed.end_p) == 0) || (ed.end_p == point && visited_p.count(ed.start_p) == 0)) && ed.weight < min_weight) {
                    min_weight = ed.weight;
                    if (ed.start_p == point) v_p = ed.end_p;
                    else v_p = ed.start_p;
                    v_ed = ed;
                }

            }

        }
        visited_p.insert(v_p);
        path.push_back(v_ed);
        sum_weight += min_weight;
        edges_in += 1;
    }

    auto read_time = system_clock::now() - start_Func;

    fout.open("Answers/" + file_name + ".txt");
    fout << "Minimal cost: " << sum_weight << endl;
    fout << "Time: " << duration_cast<microseconds>(read_time).count() << " Microseconds" << endl;
    fout << "Path:" << endl;

    if (fout.is_open()) {
        for (int i = 0; i < n - 1; i++)
        {
            fout << path[i];
        }
    }
    fout.close();
}

int findRoot(vector<int>& parent, int vertex) {
    if (parent[vertex] == vertex) {
        return vertex;
    }
    return findRoot(parent, parent[vertex]);
}

// ������� ��� ����������� ���� ��������
void unionSets(vector<int>& parent, vector<int>& rank, int root1, int root2) {
    if (rank[root1] < rank[root2]) {
        parent[root1] = root2;
    }
    else if (rank[root1] > rank[root2]) {
        parent[root2] = root1;
    }
    else {
        parent[root2] = root1;
        rank[root1]++;
    }
}

void Kruskal(int n, vector<Edge> graph, string file_name) {
    ofstream fout;
    vector<Edge> path;
    vector<int> parent(n + 1);
    vector<int> rank(n + 1, 0);
    int edges_in = 0;
    int sum_weight = 0;

    auto start_Func = system_clock::now();

    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }

    sort(graph.begin(), graph.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
        });

    for (Edge edge : graph) {
        int root1 = findRoot(parent, edge.start_p);
        int root2 = findRoot(parent, edge.end_p);

        if (root1 != root2) {
            unionSets(parent, rank, root1, root2);
            path.push_back(edge);
            sum_weight += edge.weight;
            edges_in++;

            if (edges_in == n - 1) {
                break;
            }
        }
    }

    auto read_time = system_clock::now() - start_Func;
    fout.open("Answers/" + file_name + ".txt");
    fout << "Minimal cost: " << sum_weight << endl;
    fout << "Time: " << duration_cast<microseconds>(read_time).count() << " Microseconds" << endl;
    fout << "Path:" << endl;

    if (fout.is_open()) {
        for (int i = 0; i < n - 1; i++) {
            fout << path[i];
        }
    }
    fout.close();
}

int main() {
    int n = 0;
    ifstream fin;
    vector<Edge> graph;
    Edge ed{ 0, 0, 0 };


    fin.open("Tests/1test.txt");
    if (fin.is_open()) {
        fin >> n;

        while (fin >> ed) {
            graph.push_back(ed);
        }
    }
    fin.close();
    Prim(n, graph, "Test1/Prim_tr");
    Kruskal(n, graph, "Test1/Kruskal_tr");

    graph = {};
    fin.open("Tests/2test.txt");
    if (fin.is_open()) {
        fin >> n;

        while (fin >> ed) {
            graph.push_back(ed);
        }
    }
    fin.close();
    Prim(n, graph, "Test2/Prim_tr");
    Kruskal(n, graph, "Test2/Kruskal_tr");

    graph = {};

 
    fin.open("Tests/3test.txt");
    if (fin.is_open()) {
        fin >> n;

        while (fin >> ed) {
            graph.push_back(ed);
        }
    }
    fin.close();
    Prim(n, graph, "Test3/Prim_tr");
    Kruskal(n, graph, "Test3/Kruskal_tr");

    return 0;
}