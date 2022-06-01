// psSimpleKeypad.cpp
// Piotr Sylwesiuk

#include "psSimpleKeypad.h"
#include <inttypes.h>
#include "Arduino.h"

// 4 keys - common to the ground
KeyPad4::KeyPad4(uint8_t sw1, uint8_t sw2, uint8_t sw3, uint8_t sw4) {

  KeyPad4::col1 = sw1;
  KeyPad4::col2 = sw2;
  KeyPad4::col3 = sw3;
  KeyPad4::col4 = sw4;
  
  numberOfKeys = 4;

  // Piny klawiatury
  pinMode(col1, INPUT_PULLUP);
  pinMode(col2, INPUT_PULLUP);
  pinMode(col3, INPUT_PULLUP);
  pinMode(col4, INPUT_PULLUP);

  //uint8_t current = 0;
  previous = 0;
  debouncing = 0;
  current_confirmed = 0;
  previous_confirmed = 0;
}

uint8_t KeyPad4::scan () {
  // funkcja zwraca 1 jesli klawiatura zostala przeskanowana, w przeiwnym razie zwraca 0
	uint16_t _current = 0;
  if (millis()<debouncing) return(0); // eliminate switch bouncing effect
    
    //current = 0;
    
    if (digitalRead(col1) == LOW) _current |= KEY1;
    if (digitalRead(col2) == LOW) _current |= KEY2;
    if (digitalRead(col3) == LOW) _current |= KEY3;
    if (digitalRead(col4) == LOW) _current |= KEY4;


    previous_confirmed = current_confirmed;
    current_confirmed = _current & previous;
    previous = _current;

    debouncing = millis() + KEYPAD_DELAY;
    return (1);
}

uint8_t KeyPad4::state_key(uint8_t key) {
  if ((current_confirmed & key) == key) {
    if ((previous_confirmed & key) == key) {
      return (KEY_HELD_DOWN);
    } else {
      return (KEY_PRESSED);
    }
  } else if ((previous_confirmed & key) == key) {
    return (KEY_RELEASED);
  } else {
    return (KEY_NOT_PRESSED);
  }

}

// 8 keys
KeyPad8::KeyPad8(uint8_t row1, uint8_t row2, uint8_t col1, uint8_t col2, uint8_t col3, uint8_t col4) {

  KeyPad8::row1 = row1;
  KeyPad8::row2 = row2;
  KeyPad8::col1 = col1;
  KeyPad8::col2 = col2;
  KeyPad8::col3 = col3;
  KeyPad8::col4 = col4;
  
  numberOfKeys = 8;

  // Piny klawiatury
  pinMode(row1, INPUT);
  pinMode(row2, INPUT);
  pinMode(col1, INPUT_PULLUP);
  pinMode(col2, INPUT_PULLUP);
  pinMode(col3, INPUT_PULLUP);
  pinMode(col4, INPUT_PULLUP);
  
  //current = 0;
  previous = 0;
  debouncing = 0;
  current_confirmed = 0;
  previous_confirmed = 0;
}

uint8_t KeyPad8::scan () {
  // funkcja zwraca 1 jesli klawiatura zostala przeskanowana, w przeiwnym razie zwraca 0
  
    uint16_t _current = 0;
  
    if (millis()<debouncing) return(0); // eliminate switch bouncing effect
    
    //current = 0;
    
    pinMode(row1, OUTPUT);
    digitalWrite(row1, LOW);
    if (digitalRead(col1) == LOW) _current |= KEY1;
    if (digitalRead(col2) == LOW) _current |= KEY2;
    if (digitalRead(col3) == LOW) _current |= KEY3;
    if (digitalRead(col4) == LOW) _current |= KEY4;
    pinMode(row1, INPUT); // rozwiązanie konieczne aby nie zwierac wyjsc procesora przy jednoczesnym nacisnieciu dwoch klawiszy tej samej kolumny (albo mozna zastosowac diody przy pinach wyjsciowych)
                          // Jesli konieczne jest rozpoznawanie jednoczesnego nacisniecia wielu klawiszy (wiecej niz 2) zastosowac diody przy kazdym przycisku

    pinMode(row2, OUTPUT);
    digitalWrite(row2, LOW);
    if (digitalRead(col1) == LOW) _current |= KEY5;
    if (digitalRead(col2) == LOW) _current |= KEY6;
    if (digitalRead(col3) == LOW) _current |= KEY7;
    if (digitalRead(col4) == LOW) _current |= KEY8;
    pinMode(row2, INPUT);

    previous_confirmed = current_confirmed;
    current_confirmed = _current & previous;
    previous = _current;

    debouncing = millis() + KEYPAD_DELAY;
    return (1);
}

