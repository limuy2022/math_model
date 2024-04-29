import rasterio
import matplotlib.pyplot as plt

# 打开GeoTIFF文件
with rasterio.open('./wc2.1_10m_prec_01.tif') as src:
    # 读取数据
    data = src.read(1)

    # 获取空间坐标信息
    transform = src.transform
    crs = src.crs

# 创建图形
fig, ax = plt.subplots()

# 绘制图像
img = ax.imshow(data, cmap='gray')

# 设置坐标轴
ax.set_xticks([]), ax.set_yticks([])

# 添加坐标轴标签
ax.set_xlabel('X')
ax.set_ylabel('Y')

# 显示图形
plt.show()
