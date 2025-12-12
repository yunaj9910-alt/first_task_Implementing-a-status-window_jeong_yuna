#include <iostream>
#include <string>
#include <vector>
#include <limits> // 입력 버퍼 관리를 위해 사용

using namespace std;

// 매크로 정의 (배열 인덱스의 가독성을 높입니다)
#define HP_INDEX 0
#define MP_INDEX 1
#define ATTACK_INDEX 2
#define DEFENSE_INDEX 3
#define STATUS_SIZE 4

// 플레이어 스탯 및 관리 클래스
class Player {
private:
    // status[0]: HP, status[1]: MP, status[2]: 공격력, status[3]: 방어력
    int status[STATUS_SIZE] = { 0 };
    int HPPotion_count = 0;
    int MPPotion_count = 0;
    int level = 1; // 도전 과제: 레벨

public:
    // 생성자: 스탯 초기화 및 포션 지급
    Player() {
        // C++에서는 초기화와 입력 부분을 분리하여 깔끔하게 구성
    }

    // 포션 지급/충전 함수 (도전 과제 반영)
    void setPotion(int count) {
        HPPotion_count += count;
        MPPotion_count += count;
    }

    // 입력 유효성 검사 및 초기화
    void initializeStatus() {
        int hp, mp, attack, defense;
        bool isValid = false;

        // 1. HP, MP 입력 및 유효성 검사
        while (!isValid) {
            cout << "HP와 MP를 입력해주세요: ";
            if (!(cin >> hp >> mp)) {
                cout << "잘못된 입력입니다. 숫자를 입력해주세요." << endl;
                // 입력 실패 시 버퍼 비우기 및 상태 플래그 초기화
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            if (hp <= 50 || mp <= 50) {
                cout << "HP나 MP의 값이 너무 작습니다. 다시 입력해주세요." << endl;
            }
            else {
                isValid = true;
            }
        }
        status[HP_INDEX] = hp;
        status[MP_INDEX] = mp;

        // 2. 공격력, 방어력 입력 및 유효성 검사
        isValid = false;
        while (!isValid) {
            cout << "공격력과 방어력을 입력해주세요: ";
            if (!(cin >> attack >> defense)) {
                cout << "잘못된 입력입니다. 숫자를 입력해주세요." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            if (attack <= 0 || defense <= 0) {
                cout << "공격력이나 방어력의 값이 0 이하입니다. 다시 입력해주세요." << endl;
            }
            else {
                isValid = true;
            }
        }
        status[ATTACK_INDEX] = attack;
        status[DEFENSE_INDEX] = defense;

        // 초기 포션 지급 (5개씩)
        setPotion(5);
        cout << "* 포션이 지급되었습니다. (HP, MP 포션 각 " << HPPotion_count << "개)" << endl;
        cout << "=============================================" << endl;
    }

    // 1. HP UP
    void hpUp() {
        if (HPPotion_count > 0) {
            status[HP_INDEX] += 20;
            HPPotion_count--;
            cout << "* HP가 20 증가되었습니다. 포션이 1개 차감됩니다." << endl;
            cout << "현재 HP: " << status[HP_INDEX] << endl;
            cout << "남은 포션 수: " << HPPotion_count << endl;
        }
        else {
            cout << "포션이 부족합니다." << endl;
        }
    }

    // 2. MP UP
    void mpUp() {
        if (MPPotion_count > 0) {
            status[MP_INDEX] += 20;
            MPPotion_count--;
            cout << "* MP가 20 증가되었습니다. 포션이 1개 차감됩니다." << endl;
            cout << "현재 MP: " << status[MP_INDEX] << endl;
            cout << "남은 포션 수: " << MPPotion_count << endl;
        }
        else {
            cout << "포션이 부족합니다." << endl;
        }
    }

    // 3. 공격력 UP
    void attackUp() {
        status[ATTACK_INDEX] *= 2;
        cout << "* 공격력이 2배로 증가되었습니다." << endl;
        cout << "현재 공격력: " << status[ATTACK_INDEX] << endl;
    }

    // 4. 방어력 UP
    void defenseUp() {
        status[DEFENSE_INDEX] *= 2;
        cout << "* 방어력이 2배로 증가되었습니다." << endl;
        cout << "현재 방어력: " << status[DEFENSE_INDEX] << endl;
    }

    // 5. 현재 능력치 출력 (도전 과제 반영)
    void showStatus() const {
        cout << "* Level : " << level << endl;
        cout << "* HP : " << status[HP_INDEX]
            << ", MP : " << status[MP_INDEX]
            << ", 공격력 : " << status[ATTACK_INDEX]
            << ", 방어력 : " << status[DEFENSE_INDEX] << endl;
        cout << "* 남은 HP 포션 수 : " << HPPotion_count
            << ", 남은 MP 포션 수 : " << MPPotion_count << endl;
    }

    // 6. Level Up (도전 과제 반영)
    void levelUp() {
        level++;
        setPotion(1); // 포션 1개씩 충전
        cout << "* 레벨업! (현재 레벨: " << level << ")\n";
        cout << "  HP/MP 포션이 지급됩니다.\n";
        cout << "남은 HP/MP 포션 수 : " << HPPotion_count << "/" << MPPotion_count << endl;
    }

    // 메뉴 출력 및 선택 실행
    bool runSystem() {
        int choice;

        cout << "<스탯 관리 시스템>\n";
        cout << "1. HP UP\n";
        cout << "2. MP UP\n";
        cout << "3. 공격력 UP\n";
        cout << "4. 방어력 UP\n";
        cout << "5. 현재 능력치\n";
        cout << "6. Level Up\n";
        cout << "0. 나가기\n";
        cout << "번호를 선택해주세요: ";

        if (!(cin >> choice)) {
            cout << "잘못된 입력입니다. 숫자를 입력해주세요." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return true; // 루프 계속
        }

        cout << "=============================================" << endl;

        switch (choice) {
        case 1: hpUp(); break;
        case 2: mpUp(); break;
        case 3: attackUp(); break;
        case 4: defenseUp(); break;
        case 5: showStatus(); break;
        case 6: levelUp(); break;
        case 0:
            cout << "프로그램을 종료합니다." << endl;
            return false; // 루프 종료
        default:
            cout << "잘못된 번호입니다. 다시 선택해주세요." << endl;
            break;
        }
        cout << "=============================================" << endl;
        return true; // 루프 계속
    }
};

int main() {
    // Player 클래스의 객체 생성
    Player player;

    // 스탯 초기화 및 입력
    player.initializeStatus();

    // 스탯 관리 시스템 시작
    while (player.runSystem()) {
        // runSystem() 함수가 true를 반환하는 동안 계속 실행
    }

    return 0;
}
