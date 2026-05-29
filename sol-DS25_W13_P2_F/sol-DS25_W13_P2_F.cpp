#include<iostream>
#include<vector>
using namespace std;

int main() {
	int N;
	cin >> N;
	vector<vector<int>>matrix(N, vector<int>(N));
	for (int i{ 0 }; i < N; ++i) {
		for (int j{ 0 }; j < N; ++j) {
			cin>>matrix[i][j];
		}
	}
	vector<int>degree;
	for (int i{ 0 }; i < N; ++i) {
		int n = 0;
		for (int j{ 0 }; j < N; ++j) {
			if (matrix[i][j] == 1)++n;
		}
		degree.push_back(n);
	}
	int MCC = 0;
	for (int i{ 1 }; i < N; ++i) {
		if (degree[MCC] <= degree[i])MCC = i;
	}
	vector<int>isolatedCities;
	for (int i{ 0 }; i < N; ++i) {
		if (degree[i] == 0)isolatedCities.push_back(i);
	}
	cout << "Most connected city: City " << MCC+1 << " Connected cities " << degree[MCC] << '\n';
	cout << "Isolated cities: ";
	if (isolatedCities.size() == 0) {
		cout << -1;
	}
	else {
		for (int e : isolatedCities)cout << e+1 << ' ';
	}
	cout << '\n';
}