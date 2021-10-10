//used for the LCD
#include <LiquidCrystal.h>

//used for the numeric keypad
#include <Keypad.h>

//used for the speaker
#include "pitches.h"

const int NUMBER_OF_WORDS = 19; //always 19 words

//word bank of unscrambled words
String wordList[NUMBER_OF_WORDS] = {"CINCINNATI", "HACKER", "PROGRAMMING", "MICROCONTROLLER",
"PYTHON", "ARDUINO", "AMAZON", "COMPUTER", "HACKATHON", "JAVA", "JAVASCRIPT", "CLOUD",
"INTERNET", "PROCESSOR", "WINDOWS", "LINUX", "SOFTWARE", "HARDWARE", "DIGITAL"} ; //target word list

//word bank of scrambled words whose indices match up with wordList
String scrambledWordList[NUMBER_OF_WORDS] = {"ITANCCNINI","ARHKEC", "OMAGIRRMNPG",
"OCCTEONRMIOLRRL", "THNYPO", "DUONAIR", "NZAMOA", "RCOTPUME", "CAHHTOANK", "AJVA",
"TIJSCARAPV", "UOLCD", "NRTENTIE", "SERPOORCS", "OSDWNIW", "INXUL", "RAWTFOES",
"HRWAEADR", "ADITIGL"};

char userGuess[16];   //to hold the characters for the user's guess before they submit it
char customKey;      //to hold the numeric (or #*) character that the user enters on the keypad
char outputChar;     //to hold the letter that the user is trying to represent
int indexForUserGuess = 0;     //holds the index for the user's guess
String finalUserGuess;      //user input guess converted to a string
int userScore = 0;    //hold's the user's currrent score
String wordOfInterest;    //the word that needs to be unscrambled
String scrambledWord;     //the wordOfInterest scrambled;
bool isCorrect;           //holds if the user's unscramble guess was correct
int index = 0;          //keeps the index value in the wordList and scrambledWordList
int column = 0;        //keeps track of what column the cursor is in on the display
const int DESIRED_SCORE = 2;    //desired user score, get congrats message when achieved.


//initializes the LiquidCrystal object to correct digital pins
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);


const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {0,A0,2,3};   //connect to row pinouts of the keypad (digital pin 1 is broken on our board)
byte colPins[COLS] = {4,5,6,7};    //connect to column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 


//scramble function
//input is a String word to scramble, output is a scrambled String
String StringScramble(int index){ 
  
  return scrambledWordList[index];
}


char returnLetter(int temp) {
    if (temp == 2) {
      return 'A';
    }
    if (temp == 22) {
      return 'B';
    }
    if (temp == 222) {
      return 'C';
    }
    if (temp == 3){
      return 'D';
    }
    if (temp == 33){
      return 'E';
    }
    if (temp == 333){
      return 'F';
    }
    if (temp == 4){
      return 'G';
    } 
    if(temp == 44){
      return 'H';
    }
    if(temp == 444){
      return 'I';
    }
    if(temp == 5){
      return 'J';
    }
    if(temp == 55){
      return 'K';
    }
    if(temp == 555){
      return 'L';
    }
    if(temp == 6){
      return 'M';
    }
    if(temp == 66){
      return 'N';
    }
    if(temp == 666){
      return 'O';
    }
    if (temp == 7) {
      return 'P';
    }
    if (temp == 77) {
      return 'Q';
    }
    if (temp == 777) {
      return 'R';
    }
    if (temp == 7777) {
      return 'S';
    }
    if (temp == 8) {
      return 'T';
    }
    if (temp == 88) {
      return 'U';
    }
    if (temp == 888) {
      return 'V';
    }
    if (temp == 9) {
      return 'W';
    }
    if (temp == 99) {
      return 'X';
    }
     if (temp == 999) {
      return 'Y';
    }
     if (temp == 9999) {
      return 'Z';
    } else {
      return '\0';
     
    }
}


//this function takes a character of input and returns '0' if nothing important,
//returns '*' if the number code is complete, returns a letter if the numeric 
//code is finished
char convert(char inputKey) {
  static int letterCode = 0;
  static int placeholderDigit = 0;

  if ((inputKey > 47) && (inputKey < 58)) {
    
    if (placeholderDigit == 0) {
        letterCode += (inputKey - '0');
        placeholderDigit++;
        
    }else if (placeholderDigit == 1) {
      letterCode += ((inputKey - '0') * 10);
      placeholderDigit++;
    }else if (placeholderDigit == 2) {
      letterCode += ((inputKey - '0') * 100);
      placeholderDigit++;
    } else if ((placeholderDigit > 2) && ((inputKey != '7') && (inputKey != '9'))) {
      letterCode = inputKey - '0';
      placeholderDigit = 1;
    } else if (placeholderDigit == 3) {
      letterCode += ((inputKey - '0') * 1000);
      placeholderDigit++;
    } else if ((placeholderDigit > 3) && ((inputKey == '7') || (inputKey == '9'))) {
      letterCode = inputKey - '0';
      placeholderDigit = 1;  
    } 
    if (not((letterCode == 22)|| (letterCode == 222)|| (letterCode == 33)|| (letterCode == 333)|| 
    (letterCode == 44)|| (letterCode == 444)|| (letterCode == 55)|| (letterCode == 555)|| (letterCode == 66)|| 
    (letterCode == 666)|| (letterCode == 77)|| (letterCode == 777)|| (letterCode == 7777)|| (letterCode == 88)|| 
    (letterCode == 888)|| (letterCode == 99)|| (letterCode == 999)|| (letterCode == 9999))){
      letterCode = inputKey - '0';
      placeholderDigit = 1;
    }
    lcd.setCursor(column, 1);
    lcd.print(returnLetter(letterCode));
    return returnLetter(letterCode);
  

  } if (inputKey == '#'){
    
    column++;
    userGuess[indexForUserGuess] = outputChar;
    indexForUserGuess++;
    int temp = letterCode;
    letterCode = placeholderDigit = 0; 
    return returnLetter(temp);
  }

  if (inputKey == '*') {
    column = 0;
    return '*';
  }
  return '0';
  
}




