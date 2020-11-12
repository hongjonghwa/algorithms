import numpy as np
from scipy import stats

np.random.seed(42)

heights = np.random.normal(loc=180, scale=5, size=20)
print("heights data", heights, heights.mean(), heights.var(ddof=1), heights.var(ddof=1) ** (1 / 2))

print("# 1-Sample T-test(단일 표본 t-검정)")
result = stats.ttest_1samp(heights, 175) # H0 => 평균이 175
print("result:", result)
print("result: {:f} {:f}".format(result.statistic, result.pvalue))

print("# Unpaired T-test(독립 표본 t-검정)") # paired t-test 는 scipy.stats.ttest_rel(a, b)
heights1 = np.random.normal(loc=170, scale=5, size=20)
heights2 = np.random.normal(loc=175, scale=10, size=30)
tTestResult = stats.ttest_ind(heights1, heights2) # H0 => 두 집단의 키가 같다.
print("result:", tTestResult)


print("# Paired T-test(대응 표본 t-검정)")
before = [170 + np.random.normal(0,5) for _ in range(20)]
after = before + np.random.random(size=20)

tTestResult = stats.ttest_rel(before, after) # H0 => 대응된 2 표본에 유의미한 차이가 없다
print("result:", tTestResult)
print("The T-statistic is {:f} and the p-value is {:.3f}".format(tTestResult.statistic, tTestResult.pvalue))
print("The T-statistic is %.3f and the p-value is %.3f" % tTestResult)

print("# 통계량으로 T-검정")
tTestResult = stats.ttest_ind_from_stats(170,5,50, 175,10,20)
print("result:", tTestResult)

# The T-statistic 는 두 집단의 차를 표준오차로 나눈 값. 즉, [표준오차]와 [표본평균사이의 차이]의 비율