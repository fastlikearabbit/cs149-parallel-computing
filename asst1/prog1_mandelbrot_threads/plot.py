import matplotlib.pyplot as plt

threads = [2, 3, 4, 5, 6, 7, 8]
speedup = [1.92, 2.78, 3.65, 4.47, 5.54, 6.24, 7.19]

plt.plot(threads, speedup, marker='o', linestyle='-', color='b', label='Actual Speedup')
plt.plot(threads, threads, linestyle='--', color='r', label='Ideal Speedup')
plt.xlabel('Number of Threads')
plt.ylabel('Speedup')
plt.title('Speedup vs Number of Threads')
plt.grid(True)
plt.legend()
plt.savefig('speedup_plot.png')
plt.show()
