#include "led-matrix.h"

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
    interrupt_received = true;
}

static void DrawOnCanvas(Canvas *canvas) {
    canvas->Fill(0, 0, 255);

    int center_x = canvas->width() / 2;
    int center_y = canvas->height() / 2;

    float radius_max = canvas->width() / 2;
    float angle_step = 1.0 / 360;

    for (float a = 0, r = 0; r < center_y; a += angle_step, r += angle_step) {
        if (interrupt_received) {
            return;
        }

        float dot_x = cos(a * 2 * M_PI) * r;
        float dot_y = sin(a * 2 * M_PI) * r;

        canvas->SetPixel(center_x + dot_x, center_y + dot_y, 255, 0, 0);
        // usleep(1 * 1000);
    } 
}

int main(int argc, char **argv) {
    // Set some defaults
    int l = 0;

    RGBMatrix::Options defaults;
    defaults.rows = 16;
    defaults.cols = 32;
    defaults.chain_length = 3;
    defaults.parallel = 3;
    defaults.row_address_type = 0;
    defaults.multiplexing = 8;
    defaults.pwm_lsb_nanoseconds = 90;
    
    rgb_matrix::RuntimeOptions runtime_options;
    runtime_options.gpio_slowdown = 2;

    fprintf(stderr, "%i", l++);

    Canvas *canvas = rgb_matrix::CreateMatrixFromFlags(&argc, &argv, &defaults, &runtime_options);

    fprintf(stderr, "%i", l++);

    // RGBMatrix *matrix = rgb_matrix::CreateMatrixFromFlags(&argc, &argv,
    //                                                         &options,
    //                                                         &runtime_options);
    
    if (canvas == nullptr) {
        PrintMatrixFlags(stderr, defaults, runtime_options);
        return -1;
    }

    fprintf(stderr, "%i", l++);

    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);

    fprintf(stderr, "%i", l++);

    while (!interrupt_received) {
        DrawOnCanvas(canvas);
        canvas->Clear();
    }

    fprintf(stderr, "%i", l++);

    delete canvas;
    // delete matrix;

    return 0;
}