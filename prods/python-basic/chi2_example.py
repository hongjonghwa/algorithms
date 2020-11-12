import pandas as pd
from scipy import stats

"""
카이제곱 검정(chi-squared test) 또는 χ2 검정은 카이제곱 분포에 기초한 통계적 방법으로,
관찰된 빈도가 기대되는 빈도와 의미있게 다른지의 여부를 검증하기 위해 사용되는 검증방법이다.
자료가 빈도로 주어졌을 때, 특히 명목척도 자료의 분석에 이용된다.

카이제곱 값은 χ2 = Σ (관측값 - 기댓값)^2 / 기댓값 으로 계산한다.

검증 유형 : 동질성 검증과 독립성 검증 두 유형이 있다.

동질성 검증: '변인의 분포가 이항분포나 정규분포와 동일하다'라는 가설을 설정한다. 
           이는 어떤 모집단의 표본이 그 모집단을 대표하고 있는지를 검증하는 데 사용한다.
독립성 검증: 변인이 두 개 이상일 때 사용되며, 
           기대빈도는 '두 변인이 서로 상관이 없고 독립적'이라고 기대하는 것을 의미하며 
           관찰빈도와의 차이를 통해 기대빈도의 진위여부를 밝힌다.
"""

print("# 적합도(동질성) 검정")
observed, expected = [324, 78, 261], [371, 80, 212]
df = pd.DataFrame([observed, expected], columns=['A', 'B', 'C'], index=['OBS', 'EXP'])
print(df)
statistic, pvalue = stats.chisquare(f_obs=observed, f_exp=expected)  # H0 : 관찰빈도는 기대빈도와 같다
print("statistic:", statistic)
print("pvalue:", pvalue)

print("# 독립성 검정")
observed = [[440, 567, 349, 59], [924, 1311, 794, 102], [258, 311, 157, 19]]
df = pd.DataFrame(observed, columns=['18-29', '30-44', '45-64', '65세 이상'], index=['눈', '코', '목'])

print(df)
statistic, pvalue, dof, expected = stats.chi2_contingency(observed)  # H0 : 두 독립변수가 서로 관련이 없다
print("statistic:", statistic)
print("pvalue:", pvalue) # 0.02 귀무가설 기각, 나이와 진찰받은 부위가 서로 관계가 있다
print("dof:", dof)
print("expected:", expected)
