#define DEBUG_MODE false
#define DEBOUNCE_SWITCHES true
#define DEBOUNCE_THRESHOLD 10
#define DEBOUNCE_DEBUG_THRESHOLD 1000

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

unsigned short int switchState[4][14] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

elapsedMillis switchUpTime[4][14];
unsigned int switchDebounceTime[4][14] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

unsigned int currentColumn = 1;
unsigned int currentKey1 = 0;
unsigned int currentModifier = 0;

#if DEBUG_MODE
  elapsedMillis currentTime;
  unsigned int lastUp;
#endif

int getCurrentLayer() {
  if (switchState[3][9]) { return 1; }
  if (switchState[2][12]) { return 2; }
  return 0;
}

unsigned int getMediaKey(unsigned int key) {
  if (key == KEY_MEDIA_PLAY_PAUSE) { return KEY_MEDIA_PLAY_PAUSE; }
  if (key == KEY_MEDIA_PREV_TRACK) { return KEY_MEDIA_PREV_TRACK; }
  if (key == KEY_MEDIA_NEXT_TRACK) { return KEY_MEDIA_NEXT_TRACK; }
  if (key == KEY_MEDIA_VOLUME_INC) { return KEY_MEDIA_VOLUME_INC; }
  if (key == KEY_MEDIA_VOLUME_DEC) { return KEY_MEDIA_VOLUME_DEC; }
  if (key == KEY_MEDIA_EJECT) { return KEY_MEDIA_EJECT; }
  return 0;
}

unsigned int getModifierKey(unsigned int key) {
  if (key == KEY_LEFT_SHIFT || key == KEY_RIGHT_SHIFT) { return MODIFIERKEY_SHIFT; }
  if (key == KEY_LEFT_CTRL || key == KEY_RIGHT_CTRL) { return MODIFIERKEY_CTRL; }
  if (key == KEY_LEFT_ALT || key == KEY_RIGHT_ALT) { return MODIFIERKEY_ALT; }
  if (key == KEY_LEFT_GUI || key == KEY_RIGHT_GUI) { return MODIFIERKEY_GUI; }
  return 0;
}

bool isPinOn(int pin) {
  return !digitalRead(pin);
}

bool isSwitchUp(int row, int column) {
  return !switchState[row - 1][column - 1];
}

bool isSwitchDown(int row, int column) {
  return !!switchState[row - 1][column - 1];
}

bool isSwitchDebouncedDown(int row, int column) {
  return switchDebounceTime[row - 1][column - 1] > DEBOUNCE_THRESHOLD;
}

void onKeyDown(int row, int column) {
  if (DEBOUNCE_SWITCHES && switchUpTime[row - 1][column - 1] <= DEBOUNCE_THRESHOLD) {
    switchUpTime[row - 1][column - 1] = 0;
    switchDebounceTime[row - 1][column - 1] = switchUpTime[row - 1][column - 1] + DEBOUNCE_THRESHOLD;
    return;
  }

  switchState[row - 1][column - 1] = 1;

  #if DEBUG_MODE
    Keyboard.print("Down R");
    Keyboard.print(row);
    Keyboard.print(" C");
    Keyboard.print(column);
    Keyboard.print(" T");
    
    unsigned int thisDown = currentTime;
    unsigned int diffTime = thisDown - lastUp;
    
    #if DEBOUNCE_SWITCHES
      unsigned int diffThreshold = DEBOUNCE_THRESHOLD;
    #else
      unsigned int diffThreshold = DEBOUNCE_DEBUG_THRESHOLD;
    #endif
    
    if (diffTime <= diffThreshold) {
      Keyboard.print(thisDown);
      Keyboard.print(" !!!");
      Keyboard.println(diffTime);
    } else {
      Keyboard.println(thisDown);
    }
  #else
    unsigned int key = layers[getCurrentLayer()][row - 1][column - 1];
    unsigned int modifier = getModifierKey(key);
    unsigned int media = getMediaKey(key);

    if (media) {
      Keyboard.set_media(media);
      Keyboard.send_now();
    } else if (modifier) {
      currentModifier = currentModifier | modifier;
      Keyboard.set_modifier(currentModifier);
      Keyboard.send_now();
    } else if (key) {
      currentKey1 = key;
      Keyboard.set_key1(currentKey1);
      Keyboard.send_now();
    }
  #endif
}

