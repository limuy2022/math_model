import basic
import matplotlib.pyplot as plt
import pandas as pd


def main():
    basic.prepare("../data/FG_STAID000011.txt", "FG", 30)
    data = pd.read_csv("../tmpfg.csv")
    # print(data.head(10))
    # print(data.columns)
    x = data["DATE"]
    y = data["FG"]
    plt.plot(x, y)
    plt.title("Wind Speed")
    plt.ylabel("Wind Speed/0.1m*s^-1")
    plt.show()


if __name__ == "__main__":
    main()
