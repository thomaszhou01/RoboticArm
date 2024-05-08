#include <AccelStepper.h>
#include <Arduino.h>
#include <Servo.h>

#define MotorInterfaceType 4

// put function declarations here:
Servo servo1;
Servo servo2;
AccelStepper stepper(MotorInterfaceType, 4, 6, 5, 7);
const int controller_X = 0;
const int controller_Y = 1;
const int arm_length = 73;  // mm

int x = 0;
int y = 0;
int rotation = 0;

void setup() {
    Serial.begin(9600);
    // put your setup code here, to run once:
    servo1.attach(9);
    servo2.attach(8);
    stepper.setMaxSpeed(3000.0);
    stepper.setAcceleration(100.0);
    stepper.setSpeed(400);
    pinMode(10, INPUT);
    pinMode(11, INPUT);
}

void loop() {
    if (analogRead(controller_X) / 512.0 > 1.2) {
        x++;
    } else if (analogRead(controller_X) / 512.0 < 0.8) {
        x--;
    }

    if (analogRead(controller_Y) / 512.0 < 0.8) {
        y++;
    } else if (analogRead(controller_Y) / 512.0 > 1.2) {
        y--;
    }

    double length = sqrt(x * x + y * y);
    double phi = atan2(y, x) * 180.0 / PI;
    double theta = acos((length / 2) / arm_length) * 180.0 / PI;

    servo1.write(180 - (phi + theta));
    servo2.write(2 * theta);

    // if (stepper.distanceToGo() == 0)
    // stepper.moveTo(-stepper.currentPosition());

    // // Move the motor one step
    // stepper.run();

    // Serial.print("X-axis: ");
    // Serial.print(phi + theta);
    // Serial.print(" | ");
    // Serial.print("Y-axis: ");
    // Serial.print(phi - theta);
    // Serial.print(" | ");
    // Serial.print(x);
    // Serial.print(" | ");
    // Serial.print(y);
    // Serial.print(" | ");
    // Serial.print(180 - (phi + theta));
    // Serial.print(" | ");
    // Serial.println(2 * theta);
    delay(5);
}
