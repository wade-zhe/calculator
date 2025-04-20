#include <iostream>
#include <vector>
#include <string>
using namespace std;

void diff_term(double a, char x, double b, char diff_var, double &new_a, double &new_b) {
    if (x != diff_var) {
        new_a = 0;
        new_b = 0;
        return;
    }
    if (b == 0) {
        new_a = 0;
        new_b = 0;
        return;
    }
    new_a = a * b;
    new_b = b - 1;
}

//加法 (u + v)' = u' + v'
void diff_add(double a1, char x1, double b1, double a2, char x2, double b2, char diff_var, double &new_a, double &new_b, double &new_a2, double &new_b2) {
    diff_term(a1, x1, b1, diff_var, new_a, new_b);
    diff_term(a2, x2, b2, diff_var, new_a2, new_b2);
}

//減法 (u - v)' = u' - v'
void diff_sub(double a1, char x1, double b1, double a2, char x2, double b2, char diff_var, double &new_a, double &new_b, double &new_a2, double &new_b2) {
    diff_term(a1, x1, b1, diff_var, new_a, new_b);
    diff_term(a2, x2, b2, diff_var, new_a2, new_b2);
    new_a2 = -new_a2; // v' 的係數取負
}

//乘法 (a * u)' = a * u'
void diff_mul(double a, double term_a, double term_b, double &new_a, double &new_b){
    new_a = a * term_a;
    new_b = term_b;
}

//除法 (a / x^b)' = (a * x^(-b))'
void diff_div(double a, double b, double &new_a, double &new_b) {
    new_a = a * (-b);
    new_b = -b - 1;
}

void print_term(double a, char x, double b) {
    if (a == 0) {
        cout<<"0";
        return;
    }
    if (b == 0){
        cout << a; 
        return;
    }
    if(a == 1 && b == 1) {
        cout << x;
        return;
    }
    if(a == -1 && b== 1){
        cout << "-" << x;
        return;
    }
    cout << a;
    cout << x;

    if (b != 1){
        cout << "^" << b;
    }
}


bool parse_term(const string &term, double &a, char &x, double &b) {
    a = 1.0; 
    b = 1.0; 
    x = 'x'; 
    string num = "";
    size_t i = 0;

    // 處理負號
    if (i < term.size() && term[i] == '-') {
        a = -1.0;
        i++;
    }

    // 提係數
    while (i < term.size() && (isdigit(term[i]) || term[i] == '.')) {
        num += term[i];
        i++;
    }
    if (!num.empty()) {
        a *= stod(num);
        num.clear();
    } else if (i == 0 || (i == 1 && a == -1.0)) {
        a = (a == -1.0) ? -1.0 : 1.0; 
    }

    // 提變數
    if (i < term.size() && isalpha(term[i])) {
        x = term[i];
        i++;
    } else if (i == term.size()) {
        b = 0; // 常數項
        return true;
    } else {
        return false; // 無效格式
    }

    // 提指數
    if (i < term.size() && term[i] == '^') {
        i++;
        while (i < term.size() && (isdigit(term[i]) || term[i] == '.')) {
            num += term[i];
            i++;
        }
        if (!num.empty()) {
            b = stod(num);
        } else {
            return false; // 無效指數
        }
    } else {
        b = 1; 
    }

    if (i < term.size()) {
        return false; // 多餘字符
    }
    return true;
}


bool parse_expression(const string &expr, vector<double> &a, vector<char> &x, vector<double> &b, vector<char> &op) {
    string clean_expr = "";
    // 移除空格
    for (char c : expr) {
        if (c != ' ') {
            clean_expr += c;
        }
    }

    // 處理首項的負號
    string current_term = "";
    size_t i = 0;
    if (clean_expr[0] == '-') {
        current_term = "-";
        i = 1;
    }

    // 分割項和運算符
    while (i <= clean_expr.size()) {
        if (i == clean_expr.size() || clean_expr[i] == '+' || clean_expr[i] == '-') {
            if (!current_term.empty()) {
                double term_a;
                char term_x;
                double term_b;
                if (!parse_term(current_term, term_a, term_x, term_b)) {
                    return false; // 無效項
                }
                a.push_back(term_a);
                x.push_back(term_x);
                b.push_back(term_b);
                current_term.clear();
            }
            if (i < clean_expr.size()) {
                op.push_back(clean_expr[i]);
                if (clean_expr[i] == '-') {
                    current_term = "-";
                }
            }
            i++;
        } else {
            current_term += clean_expr[i];
            i++;
        }
    }

    return true;
}

int main() {
    vector<double> a, b; //係數, 指數
    vector<char> x, op; //變數, 運算子
    char diff_var; //要微分的變數
    string input;

    cout<<"Please enter your problem (type 'done' to finish)\n";
    cout<<"Example: 3x^2 + 2x - 5x^3\n";
    cout<<"Start entering: ";
    

    while (true) {
        getline(cin, input);
        if (input == "done") {
            break;
        }

        // 清空陣列
        a.clear();
        b.clear();
        x.clear();
        op.clear();

        
        if (!parse_expression(input, a, x, b, op)) {
            cout << "Invalid input, please check the format!\n";
            cout << "Start entering: ";
            continue;
        }

        cout << "Enter the variable to differentiate with respect to: ";
        cin >> diff_var;
        cin.ignore(); // 清除換行符

        // 對每項進行微分
        vector<double> new_a(a.size()), new_b(a.size());
        vector<char> new_x(a.size());
        for (size_t i = 0; i < a.size(); i++) {
            if (i == 0) {
                diff_term(a[i], x[i], b[i], diff_var, new_a[i], new_b[i]);
                new_x[i] = x[i];
            } else {
                double temp_a1, temp_b1, temp_a2, temp_b2;
                if (op[i - 1] == '+') {
                    diff_add(a[i - 1], x[i - 1], b[i - 1], a[i], x[i], b[i], diff_var, temp_a1, temp_b1, temp_a2, temp_b2);
                } else {
                    diff_sub(a[i - 1], x[i - 1], b[i - 1], a[i], x[i], b[i], diff_var, temp_a1, temp_b1, temp_a2, temp_b2);
                }
                new_a[i - 1] = temp_a1;
                new_b[i - 1] = temp_b1;
                new_a[i] = temp_a2;
                new_b[i] = temp_b2;
                new_x[i - 1] = x[i - 1];
                new_x[i] = x[i];
            }
        }

        
        if (a.empty()) {
            cout << "0\n";
        } else {
            for (size_t i = 0; i < a.size(); i++) {
                if (i > 0) {
                    cout << (op[i - 1] == '+' ? " + " : " - ");
                    if (new_a[i] < 0) {
                        new_a[i] = -new_a[i]; // 將負係數移到運算符
                    }
                } else if (new_a[i] < 0) {
                    cout << "-";
                    new_a[i] = -new_a[i];
                }
                print_term(new_a[i], new_x[i], new_b[i]);
            }
            cout << endl;
        }

        cout << "Start entering: ";
    }
    return 0;
}
