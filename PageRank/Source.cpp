#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <map>
#include <iterator>
using namespace std;

struct dj {
    double d;
    string toS;

    double axDj() {
        ++d;
        return d;
    }
};

dj* findDj(vector<dj*> djs, string to) {
    dj* currDj = new dj;

    for (int i = 0; i < djs.size(); i++) {
        if (djs[i]->toS == to)
            currDj = djs[i];
    }

    return currDj;
}

bool comparator(string a, string b) {
    return a < b;
}

class AdjacencyList {
private:
    map<int, vector<pair<int, double>>> adjlist;
    map<int, vector<pair<int, double>>>::iterator it;

public:
    void insertEdge(map<string, int> mapper, string from, dj* to);
    void PageRank(map<string, int> mapper, vector<string> urls, int p, int n);
    
};

void AdjacencyList::insertEdge(map<string, int> mapper, string from, dj* to) {

    adjlist[mapper[from]].push_back(make_pair(mapper[to->toS], (1 / (to->axDj()))));

    if (adjlist.find(mapper[to->toS]) == adjlist.end())
        adjlist[mapper[to->toS]] = {};

    //check for repeat to ig.
    for (it = adjlist.begin(); it != adjlist.end(); ++it) {
        for (int i = 0; i < it->second.size(); i++) {
            //If theres a repeat from a different from, then update the rank
            if (it->second[i].first == mapper[to->toS]) {
                it->second[i].second = (1 / to->d);
            }
        }
    }
   
}

/* prints the PageRank of all pages after p powerIterations in ascending alphabetical order of webpagesand rounding rank to two
 decimal places */
void AdjacencyList::PageRank(map<string, int> mapper, vector<string> urls, int p, int n) {
    vector<double> ranks;
    vector<double> newRanks;

    //initialize initial ranks
    for (int i = 0; i < n; i++) {
        ranks.push_back((1 / (double)n));
    }

    //page rank calculation and printing
    if (p > 1) {
        for (int pi = 1; pi < p; pi++) {
            //Iterator is gonna go thru all of the rows
            //Remember adjlist first is integer values based on mapper
            for (it = adjlist.begin(); it != adjlist.end(); ++it) {
                double mult = 0;

                //Nested for loop. Outer goes through the columns of the adjacency list
                for (int i = 0; i < it->second.size(); i++) {
                    //Goes thru the ranks basically. 
                    for (int j = 0; j < n; j++) {
                        if (it->second[i].first == j)
                            mult += (it->second[i].second * ranks[j]);
                    }
                }

                newRanks.push_back(mult);
            }

            //set the rank matrix equal to the newRanks matrix to change values
            ranks = newRanks;
            //Clear newRanks matrix to repeat
            newRanks.clear();
        }
    }


    //Now we should have our values, so we go thru and print!
    //first sort the urls
    sort(urls.begin(), urls.end(), comparator);

    //Now we print
    for (int i = 0; i < n; i++) {
        int currRank = mapper[urls[i]];
        cout << urls[i] << " " << setprecision(2) << fixed << ranks[currRank] << endl;
    }

}



void reMap(int& j, map<string, int>& mapper, vector<dj*>& djs, vector<string>& urls, string from, string to) {
    if (mapper.find(from) == mapper.end()) {
        mapper[from] = j++;
        dj* toDj = new dj;
        toDj->toS = from;
        toDj->d = 0;
        djs.push_back(toDj);
        urls.push_back(from);
    }

    if (mapper.find(to) == mapper.end()) {
        mapper[to] = j++;
        dj* toDj = new dj;
        toDj->toS = to;
        toDj->d = 0;
        djs.push_back(toDj);
        urls.push_back(to);
    }

}



int main()
{
    AdjacencyList pages;
    map<string, int> mapper;
    vector<string> urls;
    vector<dj*> djs;
    dj* currDj;
    string from, to;

    
    int j = 0; //j is for the mapper and also the number of urls

    int n;
    cin >> n;

    int p;
    cin >> p;

    cin.ignore();

    for (int i = 0; i < n; i++)
    {
        string line;
        getline(cin, line);
        istringstream in (line);

        in >> from;

        in >> to;


        reMap(j, mapper, djs, urls, from, to);

        //find the curr dj
        currDj = findDj(djs, to);
     
        //insert the edge
        pages.insertEdge(mapper, from, currDj);
    }
    //Run the pagerank
     pages.PageRank(mapper, urls, p, j);

    return 0;
}