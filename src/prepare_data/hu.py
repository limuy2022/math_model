import basic
import matplotlib.pyplot as plt
import pandas as pd


def main():
    basic.prepare("../data/HU_STAID000011.txt", "HU", 30)
    data = pd.read_csv("../tmphu.csv")
    # print(data.head(10))
    # print(data.columns)
    x = data["DATE"]
    y = data["HU"]
    plt.title("Humidity")
    plt.ylabel("Humidity/0.1%")
    plt.plot(x, y)
    # plt.show()
    plt.savefig("hu.png")


if __name__ == "__main__":
    main()
