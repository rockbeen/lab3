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

vPoint splineCubic(double h,  const vPoint& f0) {
    double n = f0.size();
    vDouble vh;
    vPoint f;
    vDouble a;
    for (int i = 0; i < n; i++) {
        a.push_back(f0[i].y);
        if (i != n - 1)
            vh.push_back(f0[i + 1].x - f0[i].x);
    }
    vDouble c;
    vDouble ca, cc, cb, cf;
    ca.push_back(0);
    cc.push_back(2 * (vh[0] + vh[1]));
    cb.push_back(vh[1]);
    cf.push_back(3 * ((f0[2].y - f0[1].y) / vh[1] - (f0[1].y - f0[0].y) / vh[0]));
    for (int i = 1; i < n - 2; i++) {
        ca.push_back(vh[i - 1]);
        cc.push_back(2 * (vh[i - 1] + vh[i]));
        cb.push_back(vh[i + 1]);
        cf.push_back(3 * ((f0[i + 1].y - f0[i].y) / vh[i] - (f0[i].y - f0[i - 1].y) / vh[i - 1]));
    }
    ca.push_back(vh[n - 3]);
    cc.push_back(2 * (vh[n - 3] + vh[n - 2]));
    cb.push_back(0);
    cf.push_back(3 * ((f0[n - 1].y - f0[n - 2].y) / vh[n - 2] - (f0[n - 2].y - f0[n - 3].y) / vh[n - 3]));
    c = runner(ca, cc, cb, cf);
    // c.push_back(0);
    // cout << c.size() << ' ' << f0.size() << endl;

    vDouble d;
    for (int i = 0; i < n - 1; i++) {
        // cout << i << endl;
        d.push_back((c[i + 1] - c[i]) / 3 / vh[i]);
    }

    vDouble b;
    for (int i = 0; i < n - 1; i++) {
        // cout << i << endl;
        b.push_back((f0[i + 1].y - f0[i].y) / vh[i] - (2 * c[i] + c[i + 1]) * vh[i] / 3);
    }
    // for (double x: b) {
    //     cout << x << endl;
    // }
    double start = f0.front().x;
    double end = f0.back().x;
    int i = 0;
    for (double x = start; x <= end; x += h) {
        if (x >= f0[i + 1].x) i++;
        f.push_back(Point {x, a[i] + b[i] * (x - f0[i].x) + c[i] * pow((x - f0[i].x), 2) + d[i] * pow((x - f0[i].x), 3)});
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
    f = splineCubic(0.1, f0);
    out.open("graph2.dat");
    for (Point p : f) {
        out << p.x << ' ' << p.y << '\n';
    }
    out.close();
    system("python3 plot.py");
    return 0;
}
