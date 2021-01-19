

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <queue>
#include <deque>
#include <unordered_set>
#include <fstream>
#include <unordered_map>


using namespace std;

int fifo(int[], int);
int lru(int[], int);
int op(int[], int);
bool search(int, vector<int>);
int predict(int[], vector<int>,int, int);

int main() {
   
    //generate random numbers
    //fill arr page
    
    FILE *pfile;
    pfile = fopen ("data.csv","w");
    
    int pages[100];
    srand(time(NULL));
   
    for(int i = 0 ; i < 100; i ++){
        pages[i] = rand()%49;
        //cout<< page[i] << " ";
    }
    
    
    
   
    //will cycle 30 times
    int capacity = 1;
    fprintf(pfile, "FIFO     LRU     OP\n");
    cout << "FIFO     LRU     OP\n";
    while(capacity<31){
      cout << fifo(pages, capacity);
      fprintf(pfile, "%d" ,fifo(pages, capacity));
        
        
       fprintf(pfile, "     ");
       cout << "     ";
       cout << lru(pages, capacity);
       fprintf(pfile,"%d", lru(pages, capacity) );
                
        fprintf(pfile, "     ");
        cout << "     ";

        fprintf(pfile,"%d ", op(pages, capacity));
        cout << op(pages, capacity);
        
        fprintf(pfile, "\n");
        cout << "\n";
                
        capacity++;
    }
    
    fclose(pfile);
    
    return 0;
}

int fifo(int pages[100], int capacity){
    int faults=0;
    unordered_set<int> s;
    queue<int> indexes;
    
    for (int i=0; i<100; i++)
        {
            if (s.size() < capacity)
            {
                if (s.find(pages[i])==s.end())
                {
                    s.insert(pages[i]);
                    faults++;
                    indexes.push(pages[i]);
                }
            }
            else{
                       if (s.find(pages[i]) == s.end())
                       {
                           int val = indexes.front();
                           indexes.pop();
                           s.erase(val);
                           s.insert(pages[i]);
                           indexes.push(pages[i]);
                           faults++;
                       }
                   }
            }
      
    
    return faults;
}

int lru(int pages[100], int capacity){
    int faults = 0;
    unordered_set<int> s;
    unordered_map<int, int> indexes;
    int val;
    int INT_MAX;
    
    for (int i=0; i<100; i++){
            if (s.size() < capacity){
                if (s.find(pages[i])==s.end())
                {
                    s.insert(pages[i]);
                    faults++;
                }
                indexes[pages[i]] = i;
            }
            else{
                if (s.find(pages[i]) == s.end())
                {
                    int lru = INT_MAX;
                    
                    
                    for (auto it=s.begin(); it!=s.end(); it++)
                    {
                        if (indexes[*it] < lru)
                        {
                            lru = indexes[*it];
                            val = *it;
                        }
                    }
                    s.erase(val);
                    s.insert(pages[i]);
                    faults++;
                }
                indexes[pages[i]] = i;
            }
        }
    return faults;
    
}

int op(int pages[100], int capacity){
    int faults = 0;
    int hits = 0;
    
    vector<int > s;
    
    for(int i = 0; i < 100; i++){
        
        //if page is found
        if (search(pages[i], s)) {
                   hits++;
                   continue;
               }
        if (s.size() < capacity){
                   s.push_back(pages[i]);
        }
        else {
                    int j = predict(pages, s, 100, i + 1);
                    s[j] = pages[i];
                }
        
    }
    faults = 100 - hits;
    return faults;
    
}

bool search(int key, vector<int> s){
    for(int i = 0 ; i < s.size(); i++){
        if(s[i] == key){
            return true;
        }
    }
    return false;
}

int predict(int pages[100], vector<int> s ,int capacity, int index){
    
    int res = -1, farthest = index;
    
        for (int i = 0; i < s.size(); i++) {
            int j;
            for (j = index; j < capacity; j++) {
                if (s[i] == pages[j]) {
                    if (j > farthest) {
                        farthest = j;
                        res = i;
                    }
                    break;
                }
            }
      
            // If a page is never referenced in future,
            // return it.
            if (j == capacity)
                return i;
        }
      
        // If all of the frames were not in future,
        // return any of them, we return 0. Otherwise
        // we return res.
        return (res == -1) ? 0 : res;
}
