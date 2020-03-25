import numpy as np
import matplotlib.pyplot as plt
from math import factorial



def lambd(m, n):
    return factorial(m)/(factorial(m-n)*factorial(n))
def kon_rasn(y, i, k):#Конечные разности#
    if k == 0:
        return y[i]
    else:
        S = 0
        for j in range(k+1):
            S += (-1)**j*lambd(k, j)*y[k+i-j]
        return S
def kon_rasn2(y, i, k):#Тоже конечные разности#
    if k == 0:
        return y[i]
    else:
        return kon_rasn2(y, i+1, k-1) - kon_rasn2(y, i, k-1)

def nuton(x, X, Y):
    t = 0
    q = 1
    for i in range(len(y)):
        t += kon_rasn2(Y, 0, i) * q / factorial(i)
        q *= x - X[i]
    return t

def nutonn(x, X, Y):
    t = Y[-1]
    q = x - X[-1]
    j = 1
    for i in range(len(Y)-2, -1, -1):
        t += kon_rasn2(Y, i, j)*q/factorial(j)
        q *= x - X[i]
        j += 1
    return t
    
file=open("02_Великий_Новгород.csv").read().split('\n')

read=[line.split(',') for line in file]

nyear = 1884
g = int(input("Ввелите год(от 1884 до 2009): "))
m = int(input("Введите месяц: "))
g+=1
g -=nyear
kyear = g+6
kyearr = kyear +6

x=[float(read[i][0]) for i in range(g,kyear)]
y = list(float(read[i][m]) for i in range(g, kyear))
x1=[float(read[i][0]) for i in range(kyear,kyearr)]
y1 = list(float(read[i][m]) for i in range(kyear,kyearr))


for i in range(y.count(999.9)):
  del x[(y.index(999.9))]
  y.remove(999.9)

for i in range(y1.count(999.9)):
  del x1[(y1.index(999.9))]
  y1.remove(999.9)

print(x)
print(y)
print(x1)
print(y1)
xx = np.arange(np.min(x),np.max(x)+0.1, 0.1)
yy = [nuton(i, x, y) for i in xx]
plt.plot(x,y,'o',xx, yy)
xx1 = np.arange(np.min(x1),np.max(x1)+0.1, 0.1)
yy1 = [nutonn(i, x1, y1) for i in xx1]
plt.plot(x1,y1,'o',xx1,yy1)
plt.grid(True)
plt.show()
            
