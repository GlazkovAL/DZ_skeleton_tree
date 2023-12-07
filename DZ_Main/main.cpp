#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <ctime>

using namespace std;

// Структура ребра графа
struct Edge {
    int start_p;
    int end_p;
    int weight;
};

// Перегрузка оператора вывода для ребра
ostream& operator << (ostream& out_s, Edge ed) {
    return out_s << "start " << ed.start_p << " end " << ed.end_p << " weight " << ed.weight << endl;
}

istream& operator >> (istream& in, Edge& ed) {
    int start_p;
    int end_p;
    int weight;

    in >> start_p >> end_p >> weight;
    ed = { start_p,end_p,weight };

    return in;
}

// Алгоритм обратного удаления
void ReverseDelete(int n, vector<Edge> graph, string file_name) {
    ofstream fout;
    set<int> visited_p = { 1 };
    vector<Edge> path = {};
    int edges_in = n - 1;
    int active_p = 1;
    int max_weight;
    int v_p;
    Edge v_ed;
    int sum_weight = 0;
    int start = clock();

    while (edges_in != 0) {
        max_weight = -1;
        for (int point : visited_p) {
            for (Edge ed : graph) {
                if (((ed.start_p == point && visited_p.count(ed.end_p) == 0) || (ed.end_p == point && visited_p.count(ed.start_p) == 0)) && ed.weight > max_weight) {
                    max_weight = ed.weight;
                    if (ed.start_p == point) v_p = ed.end_p;
                    else v_p = ed.start_p;
                    v_ed = ed;
                }

            }

        }
        visited_p.insert(v_p);
        path.push_back(v_ed);
        sum_weight += max_weight;
        edges_in -= 1;
    }
    int end = clock();
    int t = (end - start);
    fout.open("Answers/" + file_name + ".txt");
    fout << "Maximal cost: " << sum_weight << endl;
    fout << "Time: " << t << endl;
    fout << "Path:" << endl;

    if (fout.is_open()) {
        for (int i = 0; i < n - 1; i++)
        {
            fout << path[i];
        }
    }
    fout.close();
}

int main() {
    int n = 0;
    ifstream fin;
    vector<Edge> graph;
    Edge ed{ 0,0,0 };

    // Первый тест обычный граф
    fin.open("Tests/1test.txt");
    if (fin.is_open()) {
        fin >> n;

        while (fin >> ed) {
            graph.push_back(ed);
        }
    }
    fin.close();
    ReverseDelete(n, graph, "Test1/ReverseDelete_tr");

    graph = {};

    // Второй тест полный граф
    fin.open("Tests/2test.txt");
    if (fin.is_open()) {
        fin >> n;

        while (fin >> ed) {
            graph.push_back(ed);
        }
    }
    fin.close();
    ReverseDelete(n, graph, "Test2/ReverseDelete_tr");

    graph = {};

    // Третий тест разреженный граф
    fin.open("Tests/3test.txt");
    if (fin.is_open()) {
        fin >> n;

        while (fin >> ed) {
            graph.push_back(ed);
        }
    }
    fin.close();
    ReverseDelete(n, graph, "Test3/ReverseDelete_tr");
}