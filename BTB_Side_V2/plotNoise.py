import matplotlib.pyplot as plt
import numpy as np
import sys

with open('./results/'+sys.argv[2],'r') as f:
	lines = f.readlines()
#avg = int(lines.pop(-1))
noise = [int(i) for i in lines]

with open('./results/'+sys.argv[1],'r') as f:
	lines = f.readlines()
#avg = int(lines.pop(-1))
times = [int(i) for i in lines]
m = np.mean(times)
s = np.std(times)
sigma = 1
print(m,s,m+s*sigma)
#outlier = 350

#times = [t for t in times if t<m+s*sigma and t<outlier]

#plt.plot(range(len(times)),times,color='red')
plt.scatter(range(len(times)),times,color='blue',marker='.')
plt.scatter(range(len(noise)),noise,color='red',marker='.')
#for xc in range(0,401,20):
#	plt.axvline(x=xc)
#plt.ylim(0,500)

plt.ylabel('latency (cycles)')
plt.xlabel('trials (20 per second)')
plt.ylim(m-s*sigma,m+s*sigma)
plt.savefig('./figs/{}.png'.format(sys.argv[1]))
plt.show()