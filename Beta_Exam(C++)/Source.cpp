#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <Windows.h>

using namespace std;


class Question {
public:
    string text;
    vector<string> options;
    int correctOption;
   
    Question() {}

    Question(const string& questionText, const vector<string>& questionOptions, int correct)
        : text(questionText), options(questionOptions), correctOption(correct) {}
};

class Guest {
public:
    string login;
    string password;
    string name;
    string category;
    string test;
    string address;
    string phone;
    vector<int> scores;
    vector<Question> questions;

    Guest(const string& guestName, const string& guestAddress, const string& guestPhone, const string& guestLogin, const string& guestPassword)
        : login(guestLogin), password(guestPassword), name(guestName), address(guestAddress), phone(guestPhone) {}

    void takeTest(const Guest& guest, const string& category, const string& test, const vector<Question>& questions) {
        name = guest.name;
        this->category = category;
        this->test = test;

        cout << "��� ������ ���, " << name << "!\n";
        cout << "��������: " << category << "\n";
        cout << "����: " << test << "\n\n";

        int score = 0;

        for (const Question& question : questions) {
            cout << question.text << "\n";
            cout << "������� ��������:\n";
            for (size_t i = 0; i < question.options.size(); ++i) {
                cout << i + 1 << ". " << question.options[i] << "\n";
            }

            int answer;
            cout << "������ ���� ������� (1-" << question.options.size() << "): ";
            cin >> answer;

            if (answer == question.correctOption) {
                cout << "���������!\n";
                score++;
            }
            else {
                cout << "�����������!\n";
            }
            cout << "----------------------------------------\n";
        }

        scores.push_back(score);

        int maxScore = questions.size();
        int maxGrade = 12;
        int grade = (score * maxGrade) / maxScore;

        cout << "���� ���������. ���� ������: " << grade << "/" << maxGrade << "\n";
        cout << "³������ ���������� ��������: " << (score * 100.0) / maxScore << "%\n";
        cout << "----------------------------------------\n";
    }

    void viewPreviousResults() {
        cout << "�������� ���������� ����������:\n";
        for (size_t i = 0; i < scores.size(); ++i) {
            int maxScore = 5;
            int maxGrade = 12;
            int grade = (scores[i] * maxGrade) / maxScore;

            cout << "���� " << i + 1 << ": " << scores[i] << "/" << maxScore << " (������: " << grade << "/" << maxGrade << ")\n";
        }
        cout << "----------------------------------------\n";
    }
};

class TestSystem {
public:
    vector<Guest> guests;

    void removeGuest(const string& login) {
        for (auto it = guests.begin(); it != guests.end(); ++it) {
            if (it->login == login) {
                guests.erase(it);
                return;
            }
        }
        cout << "����������� � ������ " << login << " �� ��������.\n";
    }

    void modifyGuest(const string& login) {
        for (auto& guest : guests) {
            if (guest.login == login) {
                string newName, newAddress, newPhone;
                cout << "������ ���� ��'� �����������: ";
                cin.ignore();
                getline(cin, newName);
                cout << "������ ���� ������ �����������: ";
                getline(cin, newAddress);
                cout << "������ ����� ������� �����������: ";
                getline(cin, newPhone);

                guest.name = newName;
                guest.address = newAddress;
                guest.phone = newPhone;

                cout << "���������� ��� ����������� � ������ " << login << " ������.\n";
                return;
            }
        }
        cout << "����������� � ������ " << login << " �� ��������.\n";
    }

    void registerGuest() {
        string name;
        cout << "������ ��� ��'�: ";
        cin >> name;

        string address;
        cout << "������ ���� ������� ������: ";
        cin.ignore();
        getline(cin, address);

        string phone;
        cout << "������ ��� ����� ��������: ";
        getline(cin, phone);

        bool uniqueLogin = false;
        while (!uniqueLogin) {
            string login;
            cout << "������ ������� ����: ";
            cin >> login;

            string password;
            cout << "������ ������� ������: ";
            cin >> password;

            uniqueLogin = isUniqueLogin(login);

            if (uniqueLogin) {
                guests.push_back(Guest{ name, address, phone, login, password });
                cout << "��������� ���������. ³����, " << name << "!\n";
            }
            else {
                cout << "���� ��� ���������������. ���� �����, ��������� �����.\n";
            }
        }
    }

    bool isUniqueLogin(const string& login) {
        for (const Guest& guest : guests) {
            if (guest.login == login) {
                return false;
            }
        }
        return true;
    }

