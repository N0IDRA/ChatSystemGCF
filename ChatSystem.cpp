#include <iostream>
#include <regex>
#include <thread>
#include <chrono>
#include <conio.h>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <string>
#include <limits>

using namespace std;

//change variable name 
//                     |
//                     v

void startChatAru();
void startChatKayoko();
void farewellAru();
void farewellKayoko();

//                     ^
//                     |


bool isValidEmail(const string& email) {
    const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return regex_match(email, pattern);
}


void loadingAnimation(int seconds) {
    cout << "\t\t\t\t\t\t\t\t          Loading";
    for (int i = 0; i < seconds; ++i) {
        this_thread::sleep_for(chrono::seconds(1));
        cout << ".";
    }
    cout << endl;
}


// Helper function to convert input to lowercase
string toLowerCase(const string &input) {
    string result = input;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Function to manage which character is online & chnage name of class
//change name here <I suggest go to int main first to change the bool>
void switchCharacter(bool& isAruOnline, bool& isKayokoOnline) {
    if (!isAruOnline && !isKayokoOnline) {

            cout << "Thank you!";
        exit(0);
    }
}

// Function to evaluate basic mathematical expressions
double evaluateExpression(const string &expression) {
    istringstream iss(expression);
    double num1, num2;
    char op;

    iss >> num1 >> op >> num2;
    switch (op) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': return num2 != 0 ? num1 / num2 : NAN;  // Handle division by zero
        default: return NAN;  // Invalid operator
    }
}

// Base Chatbot class
class Chatbot {
protected:
    string character;
    map<string, string> responses;
    map<string, vector<string>> alternatives;

public:
    Chatbot(const string &selectedCharacter) : character(selectedCharacter) {}

    virtual void loadResponses() = 0;

    string getAlternativeKeyword(const string &input) {
        for (const auto &pair : alternatives) {
            for (const auto &alt : pair.second) {
                if (input.find(alt) != string::npos) {
                    return pair.first;
                }
            }
        }
        return input;
    }




    // Check if user inputs an mathematical expression
    bool isMathExpression(const string &input) {
        return regex_match(input, regex("[-+]?\\d+\\s*[-+*/]\\s*\\d+"));
    }

    void respond(const string &input) {
        string lowerInput = toLowerCase(input);
        lowerInput = getAlternativeKeyword(lowerInput);



        // Handle age-related question
        if (lowerInput.find("how old are you") != string::npos) {
            int userAge;
            string ageInput;
            ageInputLoop:
            cout << "<> (" << character << "): Can't tell you, it's a secret.. Anyways, How old are you?\n";

            cin >> ageInput;

try {
    userAge = stoi(ageInput);  // Convert input string to integer
} catch (exception& e) {
    cout << "Invalid input! Please enter a valid number for your age.\n";
    cin.clear();  // Clear the error flag
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore the invalid input
    goto ageInputLoop;  // Jump back to input prompt
}

            if (userAge > 100) {
                cout << "<> (" << character << "): Wow! Over a century old? That's amazing!" << endl;
            } else if (userAge > 50) {
                cout << "<> (" << character << "): You’re quite experienced. I would say you’re old... but in a good way!" << endl;
            } else if (userAge >= 30 && userAge <= 40) {
                cout << "<> (" << character << "): Ah, you're middle-aged. A perfect time for new adventures." << endl;
            } else if (userAge < 30) {
                cout << "<> (" << character << "): You're still young! Full of energy and potential!" << endl;
            } else {
        cout << "Hmm, that doesn't seem right. Please try again.\n";
        goto ageInputLoop;
    }

            return;
        }


        //Guessing Game
    if (lowerInput.find("guessing game") != string::npos) {
    int targetNumber = 68;  // The number the user has to guess
    int userGuess;
    int attempts = 0;
    const int maxAttempts = 5;  // Maximum attempts

    while (attempts < maxAttempts) {
    string guessinput;
    cout << "<> (" << character << "): Take a guess.. The number is between 50 to 70: ";

    cin >> guessinput;

    // Check for a valid integer input
    try {
        userGuess = stoi(guessinput);  // Convert input string to integer
    } catch (invalid_argument& e) {
        cout << "<> (" << character << "): Invalid input! Please enter a number.\n";
        cin.clear();  // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore the invalid input
        continue;  // Continue to the next iteration
    }

    // Existing logic for guessing...
    if (userGuess == targetNumber) {
        cout << "<> (" << character << "): Congratulations! You've guessed the right number!\n";
        break;
    } else if (abs(userGuess - targetNumber) <= 2) {
        cout << "<> (" << character << "): You're very close!\n";
    } else if (userGuess > targetNumber) {
        cout << "<> (" << character << "): That's too high!\n";
    } else {
        cout << "<> (" << character << "): That's too low!\n";
    }

    attempts++;

    if (attempts == maxAttempts) {
        cout << "<> (" << character << "): Sorry, you're out of attempts! The correct number was " << targetNumber << ". Better luck next time!\n";
    }
}
    }

        // Handle math expression
        if (isMathExpression(input)) {
            double result = evaluateExpression(input);
            if (!isnan(result)) {
                cout << "<> (" << character << "): The result is: " << result << endl;
            } else {
                cout << "<> (" << character << "): Error in calculation..." << endl;
            }
            return;
        }

        // Handle other responses
        bool foundResponse = false;

        for (const auto &entry : responses) {
            if (lowerInput.find(entry.first) != string::npos || lowerInput == entry.first) {
                cout << "<> (" << character << "): " << entry.second << endl;
                foundResponse = true;
                break;
            }
        }

        if (!foundResponse) {
            cout << "<> (" << character << "):I don't know how to respond to that..." << endl;
        }
    }
};

