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
        if (amount > 0 && balance <= amount)
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



/////


#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_set>
// 추가로 필요하다고 생각하는 헤더들은 여기다가 자유롭게 추가할 것
using namespace std;

vector<int> removeDuplicates(const vector<int>& v) {
    // 중복을 제거하고 순서를 유지한 벡터 반환
    // 예: [1,3,2,3,1,4] -> [1,3,2,4]
    vector<int> result;
    unordered_set<int> looked;

    for (int number : v)
    {
        if (looked.find(number) == looked.end())
        {
            result.push_back(number);
            looked.insert(number);
        }
    }
    return result;
}

int main() {
    vector<int> nums = { 1, 3, 2, 3, 1, 4, 2, 5 };
    vector<int> result = removeDuplicates(nums);

    cout << "Result: ";
    for (int n : result) {
        cout << n << " ";
    }
    cout << "\n"; // 1 3 2 4 5
}


///
## 4. 언리얼 Actor 라이프사이클 – 순서 맞추기(10점)

### 문제

레벨에 미리 배치된 Actor가 있고 정상적으로 플레이를 한 후 종료가 되는 상황입니다.이 때, 어떤 순서대로 아래의 함수들이 불리는지 올바른 순서로 나열해주세요.

`EndPlay(...)`

`BeginPlay()`

`Constructor`

`PostInitializeComponents()`

`Tick(float)`

-

`Constructor`

`PostInitializeComponents()`

`BeginPlay()`

`Tick(float)`

`EndPlay(...)`


다음 Actor가 레벨에 배치되었을 때 게임 플레이 시 실제 동작 설명 중** 틀린 것을 1개 골라주세요.* *

1. 액터는 BeginPlay에서 시작 위치를 저장하고, 월드 X축 기준으로 - Amplitude에서 + Amplitude까지 직선으로 왕복한다.경계에 닿으면 CurrentOffset을 경계값으로 고정한 뒤 DirectionSign을 반전한다.
2. Amplitude가 0이면 위치는 StartLocation에 고정되고, 속도 설정과 무관하게 이동하지 않는다.
3. | YawDegPerSec | > KINDA_SMALL_NUMBER 인 동안 매 Tick에 Yaw 회전이 적용된다.
4. 액터의 이동 축은 액터의 현재 회전을 따르므로, 플레이 도중 액터를 수동으로 회전시키면 이동 경로(선)도 함께 회전한다.
5. Speed가 작을수록 왕복에 걸리는 주기 시간이 길어지고, Speed가 커질수록 짧아진다.
6. 플레이 중 액터의 로컬 회전 값을 수동으로 바꿔도, 이동 축이 월드 X축으로 고정되어 있으므로 왕복 경로(선 자체)는 변하지 않는다.

-

4번

