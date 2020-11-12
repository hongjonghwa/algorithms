import numpy as np

X = np.array([1,5,6,8,9,16,32])

print(X, X.mean(), X.var())

print((X - np.mean(X)) / np.std(X))


