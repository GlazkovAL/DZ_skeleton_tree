#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <ctime>
#include <algorithm>

using namespace std;

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

// ������� ��� ������ ����� �������
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

// �������� �������� � �������� ���������������� ��������
void Kruskal(int n, vector<Edge> graph, string file_name) {
    ofstream fout;
    vector<Edge> path;
    vector<int> parent(n + 1);
    vector<int> rank(n + 1, 0);
    int edges_in = 0;
    int sum_weight = 0;
    int start = clock();

    // ������������� ��������� ������
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }

    // ���������� ����� �� ����
    sort(graph.begin(), graph.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
        });

    // ���������� ��������� ������
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

    int end = clock();
    int t = (end - start);
    fout.open("Answers/" + file_name + ".txt");
    fout << "Minimal cost: " << sum_weight << endl;
    fout << "Time: " << t << endl;
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

    // ������ ���� ������� ����
    fin.open("Tests/1test.txt");
    if (fin.is_open()) {
        fin >> n;

        while (fin >> ed) {
            graph.push_back(ed);
        }
    }
    fin.close();
    Kruskal(n, graph, "Test1/Kruskal_tr");

    graph = {};
    // ������ ���� ������ ����
    fin.open("Tests/2test.txt");
    if (fin.is_open()) {
        fin >> n;

        while (fin >> ed) {
            graph.push_back(ed);
        }
    }
    fin.close();
    Kruskal(n, graph, "Test2/Kruskal_tr");

    graph = {};

    // ������ ���� ����������� ����
    fin.open("Tests/3test.txt");
    if (fin.is_open()) {
        fin >> n;

        while (fin >> ed) {
            graph.push_back(ed);
        }
    }
    fin.close();
    Kruskal(n, graph, "Test3/Kruskal_tr");

    return 0;
}