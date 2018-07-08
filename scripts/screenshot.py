"""Screen-shot generator for RT soldering pen"""

import argparse
import struct
import PIL.Image
import PIL.ImageOps
import swd

SRAM_START = 0x20000000
SRAM_SIZE = 4096

WIDTH = 128
HEIGHT = 32
WORD_SIZE = 8

FB_MAGIC_WORD = b'FB:'
FB_SIZE = WIDTH * HEIGHT // WORD_SIZE
FB_OFFSET = 1

def find_framebuffer(memory, magic_word, offset, size):
    """Find frame buffer in memory

    Arguments:
        memory: bytes of memory image
        magic_word: bytes or string with magic word
        offset: offset after magic_word where begin frame buffer
        size: size of frame buffer
    Return:
        return array of bytes of frame buffer
        """
    fb_start = memory.find(magic_word)
    fb_offset = fb_start + len(magic_word) + offset
    return memory[fb_offset:fb_offset + size]

def rotate_bytes(fb_input, width, height, height_type='I'):
    """rotate bytes in image"""
    fb_output = [0] * (width * height // 8)
    fb32 = struct.unpack(height_type * width, fb_input)
    x_pos = 0
    for i in fb32:
        y_pos = 0
        while i > 0:
            if i & 1:
                fb_output[(x_pos >> 3) + y_pos * (width >> 3)] |= 0x80 >> (x_pos & 7)
            i >>= 1
            y_pos += 1
        x_pos += 1
    return bytes(fb_output)

def main():
    """Read whole SRAM"""
    parser = argparse.ArgumentParser()
    parser.add_argument('file', help='file name to save screen-shot')
    parser.add_argument("-z", "--zoom", type=int, default=1, help="zoom picture multiplicator")
    parser.add_argument("-b", "--border", type=int, default=0, help="add border around screenshot")
    args = parser.parse_args()
    print(args)
    dev = swd.Swd()
    memory = bytes(dev.read_mem(SRAM_START, SRAM_SIZE))
    frame_buffer = find_framebuffer(memory, FB_MAGIC_WORD, FB_OFFSET, FB_SIZE)
    frame_buffer = rotate_bytes(frame_buffer, WIDTH, HEIGHT)
    img = PIL.Image.frombytes('1', (WIDTH, HEIGHT), frame_buffer, 'raw')
    if args.border > 0:
        img = PIL.ImageOps.expand(img, args.border)
    if args.zoom > 1:
        img = img.resize((img.width * args.zoom, img.height * args.zoom))
    img.save(args.file)

main()
