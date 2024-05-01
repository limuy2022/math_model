import pandas as pd
import matplotlib.pyplot as plt
import basic

def main():
    basic.prepare("/home/limuy/桌面/ECA_blend_cc/CC_STAID000011.txt", "CC", 15)
    data = pd.read_csv("tmpcc.csv")
    # print(data.head(10))
    # print(data.columns)
    x = data["DATE"]
    y = data["CC"]
    plt.plot(x, y)
    plt.title("云层覆盖")
    plt.xlabel("1960年起的天数除以30")
    plt.ylabel("云层覆盖")
    plt.show()

if __name__ == '__main__':
    main()
