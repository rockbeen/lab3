import numpy as np
import matplotlib.pyplot as plt
data = np.loadtxt("graph.dat")
plt.plot(data[:,0], data[:,1],'o')
data = np.loadtxt("graph2.dat")
plt.plot(data[:,0], data[:,1])
plt.show()