#include <iostream>
#include <bits/stdc++.h>

#define ci pair<string,int>
#define fi first
#define se second

using namespace std;

string operatorr[] = {"+" , "-" , "*" , "/" , "^"}; //operator
string ERRORR = "E";
int check_in_operator(string x) //dinh do uu tien
{
    if (x=="(" || x==")") return -1;
    for (int i=0; i < 5; i++)
        if (x==operatorr[i])
        {
            if (i==0 || i==1) return 1;
            if (i==2 || i==3) return 2;
            if (i==4) return 3;
        }
    return 0;
}

void caculate_balan(vector<string> &v) //thuc hien phep tinh
{
     string x = v[v.size()-1];
     v.pop_back();
     double b = stod(v[v.size()-1]);
     v.pop_back();
     double a = stod(v[v.size()-1]);
     v.pop_back();
     if (x=="+") a+=b;
     else if (x=="-") a-=b;
     else if (x=="*") a*=b;
      else if (x=="/")
      {
           if (b==0) // div / 0
               throw "Math Error";
           a/=b;
      }
      else if (x=="^") a = pow(a,b);
     v.push_back(to_string(a));
}


void ba_lan(stack< ci > &st, vector<string> &v, string x, int priority,int mode)
{
     //cout << x << "\n";
    if (priority == -1)
          if (x == "(") st.push(ci("(",-1));
    else
     {
        while (!st.empty() && st.top().fi != "(")
         {
                v.push_back(st.top().fi);
                if (mode==1) {caculate_balan(v); /*cout << v[v.size()-1] << '\n';*/}// mode -c
                st.pop();
        }
        st.pop();
    } else if (st.top().se <= priority) //dk push vao stack
        st.push(ci(x,priority));
    else
    {
        while (!st.empty() && st.top().fi != "(")
            if (st.top().se > priority) // dk push vao queue
            {
                v.push_back(st.top().fi);
                if (mode==1) {caculate_balan(v); /*cout << v[v.size()-1] << '\n';*/}// mode -c

                st.pop();
            } else break;
          st.push(ci(x,priority));
    }
}

void do_balan(int n_inp, string s_inp[], int mode) // ham main de tinh tuong lenh
{
     stack < ci > st;
    st.push(ci("(",-1));
    vector <string> v;
    for (int i=0; i<n_inp; i++)
        if (s_inp[i] == "{" || s_inp[i] == "[") s_inp[i] = "(";
        else if (s_inp[i] == "}" || s_inp[i] == "]") s_inp[i] = ")";

     try{
    for (int i=0; i<n_inp; i++)                           // run ba lan
    {
        int priority = check_in_operator(s_inp[i]);
        if (priority == 0) v.push_back(s_inp[i]);
        else ba_lan(st,v,s_inp[i],priority,mode);

    }

    ba_lan(st,v,")",-1,mode);

    for (int i=0; i<v.size(); i++)
        cout << v[i] << " ";
     }
     catch (string error) // catch error
     {
          cout << "Math Error \n";
     }
}

void make_arr(string tmp, string arr[], int &n_arr) throw(string)// dinh dang default va bat loi
{
     //getline(cin,tmp);
     stringstream stream;
     stream << tmp[0];
     for (int i=1; i<tmp.size(); i++)
          if (tmp[i]=='.')stream << tmp[i];
          else
          if (48 <= (int)tmp[i] && (int)tmp[i] <= 57 &&
               (48 <= (int)tmp[i-1] && (int)tmp[i-1] <= 57 || tmp[i-1]=='-' || tmp[i-1]=='.'))
                    stream << tmp[i];
          else
          {
               if (!(48 <= (int)tmp[i] && (int)tmp[i] <= 57) && tmp[i]!=' ')
               {
                    string x = "";
                    x = x + tmp[i];
                    if (check_in_operator(x)==0) //bat loi ki tu la
                    throw ERRORR;
               }

               stream << " " << tmp[i];
          }
     while (stream >> arr[n_arr++]){}
     for (int i=0; i<n_arr-1; i++)
     {
          if ((check_in_operator(arr[i]) > 0 && check_in_operator(arr[i+1]) > 0))  //bat loi 2 dau lien tuc
               throw ERRORR;
     }

}

int main(int arsc, char *arsv[])
{
     // prepare from cmd
     freopen(arsv[1],"r",stdin);
     freopen(arsv[4],"w",stdout);
     int n;
     try{
          n = atoi(arsv[2]);
     }
     catch (invalid_argument &e){
          cout << "Error cmd";
          return 0;
     }

     int act;
     if (arsv[3] == "-t") act = 0;
     else if (arsv[3] == "-c") act = 1;
     else {
          cout << "Error cmd";
          return 0;
     }
    //------------------------------------------------
    // time to do
    //int n=1,act=0;
    freopen("inp.inp","r",stdin);
     for (int i=0; i<n; i++)
     {
          string tmp;
          getline(cin , tmp);
          string arr[100];
          int n_arr=0;
          try{

                make_arr(tmp,arr,n_arr);//dinh dang input

               do_balan(n_arr,arr,act);
          }
         // catch(invalid_argument &e) {cout << "E \n";}  // catch error
          catch (const string& e) {cout << "E"<< '\n';}
          //catch (string &e) {cout << "E \n";}
     }
    return 0;
}

