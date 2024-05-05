import pandas as pd
import matplotlib.pyplot as plt
import basic


def main():
    basic.prepare("/home/limuy/桌面/ECA_blend_tg/TG_STAID000011.txt", "tg", 30)
    data = pd.read_csv("tmptg.csv")
    # print(data.head(10))
    # print(data.columns)
    x = data["DATE"]
    y = data["TG"]
    plt.title("Temperature")
    plt.ylabel("Temperature")
    plt.plot(x, y)
    plt.show()

if __name__ == '__main__':
    main()
