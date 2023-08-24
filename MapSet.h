#include<cstdio>
#include<stack>
#include<queue>
#include<map>
#include<set>
using namespace std;

template<typename TKey, typename Tval>
//可以通过键值来查找的set
class MapSet{
private:
    set<Tval> data_set;
    map<TKey, Tval> data_map;
public:
    void insert(TKey key, Tval val){
        data_set.insert(val);
        data_map[key] = val;
    }

    Tval get_begin_element(){
        auto it = data_set.begin();
        return *it;
    }



    void erase(TKey key, Tval val){
        data_set.erase(val);
        data_map.erase(key);
    }

    Tval get_by_key(TKey key){
        return data_map[key];
    }

    bool empty(){
        return data_set.empty();
    }

    void clear(){
        data_set.clear();
        data_map.clear();
    }
};

