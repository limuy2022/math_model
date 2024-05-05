import pandas as pd
import statsmodels.api as sm
import numpy as np
from statsmodels.tsa.vector_ar.var_model import VAR


def gen_data():
    # 列出要合并的CSV文件的路径
    csv_files = [
        "../tmpcc.csv",
        "../tmphu.csv",
        "../tmptg.csv",
        "../tmppp.csv",
        "../tmpfg.csv",
        "../tmprr.csv",
    ]

    result = None
    # 逐个读取CSV文件并将其合并到result中
    for file in csv_files:
        df = pd.read_csv(file)
        if result is None:
            result = df
        else:
            result = pd.merge(result, df, on="DATE")

    # 保存合并后的结果到新的CSV文件
    result.to_csv("merged_data_file.csv", index=False)


def main():
    gen_data()
    # 读取数据
    data = pd.read_csv("merged_data_file.csv")
    # y_data = pd.read_csv("../tmprr.csv")
    # y_data = y_data['RR'].values
    data_numpy = data.to_numpy()
    # print(data_numpy)
    data_without_first_column = data_numpy[:, 1:]
    # print(data_without_first_column)
    # 创建线性回归模型
    model = VAR(
        data_without_first_column,
    )
    res = model.fit()
    # p = res.predict(data_without_first_column)
    # cnt = 0
    # for i in range(len(y_data)):
    #     if abs(p[i] - y_data[i]) < 10:
    #         cnt += 1
    # print("rare:", cnt / len(y_data))
    forecast = res.forecast(res.y, steps=2)

    # 获取实际数据
    actual_data = data["Temperature"].iloc[-2:].values

    # 计算RMSE
    rmse = np.sqrt(np.mean((forecast - actual_data) ** 2))
    print(
        res.params,
    )
    print(res.summary())


if __name__ == "__main__":
    main()
