from matplotlib import pyplot as plt
import numpy as np

valList = []
num_str = '03'
with open(num_str+'_random16384.txt', 'r') as f:
    lines = f.readlines()
    for line in lines:
        valList.append(int(line))

valList = np.array(valList)
valList.resize((128, 128))

plt.pcolor(valList)    
plt.colorbar()
plt.savefig(num_str+'_random16384.png')
plt.show()
