#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <signal.h>
#include <stdlib.h>

#include "led-matrix.h"

#include "Server.h"

using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;


class TestServer: public Server {
    
public:
    TestServer(int port);
    
    void newConnectionCallback(ClientInfo *info);
    void newMessageCallback(TCPMessage *message);
    void clientDisconnected(ClientInfo *info);
};

TestServer::TestServer(int port):Server(port)
{
}

void TestServer::newConnectionCallback(ClientInfo *info) {
    printf("Client Connected!\n");
}
void TestServer::newMessageCallback(TCPMessage *message){
    printf("Message Received: %s\n", message->message);
}
void TestServer::clientDisconnected(ClientInfo *info){
    printf("Client Disconnected!\n");
}

static void DrawOnCanvas(Canvas *canvas) {
    canvas->Fill(0, 0, 255);

    int center_x = canvas->width() / 2;
    int center_y = canvas->height() / 2;
    float radius_max = canvas->width() / 2;
    float angle_step = 1.0 / 360;
    for (float a = 0, r = 0; r < radius_max; a += angle_step, r += angle_step) {
        float dot_x = cos(a * 2 * M_PI) * r;
        float dot_y = sin(a * 2 * M_PI) * r;
        canvas->SetPixel(center_x + dot_x, center_y + dot_y,
                            255, 0, 0);
        usleep(1 * 1000);  // wait a little to slow down things.
    }
}


int main(int argc, char **argv) {
    TestServer *server = new TestServer(12345);

    RGBMatrix::Options defaults;
    // defaults.hardware_mapping = "regular";  // or e.g. "adafruit-hat"
    defaults.rows = 16;
    defaults.cols = 32;
    defaults.chain_length = 3;
    defaults.parallel = 3;
    defaults.row_address_type = 0;
    defaults.multiplexing = 8;
    defaults.pwm_lsb_nanoseconds = 90;
    defaults.brightness = 25;

    rgb_matrix::RuntimeOptions runtime_options;
    runtime_options.gpio_slowdown = 2;

    Canvas *canvas = rgb_matrix::CreateMatrixFromFlags(&argc, &argv, &defaults, &runtime_options);
    if (canvas == NULL)
        return 1;

    while (1) {
        DrawOnCanvas(canvas);
    }

    delete server;
}