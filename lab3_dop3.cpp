#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <complex>
#include <cmath>

using namespace std;

constexpr complex<double> i{ 0, 1 };

enum year {
	YEAR = 0, Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec, Aver
};


struct tochka {
	double x;
	double y;
};

using vDouble = vector<double>;
using vtochka = vector<tochka>;
using dcompl = complex<double>;
using vcompl = vector<dcompl>;




vector<vector<string>> read(string file) {
	fstream fin;
	fin.is_open();
	fin.open(file, ios::in);
	vector<vector<string>> result;
	string line, word;
	vector<string> row;
	getline(fin, line);
	while (!fin.eof()) {
		row.clear();
		getline(fin, line);
		stringstream s(line);
		while (getline(s, word, ',')) {
			row.push_back(word);
		}
		result.push_back(row);
	}
	result.pop_back();
	fin.close();
	return result;
}

vtochka apr(double h, const vtochka& f0, int k = 50) {
	vtochka fIn;
	double xMax = f0.back().x;
	for (tochka p : f0) {
		fIn.push_back(tochka{ (p.x - xMax) / f0.size() * 2 * 3.14, p.y });
	}
	vtochka fres;
	vcompl a;
	for (int j = 0; j < k; j++) {
		a.push_back(dcompl{ 0, 0 });
		for (tochka p : fIn) {
			a[j] += p.y * exp(-i * static_cast<double>(j - k / 2) * p.x);
		}
		a[j] /= f0.size();
	}

	for (double x = f0.front().x; x <= f0.back().x; x += h) {
		dcompl sum{ 0, 0 };
		double xNorm = (x - xMax) / f0.size() * 2 * 3.14;
		for (int j = 0; j < k; j++) {
			sum += a[j] * exp(i * static_cast<double>(j - k / 2) * xNorm);
		}
		fres.push_back(tochka{ x, sum.real() });
	}

	return fres;
}


int main() {
	const double h = 0.1;
	vector<vector<string>> data = read("02_Великий_Новгород.csv");

	int month;
	cout << "Vvedite month: ";
	cin >> month;

	vtochka f;
	vtochka f0;
	for (int i = 0; i < data.size(); i++) {
		double y = stod(data[i][month]);
		if (y < 999.9) {
			f0.push_back(tochka{ stod(data[i][YEAR]), stod(data[i][month]) });
		}

	}

	ofstream out;
	out.open("graph.dat");
	for (tochka p : f0) {
		out << p.x << ' ' << p.y << '\n';
	}
	out.close();

	f = apr(h, f0);

	out.open("graph2.dat");
	for (tochka p : f) {
		out << p.x << ' ' << p.y << '\n';
	}
	out.close();

	system("python plot.py");
	return 0;
	
}
