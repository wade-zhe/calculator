#include<iostream>
#include<math.h>
using namespace std;

double change_to_radian(double rad){
    return rad * M_PI/180.0;
}

int main(){
    double num1;
    string s;
    cout<<"please enter a number: ";
    while(cin>>num1){
        bool sign = false;
        do{
            cout<<"( +, -, *, /, sin, cos, tan, cot, sec, csc) => ";
            cin>>s;
            if(s=="sin" || s=="cos" || s=="tan" || s=="cot" || s=="sec" || s=="csc" || s == "+" || s == "-" || s == "*" || s == "/"){
                sign = true;
                break;
            }else{
                cout<<"please enter the operator again.\n";
            }
        }while(sign == 0);
        if(s=="sin" || s=="cos" || s=="tan"|| s=="cot" || s=="sec" || s=="csc"){
            if(num1>=360){
                num1 = fmod(num1, 360);
            }
            if(num1<0){
                num1 += 360;
            }

            double num_rad = change_to_radian(num1);

            if(s == "sin"){
                cout<<"sin("<<num1<<") = "<< sin(num_rad) << "\n";
            }else if(s == "cos"){
                cout<<"cos("<<num1<<") = "<< cos(num_rad) << "\n";
            }else if(s == "tan"){
                cout<<"tan("<<num1<<") = "<< tan(num_rad) << "\n";
            }else if(s == "cot"){
                cout<<"cot("<<num1<<") = "<< 1.0 / tan(num_rad) << "\n";
            }else if(s == "sec"){
                cout<<"sec("<<num1<<") = "<< 1.0 / cos(num_rad) << "\n";
            }else if(s == "csc"){
                cout<<"csc("<<num1<<") = "<< 1.0 / sin(num_rad) << "\n";
            }else{
                
            }
        }else if(s == "+" || s == "-" || s == "*" || s == "/"){
            double num2,ans;
            cout<<"please enter another number: ";
            cin>>num2;
            if(s == "+"){
                ans = num1 + num2; 
            }else if(s == "-"){
                ans = num1 - num2; 
            }else if(s == "*"){
                ans = num1 * num2;
            }else if(s == "/"){
                ans = num1 / num2;
            }else{

            }
            cout<<num1<<" "<<s<<" "<<num2<<" = "<<ans<<"\n";
        }
    cout<<"please enter a number: ";
    }
 
    return 0;
}
