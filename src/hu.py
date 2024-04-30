import pandas as pd
import matplotlib.pyplot as plt
import basic

def main():
    basic.prepare("/home/limuy/桌面/ECA_blend_hu/HU_STAID000011.txt", "HU", 10)
    data = pd.read_csv("tmphu.csv")
    # print(data.head(10))
    # print(data.columns)
    x = data["DATE"]
    y = data["HU"]
    plt.title("湿度")
    plt.xlabel("1960年起的天数除以30")
    plt.ylabel("湿度")
    plt.plot(x, y)
    plt.show()

if __name__ == '__main__':
    main()
