import numpy as np
import matplotlib.pyplot as plt
  
data= np.loadtxt("input.txt")

if data.ndim == 1:
    data = np.array([data])
for i in data:
    x=[]
    y=[]
    x.append(i[0])
    x.append(i[1])
    x.append(i[1])
    x.append(i[0])
    x.append(i[0])
    y.append(i[2])
    y.append(i[2])
    y.append(i[3])
    y.append(i[3])
    y.append(i[2])
    plt.plot(x,y,color='red')


output = np.loadtxt("output.txt")

for i in output:
    x=[]
    y=[]
    x.append(i[0])
    x.append(i[1])
    y.append(i[2])
    y.append(i[3])
    plt.plot(x,y,color='green')


plt.xlabel('x - axis')
plt.ylabel('y - axis')
       
plt.show()

