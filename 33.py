import math
import numpy as np
import matplotlib.pyplot as plt
from math import factorial

def lambd(m, n):
    return factorial(m)/(factorial(m-n)*factorial(n))
def kr(y, i, k):#Конечные разности#
    if k == 0:
        return y[i]
    else:
        S = 0
        for j in range(k+1):
            S += (-1)**j*lambd(k, j)*y[k+i-j]
        return S
def kr2(y, i, k):#Конечные разности#
    if k == 0:
        return y[i]
    else:
        return kr2(y, i+1, k-1) - kr2(y, i, k-1)

def nuton1(x, X, Y):
    P = 0
    q = 1
    for i in range(len(y)):
        P += kr2(Y, 0, i) * q / factorial(i)
        q *= x - X[i]
    return P

def nuton2(x, X, Y):
    P = Y[-1]
    q = x - X[-1]
    j = 1
    for i in range(len(Y)-2, -1, -1):
        P += kr2(Y, i, j)*q/factorial(j)
        q *= x - X[i]
        j += 1
    return P
    
file=open("02_Великий_Новгород.csv").read().split('\n')

read=[line.split(',') for line in file]

inityear = 1835
g = int(input("Vvedite god "))
m = int(input("Vvedite mesyac: "))
g+=1
g -=inityear
endyear1 = g+6
endyear2 = endyear1 +6

x=[float(read[i][0]) for i in range(g,endyear1)]
y = list(float(read[i][m]) for i in range(g, endyear1))
x1=[float(read[i][0]) for i in range(endyear1,endyear2)]
y1 = list(float(read[i][m]) for i in range(endyear1,endyear2))


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
yy = [nuton1(i, x, y) for i in xx]
plt.plot(x,y,'o',xx, yy)
xx1 = np.arange(np.min(x1),np.max(x1)+0.1, 0.1)
yy1 = [nuton2(i, x1, y1) for i in xx1]
plt.plot(x1,y1,'o',xx1,yy1)
plt.grid(True)
plt.show()
            
