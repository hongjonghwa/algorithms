import numpy as np
from scipy import stats

np.random.seed(42)

norm1 = np.random.normal(size=500)
norm2 = np.random.normal(loc=1, scale=2, size=500)
print("norm1", norm1.mean(), norm1.var(ddof=1) ** (1 / 2))
print("norm2", norm2.mean(), norm2.var(ddof=1) ** (1 / 2))
