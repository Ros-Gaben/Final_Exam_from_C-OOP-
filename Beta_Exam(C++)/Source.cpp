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

        cout << "Раді бачити вас, " << name << "!\n";
        cout << "Категорія: " << category << "\n";
        cout << "Тест: " << test << "\n\n";

        int score = 0;

        for (const Question& question : questions) {
            cout << question.text << "\n";
            cout << "Варіанти відповідей:\n";
            for (size_t i = 0; i < question.options.size(); ++i) {
                cout << i + 1 << ". " << question.options[i] << "\n";
            }

            int answer;
            cout << "Введіть свою відповідь (1-" << question.options.size() << "): ";
            cin >> answer;

            if (answer == question.correctOption) {
                cout << "Правильно!\n";
                score++;
            }
            else {
                cout << "Неправильно!\n";
            }
            cout << "----------------------------------------\n";
        }

        scores.push_back(score);

        int maxScore = questions.size();
        int maxGrade = 12;
        int grade = (score * maxGrade) / maxScore;

        cout << "Тест завершено. Ваша оцінка: " << grade << "/" << maxGrade << "\n";
        cout << "Відсоток правильних відповідей: " << (score * 100.0) / maxScore << "%\n";
        cout << "----------------------------------------\n";
    }

    void viewPreviousResults() {
        cout << "Попередні результати тестування:\n";
        for (size_t i = 0; i < scores.size(); ++i) {
            int maxScore = 5;
            int maxGrade = 12;
            int grade = (scores[i] * maxGrade) / maxScore;

            cout << "Тест " << i + 1 << ": " << scores[i] << "/" << maxScore << " (Оцінка: " << grade << "/" << maxGrade << ")\n";
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
        cout << "Користувача з логіном " << login << " не знайдено.\n";
    }

    void modifyGuest(const string& login) {
        for (auto& guest : guests) {
            if (guest.login == login) {
                string newName, newAddress, newPhone;
                cout << "Введіть нове ім'я користувача: ";
                cin.ignore();
                getline(cin, newName);
                cout << "Введіть нову адресу користувача: ";
                getline(cin, newAddress);
                cout << "Введіть новий телефон користувача: ";
                getline(cin, newPhone);

                guest.name = newName;
                guest.address = newAddress;
                guest.phone = newPhone;

                cout << "Інформацію про користувача з логіном " << login << " змінено.\n";
                return;
            }
        }
        cout << "Користувача з логіном " << login << " не знайдено.\n";
    }

    void registerGuest() {
        string name;
        cout << "Введіть своє ім'я: ";
        cin >> name;

        string address;
        cout << "Введіть свою домашню адресу: ";
        cin.ignore();
        getline(cin, address);

        string phone;
        cout << "Введіть свій номер телефону: ";
        getline(cin, phone);

        bool uniqueLogin = false;
        while (!uniqueLogin) {
            string login;
            cout << "Введіть бажаний логін: ";
            cin >> login;

            string password;
            cout << "Введіть бажаний пароль: ";
            cin >> password;

            uniqueLogin = isUniqueLogin(login);

            if (uniqueLogin) {
                guests.push_back(Guest{ name, address, phone, login, password });
                cout << "Реєстрація завершена. Вітаємо, " << name << "!\n";
            }
            else {
                cout << "Логін вже використовується. Будь ласка, спробуйте інший.\n";
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
        cout << "Результати тестування загалом за категоріями:\n";

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

            cout << "Категорія: " << category << "\n";
            cout << "Тестів: " << count << "\n";
            cout << "Результат: " << correctAnswers << "/" << maxScore;
            cout << " (Оцінка: " << grade << "/" << maxGrade << ")\n";
            cout << "----------------------------------------\n";
        }
    }

    void viewTestStatistics() {
        cout << "Результати тестування за конкретними тестами:\n";


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

            cout << "Тест: " << test << "\n";
            cout << "Кількість тестів: " << count << "\n";
            cout << "Результат: " << correctAnswers << "/" << maxScore;
            cout << " (Оцінка: " << grade << "/" << maxGrade << ")\n";
            cout << "----------------------------------------\n";
        }
    }

    void viewUserStatistics() {
        cout << "Статистика для окремих користувачів:\n";

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

            cout << "Користувач: " << user << "\n";
            cout << "Кількість тестів: " << count << "\n";
            cout << "Результат: " << correctAnswers << "/" << maxScore;
            cout << " (Оцінка: " << grade << "/" << maxGrade << ")\n";
            cout << "----------------------------------------\n";
        }
    }

   //-----------------------------------------------------------------------------

    void guestLogin() {
        Guest* guest = nullptr;
        string login;
        string password;
        cout << "Введіть логін: ";
        cin >> login;
        cout << "Введіть пароль: ";
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
            cout << "Успішний вхід.\n";
            cout << "З поверненням, " << guest->name << "!\n";

            int option;
            do {
                cout << "\nМеню:\n";
                cout << "1. Пройти тест\n";
                cout << "2. Переглянути попередні результати\n";
                cout << "3. Вийти\n";
                cout << "Виберіть опцію: ";
                cin >> option;

                switch (option) {
                case 1:
                    cout << "Виберіть категорію:\n"
                        << "1 - Хімія\n"
                        << "2 - Фізика\n"
                        << "Зробіть вибір: ";
                    int categoryChoice;
                    cin >> categoryChoice;

                    if (categoryChoice == 1) 
                        takeChemistryTest(*guest);
                    else if (categoryChoice == 2)
                        takePhysicsTest(*guest);
                    else {
                        cout << "Неможливий варіант!\n";
                    }
                    break;
                case 2:
                    guest->viewPreviousResults();
                    break;
                case 3:
                    cout << "До побачення, " << guest->name << "!\n";
                    break;
                default:
                    cout << "Невірна опція. Будь ласка, виберіть знову.\n";
                    break;
                }
            } while (option != 3);
        }
        else
            cout << "Невірний логін. Будь ласка, спробуйте знову.\n";

    }

    void takeChemistryTest(Guest& guest) {
        cout << "Виберіть тест:\n"
            << "1 - Органічна хімія\n"
            << "2 - Неорганічна хімія\n"
            << "Зробіть вибір: ";
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
            cout << "Неможливий варіант тесту!\n";
            break;
        }
    }

    void takeOrganicChemistryTest(Guest& guest) {
        vector<Question> chemistryQuestions = {
            { "У всіх сполуках, за винятком СО, Карбон має валентність?", { "VI", "ІІ", "ІІІ", "ІV" }, 4 },
            { "Сполуки, які мають однаковий склад, але різняться за будовою молекул, називаються?", { "ізомерами", "гомологами", "функціональною групою", "характеристичною групою" }, 1 },
            { "Насичені вуглеводні це?", { "арени", "алкени", "алкани", "алкіни" }, 3 },
            { "Ряд органічних сполук, молекули яких подібні за будовою й різняться на одну або кілька груп атомів СН2, називається?", { "гомологічний ряд", "функціональний ряд", "ряд ізомерів", "ряд вуглеводнів" }, 1 },
            { "Безбарвна в’язка рідина, солодка на смак, не має запаху, гігроскопічна, трохи важча за воду?", { "метанол", "бензол", "фенол", "гліцерол" }, 4 }
        };

        guest.takeTest(guest, "Chemistry", "Organic Chemistry", chemistryQuestions);
    }

    void takeInorganicChemistryTest(Guest& guest) {
        vector<Question> chemistryQuestions = {
            { "Завдяки якому елементу гемоглобіну відбувається зв'язування кисню?", { "К", "Fe", "Hg", "Co" }, 2 },
            { "Вкажіть назву йону, що віддав електрон", { "анод", "катод", "аніон", "катіон" }, 4 },
            { "Який з металів є найбільш тугоплавким?", { "хром", "цезій", "кобальт", "вольфрам" }, 4 },
            { "Який метал є найактивнішим?", { "Ra", "Ca", "Fr", "Li" }, 3 },
            { "Чи є вода розчинником?", { "так", "ні" }, 1 }
        };

        guest.takeTest(guest, "Chemistry", "Inorganic Chemistry", chemistryQuestions);
    }

    void takePhysicsTest(Guest& guest) {
        cout << "Виберіть тест:\n"
            << "1 - Квантова фізика\n"
            << "2 - Механіка\n"
            << "Зробіть вибір: ";
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
            cout << "Неможливий варіант тесту!\n";
            break;
        }
    }

    void takeQuantumPhysicsTest(Guest& guest) {
        vector<Question> quantumPhysicsQuestions = {
            { "Що таке квантовий біт?", { "Одиниця інформації", "Одиниця енергії", "Одиниця часу", "Одиниця виміру довжини" }, 1 },
            { "Який принцип квантової механіки стверджує, що одночасно не можна точно визначити місцезнаходження і імпульс частинки?", { "принцип визначеності", "принцип неозначеності", "принцип суперпозиції", "принцип перетворення" }, 2 },
            { "Які два фундаментальні принципи квантової механіки були сформульовані Ейнштейном?", { "принцип суперпозиції і принцип взаємодії", "принципи дискретності і квантування", "принцип неопределенности и принцип соответствия", "принципы противоречия и причинности" }, 3 },
            { "Що таке квантовий тунельний ефект?", { "явище проникнення частинки через бар'єр з високим потенціалом", "виникнення частинки при зіткненні двох інших частинок", "поглинання частинки електроном", "випаровування частинки під впливом нагрівання" }, 1 },
            { "Який ефект пов'язаний зі спостереженням квантових частинок, що вчиняються подібно до хвиль?", { "ефект Комптона", "ефект Томсона", "ефект Доплера", "ефект Архимеда" }, 1 }
        };

        guest.takeTest(guest, "Physics", "Quantum Physics", quantumPhysicsQuestions);
    }

    void takeMechanicsTest(Guest& guest) {
        vector<Question> mechanicsQuestions = {
            { "Що таке інерція?", { "схильність тіла до зміни швидкості", "схильність тіла до зміни позиції", "схильність тіла до зміни маси", "схильність тіла до зміни форми" }, 1 },
            { "Який закон Ньютона стверджує, що на кожну дію діє протилежна за напрямом і рівна за модулем дія, і що ці дії виникають парами?", { "перший закон Ньютона", "другий закон Ньютона", "третій закон Ньютона", "четвертий закон Ньютона" }, 3 },
            { "Чим визначається момент сили?", { "проекцією сили на пряму, проходячу через точку прикладання сили", "масою тіла", "кінетичною енергією тіла", "швидкістю тіла" }, 1 },
            { "Що таке робота в фізиці?", { "фізична величина, що характеризує здатність системи виконувати роботу", "фізична величина, що характеризує швидкість виконання роботи", "фізична величина, що характеризує ефективність виконання роботи", "фізична величина, що характеризує величину виконаної роботи" }, 4 },
            { "Який закон Ньютона стверджує, що прискорення тіла пропорційне прикладеній силі і зворотно пропорційне масі тіла?", { "перший закон Ньютона", "другий закон Ньютона", "третій закон Ньютона", "четвертий закон Ньютона" }, 2 }
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
        cout << "1. Створення користувача\n";
        cout << "2. Видалення користувача\n";
        cout << "3. Модифікація користувача\n";
        cout << "Виберіть опцію: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            testSystem.registerGuest();
            break;
        case 2:
            cout << "Введіть логін користувача для видалення: ";
            (getline(cin, login_s)).get();
            testSystem.removeGuest(login_s);
            break;
        case 3:
            cout << "Введіть логін користувача для модифікації: ";
            (getline(cin, login_s)).get();
            testSystem.modifyGuest(login_s);
            break;
        default:
            cout << "Невірна опція. Будь ласка, виберіть знову.\n";
            break;
        }
    }

    void viewStatistics(TestSystem& testSystem) {
        int choice;
        cout << "1. Перегляд результатів тестування загалом за категоріями\n";
        cout << "2. Перегляд результатів тестування за конкретними тестами\n";
        cout << "3. Перегляд результатів тестування за конкретними користувачами\n";
        cout << "Виберіть опцію: ";
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
            cout << "Невірна опція. Будь ласка, виберіть знову.\n";
            break;
        }
    }

    void manageTesting(TestSystem& testSystem) {
        string text;
        int choice;
        cout << "1. Додати категорію\n";
        cout << "2. Додати тест\n";
        cout << "3. Додати запитання до тесту\n";
        cout << "4. Змінити запитання\n";
        cout << "Виберіть опцію: ";
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
            cout << "Введіть якого тесту питання ви хочете поміняти: \n";
            cout << "1 - Органічна хімія\n";
            cout << "2 - Неорганічна хімія\n";
            cout << "3 - Квантова фізика\n";
            cout << "4 - Механіка\n";
            cout << "Ваш вибір: ";
            cin >> choIce;
            cin.ignore();


            if (choIce > 4 || choIce < 1) {
                cout << "Ви вибрали неможливий варіант!\n";
            }
            else {
                cout << "Введіть текст запитання, яке потрібно змінити: ";
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
            cout << "Невірна опція. Будь ласка, виберіть знову.\n";
            break;
        }
    }

    void addCategory(TestSystem& testSystem) {
        string category;
        cout << "Введіть назву категорії: ";
        cin.ignore();
        getline(cin, category);

        for (const Guest& guest : testSystem.guests) {
            if (guest.category == category) {
                cout << "Категорія вже існує.\n";
                return;
            }
        }

        cout << "Категорія додана.\n";
    }

    void addTest(TestSystem& testSystem) {
        string test;
        cout << "Введіть назву тесту: ";
        cin.ignore();
        getline(cin, test);

        for (const Guest& guest : testSystem.guests) {
            if (guest.test == test) {
                cout << "Тест вже існує.\n";
                return;
            }
        }

        cout << "Тест додано.\n";
    }

    void addQuestion(TestSystem& testSystem) {
        string questionText;
        cout << "Введіть текст запитання: ";
        cin.ignore();
        getline(cin, questionText);

        string category;
        cout << "Введіть назву категорії: ";
        getline(cin, category);

        string test;
        cout << "Введіть назву тесту: ";
        getline(cin, test);

        Guest* guest = nullptr;
        for (Guest& g : testSystem.guests) {
            if (g.category == category && g.test == test) {
                guest = &g;
                break;
            }
        }

        if (guest == nullptr) {
            cout << "Категорія або тест не знайдені.\n";
            return;
        }

        for (const Question& q : guest->questions) {
            if (q.text == questionText) {
                cout << "Запитання вже існує.\n";
                return;
            }
        }

        Question newQuestion;
        newQuestion.text = questionText;
        guest->questions.push_back(newQuestion);

        cout << "Запитання додано.\n";
    }

    void modifyQuestion(TestSystem& testSystem, const string& test, const string& questionText) {
        for (Guest& guest : testSystem.guests) {
            if (guest.test == test) {
                for (Question& question : guest.questions) {
                    if (question.text == questionText) {
                        cout << "Введіть новий текст запитання: ";
                        cin.ignore();
                        getline(cin, question.text);

                        cout << "Введіть кількість варіантів відповідей: ";
                        int optionCount;
                        cin >> optionCount;

                        cout << "Введіть варіанти відповідей:\n";
                        cin.ignore();
                        for (int i = 0; i < optionCount; ++i) {
                            cout << i + 1 << ". ";
                            string option;
                            getline(cin, option);
                            question.options.push_back(option);
                        }

                        cout << "Введіть номер правильної відповіді: ";
                        cin >> question.correctOption;

                        cout << "Зміни до запитання збережено.\n";
                        return;
                    }
                }
            }
        }
        cout << "Запитання для тесту \"" << test << "\" з текстом \"" << questionText << "\" не знайдено.\n";
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
        cout << "Виберіть який режим ви хочете вибрати: \n";
        cout << "0 - Вихід з програми\n";
        cout << "1 - Адміністратор\n";
        cout << "2 - Тестований\n";
        cout << "Зробіть вибір: ";
        (cin >> regime).get();
        if (regime == 1) {
                string adminLogin, adminPassword;
                cout << "Введіть логін: ";
                getline(cin, adminLogin);
                cout << "Введіть пароль: ";
                getline(cin, adminPassword);

                if (God.isAdmin(adminLogin, adminPassword)) {
                    do {
                        cout << "Вітаємо вас, " << God.getLogin() << "\n";
                        cout << "Ви, як адміністратор маєте наступні функції: \n";
                        cout << "1 - Управління користувачами \n";
                        cout << "2 - Перегляд статистики \n";
                        cout << "3 - Управління тестуванням \n";
                        cout << "0 - Вихід\n";
                        cout << "Зробіть вибір: \n";
                        (cin >> choice2).get();
                        switch (choice2) {
                        case 0:
                            cout << "Вихід до головного меню...\n";
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
                            cout << "Упс, ви вибрали неможливий варіант!\n";
                        }
                        cout << "----------------------------------------\n";
                    } while (Exit == false);
                }
                else 
                    cout << "Неправильний логін або пароль. Доступ заборонено.\n";
        }
        else if (regime == 2) {
            do {
                cout << "Меню системи тестування:\n"
                    << "1 - Регестрація\n"
                    << "2 - Вхід(Логінення)\n"
                    << "0 - Вихід\n"
                    << "Зробіть вибір: ";
                cin >> choice;

                switch (choice) {
                case 0:
                    cout << "Вихід до головного меню...\n";
                    break;
                case 1:
                    testSystem.registerGuest();
                    break;
                case 2:
                    testSystem.guestLogin();
                    break;
                default:
                    cout << "Неможливий вибір. Будь-ласка попробуйте ще раз.\n";
                    break;
                }

                cout << "----------------------------------------\n";
            } while (choice != 0);
        }
        else if (regime == 0)
            cout << "Вихід з програми !!\n";

        else 
            cout << "Ви вибрали неіснуючий режим!\n";


        system("pause");
        system("cls");
    } while (regime != 0);


    return 0;
}