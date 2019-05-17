import sys
import os
from time import sleep
from math import cos, sin, pi

sys.path.append(os.path.abspath('/home/pi/scoreboard/scoreboard'))
from rgbmatrix import RGBMatrix, RGBMatrixOptions, graphics

from samplebase import SampleBase

class test_class:#(SampleBase):
    def __init__(self, *args, **kwargs):
        self.o = RGBMatrixOptions()
        self.o.rows = 16
        self.o.cols = 32
        self.o.chain_length = 3
        self.o.parallel = 3
        self.o.multiplexing = 8
        self.o.row_address_type = 0
        self.o.pwm_lsb_nanoseconds = 90
        self.o.brightness = 1
        self.matrix = RGBMatrix(options=self.o)
        # super(test_class, self).__init__(*args, **kwargs)

    def run(self):
        print "Running Test!"

        canvas = self.matrix.CreateFrameCanvas()
        for y in range(self.matrix.height):
            for x in range(self.matrix.width):
                canvas.SetPixel(x,y,255,255,255)
                print "(%i, %i)" % (x, y)
                canvas = self.matrix.SwapOnVSync(canvas)

    def b_test(self):
        canvas = self.matrix.CreateFrameCanvas()
        canvas.Fill(255,255,255)
        while True:
            self.matrix.brightness = self.matrix.brightness + 1
            canvas.Fill(255,255,255)
            print str(self.matrix.brightness) + "%"
            canvas = self.matrix.SwapOnVSync(canvas)
            sleep(1)


if __name__ == "__main__":
    test = test_class()
    # test.run()
    test.b_test()
    # if not test.process():
    #     test.print_help()
