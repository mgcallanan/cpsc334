int JoyStick_X = 34; // Analog Pin  X

int JoyStick_Y = 35; // // Analog Pin  Y

int JoyStick_button = 32; // IO Pin

int toggle = 33; // Toggle IO Pin

int push_button = 27; // Push Button IO Pin

void setup()

{

    pinMode(JoyStick_X, INPUT);

    pinMode(JoyStick_Y, INPUT);

    pinMode(JoyStick_button, INPUT_PULLUP);

    pinMode(toggle, INPUT);
    
    pinMode(push_button, INPUT);

    Serial.begin(115200);

}

void loop()

{

    int x, y, button, toggle_input, push_button_input;

    x = analogRead(JoyStick_X); //  X

    y = analogRead(JoyStick_Y); //  Y

    button = digitalRead(JoyStick_button); // joystick switch

    toggle_input = digitalRead(toggle); // toggle button

    push_button_input = digitalRead(push_button); // push button

    x = map(x, 0, 4095, -512, 512);

    y = map(y, 0, 4095, 512, -512);

    

    Serial.print("X : ");

    Serial.print(x, DEC);

    Serial.print(" / Y : ");

    Serial.print(y, DEC);

    Serial.print(" , B : ");

    Serial.print(button, DEC);

    Serial.print(" , TOG : ");

    Serial.print(toggle_input, DEC);

    Serial.print(" , PB : ");

    Serial.println(push_button_input, DEC);

    delay(100);

}
