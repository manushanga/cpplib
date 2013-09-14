#include <iostream>
#include <iomanip>
#include "cpplib.h"
using namespace std;

int main()
{

    std::edge_list<int,int> sa;
    sa.add_edge(0,1,41);
    sa.add_edge(1,2,1);
    sa.add_edge(2,1,51);
    sa.mst();
    FOREACH (i,sa){
        cout<<i->w<<endl;
    }
    std::adj_list<int,int> ad(sa);
    ad.add_edge(0,5,0);
    cout<<ad.is_edge(0,2)<<endl;
    cout<<ad.is_edge(1,2)<<endl;
    FOREACH(i,ad)
    {
        cout<<(i->find(5)!=i->end())<<endl;
    }
    cout<<std::setprecision(100)<<from_string<float>("56.6605513",10)<<endl;
    std::vector<std::string> ss;
    split("  asdfa sdf\na\tg","\t\r\n ",ss);
    for (int i=0;i<ss.size();i++)
        cout<<ss[i]<<endl;

    cout<<"|"<<std::trim("      asd dafgo o0   ")<<"|"<<endl;
    cout<<std::to_upper("FSFUsffsfa")<<endl;
    return 0;
}