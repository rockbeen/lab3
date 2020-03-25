#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
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

double dwc(const vPoint& f, int k) {
    double dw = 1;
    for (int i = 0; i < f.size(); i++) {
        if (i == k)
            continue;
        dw *= (f[k].x - f[i].x);
    }
    return dw;
}

double lk(const vPoint& f, double x, int k) {
    double lk = 1;
    for (int i = 0; i < f.size(); i++) {
        if (i == k)
            continue;
        lk *= (x - f[i].x);
    }
    return lk;
}

vPoint lagrange(double h,  const vPoint& f0) {
    vPoint f;
    vDouble dw;
    vDouble l;
    double start = f0.front().x;
    double end = f0.back().x;
    for (int i = 0; i < f0.size(); i++) {
        dw.push_back(dwc(f0, i));
    }

    for (double x = start; x <= end; x += h) {
        f.push_back({x, 0});
    }

    int i = 0;
    for (Point& p : f) {
        // if (abs(f0[i].x - p.x) <= h / 2) {
        //     p.y = f0[i].y;
        //     i++;
        // } else {
            for (int j =0; j < f0.size(); j++) {
                p.y += f0[j].y * lk(f0, p.x, j) / dw[j];
            }
    //     }
    }
    return f;
}

int main() {
    vector<vector<string>> data = read_csv("02_Великий_Новгород.csv");
    int nyear = stoi(data[0][0]);
    int year;
    cout << "Vvedite god ot " << nyear << " do " << nyear + data.size() - 12 << ": ";
    cin >> year;
    year -= nyear;
    int kyear = year + 12;
    int month;
    cout << "vvedite month: ";
    cin >> month;
    // for (vector<string> v : data) {
    //     for (string s: v) {
    //         cout << s << '\t';
    //     }
    //     cout << '\n';
    // }
    vPoint f;
    vPoint f0;
    for (int i = year; i < kyear; i++) {
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
    f = lagrange(0.1, f0);
    out.open("graph2.dat");
    for (Point p : f) {
        out << p.x << ' ' << p.y << '\n';
    }
    out.close();
    system("python3 plot.py");
    return 0;
}
