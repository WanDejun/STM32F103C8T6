# -*- coding: utf-8 -*-

# 导入包
import numpy as np
from PIL import Image

for cnt in range(1, 2191):
    # 读取图片，并转为数组
    im = np.array(Image.open(f"Image/Image{cnt}.jpg").convert('L'))

    file = open(f'Image_Encode/Image{cnt}', 'w')

    for i in range(8):
        for j in range(128):
            n = 0
            for k in range(8):
                if (im[i * 8 + k][j] >= 128):
                    n += 1 << k
            file.write("0x" + format(n, 'x') + ' ')
        file.write('\n')

    file.close()
