from PIL import Image
from collections import Counter
from scipy.spatial import KDTree
import numpy as np
def hex_to_rgb(num):
    h = str(num)
    return int(h[0:4], 16), int(('0x' + h[4:6]), 16), int(('0x' + h[6:8]), 16)
def rgb_to_hex(num):
    h = str(num)
    return int(h[0:4], 16), int(('0x' + h[4:6]), 16), int(('0x' + h[6:8]), 16)
filename = input("What's the file name? ")
outFile = open("./sprite_bytes/" + filename + '.txt', 'w')
imagename = input("What's the image name? Press Enter when done. ")
while imagename != "":
    new_w, new_h = 16, 16 #map(int, input("What's the new height x width? Like 28 28. ").split(' '))
    palette_hex = ['0x000000', '0xDEDEFF', '0xFF0000', '0xFFB7AE', '0xDE9751', '0xFFB751', '0xFFFF00', '0x00FF00', '0x47B7AE', '0x00FFFF', '0x47B7FF', '0x2121FF', '0xFFB7FF']
    palette_rgb = [hex_to_rgb(color) for color in palette_hex]

    pixel_tree = KDTree(palette_rgb)
    im = Image.open("./sprite_originals/" + imagename+ ".png") #Can be many different formats.
    im = im.convert("RGBA")
    im = im.resize((new_w, new_h),Image.ANTIALIAS) # regular resize
    pix = im.load()
    pix_freqs = Counter([pix[x, y] for x in range(im.size[0]) for y in range(im.size[1])])
    pix_freqs_sorted = sorted(pix_freqs.items(), key=lambda x: x[1])
    pix_freqs_sorted.reverse()
    print(pix)
    outImg = Image.new('RGB', im.size, color='white')
    i = 0
    for y in range(im.size[1]):
        for x in range(im.size[0]):
            pixel = im.getpixel((x,y))
            print(pixel)
            if(pixel[3] < 200):
                outImg.putpixel((x,y), palette_rgb[0])
                outFile.write("%x\n" % (0))
                print(i)
            else:
                index = pixel_tree.query(pixel[:3])[1]
                outImg.putpixel((x,y), palette_rgb[index])
                outFile.write("%x\n" % (index))
            i += 1
    outImg.save("./sprite_converted/" + imagename + ".png")
    imagename = input("What's the image name? Press Enter when done. ")
outFile.close()
