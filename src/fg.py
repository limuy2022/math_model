import pandas as pd
import matplotlib.pyplot as plt
import basic

def main():
    basic.prepare("/home/limuy/桌面/ECA_blend_fg/FG_STAID000011.txt", "FG", 30)
    data = pd.read_csv("tmpfg.csv")
    # print(data.head(10))
    # print(data.columns)
    x = data["DATE"]
    y = data["FG"]
    plt.plot(x, y)
    plt.title("风速")
    plt.xlabel("1960年起的天数除以30")
    plt.ylabel("风速/0.1m*s^-1")
    plt.show()

if __name__ == '__main__':
    main()
