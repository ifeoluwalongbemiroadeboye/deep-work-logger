#include <iostream>
#include <string>
#include <vector>
#include <fstream>  // NEW: The File Stream library
#include <limits> 

struct WorkSession {
    std::string focusArea;
    int durationMinutes;
};

int main() {
    std::vector<WorkSession> log;
    int choice;
    const std::string filename = "sessions.txt";

    std::ifstream inFile(filename);
    
    if (inFile.is_open()) {
        int duration;
        std::string focus;
        
        while (inFile >> duration) {
            inFile.ignore();
            std::getline(inFile, focus); 

            log.push_back({focus, duration}); 
        }
        inFile.close(); 
    }

    std::cout << "--- Deep Work Logger ---\n";
    std::cout << "[" << log.size() << " past sessions loaded from file]\n";

    do {
        std::cout << "\n1. Log a Session\n2. View Log\n3. Exit\n4. Clear All Logs\n";
        std::cout << "Choose an option: ";

        if (std::cin >> choice) {

            if (choice == 1) {
                WorkSession session;
                
                std::cout << "What was your focus area?: ";
                std::cin.ignore();
                std::getline(std::cin, session.focusArea);
                
                std::cout << "Duration (minutes): ";
                std::cin >> session.durationMinutes;

                log.push_back(session);

                // --- NEW: Save the new data to the file ---
                std::ofstream outFile(filename, std::ios::app);
                
                if (outFile.is_open()) {
                    outFile << session.durationMinutes << "\n" << session.focusArea << "\n";
                    outFile.close();
                    std::cout << "Session logged and saved to file successfully!\n";
                } else {
                    std::cout << "Error: Could not open file for saving.\n";
                }
                
            } else if (choice == 2) {
                std::cout << "\n--- Your Sessions ---\n";
                int totalTime = 0;
                
                for (size_t i = 0; i < log.size(); i++) {
                    std::cout << "- " << log[i].focusArea << ": " << log[i].durationMinutes << " mins\n";
                    totalTime += log[i].durationMinutes;
                }
                std::cout << "Total deep work: " << totalTime << " mins\n";
            } else if (choice == 4) {
                char confirmation;
                std::cout << "Are you sure you want to clear all logs? (y/n): ";
                std::cin >> confirmation;

                if (confirmation == 'y' || confirmation == 'Y') {
                    log.clear();

                    std::ofstream outFile(filename, std::ios::trunc);
                    if (outFile.is_open()) {
                        outFile.close();
                        std::cout << "All logs cleared successfully.\n";
                    } else {
                        std::cout << "Error: Could not open file to clear logs.\n";
                    }
                } else {
                    std::cout << "Clear logs canceled.\n";
                }
            } else if (choice != 3) {
                std::cout << "Invalid option. Please choose 1, 2, 3, or 4.\n";
            }

        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Invalid input. Please enter a valid number.\n";
            choice = 0; 
        }

    } while (choice != 3);

    std::cout << "Stay disciplined. Goodbye!\n";
    return 0; 
}
