#include "gauss.h"

vDouble gauss(std::vector<vDouble> a, vDouble b) {
    vDouble x;
    x.resize(a.size());
    for (int i = 0; i < a.size(); i++) {
        for (int j = i + 1; j < a.size(); j++) {
            double c = a[j][i] / a[i][i];
            for (int k = i; k < a[j].size(); k++) {
                a[j][k] -= a[i][k] * c;
            }
            b[j] -= b[i] * c;
        }
    }

    for (int i = a.size() - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = a.size() - 1; j > i; j--) {
            sum += a[i][j] * x[j];
        }
        x[i] = (b[i] - sum) / a[i][i];
    }

    return x;
}

vDouble runner(vDouble a, vDouble c, vDouble b, vDouble f) {
    vDouble x;
    int n = c.size();
    x.resize(n);
    for (int i = 1; i < n; i++) {
        c[i] -= a[i] / c[i-1] * b[i - 1];
        f[i] -= a[i] / c[i-1] * f[i - 1];
    }
    x[n - 1] = f[n - 1] / c[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        x[i] = (f[i] - b[i] * x[i + 1]) / c[i];
    }
    return x;
}