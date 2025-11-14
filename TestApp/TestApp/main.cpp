#include <iostream>
#include <string>

using namespace std;

int solution(const string& s) {
    // TODO: 여기에 코드를 작성하세요.
    int result = 0;
    
    for (int i = 0; i < s.length(); i++)
    {

    }

    return result;
}

/**
 * main 함수는 수정하지 마세요.
 */
int main() {
    cout << "--- 테스트 케이스 ---" << endl;
    cout << "aabbccc (예상: 6): " << solution("aabbccc") << endl;
    cout << "ab (예상: 2): " << solution("ab") << endl;
    cout << "aaaaa (예상: 2): " << solution("aaaaa") << endl;
    cout << "aaabbc (예상: 5): " << solution("aaabbc") << endl;
    cout << "abcde (예상: 5): " << solution("abcde") << endl;
    cout << "a (예상: 1): " << solution("a") << endl;
    cout << " (예상: 0): " << solution("") << endl;
    cout << "aaabbaaccccdeee (예상: 11): " << solution("aaabbaaccccdeee") << endl;
    cout << "aaaaaaaaaabb (예상: 5): " << solution("aaaaaaaaaabb") << endl;

    return 0;
}


//#include <string>
//#include <cctype>
//
//using namespace std;
//
//string solution(string s) {
//    for (int i = 0; i < s.length(); ++i) {
//        if (s[i] == ' ') continue;
//
//        bool start_of_word;
//        if (i == 0)
//            start_of_word = true;
//        else {
//            if (s[i - 1] == ' ') {
//                start_of_word = true;
//            }
//            else {
//                start_of_word = false;
//            }
//        }
//
//        if (isalpha(s[i])) {
//            if (start_of_word)
//                s[i] = toupper(s[i]);
//            else
//                s[i] = tolower(s[i]);
//        }
//    }
//    return s;
//}

//#include <iostream>
//using namespace std;
//
//int main() 
//{
//    int N;
//    if (!(cin >> N) || N <= 0) 
//        return 0;
//
//    int data[1000];
//    int freq[2001] = { 0 };
//    const int OFFSET = 1000;
//
//    int min_val, max_val;
//    long long sum = 0;
//    long long abs_sum = 0;
//    int even_count = 0;
//    int odd_count = 0;
//
//    for (int i = 0; i < N; ++i) 
//    {
//        int num;
//        cin >> num;
//        data[i] = num;
//
//        if (i == 0) 
//        {
//            min_val = num;
//            max_val = num;
//        }
//        else 
//        {
//            if (num < min_val) 
//                min_val = num;
//            if (num > max_val) 
//                max_val = num;
//        }
//
//        sum = sum + num;
//
//        int num_abs = (num < 0) ? -num : num; 
//        abs_sum = abs_sum + num_abs;
//
//        if (num % 2 == 0) 
//            even_count++;
//        else odd_count++;
//
//        freq[num + OFFSET]++;
//    }
//
//    int max_freq = 0;
//    int mode_val = 0;
//
//    for (int i = 0; i < 2001; ++i) 
//    {
//        if (freq[i] > max_freq) 
//        {
//            max_freq = freq[i];
//            mode_val = i - OFFSET;
//        }
//    }
//
//    double avg = (double)sum / N;
//    double abs_avg = (double)abs_sum / N;
//
//    cout << "min: " << min_val << "\n";
//    cout << "max: " << max_val << "\n";
//    cout << "avg: ";
//    long long rounded_avg = (long long)(avg * 10 + 0.5);
//    cout << rounded_avg / 10 << "." << rounded_avg % 10 << "\n";
//    cout << "mode: " << mode_val << "\n";
//    cout << "even: " << even_count << "\n";
//    cout << "odd: " << odd_count << "\n";
//    cout << "abs_avg: ";
//    long long rounded_abs_avg = (long long)(abs_avg * 10 + 0.5);
//    cout << rounded_abs_avg / 10 << "." << rounded_abs_avg % 10 << "\n";
//
//    return 0;
//}

//#include <iostream>
//#include <string>
//using namespace std;
//
//class BankAccount {
//private:
//    string owner; // 계좌 소유자 정보
//    double balance; // 잔액 정보
//
//public:
//    BankAccount(const string& name, double initial) {
//        // 생성자 로직을 작성해주세요.
//        // 생성자 매개변수 설명: 소유자 이름(name), 초기 잔액(initial)
//        owner = name;
//        balance = max(0.0, initial);
//    }
//
//    void deposit(double amount) {
//        // 입금 로직을 작성해주세요.
//        if (amount > 0)
//            balance = balance + amount;
//    }
//
//    bool withdraw(double amount) {
//        // 출금 로직을 작성해주세요.
//        if (amount > 0)
//        {
//            balance = amount - balance;
//            return true;
//        }
//        return false;
//    }
//
//    double getBalance() const {
//        return balance;
//        /*if (amount < 0)
//            return false;
//        else
//            return true;*/
//    }
//
//    // 계좌 정보 출력하는 함수 (구현하실 필요 없음)
//    void printInfo() const {
//        cout << "Owner: " << owner << ", Balance: " << balance << " won\n";
//    }
//};
//
//int main() {
//    BankAccount account("Alice", 1000);
//    account.printInfo(); // Owner: Alice, Balance: 1000 won
//
//    account.deposit(500);
//    account.printInfo(); // Owner: Alice, Balance: 1500 won
//
//    if (account.withdraw(2000)) {
//        cout << "Withdraw OK!\n"; // 이건 출력 안됨
//    }
//    else {
//        cout << "Withdraw FAILED!\n"; // 이것이 출력됨
//    }
//
//    if (account.withdraw(1000)) {
//        cout << "Withdraw OK!\n"; // 이것이 출력됨
//    }
//
//    account.printInfo(); // Owner: Alice, Balance: 500 won
//}

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