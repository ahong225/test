//AC!!
#include <iostream>
#include <vector>
#include <string>
using namespace std;

long long N, M, last;

struct Patient{
    long long id;
    string name;
    int age, money, membership;
    int date;
};

vector<Patient> info;

long long weightedDate(string date){
    long long tmp = 0;
    tmp +=  (date[0]-'0')*10000000 +
            (date[1]-'0')*1000000 + 
            (date[2]-'0')*100000 +
            (date[3]-'0')*10000 +
            (date[5]-'0')*1000 +
            (date[6]-'0')*100 +
            (date[8]-'0')*10 +
            (date[9]-'0');
    return 30000000 - tmp;
}

bool prioritize(Patient a, Patient b, int sort_type){//1->a 0->b
    if(sort_type==0){//panda
        if(a.membership==b.membership){
            if(a.date==b.date){
                if(a.name==b.name){
                    return a.id<b.id;
                }
                return a.name<b.name;
            }
            return a.date>b.date;
        }
        return a.membership>b.membership;
    }
    else{//bear
        if(a.money==b.money){
            return a.id<b.id;
        }
        return a.money>b.money;
    }
}

int partition(vector<Patient>& arr, int low, int high, int sort_type) {
    Patient pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (prioritize(arr[j], pivot, sort_type)) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<Patient>& arr, int low, int high, int sort_type, int num) {
    if (low < high) {
        int pi = partition(arr, low, high, sort_type);
        quickSort(arr, low, pi - 1, sort_type, num);
        if(pi<num)
            quickSort(arr, pi + 1, high, sort_type, num);
    }
}

void pop(vector<Patient>& arr, int num){
    vector<Patient> nw;
    long long nwnum = arr.size()-num;
    for(long long i=0;i<nwnum;i++){
        nw.push_back(arr[i+num]);
    }
    arr = nw;
}

int main(){
    cin>>N>>M;
    for(long long i=1;i<=N;i++){
        Patient np;
        np.id = i;
        cin.ignore();
        getline(cin, np.name);
        cin>>np.age>>np.money>>np.membership;
        string join;
        cin>>join;
        if(join=="NaN") np.date = 0;
        else np.date = weightedDate(join);
        info.push_back(np);
    }
    
    last = N;
    for(long long i=1;i<=M;i++){
        long long P,X,K;
        cin>>P>>X>>K;
        for(long long j=1;j<=P;j++){
            Patient np;
            np.id = last + j;
            cin.ignore();
            getline(cin, np.name);
            cin>>np.age>>np.money>>np.membership;
            string join;
            cin>>join;
            if(join=="NaN") np.date = 0;
            else np.date = weightedDate(join);
            info.push_back(np);
        }
        last += P;
        cout<<"DAY #"<<i<<"\n";
        long long income = 0;
        
        X = min(X, (long long)info.size());
         quickSort(info, 0, info.size() - 1, 0, X);
        for(long long j=0;j<X;j++){
            Patient p = info[j];
            cout<<p.name<<" "<<p.age<<"\n";
            income += p.money*0.9;
        }
        pop(info, X);
    
        K = min(K, (long long)info.size());
        quickSort(info, 0, info.size() - 1, 1, K);
        pop(info, K);
    
        cout<<"INCOME TODAY: "<<income<<"\n";
    }
}