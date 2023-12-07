#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <ctime>

using namespace std;

// Структура ребра графа
struct Edge {
  int start_p;
  int end_p;
  int weight;
};

// Перегрузка оператора << для вывода ребра
ostream& operator << (ostream& out_s, const Edge& ed) {
  return out_s << "start " << ed.start_p << " end " << ed.end_p << " weight " << ed.weight << endl;
}

// Перегрузка оператора >> для ввода ребра
istream& operator >> (istream& in, Edge& ed) {
  return in >> ed.start_p >> ed.end_p >> ed.weight;
}

// Функция для сравнения ребер по весу
bool compareEdges(const Edge& e1, const Edge& e2) {
  return e1.weight < e2.weight;
}

// Функция нахождения корня дерева
int findRoot(const vector<int>& parent, int i) {
  if (parent[i] == i)
    return i;
  return findRoot(parent, parent[i]);
}

// Функция объединения двух поддеревьев
void unionTrees(vector<int>& parent, int i, int j) {
  int root_i = findRoot(parent, i);
  int root_j = findRoot(parent, j);
  parent[root_i] = root_j;
}

// Функция построения минимального остовного дерева алгоритмом Краскала
void Kruskal(int n, vector<Edge>& graph, string file_name) {
  ofstream fout;
  vector<Edge> path;
  vector<int> parent(n + 1), rank(n + 1, 0);
  int sum_weight = 0;
  int start = clock();

  // Инициализация родителей вершин
  for (int i = 1; i <= n; i++)
    parent[i] = i;

  // Сортировка ребер графа по весу
  sort(graph.begin(), graph.end(), compareEdges);

  // Проход по всем ребрам графа
  for (const Edge& ed : graph) {
    int root_start = findRoot(parent, ed.start_p);
    int root_end = findRoot(parent, ed.end_p);

    // Если ребра соединяют разные поддеревья, добавляем его в остовное дерево
    if (root_start != root_end) {
      path.push_back(ed);
      sum_weight += ed.weight;
      // Объединение поддеревьев
      unionTrees(parent, root_start, root_end);
    }
  }

  int end = clock();
  int t = (end - start);
  fout.open("Answers/" + file_name + ".txt");
  fout << "Minimal cost: " << sum_weight << endl;
  fout << "Time: " << t << endl;
  fout << "Path:" << endl;

  if (fout.is_open()) {
    for (const Edge& ed : path) {
      fout << ed;
    }
  }
  fout.close();
}

int main() {
  int n = 0;
  ifstream fin;
  vector<Edge> graph;
  Edge ed{ 0,0,0 };

  // Считывание и выполнение для первого графа
  fin.open("Tests/1test.txt");
  if (fin.is_open()) {
    fin >> n;

    while (fin >> ed) {
      graph.push_back(ed);
    }
  }
  fin.close();
  Kruskal(n, graph, "Test1/Kruskal_tr");

  // Очистка графа
  graph.clear();

  // Считывание и выполнение для второго графа
  fin.open("Tests/2test.txt");
  if (fin.is_open()) {
    fin >> n;

    while (fin >> ed) {
      graph.push_back(ed);
    }
  }
  fin.close();
  Kruskal(n, graph, "Test2/Kruskal_tr");

  // Очистка графа
  graph.clear();

  // Считывание и выполнение для третьего графа
  fin.open("Tests/3test.txt");
  if (fin.is_open()) {
    fin >> n;

    while (fin >> ed) {
      graph.push_back(ed);
    }
  }
  fin.close();
  Kruskal(n, graph, "Test3/Kruskal_tr");
}