// change class Arubot to class <any name u want>

class AruBot : public Chatbot {
public:
    AruBot() : Chatbot("Aru") {
        loadResponses();
    }
    // {"keyword", "response"}

    void loadResponses() override {
        responses = {
            {"hello", "Oh, it's you. What do you want? Want to talk about movies, calculations, or let's play a game like the guessing game? Just let me know what you're up for!"},
        };

//change if you want.,
        alternatives = {
            {"hello", {"hi", "hey", "greetings", "wassup", "sup"}},
            {"movie", {"films", "cinema"}},
            {"bye", {"goodbye", "later", "see you"}},
            {"horror", {"scary"}},
            {"drama", {"telenovela"}},
            {"scifi", {"sci fi", "science fiction"}},
            {"fantasy", {"magic"}},
            {"animation", {"anime", "cartoon", "cartoons", "animations"}},
            {"are you single", {"love", "i want you", "i like you"}},
            {"how old are you", {"age"}},
            {"sure", {"I understand", "of course", "yes", "okay", "ok", "true", "agreed", "me too", "thank you", "thanks", "i see", "let's talk", "lets talk", "i want to talk", "anything"}},
            {"good", {"fine", "great", "awesome", "nice"}},
            {"bad", {"awful", "sad", "depressed"}},
            {"math", {"algebra", "mathematics", "calculate", "calculation", "calculations"}},
            {"climate change", {"weather", "climate"}},
            {"hot", {"warm"}},
            {"cold", {"freezing"}},
            {"unpredictable", {"i can't tell", "i don't know", "not sure", "it's hard to explain"}},
            {"no", {"no thanks", "nope", "nah", "i don't care"}},
            {"hobby", {"hobbies", "do for a living"}},
            {"nice to meet you", {"pleasure to meet you", "kamusta"}},
            {"how are you",{"how about you","and you","what do you do"}},
        };
    }
};

// change class Kayokobot to class <any name of ur variable>
class KayokoBot : public Chatbot {
public:
    KayokoBot() : Chatbot("Kayoko") {
        loadResponses();
    }

