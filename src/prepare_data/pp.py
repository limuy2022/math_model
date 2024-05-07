import basic
import matplotlib.pyplot as plt
import pandas as pd


def main():
    basic.prepare("../data/PP_STAID000011.txt", "pp", 30)
    data = pd.read_csv("../tmppp.csv")
    # print(data.head(10))
    # print(data.columns)
    x = data["DATE"].head(10 * 12)
    y = data["PP"].head(10 * 12)
    plt.title("Pressure")
    plt.ylabel("Pressure/0.1hPa")
    plt.plot(x, y)
    # plt.show()
    plt.savefig("pp.png")


if __name__ == "__main__":
    main()