    void viewOverallStatistics() {
        cout << "���������� ���������� ������� �� ����������:\n";

        map<string, int> categoryCounts;

        map<string, int> categoryCorrectAnswers;

        for (const Guest& guest : guests) {
            const string& category = guest.category;
            int score = guest.scores.back(); 

            categoryCounts[category]++;
            categoryCorrectAnswers[category] += score;
        }


        for (const auto& entry : categoryCounts) {
            const string& category = entry.first;
            int count = entry.second;
            int correctAnswers = categoryCorrectAnswers[category];

            int maxScore = 5 * count;
            int maxGrade = 12 * count;
            int grade = (correctAnswers * maxGrade) / maxScore;

            cout << "��������: " << category << "\n";
            cout << "�����: " << count << "\n";
            cout << "���������: " << correctAnswers << "/" << maxScore;
            cout << " (������: " << grade << "/" << maxGrade << ")\n";
            cout << "----------------------------------------\n";
        }
    }

    void viewTestStatistics() {
        cout << "���������� ���������� �� ����������� �������:\n";


        map<string, int> testCounts;

        map<string, int> testCorrectAnswers;

        for (const Guest& guest : guests) {
            const string& test = guest.test;
            int score = guest.scores.back(); 

            testCounts[test]++;
            testCorrectAnswers[test] += score;
        }

        for (const auto& entry : testCounts) {
            const string& test = entry.first;
            int count = entry.second;
            int correctAnswers = testCorrectAnswers[test];

            int maxScore = 5 * count;
            int maxGrade = 12 * count;
            int grade = (correctAnswers * maxGrade) / maxScore;

            cout << "����: " << test << "\n";
            cout << "ʳ������ �����: " << count << "\n";
            cout << "���������: " << correctAnswers << "/" << maxScore;
            cout << " (������: " << grade << "/" << maxGrade << ")\n";
            cout << "----------------------------------------\n";
        }
    }

    void viewUserStatistics() {
        cout << "���������� ��� ������� ������������:\n";

        map<string, int> userTestCounts;

        map<string, int> userCorrectAnswers;

        for (const Guest& guest : guests) {
            const string& user = guest.login;
            int score = guest.scores.back();

            userTestCounts[user]++;
            userCorrectAnswers[user] += score;
        }

        for (const auto& entry : userTestCounts) {
            const string& user = entry.first;
            int count = entry.second;
            int correctAnswers = userCorrectAnswers[user];

            int maxScore = 5 * count;
            int maxGrade = 12 * count;
            int grade = (correctAnswers * maxGrade) / maxScore;

            cout << "����������: " << user << "\n";
            cout << "ʳ������ �����: " << count << "\n";
            cout << "���������: " << correctAnswers << "/" << maxScore;
            cout << " (������: " << grade << "/" << maxGrade << ")\n";
            cout << "----------------------------------------\n";
        }
    }

   //-----------------------------------------------------------------------------

    void guestLogin() {
        Guest* guest = nullptr;
        string login;
        string password;
        cout << "������ ����: ";
        cin >> login;
        cout << "������ ������: ";
        cin >> password;

        bool found = false;
        for (Guest& g : guests) {
            if (g.login == login && g.password == password) {
                found = true;
                guest = &g;
                break;
            }
        }

        if (found) {
            cout << "������� ����.\n";
            cout << "� �����������, " << guest->name << "!\n";

            int option;
            do {
                cout << "\n����:\n";
                cout << "1. ������ ����\n";
                cout << "2. ����������� �������� ����������\n";
                cout << "3. �����\n";
                cout << "������� �����: ";
                cin >> option;

                switch (option) {
                case 1:
                    cout << "������� ��������:\n"
                        << "1 - ճ��\n"
                        << "2 - Գ����\n"
                        << "������ ����: ";
                    int categoryChoice;
                    cin >> categoryChoice;

                    if (categoryChoice == 1) 
                        takeChemistryTest(*guest);
                    else if (categoryChoice == 2)
                        takePhysicsTest(*guest);
                    else {
                        cout << "���������� ������!\n";
                    }
                    break;
                case 2:
                    guest->viewPreviousResults();
                    break;
                case 3:
                    cout << "�� ���������, " << guest->name << "!\n";
                    break;
                default:
                    cout << "������ �����. ���� �����, ������� �����.\n";
                    break;
                }
            } while (option != 3);
        }
        else
            cout << "������� ����. ���� �����, ��������� �����.\n";

    }

