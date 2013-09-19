/**
 * C++ Utility Library
 * by Madura A.
 * Placed on public domain, this is "do what ever you want with it code" with
 * an additional statement for copyright. I do hold it and due credit is admired.
 *
 */
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
#include <queue>
#include <stdexcept>

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
 *  WGT_T can be int,long,float ..etc
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
    //template<typename IDX_T>
    class vertice_comparator
    {
        vector<IDX_T> *dist;
    public:
        vertice_comparator(vector<IDX_T> *_dist){
            dist = _dist;
        }
        bool operator() (const IDX_T& a, const IDX_T& b){
            return dist->at(a) > dist->at(b);
        }

    };
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
            dist[i]=std::numeric_limits<IDX_T>::max();
            pred[i]=std::numeric_limits<IDX_T>::max();
        }
        dist[src]=0;
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

    void dijkstra_shortest_path(IDX_T src,
                                vector<IDX_T>& dist,
                                vector<IDX_T>& pred){
        vector<IDX_T> heap;
        dist.resize(this->size());
        pred.resize(this->size());
        heap.resize(this->size());
        FORI(i,0,dist.size()){
            dist[i]=std::numeric_limits<IDX_T>::max();
            pred[i]=std::numeric_limits<IDX_T>::max();
            heap[i]=i;
        }
        dist[src]=0;

        vertice_comparator vc(&dist);

        make_heap(heap.begin(), heap.end(),vc);

        while (!heap.empty()){
            pop_heap(heap.begin(),heap.end(),vc);

            IDX_T u=heap.back();
            heap.pop_back();
            if (dist[u]==numeric_limits<IDX_T>::max()) {
                break;
            }
            FOREACH(i, this->at(u)) {
                // i->first is index, i->second is weight
                WGT_T w =dist[u]+ i->second;
                if (w < dist[i->first]) {
                    dist[i->first]=w;
                    pred[i->first]=u;
                    make_heap(heap.begin(),heap.end(),vc);
                }
            }
        }

    }
};

/** Longest Common Subsequence */
/*  s1, s2 are sequence lengths
 *  i, j are starting indexes, all indexing starts with 0
 *  IDX_T - index type, SEQ_T - sequence type
 *
 *  MAKE SURE TO INITILIZE mem WITH MAX OF IDX_T
 */
template<typename IDX_T, typename SEQ_T, IDX_T s1, IDX_T s2>
IDX_T lcs(IDX_T mem[s1][s2], SEQ_T *seq1, SEQ_T *seq2, IDX_T i, IDX_T j)
{

    IDX_T ret;
    if (i==-1 || j==-1) {
        ret = 0;
    } else if (mem[i][j] != numeric_limits<IDX_T>::max()) {
        return mem[i][j];
    } else if (seq1[i] == seq2[j]){
        ret=lcs<IDX_T, SEQ_T, s1, s2>(mem,seq1,seq2,i-1,j-1)+1;
    } else {
        ret=max<IDX_T>(lcs<IDX_T, SEQ_T, s1, s2>(mem,seq1,seq2,i,j-1) , lcs<IDX_T, SEQ_T, s1, s2>(mem,seq1,seq2,i-1,j));
    }
    mem[i][j]=ret;
    return ret;
}
template<typename IDX_T, typename SEQ_T, IDX_T s1, IDX_T s2>
void lcs_trace(IDX_T mem[s1][s2], SEQ_T *seq1, SEQ_T *seq2, vector< SEQ_T >& trace, IDX_T i, IDX_T j )
{
    if (i==-1 || j==-1){
        return;
    } else if (seq1[i]==seq2[j]){
        trace.push_back(seq1[i]);
        lcs_trace<IDX_T, SEQ_T, s1, s2>(mem, seq1, seq2, trace, i-1, j-1);

    } else {
        if (mem[i][j-1] > mem[i-1][j]) {
            lcs_trace<IDX_T, SEQ_T, s1, s2>(mem, seq1, seq2, trace, i, j-1);
        } else {
            lcs_trace<IDX_T, SEQ_T, s1, s2>(mem, seq1, seq2, trace, i-1, j);
        }

    }
}
}

#endif // CPPUTILS_H
