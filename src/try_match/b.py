import pandas as pd
import statsmodels.api as sm
import numpy as np

def gen_data():
    # 列出要合并的CSV文件的路径
    csv_files = ['../tmpcc.csv', '../tmphu.csv', '../tmptg.csv', "../tmppp.csv", "../tmpfg.csv"]

    result = None
    # 逐个读取CSV文件并将其合并到result中
    for file in csv_files:
        df = pd.read_csv(file)
        if result is None:
            result = df
        else:
            result = pd.merge(result, df, on='DATE')

    # 保存合并后的结果到新的CSV文件
    result.to_csv('merged_data_file.csv', index=False)

def main():
    gen_data()
    # 读取数据
    data = pd.read_csv('merged_data_file.csv')
    y_data = pd.read_csv("../tmprr.csv")
    y_data = y_data['RR'].values
    data_numpy = data.to_numpy()
    print(data_numpy)
    data_without_first_column = data_numpy[:, 1:]
    print(data_without_first_column)
    # 创建线性回归模型
    model = sm.OLS(y_data, data_without_first_column)
    res = model.fit()
    p = res.predict(data_without_first_column)
    cnt = 0
    for i in range(len(y_data)):
        if abs(p[i] - y_data[i]) < 10:
            cnt += 1
    print("rate:", cnt / len(y_data))
    print(res.params, )
    # print(res.summary())

if __name__ == '__main__':
    main()
