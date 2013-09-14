#ifndef CPPUTILS_H
#define CPPUTILS_H

#include <string>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <cctype>
#include <cstdio>
// Madura A.
// C++ Utilities

/** General foreach for STL like containers */
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
/*  NOTE: It is assumed that IDX_T and WGT_T are numeric primitives, like
    int, long, size_t ..etc do not use float/double or any non-numeric type
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

template<typename IDX_T, typename WGT_T>
class edge_list : public vector< edge< IDX_T, WGT_T > >
{
public:
    edge_list(){}
    void add_edge(IDX_T a, IDX_T b, WGT_T w)
    {
        this->push_back(edge<IDX_T, WGT_T>(a,b,w));
    }
    void mst(){
        edge_comparator<IDX_T, WGT_T> ec;
        sort(this->begin(), this->end(), ec);
    }
};
template<typename IDX_T, typename WGT_T>
class adj_list : public vector< map<IDX_T,WGT_T> >
{
public:
    adj_list(edge_list<IDX_T, WGT_T>& edgelist)
    {
        this->resize(edgelist.size());
        FOREACH(i,edgelist) {
            add_edge(i->a, i->b, i->w);
        }
    }
    adj_list(IDX_T vertices)
    {
        this->resize(vertices);
    }
    void add_edge(IDX_T a, IDX_T b, WGT_T w)
    {
        this->at(a).insert(pair<IDX_T,WGT_T>(b,w));
    }
    bool is_edge(IDX_T a, IDX_T b)
    {
        map<IDX_T,WGT_T>& tt=this->at(a);
        return tt.find(b)!=tt.end();
    }
};
}

#endif // CPPUTILS_H