    void loadResponses() override {
         responses = {
            {"hello", "Hello, what would you like to talk about? I'm always ready to discuss about films, or even the climate of your world. \n If you need help with calculations or just a thoughtful conversation, I'm here... or will you play a guessing game with me if you want to...."},
            {"movie", "I prefer quiet, thoughtful films. What do you enjoy?"},
            {"action", "It was well-choreographed... I suppose. But did it really need that many car chases? Well... How about another kind of genre?"},
            {"horror", "Horror Movies.. It was horrifying. I couldn't stop watching. Such a gripping atmosphere... How about you? What's your Favorite"},
            {"thriller", "Brilliantly executed. The tension was palpable from start to finish..."},
            {"drama", "Dramas... Their acting was phenomenal. Such deep, emotional layers!"},
            {"scifi", "The concept was intriguing, but I found the execution lacking at times ,Anything Else?"},
            {"fantasy", "Some fantasy elements were impressive, but the story was too conventional."},
            {"documentary", "It was insightful, but I feel like they could've delved deeper into the subject. How about you? any more genres in your mind"},
            {"animation", "The visual creativity was inspiring. A delightful escape from reality...\n Any genres came to your mind?"},
            {"musical", "Musicals.. Some movies I watched had great coordination and their energy were flawless. A captivating performance...Anything else..?"},
            {"bye", "Goodbye, hope we can talk again soon."},
            {"good", "I'm glad to hear that. Keep up the momentum."},
            {"bad", "I understand. Tough times can help you move forward with composure."},
            {"math", "Yes, give me equations like 1+1, 2-2, 3/3 and 3*4, and I'll provide the answer efficiently..."},
            {"how are you", "I'm doing well, thank you for asking. How about yourself?"},
            {"how old are you?", "I'm 18 years old. How about you?"},
            {"are you single", "That's an interesting question... I prefer to focus on my responsibilities. \n can we talk about something else like movie genres? or we can say our goodbyes here..."},
            {"sure", "I'm always here if you need to talk. How about movie genres, math, or a guessing game?"},
            {"climate change", "I'm curious... What's the climate like where you are?"},
            {"hot", "It must make hydration and staying cool important."},
            {"cold", "It must be vital to conserve warmth."},
            {"unpredictable", "We all have uncertainties at times. I can suggest a topic."},
            {"no", "Understood. Let me know if you need something."},
            {"kivotos", "Kivotos is a unique realm focused on strategy and growth. What are your thoughts?"},
            {"smart", "I'd like to believe I am, but intelligence is about constant learning."},
            {"nice to meet you", "Nice to meet you! Let's discuss about movie genres or play a guessing game."},
            {"favorite food", "I find a well-balanced meal sharpens the mind. Let's talk about movies."},
            {"who are you", "I'm Kayoko. I focus on strategy and precision."},
            {"hobby", "Research and strategy planning help me focus. Let's talk about movies."}
        };

        alternatives = {
            {"hello", {"hi", "hey", "greetings", "wassup", "sup"}},
            {"movie", {"films", "cinema"}},
            {"bye", {"goodbye", "later", "see you"}},
            {"horror", {"scary"}},
            {"drama", {"telenovela"}},
            {"scifi", {"sci fi", "science fiction"}},
            {"fantasy", {"magic"}},
            {"animation", {"anime", "cartoon", "cartoons", "animations"}},
            {"are you single", {"love", "i want you", "i like you"}},
            {"how old are you", {"age"}},
            {"sure", {"I understand", "of course", "yes", "okay", "ok", "true", "agreed", "me too", "thank you", "thanks", "i see", "let's talk", "lets talk", "i want to talk", "anything"}},
            {"good", {"fine", "great", "awesome", "nice"}},
            {"bad", {"awful", "sad", "depressed"}},
            {"math", {"algebra", "mathematics", "calculate", "calculation", "calculations"}},
            {"climate change", {"weather", "climate"}},
            {"hot", {"warm"}},
            {"cold", {"freezing"}},
            {"unpredictable", {"i can't tell", "i don't know", "not sure", "it's hard to explain"}},
            {"no", {"no thanks", "nope", "nah", "i don't care"}},
            {"hobby", {"hobbies", "do for a living"}},
            {"nice to meet you", {"pleasure to meet you", "kamusta"}},
            {"how are you",{"how about you","and you","what do you do"}},
        };
    }
};

