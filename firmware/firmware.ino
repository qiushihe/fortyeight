#define LOG_TO_SERIAL false
#define LOOP_DELAY 6
#define DUPLICATE_THRESHOLD 65

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

#define KEY_EMPTY 0
#define KEY_FN1 0
#define KEY_FN2 0

unsigned int layers[3][4][14] = {
  {
    {KEY_ESC, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, KEY_LEFT_BRACE, KEY_RIGHT_BRACE, KEY_BACKSPACE},
    {KEY_TAB, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON, KEY_QUOTE, KEY_ENTER, KEY_EMPTY},
    {KEY_LEFT_SHIFT, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M, KEY_COMMA, KEY_PERIOD, KEY_SLASH, KEY_UP, KEY_FN2, KEY_EMPTY},
    {KEY_LEFT_CTRL, KEY_LEFT_ALT, KEY_LEFT_GUI, KEY_EMPTY, KEY_EMPTY, KEY_SPACE, KEY_EMPTY, KEY_EMPTY, KEY_EMPTY, KEY_FN1, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_EMPTY}
  },
  {
    {KEY_TILDE, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, KEY_MINUS, KEY_EQUAL, KEY_BACKSLASH},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, KEY_EMPTY},
    {KEY_LEFT_SHIFT, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, KEY_FN2, KEY_EMPTY},
    {KEY_LEFT_CTRL, KEY_LEFT_ALT, KEY_LEFT_GUI, KEY_EMPTY, KEY_EMPTY, KEY_SPACE, KEY_EMPTY, KEY_EMPTY, KEY_EMPTY, KEY_FN1, 0, 0, 0, KEY_EMPTY}
  },
  {
    {0, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_MEDIA_EJECT},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, KEY_EMPTY},
    {KEY_CAPS_LOCK, 0, 0, 0, 0, 0, 0, 0, 0, 0, KEY_MEDIA_PLAY_PAUSE, KEY_MEDIA_VOLUME_INC, KEY_FN2, KEY_EMPTY},
    {KEY_LEFT_CTRL, KEY_LEFT_ALT, KEY_LEFT_GUI, KEY_EMPTY, KEY_EMPTY, KEY_SPACE, KEY_EMPTY, KEY_EMPTY, KEY_EMPTY, KEY_FN1, KEY_MEDIA_PREV_TRACK, KEY_MEDIA_VOLUME_DEC, KEY_MEDIA_NEXT_TRACK, KEY_EMPTY}
  }
};

unsigned short int keyState[4][14] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

unsigned short int keyPressTime[4][14] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

unsigned short int keyStateWas[4][14] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

