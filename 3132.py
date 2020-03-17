
import numpy as np
import matplotlib.pyplot as plt
def lagranz(x,y,t):
         z=0
         for j in range(len(y)):
             p1=1; p2=1
             for i in range(len(x)):
                 if i==j:
                     p1=p1*1; p2=p2*1   
                 else: 
                     p1=p1*(t-x[i])
                     p2=p2*(x[j]-x[i])
             z=z+y[j]*p1/p2
         return z

file=open("02_Великий_Новгород.csv").read().split('\n')

read=[line.split(',') for line in file]


inityear = 1835
g = int(input("Vvedite god "))
m = int(input("Vvedite mesyac: "))
g+=1
g -=inityear
endyear = g+12

y=[float(read[i][0]) for i in range(g,endyear)]
x = list(float(read[i][m]) for i in range(g, endyear))

#print (x)
#print (y)

for i in range(x.count(999.9)):
  del y[(x.index(999.9))]
  x.remove(999.9)
    
print (x)
print (y)
ynew=np.arange(np.min(y),np.max(y)+0.1, 0.1)
xnew=[lagranz(y,x,i) for i in ynew]
plt.plot(y,x,'o',ynew,xnew)

plt.grid(True)
plt.show()




