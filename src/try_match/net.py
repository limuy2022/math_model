import pandas as pd
from keras.src.callbacks import EarlyStopping
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
from tensorflow.keras.layers import Dense, Dropout
import tensorflow
from tensorflow.keras.regularizers import l2

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

def get_rare(model, scaler, X_train, y_train):
    y_pred = model.predict(X_train)
    y_pred = scaler.inverse_transform(y_pred)
    y_train = scaler.inverse_transform(y_train)
    cnt = 0
    for i in range(len(y_train)):
        if abs(y_pred[i] - y_train[i]) < 10:
            cnt += 1
    print("rate:", cnt / len(y_train))

def main():
    gen_data()
    # 读取数据
    data = pd.read_csv('merged_data_file.csv')
    y_data = pd.read_csv("../tmprr.csv")
    y_data = y_data['RR'].values
    data_numpy = data.to_numpy()
    # print(data_numpy)
    data_without_first_column = data_numpy[:, 1:]

    scaler = StandardScaler()
    X_scaled = scaler.fit_transform(data_without_first_column)
    y_scaled = scaler.fit_transform(y_data.reshape(-1, 1))
    X_train, X_test, y_train, y_test = train_test_split(X_scaled, y_scaled, test_size=0.2, random_state=42)
    early_stopping = EarlyStopping(monitor='val_loss', patience=3, restore_best_weights=True)
    model = tensorflow.keras.models.Sequential()
    model.add(Dense(64, activation='relu'))
    # model.add(Dense(64, activation='relu', kernel_regularizer=l2(0.02)))
    model.add(Dropout(0.5))
    model.add(Dense(64, activation='relu', kernel_regularizer=l2(0.02)))
    model.add(Dropout(0.5))
    # model.add(Dense(64, activation='relu'))
    model.add(Dense(50, activation='relu'))
    model.add(Dense(1))

    model.compile(loss='mean_squared_error', optimizer='adam')
    model.fit(X_train, y_train, epochs=300, batch_size=32, validation_data=(X_test, y_test), callbacks=[early_stopping])
    print("train data:", get_rare(model, scaler, X_train, y_train))
    print("test data:", get_rare(model, scaler, X_test, y_test))
    # mse = np.mean((y_test - y_pred) ** 2)
    # print("Mean Squared Error:", mse)


if __name__ == '__main__':
    main()
