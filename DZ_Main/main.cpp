#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <chrono>

using namespace std;
using namespace chrono;

//Структура ребра графа
struct Edge {

	int start_p;
	int end_p;
	int weight;
};

//Перегрузка оператора вывода для ребра
ostream& operator << (ostream &out_s, Edge ed) {
	return out_s << "start " << ed.start_p << " end " << ed.end_p << " weight " << ed.weight << endl;
}

istream& operator >> (istream &in, Edge &ed) {
	int start_p;
	int end_p;
	int weight;

	in >> start_p >> end_p >> weight;
	ed = { start_p,end_p,weight };


	return in;
}


pair<int, int> minimal(vector<int> min_weight) {
	int min = min_weight[0];
	int min_i = 0;
	for (int i = 0; i < min_weight.size(); i++) {
		if (min_weight[i] < min) {
			min = min_weight[i];
			min_i = i;
		}
	}
	return pair<int, int> (min, min_i);
}


//Алгоритм Прима (Плотный граф)
void Dense_Prim(int n, vector <Edge> graph, string file_name) {
	const int inf = 99999;
	ofstream fout;
	set <int> visited_p = {1};
	set <int> edited_p = {1};
	vector <int> storage(n+1,inf);
	vector <int> storage_end(n+1,-1);
	vector<Edge> storage_ed(n+1, { 0,0,0 });
	vector <Edge> path = {};
	int edges_in=0;
	int active_p=1;
	int min_weight{};
	int v_p;
	Edge v_ed;
	int sum_weight=0;
	
	auto start_Func = system_clock::now();

	while (edges_in != n-1) {
		for (int point : edited_p) {
			for (Edge ed : graph) {
				if ((ed.end_p == point && visited_p.count(ed.start_p) == 0) || (ed.start_p == point && visited_p.count(ed.end_p) == 0)) {
					if (storage[point] > ed.weight) {
						storage[point] = ed.weight;
						storage_ed[point] = ed;
						cout << point << endl;
						cout << ed << endl;
						if (ed.end_p == point) {
							storage_end[point] = ed.start_p;
						}
						else {
							storage_end[point] = ed.end_p;
						}
					}
				}
			}

		}
		auto t = minimal(storage);
		min_weight = t.first;
		v_p = t.second;
		storage[v_p] = inf;
		v_ed = storage_ed[v_p];
		v_p = storage_end[v_p];
		storage[v_p] = inf;
		for (Edge ed : graph) {
			if (ed.start_p == v_p && visited_p.count(ed.end_p) != 0) { storage[ed.end_p] = inf;
			edited_p = { v_ed.start_p, v_ed.end_p, ed.end_p };
			}
			else if (ed.end_p == v_p && visited_p.count(ed.start_p) != 0) {
				storage[ed.start_p] = inf;
				edited_p = { v_ed.start_p, v_ed.end_p, ed.start_p};
			}
			else {
				edited_p = { v_ed.start_p, v_ed.end_p};
			}
		}
			
		cout << "suka" << v_p << endl;

		visited_p.insert(v_p);
		path.push_back(v_ed);
		sum_weight += min_weight;
		cout << "bimbimbambam" << min_weight << endl;
		edges_in += 1;
		cout << "blyad" << v_p << endl;
	}
	auto read_time = system_clock::now() - start_Func;
	fout.open("Answers/"+file_name+".txt");
	fout << "Minimal cost: " <<sum_weight << endl;
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


int main(){
	int n=0;
	ifstream fin; 
	vector <Edge> graph;
	Edge ed{ 0,0,0 };
	// Первый тест обычный граф
	fin.open("Tests/1test.txt");
	if (fin.is_open()) {
		fin >> n ;
		
			while(fin >> ed){
				graph.push_back(ed);
			}
	}
	fin.close();
	Dense_Prim(n, graph,"Test1/Dense_Prim");

	
	graph = {};

	//Второй тест полный граф
	fin.open("Tests/2test.txt");
	if (fin.is_open()) {
		fin >> n;

		while (fin >> ed) {
			graph.push_back(ed);
		}
	}
	fin.close();
	Dense_Prim(n, graph, "Test2/Dense_Prim");

	graph = {};

	//Третий тест разреженный граф
	fin.open("Tests/3test.txt");
	if (fin.is_open()) {
		fin >> n;

		while (fin >> ed) {
			graph.push_back(ed);
		}
	}
	fin.close();
	Dense_Prim(n, graph, "Test3/Dense_Prim");
}