    void takeChemistryTest(Guest& guest) {
        cout << "������� ����:\n"
            << "1 - �������� ����\n"
            << "2 - ���������� ����\n"
            << "������ ����: ";
        int testChoice;
        cin >> testChoice;

        switch (testChoice) {
        case 1:
            takeOrganicChemistryTest(guest);
            break;
        case 2:
            takeInorganicChemistryTest(guest);
            break;
        default:
            cout << "���������� ������ �����!\n";
            break;
        }
    }

    void takeOrganicChemistryTest(Guest& guest) {
        vector<Question> chemistryQuestions = {
            { "� ��� ��������, �� �������� ��, ������ �� ����������?", { "VI", "��", "���", "�V" }, 4 },
            { "�������, �� ����� ��������� �����, ��� �������� �� ������� �������, �����������?", { "���������", "����������", "�������������� ������", "���������������� ������" }, 1 },
            { "������� ��������� ��?", { "�����", "������", "������", "�����" }, 3 },
            { "��� ��������� ������, �������� ���� ����� �� ������� � �������� �� ���� ��� ����� ���� ����� ��2, ����������?", { "����������� ���", "�������������� ���", "��� �������", "��� ����������" }, 1 },
            { "��������� ����� �����, ������� �� ����, �� �� ������, �����������, ����� ����� �� ����?", { "�������", "������", "�����", "�������" }, 4 }
        };

        guest.takeTest(guest, "Chemistry", "Organic Chemistry", chemistryQuestions);
    }

    void takeInorganicChemistryTest(Guest& guest) {
        vector<Question> chemistryQuestions = {
            { "������� ����� �������� ���������� ���������� ��'�������� �����?", { "�", "Fe", "Hg", "Co" }, 2 },
            { "������ ����� ����, �� ����� ��������", { "����", "�����", "����", "�����" }, 4 },
            { "���� � ������ � ������� �����������?", { "����", "����", "�������", "��������" }, 4 },
            { "���� ����� � ������������?", { "Ra", "Ca", "Fr", "Li" }, 3 },
            { "�� � ���� �����������?", { "���", "�" }, 1 }
        };

        guest.takeTest(guest, "Chemistry", "Inorganic Chemistry", chemistryQuestions);
    }

    void takePhysicsTest(Guest& guest) {
        cout << "������� ����:\n"
            << "1 - �������� ������\n"
            << "2 - �������\n"
            << "������ ����: ";
        int testChoice;
        cin >> testChoice;

        switch (testChoice) {
        case 1:
            takeQuantumPhysicsTest(guest);
            break;
        case 2:
            takeMechanicsTest(guest);
            break;
        default:
            cout << "���������� ������ �����!\n";
            break;
        }
    }

    void takeQuantumPhysicsTest(Guest& guest) {
        vector<Question> quantumPhysicsQuestions = {
            { "�� ���� ��������� ��?", { "������� ����������", "������� ����㳿", "������� ����", "������� ����� �������" }, 1 },
            { "���� ������� �������� ������� ��������, �� ��������� �� ����� ����� ��������� ��������������� � ������� ��������?", { "������� �����������", "������� ������������", "������� ������������", "������� ������������" }, 2 },
            { "�� ��� ������������� �������� �������� ������� ���� ������������ ����������?", { "������� ������������ � ������� �����䳿", "�������� ����������� � �����������", "������� ���������������� � ������� ������������", "�������� ������������ � �����������" }, 3 },
            { "�� ���� ��������� ��������� �����?", { "����� ����������� �������� ����� ���'�� � ������� �����������", "���������� �������� ��� ������� ���� ����� ��������", "���������� �������� ����������", "������������� �������� �� ������� ���������" }, 1 },
            { "���� ����� ���'������ � �������������� ��������� ��������, �� ���������� ������ �� �����?", { "����� ��������", "����� �������", "����� �������", "����� ��������" }, 1 }
        };

        guest.takeTest(guest, "Physics", "Quantum Physics", quantumPhysicsQuestions);
    }

    void takeMechanicsTest(Guest& guest) {
        vector<Question> mechanicsQuestions = {
            { "�� ���� �������?", { "��������� ��� �� ���� ��������", "��������� ��� �� ���� �������", "��������� ��� �� ���� ����", "��������� ��� �� ���� �����" }, 1 },
            { "���� ����� ������� ��������, �� �� ����� �� 䳺 ���������� �� �������� � ���� �� ������� ��, � �� �� 䳿 ��������� ������?", { "������ ����� �������", "������ ����� �������", "����� ����� �������", "��������� ����� �������" }, 3 },
            { "��� ����������� ������ ����?", { "��������� ���� �� �����, ��������� ����� ����� ����������� ����", "����� ���", "��������� ����㳺� ���", "�������� ���" }, 1 },
            { "�� ���� ������ � ������?", { "������� ��������, �� ����������� �������� ������� ���������� ������", "������� ��������, �� ����������� �������� ��������� ������", "������� ��������, �� ����������� ����������� ��������� ������", "������� ��������, �� ����������� �������� �������� ������" }, 4 },
            { "���� ����� ������� ��������, �� ����������� ��� ����������� ���������� ��� � �������� ����������� ��� ���?", { "������ ����� �������", "������ ����� �������", "����� ����� �������", "��������� ����� �������" }, 2 }
        };

        guest.takeTest(guest, "Physics", "Mechanics", mechanicsQuestions);
    }
};

