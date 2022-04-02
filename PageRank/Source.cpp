#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>
#include <iterator>
using namespace std;

struct dj {
    int d = 0;
    string toS;

    int axDj() {
        return ++d;
    }
};

dj findDj(vector<dj> djs, string to) {
    dj currDj;

    for (int i = 0; i < djs.size(); i++) {
        if (djs[i].toS == to)
            currDj = djs[i];
    }

    return currDj;
}

class AdjacencyList {
private:
    map<int, vector<pair<int, double>>> adjlist;
    map<int, vector<pair<int, double>>>::iterator it;

public:
    void insertEdge(map<string, int> mapper, string from, dj to);
    void PageRank(map<string, int> mapper, int p, int n);
    
};

void AdjacencyList::insertEdge(map<string, int> mapper, string from, dj to) {
    adjlist[mapper[from]].push_back(make_pair(mapper[to.toS], 1 / (to.axDj())));

    if (adjlist.find(mapper[to.toS]) == adjlist.end())
        adjlist[mapper[to.toS]] = {};
}

/* prints the PageRank of all pages after p powerIterations in ascending alphabetical order of webpagesand rounding rank to two
 decimal places */
void AdjacencyList::PageRank(map<string, int> mapper, int p, int n) {
    vector<double> ranks;
    vector<double> newRanks;

    //initialize initial ranks
    for (int i = 0; i < n; i++) {
        ranks.push_back(1 / n);
    }

    if (p > 1) {
        //Iterator is gonna go thru all of the rows
        //Remember adjlist first is integer values based on mapper
        for (it = adjlist.begin(); it != adjlist.end(); ++it) {
            for (int i = 0; i < n; i++) {
                if (it->second[i].second == 0)
                    return;
            }

        }
    }

}



void reMap(int& j, map<string, int>& mapper, vector<dj>& djs, string from, string to) {
    if (mapper.find(from) == mapper.end())
        mapper[from] = j++;

    if (mapper.find(to) == mapper.end()) {
        mapper[to] = j++;
        dj toDj;
        toDj.toS = to;
        djs.push_back(toDj);
    }

}

dj findDj(vector<dj> djs, string to) {
    dj currDj;

    for (int i = 0; i < djs.size(); i++) {
        if (djs[i].toS == to)
            currDj = djs[i];
    }

    return currDj;
}


int main()
{
    int n, p; 
    int j = 0; //j is for the mapper and also the number of urls
    AdjacencyList pages;
    map<string, int> mapper;
    vector<dj> djs;
    string from, to;
    cin >> n;
    cin >> p;
    for (int i = 0; i < n; i++)
    {
        string line;
        getline(cin, line);
        istringstream in(line);

        string from;
        in >> from;

        string to;
        in >> to;


        reMap(j, mapper, djs, from, to);

        //find the curr dj
        dj currDj = findDj(djs, to);
        

        pages.insertEdge(mapper, from, currDj);

    }
    //Create a graph object 
     pages.PageRank(mapper, p, j);

    return 0;
}