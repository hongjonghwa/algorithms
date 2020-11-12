import pandas as pd
from matplotlib import pyplot as plt
plt.rc('font', family='Malgun Gothic')
from statsmodels.tsa.arima.model import ARIMA
from sklearn.metrics import mean_absolute_error
import np_eaxmple as np


df = pd.read_csv("SEC_TS.csv", encoding="CP949", parse_dates=['년/월/일'], thousands=",")
df = df.sort_values("년/월/일")
x = df['년/월/일'].to_numpy()
y = df['종가'].to_numpy()
# print(x, y)

from statsmodels.tsa.seasonal import seasonal_decompose

result = seasonal_decompose(df['종가'], model="m", period=30)
result.plot()