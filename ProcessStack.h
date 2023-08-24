#include<cstdio>
#include<stack>
#include<queue>
#include<map>
#include<set>
using namespace std;



template<typename T>
//单个递归函数
class ProcessStackNode{
public:
    static bool isBreak;
    T result;

    virtual ProcessStackNode* find_next_process(){return NULL;}

    virtual void merge_return_value(T previous_return_value){}

    virtual void run(){}

    virtual void traceback(){}

    void breakProcess(){
        isBreak = true;
    }

    
};
template<typename T>
bool ProcessStackNode<T>::isBreak = false;



template<typename T>
//栈式递归回溯，T代表递归函数的返回值
class ProcessStack{
private:
    stack<ProcessStackNode<T>* > sta;
public:
    T run(ProcessStackNode<T>* root){    
        //初始节点  
        while (!sta.empty()) sta.pop();
        sta.push(root);
        root->isBreak = false;
        

        int isReturn = false;
        T previous_return_value;
        while (!sta.empty()){
            ProcessStackNode<T> *current_process = sta.top();
            
            //printf("deep = %d\n", (int)sta.size());

            //从更深的节点回溯过来
            if (isReturn){
                current_process->merge_return_value(previous_return_value);
            }
            //第一次执行
            else{
                current_process->run();
            }


            //尝试往更深的节点搜索
            ProcessStackNode<T> *next_process = NULL;
            //如果未全局中断则找下一个节点
            if (!current_process->isBreak){
                next_process = current_process->find_next_process();
            }
            //该节点的分支已经遍历完
            if (next_process == NULL){
                isReturn = true;
                previous_return_value = current_process->result;
                sta.pop();
                current_process->traceback();
                delete current_process;

                continue;
            }
            //遍历该节点的其它分支
            else{
                sta.push(next_process);
                isReturn = false;
                continue;
            }
        }

        return previous_return_value;
    }


};

