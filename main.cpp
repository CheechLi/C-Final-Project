#include <algorithm>
#include <chrono>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
#include <vector>
using namespace std;
using namespace chrono;

void displayMenu() {
  cout << "Menu Options:\n";
  cout << "1. Start a New Game\n";
  cout << "2. View High Scores\n";
  cout << "3. Exit\n\n";
}

void rainbowText(string text) {
  string colors[] = {"\033[1;31m", "\033[1;33m", "\033[1;32m", "\033[1;34m", "\033[1;35m", "\033[1;36m"}; // Red, Yellow, Green, Blue, Magenta, Cyan
  int colorCount = sizeof(colors) / sizeof(colors[0]);
  for (int i = 0; i < text.length(); ++i) {
    cout << colors[i % colorCount] << text[i];
    cout.flush();
    usleep(100000); // Sleep for 100 milliseconds
  }
}

void typeWriteText(string text) {
  for (int i = 0; i < text.length(); ++i) {
    cout << text[i];
    cout.flush();
    usleep(100000); // Sleep for 100 milliseconds
  }
}

class Timer { // Timer
public:
  void start() {
    startTime = high_resolution_clock::now();
    isRunning = true;
  }
  void stop() {
    endTime = high_resolution_clock::now();
    isRunning = false;
  }
  double elapsedTime() {
    if (isRunning) {
      endTime = high_resolution_clock::now();
    }
    duration<double> elapsed = endTime - startTime;
    return elapsed.count();
  }

private:
  high_resolution_clock::time_point startTime;
  high_resolution_clock::time_point endTime;
  bool isRunning;
};

