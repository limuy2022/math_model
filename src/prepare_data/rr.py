import basic
import matplotlib.pyplot as plt
import pandas as pd


def main():
    basic.prepare("../data/RR_STAID000011.txt", "rr", 30)
    data = pd.read_csv("../tmprr.csv")
    # print(data.head(10))
    # print(data.columns)
    x = data["DATE"]
    y = data["RR"]
    plt.title("Rainfall")
    plt.ylabel("Rainfall/mm")
    plt.plot(x, y)
    plt.show()


if __name__ == "__main__":
    main()
