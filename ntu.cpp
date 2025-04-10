#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

double change_to_radian(double rad){
    return rad * M_PI/180.0;
}

int main(){
    double num1,ans;
    string s;
    cout<<"please enter a number: ";
    while(cin>>num1){
        bool sign = false;
        do{
            cout<<"( +, -, *, /, sin, cos, tan, cot, sec, csc, log, x^y, rad ,sqrt, !, 1/x) => ";
            cin>>s;
            if(s=="sin" || s=="cos" || s=="tan" || s=="cot" || s=="sec" || s=="csc" || s == "rad" || s == "+" || s == "-" || s == "*" || s == "/" || s == "log" || s == "x^y" || s == "sqrt" || s == "!" || s == "1/x"){
                sign = true;
                break;
            }else{
                cout<<"please enter the operator again.\n";
            }
        }while(sign == 0);
        if(s=="sin" || s=="cos" || s=="tan"|| s=="cot" || s=="sec" || s=="csc" || s == "rad"){
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
            }else if(s == "rad"){
                cout<<"radian("<<num1<<") = "<<num_rad<<"\n";
            }else{
            	
			}
        }else if(s == "+" || s == "-" || s == "*" || s == "/"){
            double num2;
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
        }else if(s == "log"){
        	cout<<"log("<<num1<<") = ";
        	cout<<fixed<<setprecision(4)<<log10(num1)<<"\n";
        	cout.unsetf(ios::fixed);
        	cout << setprecision(6);
		}else if(s == "x^y"){
			double y;
			cout<<"x(base) is "<<num1<<".\nPlease enter y(exponents): ";
			cin>>y;
			cout<<num1<<"^"<<y<<" = "<<pow(num1, y)<<"\n";
		}else if(s == "sqrt"){
			cout<<"√"<<num1<<" = "<<sqrt(num1)<<"\n";
		}else if(s == "!"){
			ans=1; 
			for(int i=1;i<=num1;i++){
				ans*=i;	
		   }
		   cout<<num1<<"! = "<<ans<<"\n"; 
		}else if(s == "1/x"){
			if(num1){ 
				cout<<"1/"<<num1<<" = "<<fixed<<setprecision(4)<<1.0/num1<<"\n";
				cout.unsetf(ios::fixed);
        	cout << setprecision(6);
			}else{
				cout<<"denominator can't be 0\n"; 
			} 
		} 
    cout<<"please enter a number (or press Ctrl+Z to quit): ";
    }
 
    return 0;
}
