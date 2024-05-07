import basic
import matplotlib.pyplot as plt
import pandas as pd


def main():
    basic.prepare("../data/CC_STAID000011.txt", "CC", 30)
    data = pd.read_csv("../tmpcc.csv")
    # print(data.head(10))
    # print(data.columns)
    x = data["DATE"]
    y = data["CC"]
    plt.plot(x, y)
    plt.title("Cloud Cover")
    plt.ylabel("Cloud Cover/octas")
    # plt.show()
    plt.savefig("cc.png")


if __name__ == "__main__":
    main()
