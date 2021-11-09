#define LOG_TO_SERIAL false

#define PIN_ROW1 PIN_F0
#define PIN_ROW2 PIN_F1
#define PIN_ROW3 PIN_F4
#define PIN_ROW4 PIN_F5

#define PIN_COLUMN1 PIN_B0
#define PIN_COLUMN2 PIN_B1
#define PIN_COLUMN3 PIN_B2
#define PIN_COLUMN4 PIN_B3
#define PIN_COLUMN5 PIN_B7
#define PIN_COLUMN6 PIN_D0
#define PIN_COLUMN7 PIN_D1
#define PIN_COLUMN8 PIN_D2
#define PIN_COLUMN9 PIN_D3
#define PIN_COLUMN10 PIN_C6
#define PIN_COLUMN11 PIN_C7
#define PIN_COLUMN12 PIN_D7
#define PIN_COLUMN13 PIN_B4
#define PIN_COLUMN14 PIN_B5

#define KEY_STATE_DOWN 1
#define KEY_STATE_UP 0

#define LAYER_ZERO 0
#define LAYER_ONE 1
#define LAYER_TWO 2

// The Fn1 and Fn2 keys are not mapped to any acutal key code so their real values are just `0`.
// But still define macros for them so they're easier to spot in the key maps below.
#define KEY_FN1 0
#define KEY_FN2 0

unsigned int layers[3][4][14] = {
  {
    {KEY_ESC, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, KEY_LEFT_BRACE, KEY_RIGHT_BRACE, KEY_BACKSPACE},
    {KEY_TAB, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON, KEY_QUOTE, KEY_ENTER, 0},
    {KEY_LEFT_SHIFT, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M, KEY_COMMA, KEY_PERIOD, KEY_SLASH, KEY_UP, KEY_FN2, 0},
    {KEY_LEFT_CTRL, KEY_LEFT_ALT, KEY_LEFT_GUI, 0, 0, KEY_SPACE, 0, 0, 0, KEY_FN1, KEY_LEFT, KEY_DOWN, KEY_RIGHT, 0}
  },
  {
    {KEY_TILDE, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, KEY_MINUS, KEY_EQUAL, KEY_BACKSLASH},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {KEY_LEFT_SHIFT, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, KEY_FN2, 0},
    {KEY_LEFT_CTRL, KEY_LEFT_ALT, KEY_LEFT_GUI, 0, 0, KEY_SPACE, 0, 0, 0, KEY_FN1, 0, 0, 0, 0}
  },
  {
    {0, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_MEDIA_EJECT},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {KEY_CAPS_LOCK, 0, 0, 0, 0, 0, 0, 0, 0, 0, KEY_MEDIA_PLAY_PAUSE, KEY_MEDIA_VOLUME_INC, KEY_FN2, 0},
    {KEY_LEFT_CTRL, KEY_LEFT_ALT, KEY_LEFT_GUI, 0, 0, KEY_SPACE, 0, 0, 0, KEY_FN1, KEY_MEDIA_PREV_TRACK, KEY_MEDIA_VOLUME_DEC, KEY_MEDIA_NEXT_TRACK, 0}
  }
};

unsigned int keyState[4][14] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

unsigned int keyStateWas[4][14] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

unsigned int keyLayerWas[4][14] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

unsigned int getLayer(unsigned int state[4][14]) {
  unsigned int layer = LAYER_ZERO;
  if (state[3][9] == KEY_STATE_DOWN) layer = LAYER_ONE;
  if (state[2][12] == KEY_STATE_DOWN) layer = LAYER_TWO;
  return layer;
}

unsigned int getMediaKey(unsigned int key) {
  if (key == KEY_MEDIA_PLAY_PAUSE) return KEY_MEDIA_PLAY_PAUSE;
  if (key == KEY_MEDIA_PREV_TRACK) return KEY_MEDIA_PREV_TRACK;
  if (key == KEY_MEDIA_NEXT_TRACK) return KEY_MEDIA_NEXT_TRACK;
  if (key == KEY_MEDIA_VOLUME_INC) return KEY_MEDIA_VOLUME_INC;
  if (key == KEY_MEDIA_VOLUME_DEC) return KEY_MEDIA_VOLUME_DEC;
  if (key == KEY_MEDIA_EJECT) return KEY_MEDIA_EJECT;
  return 0;
}

