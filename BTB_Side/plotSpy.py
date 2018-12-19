import matplotlib.pyplot as plt
import numpy as np

with open('out','r') as f:
	lines = f.readlines()

#avg = int(lines.pop(-1))
times = [int(i) for i in lines]
m = np.mean(times)
s = np.std(times)
sigma = .5

#times = [t for t in times if t<m+s*sigma and t>400]

plt.scatter(range(len(times)),times,color='blue')
#plt.plot([0, len(times)], [avg, avg], color='k', linestyle='-', linewidth=2)
plt.show()