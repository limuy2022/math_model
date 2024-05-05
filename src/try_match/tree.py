import random
import numpy
import pandas as pd
import statsmodels.api as sm
import numpy as np
from matplotlib import pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.tree import export_text, DecisionTreeRegressor
from sklearn.metrics import accuracy_score


def gen_data():
    # 列出要合并的CSV文件的路径
    csv_files = [
        "../tmpcc.csv",
        "../tmphu.csv",
        "../tmptg.csv",
        "../tmppp.csv",
        "../tmpfg.csv",
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


def get_rate2(model, X_train, y_train) -> float:
    y_pred = model.predict(X_train)
    sum_ = 0
    for i in range(len(y_train)):
        sum_ += abs(y_pred[i] - y_train[i])
    return sum_ / len(y_train)


def get_rate1(res, data_without_first_column, y_data):
    p = res.predict(data_without_first_column)
    cnt = 0
    for i in range(len(y_data)):
        if abs(p[i] - y_data[i]) < 10:
            cnt += 1
    return cnt / len(y_data)


def draw(X_data, actual, fit):
    plt.plot(X_data, fit, label="Fitted")
    plt.plot(X_data, actual, label="Actual", color="red")
    plt.legend()
    plt.xlabel("x")
    plt.ylabel("y")
    plt.show()


def main():
    gen_data()
    # 读取数据
    data = pd.read_csv("merged_data_file.csv")
    y_data = pd.read_csv("../tmprr.csv")
    y_data = y_data["RR"].values
    data_numpy = data.to_numpy()
    print(data_numpy)
    data_without_first_column = data_numpy[:, 1:]
    print(data_without_first_column)
    X_train, X_test, y_train, y_test = train_test_split(
        data_without_first_column, y_data, test_size=0.2, random_state=42
    )
    # 创建线性回归模型
    model = DecisionTreeRegressor()
    res = model.fit(X_train, y_train)

    print("train rate:", get_rate1(res, data_without_first_column, y_data))
    print("train rate2:", get_rate2(res, data_without_first_column, y_data))
    test_data_num = int(len(data_without_first_column) * 0.2)
    test_idx = np.random.choice(
        len(data_without_first_column), test_data_num, replace=False
    )
    test_x = data_without_first_column[test_idx]
    test_y = y_data[test_idx]
    print("test rate:", get_rate1(res, test_x, test_y))
    print("test rate2:", get_rate2(res, test_x, test_y))
    with open("final.txt", "w") as f:
        f.write(export_text(res, feature_names=["cc", "hu", "tg", "pp", "fg"]))
    draw(range(len(test_x)), test_y, res.predict(test_x))
    # print(res.summary())


if __name__ == "__main__":
    main()
