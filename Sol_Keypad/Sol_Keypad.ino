#include <Keypad.h>
#include <Keyboard.h> // used in order to make the device act like a literal keyboard would.

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns

char keys[ROWS][COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3};    //connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup()
{
    Serial.begin(9600);
    Serial.println("Jello Whirled!\n");

    keypad.addEventListener(keypadEvent);
}

void loop()
{
    char key = keypad.getKey();
    if (key)
    {
      /*Case declaration for each key. I don't think this can get any more efficent as we may need the ability to switch the function of a key if we want to.
      This will asign a key to press for each key. Again, im not aware of a method to do this any better without the keyboard lib to act as a keyboard.*/
      switch (key) {
      case '1': 
        Keyboard.press(KEY_KP_7); break;
      case '2':
        Keyboard.press(KEY_KP_8); break;
      case '3':
        Keyboard.press(KEY_KP_9); break;
      case '4':
        Keyboard.press(KEY_KP_4); break;
      case '5':
        Keyboard.press(KEY_KP_5); break;
      case '6':
        Keyboard.press(KEY_KP_6); break;
      case '7':
        Keyboard.press(KEY_KP_1); break;
      case '8':
        Keyboard.press(KEY_KP_2); break;
      case '9':
        Keyboard.press(KEY_KP_3); break;
      case '0':
        Keyboard.press(KEY_KP_DOT); break;
      case '*': 
        Keyboard.press(KEY_KP_0); break;
      case '#':
        Keyboard.press(KEY_KP_ENTER); break;
    }
    }

    // service the keystroke machine
    keystrokeMachine();
}

bool keyMachineActive;
char theCharacter;
bool holdingLinePrinted = false;

void keystrokeMachine()
{
    if (!keyMachineActive)
    {
        holdingLinePrinted = false; // Reset the flag when not active
        Keyboard.releaseAll();
        return;
    }

    if (!holdingLinePrinted)
    {
        Serial.print("Holding character: ");
        Serial.println(theCharacter);
        holdingLinePrinted = true; // Set the flag once the line is printed
    }
}

void keypadEvent(KeypadEvent key)
{
    switch (keypad.getState())
    {
    case PRESSED:
        Serial.print("Pressed character: ");
        Serial.println(theCharacter);
        keyMachineActive = true;
        theCharacter = key;
        break;

    case RELEASED:
        Serial.print("Released character: ");
        Serial.println(theCharacter);
        keyMachineActive = false;
        break;

    case HOLD:
        break;
    }
}
