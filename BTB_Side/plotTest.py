import matplotlib.pyplot as plt
import numpy as np

with open('out','r') as f:
	lines = f.readlines()

short = [int(lines[i]) for i in range(len(lines)) if i%2==0]
miss = [int(lines[i]) for i in range(len(lines)) if i%2==1]

shortMean = np.mean(short)
missMean = np.mean(miss)
shortSTD = np.std(short)
missSTD = np.std(miss)

sigma =.5
print('short',shortMean,'long',missMean)
print(len(short),len(miss))
short = [e for e in short if e<shortMean+sigma*shortSTD]
miss = [o for o in miss if o<missMean+sigma*missSTD]
print(len(short),len(miss))

plt.scatter(range(len(short)),short,color='blue',label='short',marker='.')
plt.scatter(range(len(miss)),miss,color='red',label='long',marker='.')
plt.legend()
plt.show()