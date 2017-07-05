#include <iostream>
#include <vector>
#include <queue>
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
            cout<<"\nExecutando LRU..."<<endl;
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

class LFU{
    private:
        vector< pair<int, int> > cache;
        int misses_comp;
        int misses_cap;
        int hits;
    public:
        LFU():misses_comp(0), misses_cap(0), hits(0){}
        void exe(int s, vector<int> words){
            cout<<"\nExecutando LFU..."<<endl;
            vector<int>::iterator i;
            vector< pair<int, int> >::iterator j, min;
            bool found;

            for(i=words.begin(); i!=words.end(); i++){
                cout<< "Elemento: "<<(*i);
                found = false;
                min = cache.begin();
                for(j = cache.begin(); j!=cache.end(); j++){
                    if((*j).first == (*i)){
                        found = true;
                        (*j).second++;
                        if((*min).second > (*j).second){
                            min = j;
                        }
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
                    cache.push_back(make_pair((*i), 0));
                }
                else{
                    cout<<"\tmiss\tElemento trocado: "<<(*min).first<<'.'<<endl;
                    misses_cap++;
                    *min = make_pair((*i), 0);
                }
            }

            cout<<"\nFinal da execucao. Resultados: "<<endl;
            cout<<"-Hits: "<<hits<<endl;
            cout<<"-Misses compulsorios: "<<misses_comp<<endl;
            cout<<"-Misses de capacidade: "<<misses_cap<<endl;
            hits = misses_comp = misses_cap = 0;

        }

};

class FIFO {
    private:
        vector<int> cache;
        int misses_comp;
        int misses_cap;
        int hits;
    public:
        FIFO() : misses_comp(0), misses_cap(0), hits(0) {}
        void exe(int s, vector<int> words) {
            cout << "\nExecutando FIFO..." << endl;
            vector<int>::iterator i;
            vector<int>::iterator j;
            queue<int> pos_q;
            bool found;
            for (i = words.begin(); i != words.end(); i++) {
                cout << "Elemento: " << (*i);
                found = false;
                for (j = cache.begin(); j != cache.end(); j++) {
                    if ((*j) == (*i)) {
                        cout<<"\thit."<<endl;
                        hits++;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    if (cache.size() < s) {
                        misses_comp++;
                        cache.push_back(*i);
                        pos_q.push(cache.size() - 1);
                        cout << "\tmiss\tElemento adicionado. " << (cache.size() - 1) << endl;
                    } else {
                        misses_cap++;
                        cout << "\tmiss\tElemento trocado: " << *(cache.begin() + pos_q.front()) << '.' << endl;
                        *(cache.begin() + pos_q.front()) = *i;
                        pos_q.push(pos_q.front());
                        pos_q.pop();
                    }
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

    LFU lfu;
    lfu.exe(size, words);

    FIFO fifo;
    fifo.exe(size, words);
}