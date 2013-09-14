#ifndef CPPUTILS_H
#define CPPUTILS_H
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <sstream>
#include <cmath>
#include <list>
#include <limits>
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <stdexcept>
// Madura A.
// C++ Utilities

#ifdef _MSC_VER
#define typeof(x) decltype(x)
#endif

/** General foreach for STL like containers */
#define FORI(x,i,j) \
    for(int x=i;x<j;x++)

#define FORUI(x,i,j) \
    for(unsigned int x=i;x<j;x++)

#define FORSZ(x,i,j) \
    for(size_t x=i;x<j;x++)

#define FOREACH(var, container) \
    for(typeof((container).begin()) var = (container).begin(); \
        var != (container).end(); \
        ++var)

// helpers
namespace cpplib {
inline int char_to_int(char c)
{
    switch (c){
    case 'A':
        return 10;
    case 'B':
        return 11;
    case 'C':
        return 12;
    case 'D':
        return 13;
    case 'E':
        return 14;
    case 'F':
        return 15;
    default:
        return c - '0';
    }
}
}
namespace std{

/** String Functions  **/

template<typename FROM>
/** Convert to wstring from FROM type
 */
std::wstring to_wstring(FROM f){
    std::wstringstream ss;
    ss<<f;
    return ss.str();
}
template<typename FROM>
/** Convert to string from FROM type
 */
std::string to_string(FROM f){
    std::stringstream ss;
    ss<<f;
    return ss.str();
}
/** Get upper case string
 */
std::string to_upper(std::string str);
/** Get lower case string
 */
std::string to_lower(std::string str);
/** Trim string from start and end.
	@remarks
	Uses isspace() to check for blanks
 */
std::string trim(std::string str);
/**
	Splits a string by delim (char) and puts in the given vector
  */
void split(std::string str, char delim, std::vector<std::string>& strvec);
/**
	Splits a string by delim (c_str) and puts in the given vector
  */
void split(std::string str, char *delim, std::vector<std::string>& strvec);

template<typename TO>
/** TO=conversion type, 0 < base <= 16
 */
TO from_string(std::string number, TO base)
{
    return (TO)0;
}
/** Graph structures and algorithms **/
/*  NOTE: IDX_T can be int,long ..etc
    WGT_T can be int,long,float ..etc
 */

template<typename IDX_T, typename WGT_T>
struct edge{
    IDX_T a,b;
    WGT_T w;
    edge(){}
    edge(IDX_T _a, IDX_T _b, WGT_T _w){
        a=_a;b=_b;w=_w;
    }
};

template<typename IDX_T, typename WGT_T>
struct edge_comparator{
    bool operator() (const edge<IDX_T, WGT_T>& a,const edge<IDX_T, WGT_T>& b)
    {
        return (a.w < b.w);
    }
};
template<typename IDX_T>
class set_list : public vector < list< IDX_T > * >
{
private:
    vector< list<IDX_T> > lists ;
public:
    set_list(IDX_T indexes): vector < list < IDX_T >* >(){
        this->resize(indexes);
        int idx=0;
        FOREACH(i, *this){
            *i=new list<IDX_T>;
            (*i)->push_back(idx);
            idx++;
        }
        FOREACH(i,*this){
            cout<<*i<<"("<<(*i)->front()<<") ";
        }
        cout<<endl;
    }
    void merge(IDX_T a,IDX_T b){

        list<IDX_T> *al=this->at(a);
        list<IDX_T> *bl=this->at(b);
        if (al->size() > bl->size()){
            FOREACH(i,*bl) {
                this->at( *i )=al;
            }
            al->splice(al->end(),*bl);
            delete bl;
        } else {

            FOREACH(i,*al) {
                this->at( *i )=bl;
            }
            bl->splice(bl->end(),*al);
            delete al;
        }

        FOREACH(i,*this){
            cout<<*i<<"(";
            FOREACH(j, *(*i)){
                cout<<*j<<" ";
            }
            cout<<")";
        }
        cout<<endl;
    }
    ~set_list()
    {
        set<list <IDX_T> *> f;
        FOREACH(i,*this){
            f.insert(*i);
        }
        FOREACH(i, f){
            delete *i;
        }
    }
};
template<typename IDX_T, typename WGT_T>
class edge_list : public vector< edge< IDX_T, WGT_T > >
{
private:
    IDX_T vertex_count;
public:
    edge_list(IDX_T verts) : vector< edge< IDX_T, WGT_T > >()
    {
        vertex_count = verts;
    }
    void add_edge(IDX_T a, IDX_T b, WGT_T w)
    {
        this->push_back(edge<IDX_T, WGT_T>(a,b,w));
    }
    inline IDX_T get_vertex_count(){
        return vertex_count;
    }
    void mst(edge_list< IDX_T, WGT_T >& mst){
        set_list<IDX_T> sl(this->size());
        edge_comparator<IDX_T, WGT_T> ec;
        sort(this->begin(), this->end(), ec);
        FOREACH (i, *this ) {
            cout<<"j  "<<sl[i->a]<<" "<<sl[i->b]<<" "<< i->a <<","<< i->b <<endl;
            if ( sl[i->a] != sl[i->b] ) {
                mst.push_back(*i);
                sl.merge(i->a, i->b);
            }
        }
    }
};
template<typename IDX_T, typename WGT_T>
class adj_list : public vector< map<IDX_T,WGT_T> >
{
public:
    adj_list(edge_list<IDX_T, WGT_T>& edgelist) : vector< map<IDX_T,WGT_T> > ()
    {
        this->resize(edgelist.get_vertex_count());
        FOREACH(i,edgelist) {
            add_edge(i->a, i->b, i->w);
        }
    }
    adj_list(IDX_T vertices) : vector< map<IDX_T,WGT_T> > ()
    {
        this->resize(vertices);
    }
    inline WGT_T get_weight(IDX_T a, IDX_T b)
    {
        return this->at(a).find(a)->second;
    }
    void add_edge(IDX_T a, IDX_T b, WGT_T w)
    {
        this->at(a).insert(pair<IDX_T,WGT_T>(b,w));
    }
    bool has_edge(IDX_T a, IDX_T b)
    {
        map<IDX_T,WGT_T>& tt=this->at(a);
        return tt.find(b)!=tt.end();
    }
    void bellmanford_shortest_path(IDX_T src,
                                   vector<IDX_T>& dist,
                                   vector<IDX_T>& pred)
    {
        dist.resize(this->size());
        pred.resize(this->size());
        FORI(i,0,dist.size()){
            if (i==src)
                dist[i]=0;
            else {
                dist[i]=std::numeric_limits<IDX_T>::max();
            }
            pred[i]=std::numeric_limits<IDX_T>::max();
        }
        FORI(i,0,(int)dist.size()) {
            FORSZ(row,0,this->size()) {
                FOREACH(col,this->at(row)){
                    if (dist[row] + col->second < dist[col->first]){
                        dist[col->first] = dist[row] + col->second;
                        pred[col->first] = row;

                    }
                }
            }
        }

        FORSZ(row,0,this->size()) {
            FOREACH(col,this->at(row)){

                if (dist[row] + col->second < dist[col->first] )
                    throw std::runtime_error("Graph contains a negative-weight cycle");
            }
        }

    }
};
}

#endif // CPPUTILS_H
