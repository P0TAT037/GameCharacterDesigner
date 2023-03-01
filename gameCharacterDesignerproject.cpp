#include <iostream>
#include <vector>
using namespace std;


class Character;
class Configuration;

class CharacterType {
public:
    const float speed;
    const float power;
    const float range;
    const float health;

    CharacterType(float speed, float power, float range, float health) : speed(speed), power(power), range(range), health(health) {};

    virtual void attack() = 0;
    virtual void takeDamage() = 0;
};

class SwordMaster : public CharacterType {
public:
    SwordMaster() : CharacterType(30, 80, 20, 100) {}

    void attack() override {
        cout << "SwordMaster deals damage" << endl;
    }
    void takeDamage() override {
        cout << "SwordMaster takes damage" << endl;
    }
};

class Archer : public CharacterType {
public:
    Archer() : CharacterType(90, 40, 120, 60) {}

    void attack() override {
        cout << "Archer deals damage" << endl;
    }
    void takeDamage() override {
        cout << "Archer takes damage" << endl;
    }
};

class Configuration {
private:
    inline static vector<Character*> Characters;

    inline static Configuration* conf = nullptr;
    inline static float speedMultiplier = 1;
    inline static float powerMultiplier = 1;
    inline static float rangeMultiplier = 1;
    inline static float healthMultiplier = 1;

    Configuration() {
        Configuration::conf = this;
    }

public:
    void addObserver(Character* character) {
        this->Characters.push_back(character);
    }
    float getSpeedMultiplier() {
        return speedMultiplier;
    }

    float getPowerMultiplier() {
        return powerMultiplier;
    }

    float getRangeMultiplier() {
        return rangeMultiplier;
    }

    float getHealthMultiplier() {
        return healthMultiplier;
    }

    void notify();
    void SetAttributes(float speed, float power, float range, float health) {
        Configuration::speedMultiplier = speed;
        Configuration::powerMultiplier = power;
        Configuration::rangeMultiplier = range;
        Configuration::healthMultiplier = health;
        notify();
    }

    static Configuration getConfig() { //singletoon
        if (conf == nullptr) {
            conf = new Configuration();
        }
        return *conf;
    }
};

class Character {
private:
    string name;
    float speed;
    float power;
    float range;
    float health;

    CharacterType* playerType;
    Configuration config = Configuration::getConfig();
public:
    Character(string name, CharacterType* type) : name(name), playerType(type) {
        this->speed = type->speed;
        this->power = type->power;
        this->range = type->range;
        this->health = type->health;
        config.addObserver(this);
    }

    void attack() {
        playerType->attack();
    }

    void takeDamage() {
        playerType->takeDamage();
    }

    void display() {
        cout << "==========================" << endl;
        cout << "Name: " << name << endl;
        cout << "==========================" << endl;
        cout << "Speed: " << speed << endl;
        cout << "Power: " << power << endl;
        cout << "Range: " << range << endl;
        cout << "Health: " << health << endl;
        cout << "==========================" << endl;
    }
    
    void update() {
        this->speed = speed * config.getSpeedMultiplier();
        this->power = power * config.getPowerMultiplier();
        this->range = range * config.getRangeMultiplier();
        this->health = health * config.getHealthMultiplier();
    };
};

void Configuration::notify() {
    for (int i = 0; i < (&Characters)->size(); i++) {
        Characters[i]->update();
    }

}

int showMenu() {
    system("cls");
    cout << "1. Create Character" << endl;
    cout << "2. Display Character" << endl;
    cout << "3. Change Configuration" << endl;
    cout << "0. Exit" << endl;
    cout << ">> ";
    int choice;
    cin >> choice;
    return choice;
}

int main() {
    vector<Character*> characters;
    bool flag = true;
    while (flag) {
        cin.clear();
        int choice = showMenu();
        switch (choice) {
        
        case 1:
        {
            system("cls");
            cout << "Enter the character's name: ";
            string name;
            cin >> name;
            cout << "Choose the type: " << endl;
            cout << "1. SwordMaster" << endl;
            cout << "2. Archer" << endl;
            cout << ">> ";
            int type;
            cin >> type;
            CharacterType* playerType;
            switch (type) {
            case 1:
                playerType = new SwordMaster();
                break;
            case 2:
                playerType = new Archer();
                break;
            default:
                cout << "Invalid type, using SwordMaster by default" << endl;
                playerType = new SwordMaster();
                system("pause");
                break;
            }
            Character* character = new Character(name, playerType);
            characters.push_back(character);
            cout << "Character created" << endl;
            system("pause");
            break;
        }
        case 2: {
            system("cls");
            for (auto& character : characters) {
                character->display();
                character->attack();
                character->takeDamage();
                cout << "==========================" << endl;
            }
            cout << "1. Change Configuration" << endl;
            cout << "2. Back" << endl;
            cout << ">> ";
            int choice;
            cin >> choice;
            while (choice == 1) {
                system("cls");
                for (auto& character : characters) {
                    character->display();
                    character->attack();
                    character->takeDamage();
                    cout << "==========================" << endl;
                }

                cout << "to change configurations enter them in this order:\n speedMultiplier powerMultiplier rangeMultiplier healthMultiplier" << endl;
                cout << ">> ";
                float speed, power, range, health;
                cin >> speed >> power >> range >> health;
                Configuration::getConfig().SetAttributes(speed, power, range, health);
                system("cls");
                for (auto& character : characters) {
                    character->display();
                    character->attack();
                    character->takeDamage();
                    cout << "==========================" << endl;
                }
                cout << "1. Change Configuration" << endl;
                cout << "2. Back" << endl;
                cout << ">> ";
                cin >> choice;
            }

            break;
        }
        
        case 3: {
            system("cls");
            cout << "to change configurations enter them in this order:\n speedMultiplier powerMultiplier rangeMultiplier healthMultiplier" << endl;
            cout << ">> ";
            float speed, power, range, health;
            cin >> speed >> power >> range >> health;
            Configuration::getConfig().SetAttributes(speed, power, range, health);
            cout << "Configuration changed" << endl;
            system("pause");
            break;
        }
        case 0: {
            flag = false;
            break;
        }
        default:
            cout << "invalid choice" << endl;
            system("pause");
            continue;
        }
    }
    return 0;
}