void onKeyUp(int row, int column) {
  switchState[row - 1][column - 1] = 0;

  #if DEBUG_MODE
    Keyboard.print("  Up R");
    Keyboard.print(row);
    Keyboard.print(" C");
    Keyboard.print(column);
    Keyboard.print(" T");
    lastUp = currentTime;
    Keyboard.println(lastUp);
  #else
    unsigned int key = layers[getCurrentLayer()][row - 1][column - 1];
    unsigned int modifier = getModifierKey(key);
    unsigned int media = getMediaKey(key);

    if (media) {
      Keyboard.set_media(0);
      Keyboard.send_now();
    } else if (modifier) {
      currentModifier = currentModifier & ~modifier;
      Keyboard.set_modifier(currentModifier);
      Keyboard.send_now();
    } else if (key) {
      currentKey1 = 0;
      Keyboard.set_key1(currentKey1);
      Keyboard.send_now();
    }
  #endif

  switchUpTime[row - 1][column - 1] = 0;
}

void activateColumn(unsigned int column) {
  if (column != 1) { digitalWrite(PIN_COLUMN1, HIGH); }
  if (column != 2) { digitalWrite(PIN_COLUMN2, HIGH); }
  if (column != 3) { digitalWrite(PIN_COLUMN3, HIGH); }
  if (column != 4) { digitalWrite(PIN_COLUMN4, HIGH); }
  if (column != 5) { digitalWrite(PIN_COLUMN5, HIGH); }
  if (column != 6) { digitalWrite(PIN_COLUMN6, HIGH); }
  if (column != 7) { digitalWrite(PIN_COLUMN7, HIGH); }
  if (column != 8) { digitalWrite(PIN_COLUMN8, HIGH); }
  if (column != 9) { digitalWrite(PIN_COLUMN9, HIGH); }
  if (column != 10) { digitalWrite(PIN_COLUMN10, HIGH); }
  if (column != 11) { digitalWrite(PIN_COLUMN11, HIGH); }
  if (column != 12) { digitalWrite(PIN_COLUMN12, HIGH); }
  if (column != 13) { digitalWrite(PIN_COLUMN13, HIGH); }
  if (column != 14) { digitalWrite(PIN_COLUMN14, HIGH); }

  switch(column) {
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

void advanceColumn() {
  currentColumn = currentColumn + 1;
  if (currentColumn > 14) {
    currentColumn = 1;
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

  Keyboard.begin();
}

void loop() {
  // Deactivate all columns and activate the current column
  activateColumn(currentColumn);

  // Check for key down
  if (isPinOn(PIN_ROW1) && isSwitchUp(1, currentColumn)) { onKeyDown(1, currentColumn); }
  if (isPinOn(PIN_ROW2) && isSwitchUp(2, currentColumn)) { onKeyDown(2, currentColumn); }
  if (isPinOn(PIN_ROW3) && isSwitchUp(3, currentColumn)) { onKeyDown(3, currentColumn); }
  if (isPinOn(PIN_ROW4) && isSwitchUp(4, currentColumn)) { onKeyDown(4, currentColumn); }

  // Check for key up
  if (!isPinOn(PIN_ROW1) && isSwitchDown(1, currentColumn)) { onKeyUp(1, currentColumn); }
  if (!isPinOn(PIN_ROW2) && isSwitchDown(2, currentColumn)) { onKeyUp(2, currentColumn); }
  if (!isPinOn(PIN_ROW3) && isSwitchDown(3, currentColumn)) { onKeyUp(3, currentColumn); }
  if (!isPinOn(PIN_ROW4) && isSwitchDown(4, currentColumn)) { onKeyUp(4, currentColumn); }

  // Check for debounced key down
  #if DEBOUNCE_SWITCHES
    if (!isPinOn(PIN_ROW1) && isSwitchDebouncedDown(1, currentColumn)) { onKeyDown(1, currentColumn); }
    if (!isPinOn(PIN_ROW2) && isSwitchDebouncedDown(2, currentColumn)) { onKeyDown(2, currentColumn); }
    if (!isPinOn(PIN_ROW3) && isSwitchDebouncedDown(3, currentColumn)) { onKeyDown(3, currentColumn); }
    if (!isPinOn(PIN_ROW4) && isSwitchDebouncedDown(4, currentColumn)) { onKeyDown(4, currentColumn); }
  #endif

  // Advance to the next column
  advanceColumn();
}
