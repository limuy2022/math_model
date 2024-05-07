import basic
import matplotlib.pyplot as plt
import pandas as pd


def main():
    basic.prepare("../data/TG_STAID000011.txt", "tg", 30)
    data = pd.read_csv("../tmptg.csv")
    # print(data.head(10))
    # print(data.columns)
    x = data["DATE"]
    y = data["TG"]
    plt.title("Temperature")
    plt.ylabel("Temperature/0.1°C")
    plt.plot(x, y)
    plt.show()


if __name__ == "__main__":
    main()