class Admin {
    string login;
    string password;

public:
    Admin(const string& adminLogin, const string& adminPassword)
        : login(adminLogin), password(adminPassword) {}

    string getLogin() {
        return login;
    }
    string getPassword() {
        return password;
    }

    bool isAdmin(const string& adminLogin, const string& adminPassword) const {
        return (login == adminLogin && password == adminPassword);
    }

    void manageUsers(TestSystem& testSystem) {
        string login_s;
        int choice;
        cout << "1. ��������� �����������\n";
        cout << "2. ��������� �����������\n";
        cout << "3. ����������� �����������\n";
        cout << "������� �����: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            testSystem.registerGuest();
            break;
        case 2:
            cout << "������ ���� ����������� ��� ���������: ";
            (getline(cin, login_s)).get();
            testSystem.removeGuest(login_s);
            break;
        case 3:
            cout << "������ ���� ����������� ��� �����������: ";
            (getline(cin, login_s)).get();
            testSystem.modifyGuest(login_s);
            break;
        default:
            cout << "������ �����. ���� �����, ������� �����.\n";
            break;
        }
    }

    void viewStatistics(TestSystem& testSystem) {
        int choice;
        cout << "1. �������� ���������� ���������� ������� �� ����������\n";
        cout << "2. �������� ���������� ���������� �� ����������� �������\n";
        cout << "3. �������� ���������� ���������� �� ����������� �������������\n";
        cout << "������� �����: ";
        cin >> choice;

        switch (choice) {
        case 1:
            testSystem.viewOverallStatistics();
            break;
        case 2:
            testSystem.viewTestStatistics();
            break;
        case 3:
            testSystem.viewUserStatistics();
            break;
        default:
            cout << "������ �����. ���� �����, ������� �����.\n";
            break;
        }
    }

    void manageTesting(TestSystem& testSystem) {
        string text;
        int choice;
        cout << "1. ������ ��������\n";
        cout << "2. ������ ����\n";
        cout << "3. ������ ��������� �� �����\n";
        cout << "4. ������ ���������\n";
        cout << "������� �����: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            addCategory(testSystem);
            break;
        case 2:
            addTest(testSystem);
            break;
        case 3:
            addQuestion(testSystem);
            break;
        case 4:
            int choIce;
            cout << "������ ����� ����� ������� �� ������ �������: \n";
            cout << "1 - �������� ����\n";
            cout << "2 - ���������� ����\n";
            cout << "3 - �������� ������\n";
            cout << "4 - �������\n";
            cout << "��� ����: ";
            cin >> choIce;
            cin.ignore();


            if (choIce > 4 || choIce < 1) {
                cout << "�� ������� ���������� ������!\n";
            }
            else {
                cout << "������ ����� ���������, ��� ������� ������: ";
                (getline(cin, text)).get();
                if (choIce == 1)
                    modifyQuestion(testSystem, "Organic Chemistry", text);
                else if (choIce == 2)
                    modifyQuestion(testSystem, "Inorganic Chemistry", text);
                else if (choIce == 3)
                    modifyQuestion(testSystem, "Quantum Physics", text);
                else
                    modifyQuestion(testSystem, "Mechanics", text);
            }
            break;
        default:
            cout << "������ �����. ���� �����, ������� �����.\n";
            break;
        }
    }

    void addCategory(TestSystem& testSystem) {
        string category;
        cout << "������ ����� �������: ";
        cin.ignore();
        getline(cin, category);

        for (const Guest& guest : testSystem.guests) {
            if (guest.category == category) {
                cout << "�������� ��� ����.\n";
                return;
            }
        }

        cout << "�������� ������.\n";
    }

    void addTest(TestSystem& testSystem) {
        string test;
        cout << "������ ����� �����: ";
        cin.ignore();
        getline(cin, test);

        for (const Guest& guest : testSystem.guests) {
            if (guest.test == test) {
                cout << "���� ��� ����.\n";
                return;
            }
        }

        cout << "���� ������.\n";
    }

    void addQuestion(TestSystem& testSystem) {
        string questionText;
        cout << "������ ����� ���������: ";
        cin.ignore();
        getline(cin, questionText);

        string category;
        cout << "������ ����� �������: ";
        getline(cin, category);

        string test;
        cout << "������ ����� �����: ";
        getline(cin, test);

        Guest* guest = nullptr;
        for (Guest& g : testSystem.guests) {
            if (g.category == category && g.test == test) {
                guest = &g;
                break;
            }
        }

        if (guest == nullptr) {
            cout << "�������� ��� ���� �� �������.\n";
            return;
        }

        for (const Question& q : guest->questions) {
            if (q.text == questionText) {
                cout << "��������� ��� ����.\n";
                return;
            }
        }

        Question newQuestion;
        newQuestion.text = questionText;
        guest->questions.push_back(newQuestion);

        cout << "��������� ������.\n";
    }

    void modifyQuestion(TestSystem& testSystem, const string& test, const string& questionText) {
        for (Guest& guest : testSystem.guests) {
            if (guest.test == test) {
                for (Question& question : guest.questions) {
                    if (question.text == questionText) {
                        cout << "������ ����� ����� ���������: ";
                        cin.ignore();
                        getline(cin, question.text);

                        cout << "������ ������� ������� ��������: ";
                        int optionCount;
                        cin >> optionCount;

                        cout << "������ ������� ��������:\n";
                        cin.ignore();
                        for (int i = 0; i < optionCount; ++i) {
                            cout << i + 1 << ". ";
                            string option;
                            getline(cin, option);
                            question.options.push_back(option);
                        }

                        cout << "������ ����� ��������� ������: ";
                        cin >> question.correctOption;

                        cout << "���� �� ��������� ���������.\n";
                        return;
                    }
                }
            }
        }
        cout << "��������� ��� ����� \"" << test << "\" � ������� \"" << questionText << "\" �� ��������.\n";
    }
};