int main () {
    string username, password, email;
    
    //change the varible names of the bool
    //change all the variables you changed related to bool
    
    bool isAruOnline = true, isKayokoOnline = true;
    char ch;
    const int maxattempts = 3;

    // Login system
    cout << "\t\t\t\t\t\t\t\t<>------------------------<>\n";
    cout << "\t\t\t\t\t\t\t\t     Kivotos Chat System     \n";
    cout << "\t\t\t\t\t\t\t\t<>------------------------<>\n";
    cout << "\t\t\t\t\t\t\t\t-----[  Login Screen  ]-----\n";
    cout << "\t\t\t\t\t\t\t\t<>Enter your Username: ";
    cin >> username;

    cout << "\t\t\t\t\t\t\t\t<>Enter your Password: ";
    ch = _getch();
    while (ch != 13) {
        password.push_back(ch);
        cout << '*';
        ch = _getch();
    }
    cout << endl;
       bool validEmail = false;
    int emailAttempts = 0;

    while (emailAttempts < maxattempts && !validEmail) {
        cout << "\t\t\t\t\t\t\t\t<>Enter your Email: ";
        cin >> email;
        if (isValidEmail(email)) {
            validEmail = true;
        } else {
            emailAttempts++;
            cout << "\t\t\t\t\t\t\t\t<>[Invalid email format.] \n \t\t\t\t\t\t\t\t<>[Attempt "
                 << emailAttempts << " of " << maxattempts << ". Please try again.]\n";
            if (emailAttempts == maxattempts) {
            cout << "\t\t\t\t\t\t\t\t<>Too many invalid email attempts. Access denied.\n";
            cout<<endl;
         
                return 0;
            }
        }
    }



    // Welcome screen with animation
    cout << "\t\t\t\t\t\t\t\t<>------------------------<>\n";
    cout << "\t\t\t\t\t\t\t\t    Kivotos Chat System     \n";
    cout << "\t\t\t\t\t\t\t\t<>------------------------<>\n";
    cout << "\t\t\t\t\t\t\t\t     [    Welcome     ]     \n";
    cout << "\t\t\t\t\t\t\t\t          "<< username <<"       \n"; // Displays user's name
    cout << "\t\t\t\t\t\t\t\t<>------------------------<>\n";
    cout << endl;


    loadingAnimation(5);

    // ChatMate selection screen
     string choiceinput;
    int choice;

    do {
        cout << endl;
        cout << "\t\t\t\t\t\t\t\t<>------------------------<>\n";
        cout << "\t\t\t\t\t\t\t\tPlease Select Your ChatMate!\n";
        cout << "\t\t\t\t\t\t\t\t<>------------------------<>\n";
        cout << "\t\t\t\t\t\t\t\t-----[Users  Available]-----\n";
        cout << "\t\t\t\t\t\t\t\t<>------------------------<>\n";
        cout << endl;

        // Displaying options
        cout << "\t\t\t\t\t\t   ::::::::::::::::::::::::       ::::::::::::::::::::::::\n";
        cout << "\t\t\t\t\t\t   :::::::::@@@@@::::::::::       :::::::::@@@@@::::::::::\n";
        cout << "\t\t\t\t\t\t   ::::::::@@@@@@@:::::::::       ::::::::@@@@@@@:::::::::\n";
        cout << "\t\t\t\t\t\t   ::::::::@@@@@@@:::::::::       ::::::::@@@@@@@:::::::::\n";
        cout << "\t\t\t\t\t\t   :::::::::@@@@@::::::::::       :::::::::@@@@@::::::::::\n";
        cout << "\t\t\t\t\t\t   ::::::::::::::::::::::::       ::::::::::::::::::::::::\n";
        cout << "\t\t\t\t\t\t   ::::::::@@@@@@@:::::::::       ::::::::@@@@@@@:::::::::\n";
        cout << "\t\t\t\t\t\t   ::::::@@@@@@@@@@@:::::::       ::::::@@@@@@@@@@@:::::::\n";
        cout << "\t\t\t\t\t\t   :::::@@@@@@@@@@@@@::::::       :::::@@@@@@@@@@@@@::::::\n";
        cout << "\t\t\t\t\t\t   |1|[Online] Rikuhachima Aru    |2|[Online] Onikata Kayoko\n";
        cout << endl;

        cout << "\t\t\t\t\t\t   ::::::::::::::::::::::::       ::::::::::::::::::::::::\n";
        cout << "\t\t\t\t\t\t   :::::::::@@@@@::::::::::       :::::::::@@@@@::::::::::\n";
        cout << "\t\t\t\t\t\t   ::::::::@@@@@@@:::::::::       ::::::::@@@@@@@:::::::::\n";
        cout << "\t\t\t\t\t\t   ::::::::@@@@@@@:::::::::       ::::::::@@@@@@@:::::::::\n";
        cout << "\t\t\t\t\t\t   :::::::::@@@@@::::::::::       :::::::::@@@@@::::::::::\n";
        cout << "\t\t\t\t\t\t   ::::::::::::::::::::::::       ::::::::::::::::::::::::\n";
        cout << "\t\t\t\t\t\t   ::::::::@@@@@@@:::::::::       ::::::::@@@@@@@:::::::::\n";
        cout << "\t\t\t\t\t\t   ::::::@@@@@@@@@@@:::::::       ::::::@@@@@@@@@@@:::::::\n";
        cout << "\t\t\t\t\t\t   :::::@@@@@@@@@@@@@::::::       :::::@@@@@@@@@@@@@::::::\n";
        cout << "\t\t\t\t\t\t   |3|[Offline] Asagi Mutsuki     |4|[Offline] Igusa Haruka\n";
        cout << endl;

        cout << "\t\t\t\t\t\t\t\t<>------------------------<>\n";
        cout << "\t\t\t\t\t\t\t<>Please enter your choice (1, 2, 3, or 4) \n";
        cout << "\t\t\t\t\t\t\t<>(5) to Exit the chat: ";

        // Read input as a string to check if it can be converted to a valid number
        cin >> choiceinput;

        try {
            choice = stoi(choiceinput);  // Try converting to an integer
        } catch (exception& e) {
            // Handle invalid input (non-integer)
            cout << "\t\t\t\t\t\t\t<>Invalid input! Please enter a number (1-5).\n";
            continue;  // Skip the rest of the loop and prompt again
        }

        cout << "\t\t\t\t\t\t\t\t<>------------------------<>\n";

        // Process choice
        if (choice == 1 && isAruOnline) {
            startChatAru();
            isAruOnline = false;  // Aru goes offline after chatting
        } else if (choice == 2 && isKayokoOnline) {
            startChatKayoko();
            isKayokoOnline = false;  // Kayoko goes offline after chatting
        } else if (choice == 5) {
            cout<<endl;
            cout << "\t\t\t\t\t\t\t\t<>------------------------<>\n";
            cout<<"\t\t\t\t\t\t\t<>Exiting the Kivotos Chat System. Goodbye!\n";
            cout << "\t\t\t\t\t\t\t\t<>------------------------<>\n";
            cout<<endl;
            exit(0);
        } else {
            cout << "\t\t\t\t\t\t\t<>Invalid choice or character offline. Please try again.\n";
        }

        // If both characters are offline, exit the chat system
        //change the names too
        switchCharacter(isAruOnline, isKayokoOnline);

    } while (true);  // Loop until a valid option or exit is selected

    return 0;
    
    //my void is a mess lmao you can change the void varibles to any name
    // void startchat<urbotname>
}
void startChatAru() {
    AruBot aruBot;
    string userInput;

    cout << "\t\t\t\t\t<>You are now chatting with Aru! Say 'hi' to start chatting! or 'bye' to end the chat !.\n";
    cout << endl;
    while (true) {
        cout << "You: ";
        getline(cin >> ws, userInput);

        if (toLowerCase(userInput) == "bye"  || toLowerCase(userInput) == "goodbye" || toLowerCase(userInput) == "see you"   ) {
            farewellAru();
            break;
        }
        //<name of ur bot of the class bot>.respond(userinput)
        aruBot.respond(userInput);
    }
}

void startChatKayoko() {
    KayokoBot kayokoBot;
    string userInput;

    cout << "\t\t\t\t<>You are now chatting with Kayoko! Say 'hi' to start chatting! or 'bye' to end the chat!.\n";
    cout << endl;
    while (true) {
        cout << "You: ";
        getline(cin >> ws, userInput);

        if (toLowerCase(userInput) == "bye"  || toLowerCase(userInput) == "goodbye" || toLowerCase(userInput) == "see you"   ) {
            farewellKayoko();
            break;
        }
        kayokoBot.respond(userInput);
    }
}

//change farewellAru to farewell<name>
void farewellAru() {
    cout << "<> Aru: I expect to see you back soon for more action. See you!\n";
}

void farewellKayoko() {
    cout << "<> Kayoko: Very well. Take care, and don't forget to stay sharp.\n";
}
