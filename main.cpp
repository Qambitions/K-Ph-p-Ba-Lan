#include <iostream>
#include <bits/stdc++.h>

#define ci pair<string,int>
#define fi first
#define se second

using namespace std;

string operatorr[] = {"+" , "-" , "*" , "/" , "^"};

int check_in_operator(string x)
{
    if (x=="(" || x==")") return -1;
    for (int i=0; i < sizeof(operatorr); i++)
        if (x==operatorr[i])
        {
            if (i==0 || i==1) return 1;
            if (i==2 || i==3) return 2;
            if (i==4) return 3;
        }
    return 0;
}

void ba_lan(stack< ci > &st, vector<string> &v, string x, int priority)
{
    if (priority == -1)
    {
        while (!!st.empty() && st.top().fi != "(")
         {
                v.push_back(st.top().fi);
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
                st.pop();
            } else break;
    }
}

int main(int arsc, char *arsv[])
{
    freopen("inp.inp","r",stdin);
   // freopen("out.out","w",stdin);
    //while (cin >> )
    int n_inp;
    string s_inp[100];
    cin >> n_inp;
    for (int i=0; i<n_inp; i++)
        cin >> s_inp[i];



    //------------------------------------------------
    stack < ci > st;
    st.push(ci("(",-1));
    vector <string> v;
    for (int i=0; i<n_inp; i++)
        if (s_inp[i] == "{" || s_inp[i] == "[") s_inp[i] = "(";
        else if (s_inp[i] == "}" || s_inp[i] == "]") s_inp[i] = ")";

    for (int i=0; i<n_inp; i++)
    {
        int priority = check_in_operator(s_inp[i]);
        if (priority == 0) v.push_back(s_inp[i]);
        else ba_lan(st,v,s_inp[i],priority);
    }
    ba_lan(st,v,")",-1);

    for (int i=0; i<v.size(); i++)
        cout << v[i] << " ";
    return 0;
}
