#include <iostream>
#include <algorithm> //used for random shuffling
#include <cstdlib> //standard library
#include <time.h> //used to generate time seed
#include <string>  

using namespace std;

const int NUMBER_OF_WORDS = 26; //always 26 words


//scramble function
//input is a string word to scramble, output is a scrambled string
string stringScramble(string wordToScramble){ 
  string scrambledWord = wordToScramble;
    
  while (scrambledWord == wordToScramble) {
    srand (time(NULL));
    random_shuffle(wordToScramble.begin(), wordToScramble.end());
  } //end of while loop

  return wordToScramble;
} //end of scramble function





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
    } else if (placeholderDigit == 1) {
      letterCode += ((inputKey - '0') * 10);
      placeholderDigit++;
    } else if (placeholderDigit == 2) {
      letterCode += ((inputKey - '0') * 100);
      placeholderDigit++;
    } else if (placeholderDigit == 3) {
      letterCode += ((inputKey - '0') * 1000);
      placeholderDigit++;
    } else if (placeholderDigit == 4) {
      letterCode += ((inputKey - '0') * 10000);
      placeholderDigit++;
    }
  }

  if (inputKey == '#'){
    int temp = letterCode;
    letterCode = placeholderDigit = 0;
    
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
    }
  }

  if (inputKey == '*')
    return '*';
  
  return '0';
}





//this function compares the userGuess with the word of interest 
//and returns a bool if they are the same or not
bool compare(string userGuess, string wordOfInterest){
  if (userGuess == wordOfInterest) {
      return true;
  } else {
    return false;
  }
}





//this function outputs result
void outputResult(bool isCorrect, int &userScore) {
  if (isCorrect) {
    cout << "Good jobe!";
    userScore++;
  } else {
    cout << "Try again!";
  }
  cout << "Current Score: " << userScore;
}


//given a string array with words in it, loads a random word 
string loadNewWord(int numberOfWords, string wordList[NUMBER_OF_WORDS]) {
  int randNum = 0; //create randomnumber variable
  string wordOfInterest; //target word
  srand (time(NULL));

  randNum = rand() % numberOfWords;

  wordOfInterest = wordList[randNum]; 

  return wordOfInterest;
}

//converts an array to a string
string arrayToString(char userGuess[16], int numOfLetters) {
  int i;
  int j;
  string s = "";
  for (i = 0; i < numOfLetters; i++) {
      s = s + userGuess[i];
    }
    return s;
}





int main() {
  //these will all be global variables in the arduino program
  string wordList[NUMBER_OF_WORDS] = {"ALPHABET", "BRICK", "CAT", "DOG", "ETHERNET", 
  "FRIENDS", "GOLDEN", "HUMAN", "INTEREST", "JUMP", "KIRKLAND", "LOST", "MAP", "NEAR",
  "OPEN", "PERSONAL", "QUINCY", "RUNNING", "SUPER", "TRIP", "UNDERNEATH", "VIVARIUM", 
  "WINNING", "XYLOPHONE", "YOUR", "ZEBRA"}; //target word list
  char userGuess[16];
  char customKey;
  char outputChar;
  int placeHolderForUG = 0;
  string finalUserGuess; //user input guess
  int userScore = 0; //userscore
  string wordOfInterest;
  string scrambledWord;
  bool isCorrect;

  //load new word to compare
  wordOfInterest = loadNewWord(NUMBER_OF_WORDS, wordList);

  cout << "word of interest: " << wordOfInterest << "\n";

  scrambledWord = stringScramble(wordOfInterest);

  cout << "scrambled word: " << scrambledWord << "\n";

  //display the scrambled word in the arduino

  for (int i = 0; i > -1; i++) {
    cin >> customKey;

    outputChar = convert(customKey);

    if ((outputChar != '0') && (outputChar != '*')) {
      userGuess[placeHolderForUG] = outputChar;
      placeHolderForUG++;

      //print out the letter on the display
    }

    if (outputChar == '*') {
      //convert the userGuess array into a string 
      finalUserGuess = arrayToString(userGuess, placeHolderForUG);
      placeHolderForUG = 0;

      cout << finalUserGuess;

      //turn the userGuess array back to empty
      char userGuess[16];

      //inputs are the user guess and the word we are comparing it to, output a bool
      isCorrect = compare(finalUserGuess, wordOfInterest); 

      //make sure to have a delay here as well and increment userScore if needed
      outputResult(isCorrect, userScore); 

      isCorrect = false;
      
      wordOfInterest = loadNewWord(NUMBER_OF_WORDS, wordList);

      cout << "word of interest: " << wordOfInterest << "\n";

      scrambledWord = stringScramble(wordOfInterest);

      cout << "scrambled word: " << scrambledWord << "\n";

      //display the scrambled word

    }

    cout << outputChar;
  }

  return 0;
}





/*
#include <LiquidCrystal.h>
#include <Keypad.h>

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
//byte rowPins[ROWS] = {9, 8, 7, 6}; connect to the row pinouts of the keypad
//byte colPins[COLS] = {5, 4, 3, 2}; connect to the column pinouts of the keypad
byte rowPins[ROWS] = {0,A0,2,3};
byte colPins[COLS] = {4,5,6,7};

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup()
{
  lcd.begin(16,1);
  Serial.begin(9600);
}

void loop() 
{
  char customKey = customKeypad.getKey();

  if (customKey) {
    lcd.print(customKey);
  }
  
}
*/