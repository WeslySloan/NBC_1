#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    string owner; // 계좌 소유자 정보
    double balance; // 잔액 정보

public:
    BankAccount(const string& name, double initial) {
        // 생성자 로직을 작성해주세요.
        // 생성자 매개변수 설명: 소유자 이름(name), 초기 잔액(initial)
        owner = name;
        balance = max(0.0, initial);
    }

    void deposit(double amount) {
        // 입금 로직을 작성해주세요.
        if (amount > 0)
            balance = balance + amount;
    }

    bool withdraw(double amount) {
        // 출금 로직을 작성해주세요.
        if (amount > 0)
        {
            balance = amount - balance;
            return true;
        }
        return false;
    }

    double getBalance() const {
        return balance;
        /*if (amount < 0)
            return false;
        else
            return true;*/
    }

    // 계좌 정보 출력하는 함수 (구현하실 필요 없음)
    void printInfo() const {
        cout << "Owner: " << owner << ", Balance: " << balance << " won\n";
    }
};

int main() {
    BankAccount account("Alice", 1000);
    account.printInfo(); // Owner: Alice, Balance: 1000 won

    account.deposit(500);
    account.printInfo(); // Owner: Alice, Balance: 1500 won

    if (account.withdraw(2000)) {
        cout << "Withdraw OK!\n"; // 이건 출력 안됨
    }
    else {
        cout << "Withdraw FAILED!\n"; // 이것이 출력됨
    }

    if (account.withdraw(1000)) {
        cout << "Withdraw OK!\n"; // 이것이 출력됨
    }

    account.printInfo(); // Owner: Alice, Balance: 500 won
}

// 최대값 초기생성자
// 잔액은 음수가 될 수 없으며



//#include "GameManager.h"
//
//// 프로그램 진입점: GameManager 루프 시작
//int main() {
//    GameManager game;
//    game.run();
//    return 0;
//}