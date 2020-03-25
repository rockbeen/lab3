#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include "gauss.cpp"
using namespace std;

enum Data {
    YEAR = 0,
    JAN,
    FEB,
    MAR,
    APR,
    MAY,
    JUN,
    JUL,
    AUG,
    SEP,
    OCT,
    NOV,
    DEC,
    AVE
};

struct Point {
    double x;
    double y;
};

using vDouble = vector<double>;
using vPoint = vector<Point>;

vector<vector<string>> read_csv(string filename) {
    ifstream fin;
    fin.open(filename, ios::in);
    vector<vector<string>> result;
    string line, word;
    vector<string> row;
    getline(fin, line);
    while (!fin.eof()) { 
  
        row.clear(); 
  
        // Считываем строку целиком и сохраняем её в строковой переменной 'line' 
        getline(fin, line); 
        // Будем использовать stringstream для того, чтобы разбить строку на элементы (слова) 
        stringstream s(line); 
  
        // Считываем каждый элемент строки (слово) и сохраняем его в строковой переменной 'word'
        while (getline(s, word, ',')) { 
  
            // Добавляем все элементы (слова) в вектор из строк  
            row.push_back(word); 
        } 
        result.push_back(row);
    }
    result.pop_back();
    fin.close();
    return result;
}

double polynom(double x, vDouble a) {
    double sum;
    for (int i = 0; i < a.size(); i++) {
        sum += a[i] * pow(x, i);
    }
    return sum;
}

vPoint approx(double h,  const vPoint& f0) {
    vPoint f;
    double start = f0.front().x;
    double end = f0.back().x;
    vector<vDouble> s;
    vDouble xy;
    double sum;
    for (int i = 0; i < 5; i++) {
        s.push_back(vDouble{});
        for (int j = 0; j < 5; j++) {
            if (i == 0 && j == 0) {
                s[i].push_back(f0.size());
            } else {
                sum = 0;
                for (int k = 0; k < f0.size(); k++) {
                    sum += pow(f0[k].x, i + j);
                }
                s[i].push_back(sum);
            }
        }
        sum = 0;
        for (int j = 0; j < f0.size(); j++) {
            sum += pow(f0[j].x, i) * f0[j].y;
        }
        xy.push_back(sum);
    }

    vDouble a = gauss(s, xy);

    for (double x = start; x <= end; x += h) {
        f.push_back({x, polynom(x, a)});
    }

    return f;
}

int main() {
    const double h = 0.1;
    vector<vector<string>> data = read_csv("02_Великий_Новгород.csv");

    int month;
    cout << "vvedite month:  ";
    cin >> month;

    vPoint f;
    vPoint f0;
    for (int i = 0; i < data.size(); i++) {
        double y = stod(data[i][month]);
        if (y < 999.9) {
            f0.push_back(Point {stod(data[i][YEAR]), stod(data[i][month])});
        }
        // cout << data[i][YEAR] << '\t' << data[i][month] << endl;
    }

    ofstream out;
    out.open("graph.dat");
    for (Point p : f0) {
        out << p.x << ' ' << p.y << '\n';
    }
    out.close();

    f = approx(h, f0);

    out.open("graph2.dat");
    for (Point p : f) {
        out << p.x << ' ' << p.y << '\n';
    }
    out.close();

    system("python3 plot.py");
    return 0;
}
