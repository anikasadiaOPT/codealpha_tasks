#include <bits/stdc++.h>
using namespace std;

void calculate_cgpa(int n){
    vector<int> credits(n);
    vector<float> grades(n);
    
    for(int i = 0; i<n; i++){
        cout << "Enter the credits for subject " << i+1 << ": ";
        cin >> credits[i];
    }
    cout << endl;
    int m = n;
    for(int j = 0; j<m; j++){
        cout << "Enter the grade for subject " << j+1 << ": " ;
        cin >> grades[j];
    }
    float total_credits = 0, total = 0;
    for(int i = 0; i<n; i++){
        total_credits += credits[i];
        total += credits[i] * grades[i];
    }  
    
    float cgpa = (float)total / total_credits;
    for(int i = 0; i<n; i++){
        cout << "Subject " << i+1 << ": " << grades[i] << " " << "Credits " << i+1 << ": " << credits[i] << endl;
    }
    cout << "CGPA: " << fixed << setprecision(2) << cgpa << endl;

}
int main(){
    int n;
    cout << "Enter the number of subjects: ";
    cin >> n;
    calculate_cgpa(n);
    return 0;
}