unsigned short int keyLayerWas[4][14] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int getRowPin(unsigned int row) {
  int rowPin = 0;
  if (row == 1) rowPin = PIN_ROW1;
  if (row == 2) rowPin = PIN_ROW2;
  if (row == 3) rowPin = PIN_ROW3;
  if (row == 4) rowPin = PIN_ROW4;
  return rowPin;
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

void sendKeyDown(int layer, int row, int column) {
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

void sendKeyUp(int layer, int row, int column) {
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

  switch (column) {
    case 1: return digitalWrite(PIN_COLUMN1, LOW);
    case 2: return digitalWrite(PIN_COLUMN2, LOW);
    case 3: return digitalWrite(PIN_COLUMN3, LOW);
    case 4: return digitalWrite(PIN_COLUMN4, LOW);
    case 5: return digitalWrite(PIN_COLUMN5, LOW);
    case 6: return digitalWrite(PIN_COLUMN6, LOW);
    case 7: return digitalWrite(PIN_COLUMN7, LOW);
    case 8: return digitalWrite(PIN_COLUMN8, LOW);
    case 9: return digitalWrite(PIN_COLUMN9, LOW);
    case 10: return digitalWrite(PIN_COLUMN10, LOW);
    case 11: return digitalWrite(PIN_COLUMN11, LOW);
    case 12: return digitalWrite(PIN_COLUMN12, LOW);
    case 13: return digitalWrite(PIN_COLUMN13, LOW);
    case 14: return digitalWrite(PIN_COLUMN14, LOW);
  }
}

void setup() {
  pinMode(PIN_ROW1, INPUT_PULLUP);
  pinMode(PIN_ROW2, INPUT_PULLUP);
  pinMode(PIN_ROW3, INPUT_PULLUP);
  pinMode(PIN_ROW4, INPUT_PULLUP);

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
  unsigned long loopTime = millis();

  unsigned int curRow = 0;
  unsigned int curCol = 0;

  for (curRow = 1; curRow <= 4; curRow++) {
    for (curCol = 1; curCol <= 14; curCol++) {
      // Determine the pin for the current row.
      int curRowPin = getRowPin(curRow);

      // Deactivate all columns other than the current column.
      activateColumn(curCol);

      // A pin is considered "on" if the pin's signal is "low".
      // So here we use `!` to check.
      if (!digitalRead(curRowPin)) {
        keyState[curRow - 1][curCol - 1] = 1;
      } else {
        keyState[curRow - 1][curCol - 1] = 0;
      }

      // Determine the current layer based on Fn key states.
      unsigned int layer = 0;
      if (keyState[3][9] == 1) layer = 1;
      if (keyState[2][12] == 1) layer = 2;

      // If the key was down ...
      if (keyStateWas[curRow - 1][curCol - 1] == 1) {
        // ... and still down ...
        if (keyState[curRow - 1][curCol - 1] == 1) {
          // ... then do nothing (no need to send "press" signal again).
        }
        // ... but is no longer down ...
        else {
          // ... then send the "release" signal ...
          sendKeyUp(keyLayerWas[curRow - 1][curCol - 1], curRow, curCol);

#if LOG_TO_SERIAL
          Serial.print(loopTime);
          Serial.print("] Up: l");
          Serial.print(keyLayerWas[curRow - 1][curCol - 1]);
          Serial.print(" / r");
          Serial.print(curRow);
          Serial.print(" / c");
          Serial.print(curCol);
          Serial.println();
#endif

          // ... and clear the previous states.
          keyPressTime[curRow - 1][curCol - 1] = loopTime;
          keyStateWas[curRow - 1][curCol - 1] = 0;
          keyLayerWas[curRow - 1][curCol - 1] = 0;
        }
      }
      // If the key was up ...
      else {
        // ... but the key is now down ...
        if (keyState[curRow - 1][curCol - 1] == 1) {
          unsigned long keyDeltaTime = loopTime - keyPressTime[curRow - 1][curCol - 1];

          // ... and if delta time is greater than the duplicate detection threshold ...
          if (keyDeltaTime > DUPLICATE_THRESHOLD) {
            // ... then send the "press" signal ...
            sendKeyDown(layer, curRow, curCol);

#if LOG_TO_SERIAL
            Serial.print(loopTime);
            Serial.print("] Down: l");
            Serial.print(layer);
            Serial.print(" / r");
            Serial.print(curRow);
            Serial.print(" / c");
            Serial.print(curCol);
            Serial.print(" / kd");
            Serial.print(loopTime - keyPressTime[curRow - 1][curCol - 1]);
            Serial.println();
#endif
          }

          // ... then update previous state regardless of key delta time.
          // It's important for these updates to happen regardless of the current delta time
          // because if these updates don't happen, a duplicate's delta time would be effectively
          // taken out of the key's total available duplicate detection threshold, and then more
          // duplicates could still potentially happen after the first duplicate. By updating the
          // key's state regardless of delta time, we can prevent duplicates from "eating up" a
          // key's total available duplicate detection time.
          keyPressTime[curRow - 1][curCol - 1] = loopTime;
          keyStateWas[curRow - 1][curCol - 1] = 1;
          keyLayerWas[curRow - 1][curCol - 1] = layer;
        }
        // ... and the key is still up ...
        else {
          // ... then do nothing.
        }
      }
    }
  }

  delay(LOOP_DELAY);
}
