import sys

from PIL import Image

# this program takes 128 x 28 black and white image, converts it to SSD1306 format (8 bit horizontal),
# and puts output in hex format in "out_hex.txt", that can be used in c ???

input_file = sys.argv[1]

img = Image.open(input_file).convert("1") # load as black and white
pixels = img.load()

out_buffer = []

for page_num in range(0, 4):
    for x_column in range(0,128):
        byte_str = ""
        for page_row in range(0, 8):
            y = (page_num * 8) + page_row
            pixel = pixels[x_column, y]
            byte_str += '1' if pixel == 0 else '0'

        reversed_s = byte_str[::-1]
        hex_str = hex(int(reversed_s, 2))
        out_buffer.append(hex_str)

with open("out_hex.txt", "w") as out_file:
    out_file.write(",".join(out_buffer))