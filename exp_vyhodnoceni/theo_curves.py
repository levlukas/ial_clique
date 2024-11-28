from matplotlib import pyplot as plt
import numpy as np

def bf_complexity(n):
    return n**2 * 2**n

def bt_complexity(n):
    return n * 2**n

n = np.linspace(1, 5, 100)
bf = bf_complexity(n)
bt = bt_complexity(n)

plt.figsize = (10, 10)
plt.plot(n, bf, label='hrubá síla')
plt.plot(n, bt, label='zpětné vyhledávání')

plt.xlabel('n')
plt.ylabel('časová složitost')
plt.legend()

plt.show()
plt.close()

# second plot
plt.figsize = (10, 10)
plt.plot(n, bf, label='hrubá síla')
plt.plot(n, bt, label='zpětné vyhledávání')

plt.xscale('log')
plt.yscale('log')

plt.xlabel('log(n)')
plt.ylabel('časová složitost, log')
plt.legend()

plt.show()

# third plot
n2 = np.linspace(0, 25, 1000)
bf2 = bf_complexity(n2)
bt2 = bt_complexity(n2)

plt.figsize = (10, 10)
plt.plot(n2, np.log(bf2) / np.log(bt2))
plt.plot(n2, n2 / n2, linestyle='--')

# plt.xscale('log')
# plt.yscale('log')

plt.ylim([0,2])

plt.xlabel('n')
plt.ylabel('poměr logaritmů složitostí')
plt.legend()

plt.show()

