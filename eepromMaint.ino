/* ------------------------------------------------------------------------- *
 * Name   : eepromMaint
 * Author : Gerard Wassink
 * Date   : November 10, 2021
 * Purpose: Inspect and maintain the Arduino's EEPROM contents
 * Versions:
 *   0.1  : Initial code base, displaying full EEPROM contents (512 bytes)
 * ------------------------------------------------------------------------- */
#define progVersion "0.1"                   // Program version definition
/* ------------------------------------------------------------------------- *
 *             GNU LICENSE CONDITIONS
 * ------------------------------------------------------------------------- *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * ------------------------------------------------------------------------- *
 *       Copyright (C) 2021 Gerard Wassink
 * ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- *
 *       Debugging
 * ------------------------------------------------------------------------- */
#define DEBUG 1

#if DEBUG == 1
  #define debugstart(x) Serial.begin(x)
  #define debug(x) Serial.print(x)
  #define debugln(x) Serial.println(x)
#else
  #define debugstart(x)
  #define debug(x)
  #define debugln(x)
#endif

#include <EEPROM.h>


/* ------------------------------------------------------------------------- *
 *       Main program loop                                            loop()
 * ------------------------------------------------------------------------- */
void loop() {
  char choice = ' ';

  displayMainMenu();
  
  while (choice != 'x') {
    
    if (Serial.available() > 0) {
      choice = Serial.read();
      
      switch (choice) {
        
        case 'd':
        case 'D':
          debugln(String(choice));
          displayEEPROM();
          debugln();
          displayMainMenu();
          break;
        
        case 'x':
        case 'X':
          debugln(String(choice));
          debugln(F(" "));
          displayHeader("exit program");
          delay(500);
          exit(0);
        
        case '\n':                  // skip the enter key
          break;
        
        default:
          debugln();
          debug(F("Invalid choice '"));
          debug(String(choice));
          debugln(F("', try again: >"));
          break;
        
      }
    }
  }
    
  delay(500);
}


/* ------------------------------------------------------------------------- *
 *       Display main menu                                 displayMainMenu()
 * ------------------------------------------------------------------------- */
void displayMainMenu() {
  debugln(F(" "));
  displayHeader("main menu");
  debugln(F("D. Display EEPROM contents"));
  debugln(F("X. Exit"));
  debugln(F("Make a choice"));
  debug("> ");
}


/* ------------------------------------------------------------------------- *
 *       Display contents of EEPROM                          displayEEPROM()
 * ------------------------------------------------------------------------- */
void displayEEPROM() {
  int a = 0;
  byte b;
  int len = 0;
  String tmp;
  String hex;
  
  displayHeader("print EEPROM contents");
  debugln("");
  debugln(F("addr - 0        4        8        C          10       14       18       1C      "));

  for (a=0; a<512; a++) {
    b = EEPROM.read(a);
    
    if ( (a % 32) == 0 ) {
      if (a > 0 ) debugln("");
      hex = "000";
      hex.concat(String(a, HEX));
      hex = hex.substring(hex.length()-4);
      debug(hex);
    }
    
    if ( (a % 16) == 0 ) {
      debug(" -");
    }
    
    if ( (a % 4) == 0 ) {
      debug(" ");
    }
    
    hex = "0";
    hex.concat(String(b, HEX));
    hex = hex.substring(hex.length()-2);
    debug(hex);

  }
  
}


/* ------------------------------------------------------------------------- *
 *       Display program header                              displayHeader()
 * ------------------------------------------------------------------------- */
void displayHeader(String hdr) {
  debug(F("---===### eepromMaint - "));
  debug(hdr);
  debugln(F(" ###===---"));
}


/* ------------------------------------------------------------------------- *
 *       Initial setup routing                                       setup()
 * ------------------------------------------------------------------------- */
void setup() {
  debugstart(57600);
  delay(500);
  while (!Serial) {
    debugln("no serial connection (yet)");
  }
  Serial.setTimeout(60000);           // wait for max this time
}
