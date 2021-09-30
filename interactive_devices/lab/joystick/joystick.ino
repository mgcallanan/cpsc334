int JoyStick_X = A6; // Analog Pin  X

int JoyStick_Y = A7; // // Analog Pin  Y

int JoyStick_button = 32; // IO Pin

void setup()

{

    pinMode(JoyStick_X, INPUT);

    pinMode(JoyStick_Y, INPUT);

    pinMode(JoyStick_button, INPUT_PULLUP);

    Serial.begin(115200);

}

void loop()

{

    int x, y, button;

    x = analogRead(JoyStick_X); //  X

    y = analogRead(JoyStick_Y); //  Y

    button = digitalRead(JoyStick_button); // 

    x = map(x, 0, 1023, -512, 512);

    y = map(y, 0, 1023, 512, -512);

    

    Serial.print("X : ");

    Serial.print(x, DEC);

    Serial.print(" / Y : ");

    Serial.print(y, DEC);

    Serial.print(" , B : ");

    Serial.println(button, DEC);

    delay(100);

}
