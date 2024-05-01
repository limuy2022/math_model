import pandas as pd
import matplotlib.pyplot as plt
import basic


def main():
    basic.prepare("/home/limuy/桌面/ECA_blend_pp/PP_STAID000011.txt", "pp", 30)
    data = pd.read_csv("tmppp.csv")
    # print(data.head(10))
    # print(data.columns)
    x = data["DATE"]
    y = data["PP"]
    plt.title("气压")
    plt.xlabel("1960年起的天数除以30")
    plt.ylabel("气压")
    plt.plot(x, y)
    plt.show()

if __name__ == '__main__':
    main()
