import numpy as np
from matplotlib import pyplot as plt


def noise(x, scale=0.1):
    return x + np.random.normal(0, scale, x.size)


# 1)
"""
x = np.arange(1, 10, 0.1)
x = noise(x)
y = 1 / x
y = noise(y, scale=0.001)
x_trans = x
y_trans = y
"""

# 2)
"""
"""
x = np.arange(1, 10, 0.1)
x = noise(x)
y = x**2
y = noise(y, scale=0.001)
x_trans = (x)**2
y_trans = (y)

# 3)
"""
x = np.arange(1, 100, 0.1)
x = noise(x)
y = x**(1/4)
y = noise(y, scale=0.001)
x_trans = np.log(x)
y_trans = y
"""

# skewad)
"""

mu, sigma = 10, 3
data = np.random.lognormal(mu, sigma, 1000) + 0.1
count, bins, ignored = plt.hist(data, mu, density=True, align='mid')
x = np.linspace(min(bins), max(bins), 10000)
pdf = (np.exp(-(np.log(x) - mu) ** 2 / (2 * sigma ** 2)) / (x * sigma * np.sqrt(2 * np.pi)))
y = pdf
x_trans = x
y_trans = y

"""
plt.scatter(x, y, s=2, color="k")
plt.scatter(x_trans, y_trans, s=1, color="r")

plt.show()

print(x.size)
