import scipy as sp
import matplotlib.pyplot as plt
def func(x,y):
              d=5
              fp, residuals, rank, sv, rcond = sp.polyfit(x, y, d, full=True) 
              f = sp.poly1d(fp) 
              fx = sp.linspace(x[0], x[-1] + 1, len(x)) 
              plt.plot(x, y, 'o', label='Original data', markersize=10)
              plt.plot(fx, f(fx), linewidth=2)
              plt.grid(True)
              plt.show()

file=open("02_Великий_Новгород.csv").read().split('\n')

read=[line.split(',') for line in file]

inityear = 1884
m = int(input("Введите месяц: "))

y=[float(read[i][0]) for i in range(1,136)]
x = list(float(read[i][m]) for i in range(1,136))
#print (x)
#print (y)

for i in range(x.count(999.9)):
  del y[(x.index(999.9))]
  x.remove(999.9)
func(y,x)
