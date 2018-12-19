import matplotlib.pyplot as plt
import numpy as np

with open('out','r') as f:
	lines = f.readlines()

short = [int(lines[i]) for i in range(len(lines)) if i%2==0]
longer = [int(lines[i]) for i in range(len(lines)) if i%2==1] #odd

shortMean = np.mean(short)
longerMean = np.mean(longer)
shortSTD = np.std(short)
longerSTD = np.std(longer)

sigma =.5
print('short',shortMean,'long',longerMean)
print(len(short),len(longer))
short = [e for e in short if e<shortMean+sigma*shortSTD]
longer = [o for o in longer if o<longerMean+sigma*longerSTD]
print(len(short),len(longer))
'''
plt.scatter(range(len(short)),short,color='blue',label='short',marker='.')
plt.scatter(range(len(longer)),longer,color='red',label='long',marker='.')
plt.legend()
plt.show()
'''