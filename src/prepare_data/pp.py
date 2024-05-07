import basic
import matplotlib.pyplot as plt
import pandas as pd


def main():
    basic.prepare("../data/PP_STAID000011.txt", "pp", 30)
    data = pd.read_csv("../tmppp.csv")
    # print(data.head(10))
    # print(data.columns)
    x = data["DATE"]
    y = data["PP"]
    plt.title("Pressure")
    plt.ylabel("Pressure/0.1hPa")
    plt.plot(x, y)
    plt.show()


if __name__ == "__main__":
    main()
