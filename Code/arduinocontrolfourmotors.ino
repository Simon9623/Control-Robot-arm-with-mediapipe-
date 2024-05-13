#include <Servo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575 // this is the 'maximum' pulse length count (out of 4096)

void setup() {
    servo1.attach(8);
    servo2.attach(9);
    servo3.attach(10);
    servo4.attach(11);
    
    Serial.begin(115200);
    Serial.setTimeout(10);
}

void loop() {
    while (Serial.available() == 0) {}

    String data = Serial.readStringUntil('\n');
    if (data.length() > 0) {
        // 解析CSV格式的数据
        int angles[4];
        int index = 0;
        char *ptr = strtok((char *)data.c_str(), ",");
        while (ptr != NULL && index < 4) {
            angles[index++] = atoi(ptr);
            ptr = strtok(NULL, ",");
        }

        // 输出值到各个舵机
        servo1.write(angles[0]);
        servo2.write(angles[1]);
        servo3.write(angles[2]);
        servo4.write(angles[3]);

        // 打印接收到的数据
        Serial.print("Received data: ");
        Serial.println(data);
    }
}