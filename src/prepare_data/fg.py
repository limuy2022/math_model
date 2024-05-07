import basic
import matplotlib.pyplot as plt
import pandas as pd


def main():
    basic.prepare("../data/FG_STAID000011.txt", "FG", 30)
    data = pd.read_csv("../tmpfg.csv")
    # print(data.head(10))
    # print(data.columns)
    x = data["DATE"].head(12 * 10)
    y = data["FG"].head(10 * 12)
    plt.plot(x, y)
    plt.title("Wind Speed")
    plt.ylabel("Wind Speed/0.1m*s^-1")
    # plt.show()
    plt.savefig("fg.png")


if __name__ == "__main__":
    main()
