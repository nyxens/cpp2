#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2005;
int parent[MAXN], sz[MAXN];
int find_set(int v) {
    if (parent[v] == v) return v;
    return parent[v] = find_set(parent[v]);
}
void union_set(int a, int b){
    a = find_set(a);
    b = find_set(b);
    if(a != b){
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
    }
}
bool oneAddRemove(const string &a, const string &b){
    if (abs((int)a.size() - (int)b.size()) != 1) 
        return false;
    const string &sm = (a.size() < b.size() ? a : b);
    const string &lg = (a.size() < b.size() ? b : a);
    int i = 0, j = 0, diff = 0;
    while(i < (int)sm.size() && j < (int)lg.size()){
        if(sm[i] == lg[j]){
            i++; j++;
        }else{
            diff++;
            j++;
            if (diff > 1) 
                return false;
        }
    }
    return true;
}
bool oneReplace(const string &a, const string &b){
    if (a.size() != b.size()) 
        return false;
    int diff = 0;
    for(int i = 0; i < (int)a.size(); i++){
        if(a[i] != b[i]){
            diff++;
            if (diff > 1) 
                return false;
        }
    }
    return true;
}
bool connected(const string &a, const string &b){
    if (a == b) 
        return true;
    return oneAddRemove(a, b) || oneReplace(a, b);
}
vector<int> groupStrings(vector<string> &words){
    int n = words.size();
    for(int i = 0; i < n; i++){
        parent[i] = i;
        sz[i] = 1;
    }
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            if(connected(words[i], words[j])){
                union_set(i, j);
            }
        }
    }
    unordered_map<int,int> compSize;
    int maxGroupSize = 0;
    for(int i = 0; i < n; i++){
        int root = find_set(i);
        compSize[root]++;
        maxGroupSize = max(maxGroupSize, compSize[root]);
    }
    int groups = compSize.size();
    return {groups, maxGroupSize};
}
int main(){
    vector<string> words = {"a","b","ab","cde"};
    vector<int> ans = groupStrings(words);
    cout << ans[0] << " " << ans[1] << endl;
    return 0;
}
