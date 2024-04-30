import statsmodels.api as sm
import numpy as np

# 准备数据
X = np.array([[1, 2], [3, 4], [5, 6]])
y = np.array([2, 4, 6])

# 创建线性回归模型
model = sm.OLS(y, X)

# 拟合模型
results = model.fit()

# 获取数学函数的结果
predictions = results.predict(X)

collects = results.params

# 打印预测结果
print(predictions, collects)