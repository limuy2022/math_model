import basic
import matplotlib.pyplot as plt
import pandas as pd


def main():
    basic.prepare("../data/RR_STAID000011.txt", "rr", 30)
    data = pd.read_csv("../tmprr.csv")
    # print(data.head(10))
    # print(data.columns)
    x = data["DATE"].head(10 * 12)
    y = data["RR"].head(10 * 12)
    plt.title("Rainfall")
    plt.ylabel("Rainfall/mm")
    plt.plot(x, y)
    # plt.show()
    plt.savefig("rr.png")


if __name__ == "__main__":
    main()
