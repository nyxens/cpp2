#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>
#include <iomanip>
using namespace std;
int main(){
	int n,k,m;
	double alpha,beta;
	if(!(cin>>n>>k>>m>>alpha>>beta)) 
        return 0;
	vector<int> region(n);
	for(int i=0;i<n;i++) 
        cin>>region[i];
	vector<unsigned long long> adj(n,0);
	for(int i=0;i<m;i++){
		int u,v; 
        cin>>u>>v;
		adj[u] |= (1ULL<<v);
		adj[v] |= (1ULL<<u);
	}
	vector<vector<int>> nodes(k);
	for(int i=0;i<n;i++) 
        nodes[region[i]].push_back(i);
	vector<vector<unsigned long long>> regionSets(k);
	for(int r=0;r<k;r++){
		int sz = nodes[r].size();
		for(int mask=0; mask < (1<<sz); ++mask){
			unsigned long long globalMask = 0;
			bool ok = true;
			for(int i=0;i<sz && ok;i++) 
                if(mask & (1<<i)){
				    int u = nodes[r][i];
				    for(int j=0;j<sz;j++) if((mask & (1<<j)) && j<i){
					    int v = nodes[r][j];
					    if((adj[u] >> v) & 1ULL ){
                            ok = false; 
                            break;
                    }
				}
				globalMask |= (1ULL<<u);
			}
			if(!ok) 
                continue;
			bool maximal = true;
			for(int j=0;j<sz;j++) 
                if(!(mask & (1<<j))){
				    int v = nodes[r][j];
				    bool blocked = false;
				    for(int t=0;t<sz;t++) if(mask & (1<<t)){
					    int u = nodes[r][t];
					        if( (adj[u] >> v) & 1ULL ) {
                                blocked = true; 
                                break; 
                            }
				    }
				if(!blocked){ 
                    maximal = false; 
                    break; 
                }
			}
			if(maximal) regionSets[r].push_back(globalMask);
		}
		if(nodes[r].empty()) 
            regionSets[r].push_back(0ULL);
		if(regionSets[r].empty()){
			for(int i=0;i<sz;i++) 
                regionSets[r].push_back(1ULL<<nodes[r][i]);
		}
	}
	vector<unsigned long long> conf = adj;
	double bestScore = -1e300;
	vector<int> bestCaps(k,0);
	unsigned long long bestActive = 0ULL;
	vector<int> bestColor(k,0);
	vector<unsigned long long> chosenMask(k,0);
	auto colorize = [&](const vector<int>& deg,const vector<unsigned int>& adjR,int &outC,vector<int>& outColors){
		int K = k;
		outC = K; outColors.assign(K,0);
		vector<int> order(K); iota(order.begin(),order.end(),0);
		sort(order.begin(),order.end(),[&](int a,int b){ return deg[a]>deg[b]; });
		for(int C=1; C<=K; ++C){
			vector<int> col(K,-1);
			function<bool(int)> dfs = [&](int idx)->bool{
				if(idx==K) return true;
				int v = order[idx];
				for(int c=0;c<C;c++){
					bool ok = true;
					for(int u=0;u<K;u++) if(col[u]==c){
						if( (adjR[v]>>u) & 1u ){ ok = false; break; }
					}
					if(ok){ 
                        col[v]=c; 
                        if(dfs(idx+1)) 
                        return true; 
                        col[v]=-1; 
                    }
				}
				return false;
			};
			if(dfs(0)){
				outC = C; outColors = col; return;
			}
		}
	};
	function<void(int)> dfsRegion = [&](int r){
		if(r==k){
			vector<int> caps(k,0);
			unsigned long long active = 0ULL;
			for(int i=0;i<k;i++){ 
                caps[i] = __builtin_popcountll(chosenMask[i]); active |= chosenMask[i]; 
            }
			int totalActive = 0; for(int x: caps) totalActive += x;
			vector<unsigned int> adjR(k,0);
			vector<int> deg(k,0);
			for(int i=0;i<k;i++) for(int j=i+1;j<k;j++){
				bool edge=false;
				unsigned long long A = chosenMask[i];
				unsigned long long B = chosenMask[j];
				unsigned long long tmp = A;
				while(tmp){ 
                    unsigned long long lb = tmp & -tmp; 
                    int u = __builtin_ctzll(tmp); 
                    if(conf[u] & B){ 
                        edge=true; 
                        break; 
                    } 
                    tmp -= lb; 
                }
				if(edge){ 
                    adjR[i] |= (1u<<j); 
                    adjR[j] |= (1u<<i); 
                    deg[i]++; 
                    deg[j]++; 
                }
			}
			int numColors; vector<int> colors;
			colorize(deg,adjR,numColors,colors);
			double totalPenalty = 0.0;
			for(int i=0;i<k;i++) 
                for(int j=i+1;j<k;j++) 
                    if(colors[i]==colors[j]){
				        if( (adjR[i]>>j)&1u ){ 
                            totalPenalty += (double)caps[i] * (double)caps[j] * 1.0; 
                        }
			        }
			double score = (double)totalActive - alpha * (double)numColors - beta * totalPenalty;
			if(score > bestScore){
				bestScore = score;
				bestCaps = caps;
				bestActive = active;
				bestColor = colors;
			}
			return;
		}
		for(auto mask : regionSets[r]){
			chosenMask[r] = mask;
			dfsRegion(r+1);
		}
	};
	dfsRegion(0);
	cout<<bestScore<<"\n";
	cout<< (int)(*max_element(bestColor.begin(),bestColor.end()) + 1);
	for(int i=0;i<k;i++) 
        cout<<" "<<bestCaps[i];
	cout<<"\n";
	vector<int> activeList;
	for(int i=0;i<n;i++) 
        if( (bestActive>>i)&1ULL ) 
            activeList.push_back(i);
	if(!activeList.empty()){
		for(size_t i=0;i<activeList.size();++i){ 
            if(i) 
                cout<<" "; 
            cout<<activeList[i]; 
        }
	}
	cout<<"\n";
	for(int i=0;i<k;i++){ 
        if(i) 
            cout<<" "; 
        cout<<bestColor[i]; 
    }
	cout<<"\n";
	return 0;
}