unsigned int getModifierKey(unsigned int key) {
  if (key == KEY_LEFT_SHIFT || key == KEY_RIGHT_SHIFT) return MODIFIERKEY_SHIFT;
  if (key == KEY_LEFT_CTRL || key == KEY_RIGHT_CTRL) return MODIFIERKEY_CTRL;
  if (key == KEY_LEFT_ALT || key == KEY_RIGHT_ALT) return MODIFIERKEY_ALT;
  if (key == KEY_LEFT_GUI || key == KEY_RIGHT_GUI) return MODIFIERKEY_GUI;
  return 0;
}

bool isKeyDown(unsigned int row, unsigned int column) {
  int rowPin = 0;
  if (row == 1) rowPin = PIN_ROW1;
  if (row == 2) rowPin = PIN_ROW2;
  if (row == 3) rowPin = PIN_ROW3;
  if (row == 4) rowPin = PIN_ROW4;

  // A pin is considered "on" (i.e. it's associated with a switch that is pressed down) if
  // the pin's signal is "low". So here we use `!` to check.
  return !digitalRead(rowPin);
}

void sendKeyDown(unsigned int layer, unsigned int row, unsigned int column) {
  unsigned int key = layers[layer][row - 1][column - 1];
  unsigned int modifier = getModifierKey(key);
  unsigned int media = getMediaKey(key);

  if (media) {
    Keyboard.set_media(media);
    Keyboard.send_now();
  } else if (modifier) {
    Keyboard.press(modifier);
  } else if (key) {
    Keyboard.press(key);
  }
}

void sendKeyUp(unsigned int layer, unsigned int row, unsigned int column) {
  unsigned int key = layers[layer][row - 1][column - 1];
  unsigned int modifier = getModifierKey(key);
  unsigned int media = getMediaKey(key);

  if (media) {
    Keyboard.set_media(0);
    Keyboard.send_now();
  } else if (modifier) {
    Keyboard.release(modifier);
  } else if (key) {
    Keyboard.release(key);
  }
}

void activateColumn(unsigned int column) {
  // Setting a line to "high" indicates the line is "off".
  // So here we turn off the lines for all columns except the given column.
  if (column != 1) digitalWrite(PIN_COLUMN1, HIGH);
  if (column != 2) digitalWrite(PIN_COLUMN2, HIGH);
  if (column != 3) digitalWrite(PIN_COLUMN3, HIGH);
  if (column != 4) digitalWrite(PIN_COLUMN4, HIGH);
  if (column != 5) digitalWrite(PIN_COLUMN5, HIGH);
  if (column != 6) digitalWrite(PIN_COLUMN6, HIGH);
  if (column != 7) digitalWrite(PIN_COLUMN7, HIGH);
  if (column != 8) digitalWrite(PIN_COLUMN8, HIGH);
  if (column != 9) digitalWrite(PIN_COLUMN9, HIGH);
  if (column != 10) digitalWrite(PIN_COLUMN10, HIGH);
  if (column != 11) digitalWrite(PIN_COLUMN11, HIGH);
  if (column != 12) digitalWrite(PIN_COLUMN12, HIGH);
  if (column != 13) digitalWrite(PIN_COLUMN13, HIGH);
  if (column != 14) digitalWrite(PIN_COLUMN14, HIGH);

  // Setting a line to "low" indicates the line is "on".
  // So here we only turn on the line for the given column.
  switch (column) {
    case 1: digitalWrite(PIN_COLUMN1, LOW); break;
    case 2: digitalWrite(PIN_COLUMN2, LOW); break;
    case 3: digitalWrite(PIN_COLUMN3, LOW); break;
    case 4: digitalWrite(PIN_COLUMN4, LOW); break;
    case 5: digitalWrite(PIN_COLUMN5, LOW); break;
    case 6: digitalWrite(PIN_COLUMN6, LOW); break;
    case 7: digitalWrite(PIN_COLUMN7, LOW); break;
    case 8: digitalWrite(PIN_COLUMN8, LOW); break;
    case 9: digitalWrite(PIN_COLUMN9, LOW); break;
    case 10: digitalWrite(PIN_COLUMN10, LOW); break;
    case 11: digitalWrite(PIN_COLUMN11, LOW); break;
    case 12: digitalWrite(PIN_COLUMN12, LOW); break;
    case 13: digitalWrite(PIN_COLUMN13, LOW); break;
    case 14: digitalWrite(PIN_COLUMN14, LOW); break;
  }
}