int main() {
  string companyName = "CONTECHLI GAMES";
  string companySlogan = "Make change in your life!";
  rainbowText(companyName); // Outputs company name in rainbow text
  cout << endl;
  rainbowText(companySlogan); // Outputs company slogan in rainbow text
  cout << "\n\n\n";
  cout << "\033[0m";
  bool gameActive = false; // Game activity is defaulted to false
  char playAgain = 'n';    // Play again is defaulted to no
  do {
    displayMenu(); // Shows player the menu options
    int choice;
    string questionSetFile;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();
    cout << endl;

    switch (choice) // Checks what choice the player chose
    {
    case 1: {
      bool gameFileExists = false; // Game file exists is defaulted to false
      while (gameFileExists == false) { // Checks if game file exists
        cout << "Enter the title of the game version you would like to play! (please exclude .txt)" << endl << endl;
        cout << "Game title: ";
        getline(cin, questionSetFile);
        ifstream checkIfFileExists(questionSetFile + ".txt");
        if (checkIfFileExists.is_open())
          gameFileExists = true;
        else {
          cout << questionSetFile << " was not found!" << endl << endl;
          cout << "Contact ContechLi Games for assistance" << endl << endl;
          cout << "www.ContechLi_Games/Mr_Glebas/Michael_Conteh/Yingqi_Cheech_Li/support.com" << endl << endl;
        }
      }
      cout << "\nStarting a new game...\n\n"; // Tells player game is about to start
      cout << "When answering, enter: a, b, c, d, A, B, C, or D\n\n"; // Rules
      cout << "When requesting a use of a 50-50 elimination, enter: 50/50\n\n"; // Rules
      cout << "You have 5 seconds to get ready!\n"; // Rules"
      this_thread::sleep_for(seconds(5)); // Gives the player a 5 second break time to read the rules
      Timer timer;
      timer.start(); // Timer begins
      cout << "Your timer starts now! Good luck!\n\n";
      vector<string> qnaFile; // QuestionsAndAnswers vector
      vector<string> question; // Vector of questions
      vector<string> correctAnswer; // Vector of answers
      vector<string> fiftyfiftyAnswer; // Vector of 50-50 answers
      vector<string> incorrectAnswerGroupOne; // Vector of incorrect answers
      vector<string> incorrectAnswerGroupTwo; // Vector of incorrect answers
      vector<string> questionSetToAnswer; // Vector of question sets to answer
      vector<string> letters{"a. ", "b. ", "c. ", "d. "}; // Vector of letters to show position of answer choices
      string answer, name;
      char saveScore;
      int score = 0;
      bool validAnswer = false, fiftyfiftyUsed = false;
      gameActive = true; // Activates Game
      ifstream file(questionSetFile + ".txt"); // Calls for the game card file

      while (gameActive == true) { // Checks if the game is active
        if (file.is_open()) {      // Checks if file is open
          string line;
          while (getline(file, line)) {
            qnaFile.push_back(line); // Reads the file into the vector
          }
          file.close(); // Closes the file
        }

        for (int i = 0; i < 55; i = i + 6) // Create questions vector
          question.push_back(qnaFile[i]);

        for (int i = 1; i < 56; i = i + 6) // Create correct answers vector
          correctAnswer.push_back(qnaFile[i]);

        for (int i = 2; i < 57; i = i + 6) // Create 50-50 answers vector
          fiftyfiftyAnswer.push_back(qnaFile[i]);

        for (int i = 3; i < 58; i = i + 6) // Create incorrect answers vector
          incorrectAnswerGroupOne.push_back(qnaFile[i]);

        for (int i = 4; i < 59; i = i + 6) // Create incorrect answers vector
          incorrectAnswerGroupTwo.push_back(qnaFile[i]);

        for (int i = 0; i < question.size();
             i++) { // Create question set to answer vector
          cout << (i + 1) << ". " << question[i] << endl; // Outputs question
          questionSetToAnswer.clear();
          questionSetToAnswer.push_back(correctAnswer[i]); // Adds correct answers to vector
          questionSetToAnswer.push_back(fiftyfiftyAnswer[i]); // Adds 50-50 answers to vector
          questionSetToAnswer.push_back(incorrectAnswerGroupOne[i]); // Adds incorrect answer to vector
          questionSetToAnswer.push_back(incorrectAnswerGroupTwo[i]); // Adds incorrect answer to vector

          for (int i = 0; i < 100; i++) // Shuffles 100 times for super randomness!
            random_shuffle(questionSetToAnswer.begin(), questionSetToAnswer.end());

          for (int j = 0; j < 4; j++) // Outputs the answer choices to the question
            cout << letters[j] << questionSetToAnswer[j] << endl;

          validAnswer = false; // Resets

          while (validAnswer == false) { // Error traps for valid answer
            cout << "Answer: ";
            cin >> answer;
            if (answer == "a" || answer == "b" || answer == "c" || answer == "d" || answer == "A" || answer == "B" || answer == "C" || answer == "D" || answer == "50/50") {
              validAnswer = true;
              cout << endl;

              // Verifies answer
              if (answer == "a" || answer == "A") {
                if (questionSetToAnswer[0] == correctAnswer[i]) { // Checks if answer is correct
                  score += 1; // Incriments score
                  cout << "\033[1;32m"; // Makes text green
                  cout << "Correct! +1 point\n\n"; // Correct response
                  cout << "\033[0m"; // Resets textcolor
                } 
                else {
                  cout << "\033[1;31m"; // Makes text red
                  cout << "Incorrect! No points awarded!\n\n"; // Incorrect response
                  cout << "The correct answer was" << correctAnswer[i] << endl << endl; // Correct answer
                  cout << "\033[0m"; // Resets textcolor
                }
              } 
              else if (answer == "b" || answer == "B") {
                if (questionSetToAnswer[1] == correctAnswer[i]) { // Checks if answer is correct
                  score += 1; // Incriments score
                  cout << "\033[1;32m"; // Makes text green
                  cout << "Correct! +1 point\n\n"; // Correct response
                  cout << "\033[0m"; // Resets textcolor
                } 
                else {
                  cout << "\033[1;31m"; // Makes text red
                  cout << "Incorrect! No points awarded!\n\n"; // Incorrect response
                  cout << "The correct answer was" << correctAnswer[i] << endl
                       << endl;      // Correct answer
                  cout << "\033[0m"; // Resets textcolor
                }
              } 
              else if (answer == "c" || answer == "C") {
                if (questionSetToAnswer[2] == correctAnswer[i]) { // Checks if answer is correct
                  score += 1; // Incriments score
                  cout << "\033[1;32m"; // Makes text green
                  cout << "Correct! +1 point\n\n"; // Correct response
                  cout << "\033[0m"; // Resets textcolor
                } 
                else {
                  cout << "\033[1;31m"; // Makes text red
                  cout << "Incorrect! No points awarded!\n\n"; // Incorrect response
                  cout << "The correct answer was" << correctAnswer[i] << endl << endl; // Correct answer
                  cout << "\033[0m"; // Resets textcolor
                }
              } 
              else if (answer == "d" || answer == "D") {
                if (questionSetToAnswer[3] == correctAnswer[i]) { // Checks if answer is correct
                  score += 1; // Incriments score
                  cout << "\033[1;32m"; // Makes text green
                  cout << "Correct! +1 point\n\n"; // Correct response
                  cout << "\033[0m"; // Resets textcolor
                } 
                else {
                  cout << "\033[1;31m"; // Makes text red
                  cout << "Incorrect! No points awarded!\n\n"; // Incorrect response
                  cout << "The correct answer was" << correctAnswer[i] << endl
                       << endl;      // Correct answer
                  cout << "\033[0m"; // Resets textcolor
                }
              } 
              else if (answer == "50/50") { // 50/50 elimination
                if (fiftyfiftyUsed == false) { // Checks if 50/50 was used already
                  int fiftyfifty;
                  cout << "50/50 elimination!\n\n";
                  srand(time(0));
                  int random = (rand() % 2) + 1; // Generates random response where correct answer is 1 or 2
                  if (random == 1)
                    cout << "Choose: " << correctAnswer[i] << " or " << fiftyfiftyAnswer[i] << endl;
                  if (random == 2)
                    cout << "Choose: " << fiftyfiftyAnswer[i] << " or " << correctAnswer[i] << endl;

                  // Error Trap for integers only
                  bool isInt = false;
                  while (isInt == false) {
                    cout << "Enter 1 or 2: ";
                    if (cin >> fiftyfifty) { // Check if the input is an integer
                      if (fiftyfifty == 1 || fiftyfifty == 2) {
                        isInt = true; // Input is valid
                      } 
                      else {
                        cout << "Invalid input. Please enter 1 or 2.\n";
                        cin.clear();  // Clear error state
                        cin.ignore(); // Discard remaining input
                      }
                    } 
                    else {
                      cout << "Invalid input. Please enter 1 or 2.\n";
                      cin.clear();  // Clear error state
                      cin.ignore(); // Discard remaining input
                    }
                  }

                  if (random == 1 && fiftyfifty == 1 || random == 2 &&fiftyfifty == 2) { // Checcks if answer is correct
                    score += 1; // Incriments score
                    cout << "\033[1;32m"; // Makes text green
                    cout << "Correct! +1 point\n\n"; // Correct response
                    cout << "\033[0m"; // Resets textcolor
                  } 
                  else {
                    cout << "\033[1;31m"; // Makes text green
                    cout << "Incorrect! No points awarded!\n\n"; // Incorrect response
                    cout << "The correct answer was" << correctAnswer[i] << endl << endl; // Correct answer
                    cout << "\033[0m"; // Resets textcolor
                  }
                  fiftyfiftyUsed = true; // Uses 50/50
                } 
                else {
                  cout << "You've already used a 50/50 elimination!\n\n"; // Warns player
                  validAnswer = false; // Marks answer as invalid and loops for a valid answer
                }
              } 
              else
                cout << "Please answer with: a, b, c, d, A, B, C, or D" << endl; // Warns player
            }
          }
        }
        gameActive = false; // Closes game
        timer.stop(); // Stops timer

        // Players stats
        cout << "Your score was " << score << " out of 10!" << endl;
        // Taunts
        if (score == 10) {
          string perfectScore = "PERFECT SCORE! CONGRATULATIONS! YOU JUST WON A MILLION GLEBAS BUCKS! YOU'RE AMAZING!";
          rainbowText(perfectScore);
          cout << endl;
        } 
        else if (score == 9) {
          string nineScore = "Almost there buddy!";
          cout << "\033[1;32m"; // Makes text green
          typeWriteText(nineScore);
          cout << "\033[0m"; // Resets textcolor
          cout << endl;
        } 
        else if (score == 8) {
          string eightScore = "You absolute geniu... Nevermind, you got two wrong!";
          cout << "\033[1;33m"; // Makes text yellow
          typeWriteText(eightScore);
          cout << "\033[0m"; // Resets textcolor
          cout << endl;
        } 
        else if (score <= 7 && score >= 6) {
          string sevenToSixScore = "Good job!";
          cout << "\033[1;33m"; // Makes text yellow
          typeWriteText(sevenToSixScore);
          cout << "\033[0m"; // Resets textcolor
          cout << endl;
        } 
        else if (score <= 5 && score >= 3) {
          string fiveToThreeScore = "Eh, you could've done better.";
          cout << "\033[1;33m"; // Makes text yellow
          typeWriteText(fiveToThreeScore);
          cout << "\033[0m"; // Resets textcolor
          cout << endl;
        } 
        else if (score <= 2 && score >= 1) {
          string twoToOneScore = "Seriously?";
          cout << "\033[1;31m"; // Makes text red
          typeWriteText(twoToOneScore);
          cout << "\033[0m"; // Resets textcolor
          cout << endl;
        } 
        else if (score == 0) {
          string failScore = "How? That's like impossible, there is no way you got all of them wrong... YOU SUCK!";
          cout << "\033[1;31m"; // Makes text red
          typeWriteText(failScore);
          cout << "\033[0m"; // Resets textcolor
          cout << endl;
        }
        cout << "You spent a total of: " << timer.elapsedTime() << " seconds!" << endl;
        cout << "Would you like to save your score? (y/n): ";
        cin >> saveScore; // Saves score
        if (tolower(saveScore) == 'y') {
          cout << "Enter player name: ";
          cin.ignore();
          getline(cin, name); // Gets player name input
          ofstream file("scores.txt", ios::app); // Opens scoreboard textfile
          file << name << ", " << questionSetFile << ", " << "Score: " << score << ", " << timer.elapsedTime() << " seconds" << endl;
          file.close();
        }
      }
      cout << "Do you want to play again? (y/n): ";
      cin >> playAgain; // Prompts user to play again
      break;
    }
    case 2: {
      // Loads scores
      string scores;
      string scoreText = "Loading scores...";
      typeWriteText(scoreText);
      cout << endl << endl;
      ifstream file("scores.txt"); // Loads file
      if (file.is_open()) {        // Opens file
        string line;
        while (getline(file, line)) {
          scores += line + "\n"; // Writes scores into string
        }
        file.close(); // Closes file
      }
      cout << scores << endl;
      playAgain = 'y';
      break;
    }
    case 3: {
      string exitingText = "Exiting the Memory System.";
      rainbowText(exitingText);
      cout << endl;
      cout << "\033[0m"; // Resets textcolor
      playAgain = 'n';
      break;
    }
    default: {
      cout << "Invalid choice. Please try again.\n"; // Defaults to invalidity
      playAgain = 'y';
      break;
    }
    }
  } 
  while (tolower(playAgain) == 'y'); // Checks if player wants to play again
  string goodbyeText = "See you next time!";
  rainbowText(goodbyeText);
  cout << "\033[0m"; // Resets textcolor
  return 0;
}