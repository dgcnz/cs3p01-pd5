import os
import time
import numpy as np
import matplotlib.pyplot as plt

processes = [1, 2, 4, 8]
times = np.zeros(4)

for i, process in enumerate(processes):
	start = time.time()
	os.system('./qsort')
	end = time.time()

	times[i] = end - start

fig = plt.figure(figsize=(10, 8))
plt.plot(processes, times)
plt.title("Execution time vs. number of processes for N=1e6")
plt.xlabel("# Processes")
plt.ylabel("Time (s)")
plt.savefig("plot.png")
plt.close(fig)