void setup() {
  // Set pins for rows as input pins.
  // This means from this program, we can determine if these pins are on or off.
  pinMode(PIN_ROW1, INPUT_PULLUP);
  pinMode(PIN_ROW2, INPUT_PULLUP);
  pinMode(PIN_ROW3, INPUT_PULLUP);
  pinMode(PIN_ROW4, INPUT_PULLUP);

  // Set pins for columns as output pins.
  // This means from this program, we can manipulate if these pins are on or off.
  pinMode(PIN_COLUMN1, OUTPUT);
  pinMode(PIN_COLUMN2, OUTPUT);
  pinMode(PIN_COLUMN3, OUTPUT);
  pinMode(PIN_COLUMN4, OUTPUT);
  pinMode(PIN_COLUMN5, OUTPUT);
  pinMode(PIN_COLUMN6, OUTPUT);
  pinMode(PIN_COLUMN7, OUTPUT);
  pinMode(PIN_COLUMN8, OUTPUT);
  pinMode(PIN_COLUMN9, OUTPUT);
  pinMode(PIN_COLUMN10, OUTPUT);
  pinMode(PIN_COLUMN11, OUTPUT);
  pinMode(PIN_COLUMN12, OUTPUT);
  pinMode(PIN_COLUMN13, OUTPUT);
  pinMode(PIN_COLUMN14, OUTPUT);

#if LOG_TO_SERIAL
  // Start serial mode.
  Serial.begin(9600);
  // Enable serial output.
  pinMode(11, OUTPUT);
#endif

  // Start keyboard mode.
  Keyboard.begin();
}

void loop() {
  unsigned int curRow = 0;
  unsigned int curCol = 0;

  // Loop over each column ...
  for (curCol = 1; curCol <= 14; curCol++) {
    // ... and turn off all columns except the current column.
    activateColumn(curCol);

    // ... then loop over each row in the current column.
    for (curRow = 1; curRow <= 4; curRow++) {
      // Update key down/up state.
      keyState[curRow - 1][curCol - 1] = isKeyDown(curRow, curCol) ? KEY_STATE_DOWN : KEY_STATE_UP;

      // Determine the current layer based on Fn key states.
      unsigned int layer = getLayer(keyState);

      // If the key was down ...
      if (keyStateWas[curRow - 1][curCol - 1] == KEY_STATE_DOWN) {
        // ... and still down ...
        if (keyState[curRow - 1][curCol - 1] == KEY_STATE_DOWN) {
          // ... then do nothing (no need to send "press" signal again).
        }
        // ... but is no longer down ...
        else {
          // ... then send the "release" signal ...
          sendKeyUp(keyLayerWas[curRow - 1][curCol - 1], curRow, curCol);

#if LOG_TO_SERIAL
          Serial.print("Up:   l");
          Serial.print(keyLayerWas[curRow - 1][curCol - 1]);
          Serial.print(" / r");
          Serial.print(curRow);
          Serial.print(" / c");
          Serial.print(curCol);
          Serial.println();
#endif

          // ... and clear the previous states.
          keyStateWas[curRow - 1][curCol - 1] = KEY_STATE_UP;
          keyLayerWas[curRow - 1][curCol - 1] = LAYER_ZERO;
        }
      }
      // If the key was up ...
      else {
        // ... but the key is now down ...
        if (keyState[curRow - 1][curCol - 1] == KEY_STATE_DOWN) {
          // ... then send the "press" signal ...
          sendKeyDown(layer, curRow, curCol);

#if LOG_TO_SERIAL
          Serial.print("Down: l");
          Serial.print(layer);
          Serial.print(" / r");
          Serial.print(curRow);
          Serial.print(" / c");
          Serial.print(curCol);
          Serial.println();
#endif

          // ... and update key states.
          keyStateWas[curRow - 1][curCol - 1] = KEY_STATE_DOWN;
          keyLayerWas[curRow - 1][curCol - 1] = layer;
        }
        // ... and the key is still up ...
        else {
          // ... then do nothing.
        }
      }
    }

    // This 1ms delay, together with the 1ms delay below are important to prevent an issue
    // where key strokes would randomly duplicate. While I still don't really understand why
    // adding these delay addresses the issue, they nonetheless do.
    delay(1);
  }

  // This 1ms delay, together with the 1ms delay above are important to prevent an issue where
  // key strokes would randomly duplicate. While I still don't really understand why adding
  // these delay addresses the issue, they nonetheless do.
  delay(1);
}
