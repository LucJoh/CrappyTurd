#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(19, 23, 18, 17, 16, 15);

enum states {
    none,
    startMenu,
    play,
    dead
};

////////////////// CUSTOM CHARACTERS ////////////////////////
byte poop[8] = {
    B00000,
    B00000,
    B00100,
    B01110,
    B01110,
    B11111,
    B11111,
    B00000
};

byte toilet[8] = {
    B00011,
    B00011,
    B00011,
    B11111,
    B11110,
    B01100,
    B11110,
    B00000
};
////////////////////////////////////////////////////////////

///////////////////// VARIABLES ///////////////////////////
states prior_state, state;
bool startMenuBlink;
bool player_position;
bool debounce = false;
int button = 32;
int score;
int pace = 500;
int j = 0;
int i = 0;
int k = 0;
int l = 0;
int m = 0;
int n = 0;
int o = 0;
int org_top [50]    = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0};
int org_bottom [50] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0};
int top [50]    = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0};
int bottom [50] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0};

unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
unsigned long interval = 10000;

unsigned long debounceTime = 0;
unsigned long previousDebounceTime = 0;

///////////////////////////////////////////////////////////

////////////////// STATE FUNCTIONS ////////////////////////
void start_menu_function() {
    // initialization
    if (state != prior_state) {
        prior_state = state;
    }

    // perform state tasks
    lcd.setCursor(0, 0);
    lcd.print("  ");
    lcd.write(byte(0));
    lcd.print("CrappyTurd");
    lcd.write(byte(0));
    lcd.setCursor(0, 1);
    if (startMenuBlink == true) {
        lcd.print(" Click to start");
    }
    else lcd.print("                ");
    startMenuBlink = !startMenuBlink;
    for (l = 0; l < 1100; l++) {  // delay loop for fast response time when player presses button
        delay(1);
        if (digitalRead(button) == LOW) {  // button polarity is reversed
            state = play;	
            lcd.clear();
            score = 0;
            break;
        }
    }
    if (l == 1100) l = 0;
    //delay(1100); // replaced by the for loop for faster response time

    // check for state transitions
    if (digitalRead(button) == LOW) {  // button polaririor_state) {
                                       // clear LCD?
        lcd.clear();
        delay(2000);
    }
    }

    void play_function() {

        // initialization
        if (state != prior_state) {
            prior_state = state;
        }

        // perform state tasks

        if (digitalRead(button) == LOW) {  // button polarity is reversed
                                           //state = dead;
                                           //lcd.clear();
                                           //j = 0;
                                           //break;
                                           //player_position != player_position;
        }

        lcd.clear();
        //lcd.scrollDisplayLeft(); 

        //lcd.setCursor(5, 0);
        //lcd.print("k");

        if (player_position == false) {
            lcd.setCursor(0, 1);
            lcd.write(byte(0));
            lcd.setCursor(0, 0);
            lcd.print(" ");
        }
        else if (player_position == true) {
            lcd.setCursor(0, 0);
            lcd.write(byte(0));
            lcd.setCursor(0, 1);
            lcd.print(" ");
        }

        // write out toilets
        for (m = 16; m > -1; m--) {
            lcd.setCursor(m, 0); ////////////////////////
            if (top[m] == 1) {
                if (player_position == true && m == 0) {
                    state = dead;
                    break;
                }
                else lcd.write(byte(1));
            }
            else lcd.print(" ");

            lcd.setCursor(m, 1); ////////////////////////
            if (bottom[m] == 1) {
                if (player_position == false && m == 0) {
                    state = dead;
                    break;
                }
                else lcd.write(byte(1));
            }	
            else lcd.print(" ");
        }

        if (player_position == false) {
            lcd.setCursor(0, 1);
            lcd.write(byte(0));
            //lcd.setCursor(0, 0);
            //lcd.print(" ");
        }
        else if (player_position == true) {
            lcd.setCursor(0, 0);
            lcd.write(byte(0));
            //lcd.setCursor(0, 1);
            //lcd.print(" ");
        }

        for (k = 0; k < pace; k++) {  // delay loop for fast response time when player presses button
            delay(1);
            if ((digitalRead(button) == LOW) && (debounce == false)) {  // button polarity is reversed
                                                                        //delay(30);
                debounceTime = millis();
                debounce = true;
            }
            if (debounce == true) {
                if ((digitalRead(button) == HIGH) && (debounceTime - previousDebounceTime > 30)) {
                    previousDebounceTime = debounceTime;
                    //state = dead;
                    //lcd.clear();
                    //j = 0;
                    //break;
                    player_position = !player_position;
                    debounce = false;
                }
            }
        }
        //if (k == 500) k = 0;

        // check for state transitions
        /*if (digitalRead(button) == LOW) {  // button polarity is reversed
          state = dead;
          lcd.clear();
          j = 0;
          }*/

        // cleanup if we are leaving state
        if (state != prior_state) {
            // clear LCD?
            lcd.clear();
        }

        // left shift toilets
        int size = sizeof(top) / sizeof(top[0]);
        int temp_top = top[0];
        int temp_bottom = bottom[0];
        for (int i = 1; i < size; i++) {
            top[i - 1] = top[i];
            bottom[i - 1] = bottom[i];
        }
        top[size - 1] = temp_top;
        bottom[size - 1] = temp_bottom;

        currentMillis = millis();

        if (currentMillis - previousMillis >= interval) {
            previousMillis = currentMillis;
            if (pace < 300) pace = pace - 50;
            else pace = pace - 50;
        }
        score = score + 1;
    }

    void dead_function() {

        // initialization

        // perform state tasks
        lcd.setCursor(0, 0);
        lcd.print("   You died :(");
        lcd.setCursor(0, 1);
        lcd.print("   Score: ");
        lcd.print(score);
        for (o = 0; o < sizeof(org_top) / sizeof(org_top[0]); o++) {
            top[o] = org_top[o];
            bottom[o] = org_bottom[o];
        }
        pace = 500;
        delay(4000);
        lcd.clear();
        state = startMenu;

        // check for state transitions

        // cleanup if we are leaving state	
    }
    ///////////////////////////////////////////////////////////

    void setup() {

        lcd.clear();
        // initialize button
        pinMode(button, INPUT_PULLUP);
        // set up the LCD's number of columns and rows:
        lcd.begin(16, 2);
        // create custom characters
        lcd.createChar(0, poop);
        lcd.createChar(1, toilet);
        // set initial states
        prior_state = none;
        state = startMenu;
        // set initial states of booleans
        startMenuBlink = true;
        player_position = false;
    }

    void loop() {
        switch(state) {
            case startMenu:
                start_menu_function();
                break;
            case play:
                play_function();
                break;
            case dead:
                dead_function();
                break;
        }
    } 
