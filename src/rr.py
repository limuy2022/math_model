import pandas as pd
import matplotlib.pyplot as plt
import basic

def main():
    basic.prepare("/home/limuy/桌面/ECA_blend_rr/RR_STAID000011.txt", "rr", 15)
    data = pd.read_csv("tmprr.csv")
    # print(data.head(10))
    # print(data.columns)
    x = data["DATE"]
    y = data["RR"]
    plt.title("降水量")
    plt.xlabel("1960年起的天数除以30")
    plt.ylabel("降水量/mm")
    plt.plot(x, y)
    plt.show()

if __name__ == '__main__':
    main()
