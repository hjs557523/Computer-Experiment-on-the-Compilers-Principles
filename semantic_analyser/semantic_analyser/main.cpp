#include<iostream>
#include<cstdio>
#include<map>
#include<cstdlib>
#include<vector>
#include<cstring>
#include<string>
#include<queue>
#define N 110000
using namespace std;


int idx=1,CharNode,DigNode;
int flag[N];
map<char,int> node[N];
vector<int> unval[N];
int hs[N];

bool Dot(string s){
    for(int i=0;i<s.size();++i)
        if(s[i]=='.') return 1;
    return 0;
}

bool check(int p){
    if(!flag[p])
        return 0;
    return 1;
}

bool IsIgnore(char s){
    if(s==' ' || s=='\n') return 1;
    return 0;
}

bool LetterOrNumber(char s){
    if(s>='0' && s<='9' || s>='a' && s<='z' ||s>='A' && s<='Z')
        return 1;
    return 0;
}

bool IsDigit(char c){
    if(c>='0' && c<='9') return 1;
    return 0;
}
bool IsDot(char c){return c=='.';}

vector<pair<string,int> > V;
char s[N];
int Sparsing(){/// 0 string  1 int 2 real 3 int* 4 : 5 ;
    int len=strlen(s);
    for(int i=0;i<len;++i)if(!IsIgnore(s[i])){
        string tmp="";
        int type;
        if(isdigit(s[i])){
            type=1;
            while(i<len){
                if(IsIgnore(s[i])){
                    ++i;continue;
                }
                if(isdigit(s[i]))
                    tmp+=s[i],++i;
                else if(IsDot(s[i]))
                    tmp+=s[i],++i,type=2;
                else break;
            }
            --i;
        }
        else if(s[i]=='*'){
            V.push_back({"*",3});
            continue;
        }
        else if(s[i]==':'){
            tmp+=":";
            type=4;
        }
        else if(s[i]==';'){
            tmp+=";";
            type=5;
        }
        else if(LetterOrNumber(s[i])){
            type=0;
            while(i<len){
                if(IsIgnore(s[i])){
                    ++i;continue;
                }
                if(tmp=="proc") break;
                if(LetterOrNumber(s[i]))
                    tmp+=s[i],++i;
                else break;
            }
            --i;
        }
        else{
            printf("error\n");
            while(1);
        }
        V.push_back({tmp,type});
    }
}

void GetText(){
    int x=0;
    char c;
    while(c=getchar(),c!=-1){
        if(c==-95) continue;
        if(c==-4) c='*';
        s[x++]=c;
    }
//    for(int i=0;i<strlen(s);++i)
//        cout<<(int)s[i]<< ' ';cout<<endl;
    printf("%s",s);
}

struct Table{
    int  Width;
    Table(){
        Width=0;
    }
    struct st{
        string name;
        int type;
        int offset;
    };
    vector<st> item;
    void OUT(){
        puts("");
        printf("Width : %d\n",Width);
        puts("-------------------------");
        printf("*name\ttype\toffset\t*\n");
        puts("-------------------------");
        for(int i=0;i<item.size();++i){
//                cout<<item[i].type<<endl;
            if(item[i].type==1)
                cout<<"*"<<item[i].name<<'\t'<<"integer"<<'\t'<<item[i].offset<<"\t*"<<endl;
            if(item[i].type==2)
                cout<<"*"<<item[i].name<<'\t'<<"real"<<'\t'<<item[i].offset<<"\t*"<<endl;
            char p[10];
            p[0]=-95;p[1]=-4;p[2]=0;
            if(item[i].type==3)
                cout<<"*"<<item[i].name<<'\t'<<p<<"integer"<<'\t'<<item[i].offset<<"\t*"<<endl;
            if(item[i].type==4)
                cout<<"*"<<item[i].name<<'\t'<<p<<"real"<<'\t'<<item[i].offset<<"\t*"<<endl;
        	if(item[i].type==5) {

        		cout<<"*"<<item[i].name<<'\t'<<"proc"<<'\t'<<"\t*"<<endl;
				cout<<endl;
			}
		}
        puts("-------------------------");
    }
};

vector<int> offset;
vector<Table*> tblptr;
queue<pair<string,int> > Q;
int fun9(){
    Q.pop();
    int type=3;
    if(Q.front().first=="integer") type=3;
    else type=4;
    pair<string,int> P=Q.front();Q.pop();
//    cout<<"asff   "<<Q.front().first<<endl;
    return type;
}
void fun8(){
    pair<string,int> P=Q.front();Q.pop();
}
void fun7(){
    pair<string,int> P=Q.front();Q.pop();
}
void fun5(){
    pair<string,int> P=Q.front();Q.pop();
    if(P.first=="proc") {
    	Table * tbl=tblptr.back();
    	(tbl->item).push_back({Q.front().first, 5, offset.back()=0});
    	Q.pop();
    	return;
	}
    if(Q.front().first!=":"){printf("fun5 error\n");while(1);}
    Q.pop();
    int type;
    if(Q.front().first=="integer") fun7(),type=1;
    else if(Q.front().first=="real") fun8(),type=2;
    else if(Q.front().first=="*") type=fun9();
    else {printf("fun5 error\n");while(1);}

    if(tblptr.size()==0){printf("fun5 error\n");while(1);}
    Table * tbl=tblptr.back();
    (tbl->item).push_back({P.first, type, offset.back()});
    if(type!=2)
        offset.back()+=4;
    else offset.back()+=8;
}
void fun6(){
    Table *tbl=new Table();
    tblptr.push_back(tbl);
    offset.push_back(0);
}
void fun4(){
    fun6();
    fun5();
    Table *tbl=tblptr.back();
    tbl->Width+=offset.back();
    tblptr.pop_back();
    offset.pop_back();
}
void fun3(){
    if(Q.empty()) return ;
    //if(Q.front().first=="proc") fun4();
    fun5();
//    cout<<Q.front().first<<endl;
    if(Q.empty()) return ;
//    cout<<Q.front().first<<' '<<Q.front().second<<endl;
    if(Q.front().first!=";"){
        printf("fun3 error\n");
        while(1);
    }
    Q.pop();
    fun3();
}
void fun2(){/// M->e
    Table *tbl=new Table();
    tblptr.push_back(tbl);
    offset.push_back(0);
}
void fun1(){///P->MD
    fun2();
    fun3();
    Table * tbl=tblptr.back();
    int of=offset.back();
    tbl->Width+=of;
//    tblptr.pop_back();
//    offset.pop_back();
}

void Analyze(){
    for(int i=0;i<V.size();++i)
        Q.push(V[i]);
    fun1();
}

int main(){
    GetText();
    Sparsing();
    for(int i=0;i<V.size();++i)
        cout<<V[i].first<<' '<<V[i].second<<endl;cout<<endl;
    Analyze();
    for(int i=0;i<tblptr.size();++i){
        Table* tbl=tblptr[i];
        tbl->OUT();
    }
    return 0;
}



