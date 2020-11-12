import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import scipy.stats as stats
from statsmodels.formula.api import ols
from statsmodels.stats.anova import anova_lm

data = np.genfromtxt("altman_910.txt", delimiter=",")
# print(data)
group1 = data[data[:, 1] == 1, 0]
group2 = data[data[:, 1] == 2, 0]
group3 = data[data[:, 1] == 3, 0]

print("Group1:", group1)
print("Group2:", group2)
print("Group3:", group3)
plot_data = [group1, group2, group3]
print(plot_data)
ax = plt.boxplot(plot_data)
# plt.show()

statistic, pvalue = stats.f_oneway(group1, group2, group3)

print("# 일원분산북석 : {:f} {:f}".format(statistic, pvalue))

df = pd.DataFrame(data, columns=['value', 'treatment'])
model = ols('value ~ C(treatment)', df).fit()
print(anova_lm(model))
