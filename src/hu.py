import pandas as pd
import matplotlib.pyplot as plt

def prepare(path):
    with open(path, 'r') as f:
        for i in range(21):
            f.readline()
        with open("tmphu.csv", "w") as ff:
            cnt = 1
            tmp = 0
            ff.write("DATE,HU\n")
            flag = False
            for i in f:
                l = [i.strip() for i in i.split(',')]
                if l[2][:4] != "1998" and not flag:
                    continue
                flag = True
                tmp += int(l[3])
                cnt += 1
                if cnt % 30 == 0:
                    ff.write(f"{int(cnt/30)},{tmp/30}\n")
                    tmp = 0
                if cnt > 365 * 5:
                    break
def main():
    prepare("/home/limuy/桌面/ECA_blend_hu/HU_STAID000036.txt")
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
