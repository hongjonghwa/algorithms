from sklearn.cluster import AgglomerativeClustering
import numpy as np
from matplotlib import pyplot as plt


x = np.array([
    [0, 0],
    [0, 1],
    [1, 1.5],
    [3, 1],
    [3, 3]
])

clustering = AgglomerativeClustering(n_clusters=2, linkage="complete")
clustering.fit(x)
print(clustering.labels_)
# plt.scatter(x= x[:, 0], y = x[:, 1], color=clustering)
plt.scatter(x=x[:, 0], y=x[:, 1], c=clustering.labels_)
plt.show()
