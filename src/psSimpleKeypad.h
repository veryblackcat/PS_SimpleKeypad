// psSimpleKeypad.h
// Piotr Sylwesiuk

#ifndef PS_SimpleKeypad_h
#define PS_SimpleKeypad_h

#include <inttypes.h>

// Keypad
#define KEY1  0x0001
#define KEY2  0x0002
#define KEY3  0x0004
#define KEY4  0x0008
#define KEY5  0x0010
#define KEY6  0x0020
#define KEY7  0x0040
#define KEY8  0x0080
#define KEY9  0x0100
#define KEY10 0x0200
#define KEY11 0x0400
#define KEY12 0x0800
#define KEY13 0x1000
#define KEY14 0x2000
#define KEY15 0x4000
#define KEY16 0x8000
/*
#define KEY1 0x01
#define KEY2 0x02
#define KEY3 0x04
#define KEY4 0x08
#define KEY5 0x10
#define KEY6 0x20
#define KEY7 0x40
#define KEY8 0x80
*/

// Stan klawisza
#define KEY_NOT_PRESSED 0
#define KEY_PRESSED 1
#define KEY_HELD_DOWN 3
#define KEY_RELEASED 4

#define KEYPAD_DELAY 20 // opoznienie pomiedzy odczytami klawiatury

// 4 keys - common to the ground
class KeyPad4 {  
  
  protected:
    //uint8_t sw1, sw2, sw3, sw4;
	uint8_t col1, col2, col3, col4;
	uint8_t numberOfKeys;
   // uint8_t current = 0;
    uint8_t previous = 0;
	//uint16_t previous = 0;
    uint32_t debouncing = 0;

  public:
    //uint16_t current_confirmed = 0;
    //uint16_t previous_confirmed = 0;
	uint8_t current_confirmed = 0;
    uint8_t previous_confirmed = 0;

    KeyPad4(uint8_t sw1, uint8_t sw2, uint8_t sw3, uint8_t sw4);
    
    uint8_t scan();
    uint8_t state_key(uint8_t key);
	//uint8_t state_key(uint16_t key);
};

// 8 keys
class KeyPad8 {
  
  protected:
    uint8_t row1, row2, col1, col2, col3, col4;
	uint8_t numberOfKeys;
    //uint8_t current;
	uint16_t previous;
    //uint8_t previous;
    uint32_t debouncing;

  public:
    uint16_t current_confirmed;
    uint16_t previous_confirmed;
	//uint8_t current_confirmed;
    //uint8_t previous_confirmed;

	KeyPad8(uint8_t row1, uint8_t row2, uint8_t col1, uint8_t col2, uint8_t col3, uint8_t col4); // 8 keys
    
    uint8_t scan();
    uint8_t state_key(uint16_t key);
};

class Keypad16 { 
  
  private:
    uint8_t col[5];
    uint8_t row[5];
    
    uint16_t previous;
    uint32_t debouncing;

  public:
    uint16_t current_confirmed;
    uint16_t previous_confirmed;

    Keypad16(uint8_t col1, uint8_t col2, uint8_t col3, uint8_t col4, uint8_t row1, uint8_t row2, uint8_t row3, uint8_t row4); // 16 keys - matrix 4x4
    //Keypad16(uint8_t col1, uint8_t col2, uint8_t col3, uint8_t col4, uint8_t row1, uint8_t row2, uint8_t row3); // 12 keys - matrix 4x3
    
    uint8_t scan();
    uint8_t state_key(uint16_t key);
};

#endif