"""
https://partrita.github.io/posts/ANOVA-python/
"""
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import scipy.stats as stats
from statsmodels.formula.api import ols
from statsmodels.stats.anova import anova_lm

centers = [5, 5.3, 4.5]
std = 0.1
# std = 2
colors = 'brg'

mat = []
for i in range(3):
    l = 100
    x = np.arange(l) + i * l
    y = stats.norm(centers[i], std).rvs(l)
    plt.plot(x, y, '.', c=colors[i])
    # plt.plot(x , data_1[i], '.', color=colors[i])
plt.show()
