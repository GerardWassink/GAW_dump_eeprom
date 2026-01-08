/* ------------------------------------------------------------------------- *
 * Name   : GAW_dump_eeprom
 * Author : Gerard Wassink
 * Date   : January, 2026
 * Purpose: Show an Arduino's EEPROM contents
 * Versions:
 *   0.1  : Initial code base, displaying full EEPROM contents
 *   0.2  : Added printable characters
 * ------------------------------------------------------------------------- */
#define progVersion "0.2"                   // Program version definition
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
 *       Copyright (C) 2026 Gerard Wassink
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

int EEPROM_size = EEPROM.length();

/* ------------------------------------------------------------------------- *
 *       Main program loop                                            loop()
 * ------------------------------------------------------------------------- */
void loop() {

  displayMainMenu();

  displayEEPROM();
        
  debugln();
  displayHeader(" - end of dump, reset to dump again");
  delay(500);
  exit(0);

}


/* ------------------------------------------------------------------------- *
 *       Display main menu                                 displayMainMenu()
 * ------------------------------------------------------------------------- */
void displayMainMenu() {
  debugln(F(" "));
  debug("EEPROM length: ");
  debugln(EEPROM_size);
}


/* ------------------------------------------------------------------------- *
 *       Display contents of EEPROM                          displayEEPROM()
 * ------------------------------------------------------------------------- */
void displayEEPROM() {
  int adr = 0;
  char byte;
  String hex;
  String chars = "";
  char c;
  
  displayHeader("");
  debugln("");
  debugln(F("addr 0        4        8        C          10       14       18       1C      "));

  for (adr = 0; adr < EEPROM_size; adr++) {
    byte = EEPROM.read(adr);
    
    if ( (adr % 32) == 0 ) {                // time for a newline?
      if (adr > 0 ) {                       // not for first line
        debug(" - ");
        debugln(chars);
        chars = "";
      }
      hex = "000";                          // create
      hex.concat(String(adr, HEX));         //   hex
      hex = hex.substring(hex.length()-4);  //   address
      debug(hex);                           // print hex address
      debug(" ");

    } else if ( (adr % 16) == 0 ) {         // create
      debug(" - ");                          // gap at % 16 
      chars.concat(" - ");

    } else if ( (adr % 4) == 0 ) {          // create
      debug(" ");                           //   space at %4
      chars.concat(" ");

    }
    
    isPrintable(byte) ? c = byte : c='.';   // add character
    chars.concat(c);                        //   to char string

    hex = "0";                              // make
    hex.concat(String(byte, HEX));          //   up
    hex = hex.substring(hex.length()-2);    //   hex digit
    debug(hex);                             // and print it

  }

  debug(" - ");                             // print last
  debugln(chars);                           //   batch of
  chars = "";                               //   characters

}


/* ------------------------------------------------------------------------- *
 *       Display program header                              displayHeader()
 * ------------------------------------------------------------------------- */
void displayHeader(String hdr) {
  debug(F("---===### GAW_dump_eeprom "));
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

}
