#include <iostream>
#include <iomanip>
#include "cpplib.h"

using namespace std;

int main()
{
    int mem[5][5];
    FORI(i,0,5){
        FORI(j,0,5){
            mem[i][j]=std::numeric_limits<int>::max();
        }
    }

    char g[]="abcde";
    char f[]="adeac";
    std::vector<char> ll;
    std::cout<<std::lcs<int, char, 5, 5>(mem,g,f,4,4)<<std::endl;
    std::lcs_trace<int, char, 5, 5>(mem,g,f,ll,4,4);
    FOREACH (i,ll){
        std::cout<<*i<<std::endl;
    }
    std::edge_list<int,int> sa(6),kk(6);
    sa.add_edge(0,1,4);
    sa.add_edge(1,2,4);
    sa.add_edge(1,4,2);
    sa.add_edge(4,3,6);
    sa.add_edge(2,3,2);
    sa.add_edge(3,5,1);
    sa.add_edge(5,0,8);


    sa.mst(kk);
    FOREACH (i,kk){
        cout<<i->a<<" "<<i->b<<endl;
    }
    std::cout<<"shortest paths"<<endl;

    std::adj_list<int,int> ad(sa);
    std::vector<int> dd,ff,dd1,ff1;
    ad.bellmanford_shortest_path(0,dd,ff);
    FORI(i,0,dd.size())
    {
        std::cout<<"0 to "<<i<<" "<<dd[i]<<std::endl;
    }
    ad.dijkstra_shortest_path(0,dd1,ff1);
    FORI(i,0,dd1.size())
    {
        std::cout<<"0 to "<<i<<" "<<dd1[i]<<std::endl;
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