//this function compares the userGuess with the word of interest 
//and returns a bool if they are the same or not
bool compare(String userGuess, String wordOfInterest){
  if (userGuess == wordOfInterest) {
      return true;
  } else {
    return false;
  }
}





//this function outputs result
void outputResult(bool isCorrect, int &userScore) {
  lcd.clear();
  lcd.setCursor(0,0);
  
  if (isCorrect) {
    userScore++;
    lcd.print("Correct!");
    tone(A5, NOTE_C2, 100);
    delay(100);
    tone(A5, NOTE_C3, 100);
    delay(100);
    tone(A5, NOTE_C4, 100);
    delay(100);
    tone(A5, NOTE_C5, 100);
  } else {
    tone(A5, NOTE_C5, 100);
  delay(100);
  tone(A5, NOTE_C4, 100);
  delay(100);
  tone(A5, NOTE_C3, 100);
  delay(100);
  tone(A5, NOTE_C2, 100);
    lcd.print("Incorrect...");
  }
  lcd.setCursor(0,1);
  lcd.print("Score: " + String(userScore) + "/" + String(DESIRED_SCORE));
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
}


//given a String array with words in it, loads a random word 
String loadNewWord(int numberOfWords, String wordList[NUMBER_OF_WORDS], int &index) {
  int randNum = 0; //create randomnumber variable
  String wordOfInterest; //target word

  randNum = random(1, 9999) % NUMBER_OF_WORDS;

  wordOfInterest = wordList[randNum]; 

  index = randNum;

  return wordOfInterest;
}

//converts an array to a String
String arrayToString(char userGuess[16], int numOfLetters) {
  int i;
  int j;
  String s = "";
  for (i = 0; i < numOfLetters; i++) {
      s = s + userGuess[i];
    }
    return s;
}



void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.print("Unscramble game!");
  lcd.setCursor(0, 1);
  lcd.print("# letter, * word");
  randomSeed(analogRead(0));

  
  tone(A5, NOTE_C2, 100);
  delay(100);
  tone(A5, NOTE_C3, 100);
  delay(100);
  tone(A5, NOTE_C4, 100);
  delay(100);
  tone(A5, NOTE_C5, 100);
  delay(4700);

  lcd.clear();
  lcd.setCursor(0,0);

  //load new word to compare
  wordOfInterest = loadNewWord(NUMBER_OF_WORDS, wordList, index);

  scrambledWord = StringScramble(index);

  lcd.print(scrambledWord);
  lcd.setCursor(0,1);
}



void loop() {

  char customKey = customKeypad.getKey();

  if (customKey) {

    if ((customKey == '#') || (customKey == '*')) {
      tone(A5, NOTE_C4, 100);
    } else {
      tone(A5, NOTE_C3, 100);
    }
    
    outputChar = convert(customKey);
    Serial.println(outputChar);
    Serial.println(column);
    Serial.println(customKey);

    
    if (outputChar == '*') {
      //convert the userGuess array into a String 
      finalUserGuess = arrayToString(userGuess, indexForUserGuess);
      indexForUserGuess = 0;

      //turn the userGuess array back to empty
      char userGuess[16];

      //inputs are the user guess and the word we are comparing it to, output a bool
      isCorrect = compare(finalUserGuess, wordOfInterest); 

      //make sure to have a delay here as well and increment userScore if needed
      outputResult(isCorrect, userScore); 

      isCorrect = false;

      if (userScore == DESIRED_SCORE) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Congratulations,");
        lcd.setCursor(0,1);
        lcd.print("You win!");

        tone(A5, NOTE_C2, 100);
        delay(100);
        tone(A5, NOTE_C3, 100);
        delay(100);
        tone(A5, NOTE_C4, 100);
        delay(100);
        tone(A5, NOTE_C5, 300);
        delay(300);
        tone(A5, NOTE_C4, 100);
        delay(100);
        tone(A5, NOTE_C5, 300);
        delay(4500);
        userScore = 0;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Press button to");
        lcd.setCursor(0,1);
        lcd.print("play again!");
        customKey = customKeypad.waitForKey();
        lcd.clear();
        lcd.setCursor(0,0);
      }

      
      wordOfInterest = loadNewWord(NUMBER_OF_WORDS, wordList, index);
      scrambledWord = StringScramble(index);

      lcd.print(scrambledWord);
      lcd.setCursor(0,1);
    }
  }
 }
    
