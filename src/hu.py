import pandas as pd
import matplotlib.pyplot as plt
import basic

def main():
    basic.prepare("/home/limuy/桌面/ECA_blend_hu/HU_STAID000011.txt", "HU", 30)
    data = pd.read_csv("tmphu.csv")
    # print(data.head(10))
    # print(data.columns)
    x = data["DATE"]
    y = data["HU"]
    plt.title("Humidity")
    plt.ylabel("Humidity")
    plt.plot(x, y)
    plt.show()

if __name__ == '__main__':
    main()
