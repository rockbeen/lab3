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
using itvPoint = vPoint::const_iterator;

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

double fn(itvPoint begin, itvPoint end) {
    size_t size = end - begin;
    if (size == 1)
        return begin->y;
    if (size == 2) {
        return (begin->y - (begin+1)->y) / (begin->x - (begin+1)->x);
    }
    return (fn(begin, end - 1) - fn(begin + 1, end)) / (begin->x - (end-1)->x);
}

double pn1(const vPoint& v, double x) {
    auto begin = v.begin();
    auto end = v.end();
    double mult;
    double sum = 0;
    for (auto it = end - 1; it >= begin; it--) {
        mult = 1;
        for (auto it2 = begin; it2 < it; it2++) {
            mult *= (x - it2->x);
        }
        sum += fn(begin, it + 1) * mult;
    }
    return sum;
}

double pn2(const vPoint& v, double x) {
    auto begin = v.begin();
    auto end = v.end();
    double mult;
    double sum = 0;
    for (auto it = begin; it < end; it++) {
        mult = 1;
        for (auto it2 = it + 1; it2 < end; it2++) {
            mult *= (x - it2->x);
        }
        sum += fn(it, end) * mult;
    }
    return sum;
}


vPoint nuton1(double h,  const vPoint& f0) {
    vPoint f;
    double start = f0.front().x;
    double end = f0.back().x;
    for (double x = start; x <= end; x += h) {
        f.push_back({x, 0});
    }
    int i = 0;
    for (Point& p : f) {
        p.y = pn1(f0, p.x);
    }
    return f;
}

vPoint nuton2(double h,  const vPoint& f0) {
    vPoint f;
    double start = f0.front().x;
    double end = f0.back().x;
    for (double x = start; x <= end; x += h) {
        f.push_back({x, 0});
    }
    int i = 0;
    for (Point& p : f) {
        p.y = pn2(f0, p.x);
    }
    return f;
}


int main() {
    const double h = 0.1;
    vector<vector<string>> data = read_csv("02_Великий_Новгород.csv");

    int nyear = stoi(data[0][0]);
    int year;
    cout << "Vvedite god ot " << nyear << " do " << nyear + data.size() - 12 << ": ";
    cin >> year;
    year -= nyear;
    int kyear1 = year + 6;
    int kyear2 = kyear1 + 6;

    int month;
    cout << "vedite month: ";
    cin >> month;

    vPoint f;
    vPoint f0;
    for (int i = year; i < kyear1; i++) {
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

    f = nuton1(h, f0);

    out.open("graph2.dat");
    for (Point p : f) {
        out << p.x << ' ' << p.y << '\n';
    }
    out.close();

    system("python plot.py");

    f0.clear();
    f.clear();
    for (int i = kyear1; i < kyear2; i++) {
        double y = stod(data[i][month]);
        if (y < 999.9) {
            f0.push_back(Point {stod(data[i][YEAR]), stod(data[i][month])});
        }
        //cout << data[i][YEAR] << '\t' << data[i][month] << endl;
    }

    f = nuton2(h, f0);

    out.open("graph.dat");
    for (Point p : f0) {
        out << p.x << ' ' << p.y << '\n';
        cout << p.x << ' ' << p.y << '\n';
    }
    out.close();

    out.open("graph2.dat");
    for (Point p : f) {
        out << p.x << ' ' << p.y << '\n';
    }
    out.close();

    system("python3 plot.py");
    return 0;
}
