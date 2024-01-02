cnt = 28
file = open(f'Image_Encode/Image{cnt}', 'r')
array = list(map(lambda x: int(x, 16), file.read().split()))
print("LED_ON!\n".encode('utf-8'))