int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Admin God("Papasik223", "Fork34");
    TestSystem testSystem;
    int choice, regime, choice2;
    bool Exit = false;
    

    do {
        cout << "������� ���� ����� �� ������ �������: \n";
        cout << "0 - ����� � ��������\n";
        cout << "1 - �����������\n";
        cout << "2 - ����������\n";
        cout << "������ ����: ";
        (cin >> regime).get();
        if (regime == 1) {
                string adminLogin, adminPassword;
                cout << "������ ����: ";
                getline(cin, adminLogin);
                cout << "������ ������: ";
                getline(cin, adminPassword);

                if (God.isAdmin(adminLogin, adminPassword)) {
                    do {
                        cout << "³���� ���, " << God.getLogin() << "\n";
                        cout << "��, �� ����������� ���� ������� �������: \n";
                        cout << "1 - ��������� ������������� \n";
                        cout << "2 - �������� ���������� \n";
                        cout << "3 - ��������� ����������� \n";
                        cout << "0 - �����\n";
                        cout << "������ ����: \n";
                        (cin >> choice2).get();
                        switch (choice2) {
                        case 0:
                            cout << "����� �� ��������� ����...\n";
                            Exit = true;
                            break;
                        case 1:
                            God.manageUsers(testSystem);
                            break;
                        case 2:
                            God.viewStatistics(testSystem);
                            break;
                        case 3:
                            God.manageTesting(testSystem);
                            break;
                        default:
                            cout << "���, �� ������� ���������� ������!\n";
                        }
                        cout << "----------------------------------------\n";
                    } while (Exit == false);
                }
                else 
                    cout << "������������ ���� ��� ������. ������ ����������.\n";
        }
        else if (regime == 2) {
            do {
                cout << "���� ������� ����������:\n"
                    << "1 - �����������\n"
                    << "2 - ����(��������)\n"
                    << "0 - �����\n"
                    << "������ ����: ";
                cin >> choice;

                switch (choice) {
                case 0:
                    cout << "����� �� ��������� ����...\n";
                    break;
                case 1:
                    testSystem.registerGuest();
                    break;
                case 2:
                    testSystem.guestLogin();
                    break;
                default:
                    cout << "���������� ����. ����-����� ���������� �� ���.\n";
                    break;
                }

                cout << "----------------------------------------\n";
            } while (choice != 0);
        }
        else if (regime == 0)
            cout << "����� � �������� !!\n";

        else 
            cout << "�� ������� ��������� �����!\n";


        system("pause");
        system("cls");
    } while (regime != 0);


    return 0;
}