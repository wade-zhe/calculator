#include<iostream>
#include<math.h>
using namespace std;

double change_to_radian(double rad){
    return rad * M_PI/180.0;
}

int main(){
    double num;
    string s;
    cout<<"please enter a number: ";
    cin>>num;
    cout<<"(sin, cos, tan, cot, sec, csc) => ";
    cin>>s;
    if(s=="sin" ||s=="cos" ||s=="tan"|| s=="cot" ||s=="sec" ||s=="csc"){
        if(num>=360){
            num = fmod(num, 360);
        }
        if(num<0){
            num += 360;
        }

        double num_rad = change_to_radian(num);

        if(s == "sin"){
            cout<<"sin("<<num<<") = "<< sin(num_rad) << "\n";
        }else if(s == "cos"){
            cout<<"cos("<<num<<") = "<< cos(num_rad) << "\n";
        }else if(s == "tan"){
            cout<<"tan("<<num<<") = "<< tan(num_rad) << "\n";
        }else if(s == "cot"){
            cout<<"cot("<<num<<") = "<< 1.0 / tan(num_rad) << "\n";
        }else if(s == "sec"){
            cout<<"sec("<<num<<") = "<< 1.0 / cos(num_rad) << "\n";
        }else if(s == "csc"){
            cout<<"csc("<<num<<") = "<< 1.0 / sin(num_rad) << "\n";
        }else{
            
        }
    }
    return 0;
}
