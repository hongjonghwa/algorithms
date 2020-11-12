import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import scipy.stats as stats
from statsmodels.formula.api import ols
from statsmodels.stats.anova import anova_lm

data = np.genfromtxt("altman_12_6.txt", delimiter=",")
print(data)
df = pd.DataFrame(data, columns=['head_size', 'fetus', 'observer'])

df.boxplot(column = 'head_size', by='fetus')


formula = 'head_size ~ C(fetus) + C(observer) + C(fetus):C(observer)'
lm = ols(formula, df).fit()
print(anova_lm(lm))

plt.show()