uint8_t KeyPad8::state_key(uint16_t key) {
  if ((current_confirmed & key) == key) {
    if ((previous_confirmed & key) == key) {
      return (KEY_HELD_DOWN);
    } else {
      return (KEY_PRESSED);
    }
  } else if ((previous_confirmed & key) == key) {
    return (KEY_RELEASED);
  } else {
    return (KEY_NOT_PRESSED);
  }

}

// 16 keys
Keypad16::Keypad16(uint8_t col1, uint8_t col2, uint8_t col3, uint8_t col4, uint8_t row1, uint8_t row2, uint8_t row3, uint8_t row4) {  // 16 keys - matrix 4x4

  // zmienic do wierszy i kolumn zastosowac tablice z pamiecia przydzielana dynamicznie, elementy zerowe maja zawierac dlugosc tablicy

  col[0] = 4; // nomber of collumns
  col[1] = col1;
  col[2] = col2;
  col[3] = col3;
  col[4] = col4;
  
  row[0] = 4; // number or rows
  row[1] = row1;
  row[2] = row2;
  row[3] = row3;
  row[4] = row4;

  // Piny klawiatury
  pinMode(row[1], INPUT);
  pinMode(row[2], INPUT);
  pinMode(row[3], INPUT);
  pinMode(row[4], INPUT);
  pinMode(col[1], INPUT_PULLUP);
  pinMode(col[2], INPUT_PULLUP);
  pinMode(col[3], INPUT_PULLUP);
  pinMode(col[4], INPUT_PULLUP);

  previous = 0;
  debouncing = 0;
  current_confirmed = 0;
  previous_confirmed = 0;
}

uint8_t Keypad16::scan() {
  // funkcja zwraca 1 jesli klawiatura zostala przeskanowana, w przeiwnym razie zwraca 0
  
  uint16_t _current = 0;
  uint16_t _keycode = 1;
  
  if (millis()<debouncing) return(0); // eliminate switch bouncing effect
    for(uint8_t r=1; r<=row[0]; r++){ //scan kepad
      pinMode(row[r], OUTPUT);
      digitalWrite(row[r], LOW);
      for(uint8_t c=1; c<=col[0]; c++){
        if (digitalRead(col[c]) == LOW) _current |= _keycode;
        _keycode <<= 1;
      }
      pinMode(row[r], INPUT); // rozwiązanie konieczne aby nie zwierac wyjsc procesora przy jednoczesnym nacisnieciu dwoch klawiszy tej samej kolumny (albo mozna zastosowac diody przy pinach wyjsciowych)
                              // Jesli konieczne jest rozpoznawanie jednoczesnego nacisniecia wielu klawiszy (wiecej niz 2) zastosowac diody przy kazdym przycisku
    }
    
    previous_confirmed = current_confirmed;
    current_confirmed = _current & previous;
    previous = _current;

    debouncing = millis() + KEYPAD_DELAY;
    return (1);
}

uint8_t Keypad16::state_key(uint16_t key) {
  if ((current_confirmed & key) == key) {
    if ((previous_confirmed & key) == key) {
      return (KEY_HELD_DOWN);
    } else {
      return (KEY_PRESSED);
    }
  } else if ((previous_confirmed & key) == key) {
    return (KEY_RELEASED);
  } else {
    return (KEY_NOT_PRESSED);
  }

}