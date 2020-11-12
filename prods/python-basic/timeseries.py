import pandas as pd
from matplotlib import pyplot as plt
from statsmodels.tsa.arima.model import ARIMA
from sklearn.metrics import mean_absolute_error
import np_eaxmple as np

df = pd.read_csv("SEC_TS.csv", encoding="CP949", parse_dates=['년/월/일'], thousands=",")
df = df.sort_values("년/월/일").head(25)

x = df['년/월/일'].to_numpy()
y = df['종가'].to_numpy()
y2 = df['종가'].ewm(alpha=0.2).mean() # 지수평할법
y2 = y2.to_numpy()
plt.plot(x, y, x, y2)
#plt.show()
print(y2)
print("MAE", mean_absolute_error(y,y2))

y_true = y
y_pred = y2
mape = np.mean(np.abs((y_true - y_pred) / y_true)) * 100
print("MAPE", mape)

autocorr = df['종가'].autocorr()
print("autocorr", autocorr)