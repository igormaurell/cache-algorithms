#include <iostream>
#include <vector>
#include <utility>

using namespace std;
class LRU{
    private:
        vector< pair<int, int> > cache;
        int misses_comp;
        int misses_cap;
        int hits;
    public:
        LRU():misses_comp(0), misses_cap(0), hits(0){}

        void exe(int s, vector<int> words){
            cout<<"Executando LRU..."<<endl;
            vector<int>::iterator it;
            vector< pair<int, int> >::iterator jt, mt;
            bool found;
            for(it = words.begin();it!=words.end();it++){
                cout<<"Elemento: "<<(*it);
                found = false;
                mt = cache.begin();
                for(jt = cache.begin();jt!=cache.end();jt++){
                    if((*jt).first!=(*it)){
                        (*jt).second++;
                        if((*mt).second<(*jt).second){
                            mt = jt;
                        }        
                    } 
                    else{
                        (*jt).second = 0;
                        found = true;
                    }
                }
                if(found){
                    cout<<"\thit."<<endl;
                    hits++;
                    continue;
                }
                if(cache.size()!=s){
                    cout<<"\tmiss\tElemento adicionado."<<endl;
                    misses_comp++;
                    cache.push_back(make_pair((*it), 0));
                }
                else{
                    cout<<"\tmiss\tElemento trocado: "<<(*mt).first<<'.'<<endl;
                    misses_cap++;
                    *mt = make_pair((*it), 0);
                }       
            }

            cout<<"\nFinal da execucao. Resultados: "<<endl;
            cout<<"-Hits: "<<hits<<endl;
            cout<<"-Misses compulsorios: "<<misses_comp<<endl;
            cout<<"-Misses de capacidade: "<<misses_cap<<endl;
            hits = misses_comp = misses_cap = 0;
        }
};

int main(){
    int size;
    vector<int> words;
    cout<<"Tamanho da cache: ";
    cin>>size;

    int i, value;
    for(i = 0;cin>>value && value!=-1;i++){
        words.push_back(value);
    }
    LRU lru;
    lru.exe(size, words);
}