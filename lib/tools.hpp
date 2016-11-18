#ifndef _TOOLS_HPP
#define _TOOLS_HPP

#include <array>
#include <chrono>
#include <macros.hpp>
#include <string>
#include <vector>

using namespace std;

//! measure time
using instant_t=chrono::time_point<chrono::steady_clock>;
inline instant_t take_time()
{return chrono::steady_clock::now();}

//! compute elapsed time
inline string elapsed_time(const instant_t &start)
{
  auto diff=take_time()-start;
  
  double el_nano=chrono::duration<double,nano>(diff).count();
  if(el_nano<1000) return to_string(el_nano)+" ns";
  
  double el_micro=chrono::duration<double,micro>(diff).count();
  if(el_micro<1000) return to_string(el_micro)+" us";
  
  double el_milli=chrono::duration<double,milli>(diff).count();
  if(el_milli<1000) return to_string(el_milli)+" ms";
  
  double el_sec=chrono::duration<double>(diff).count();
  return to_string(el_sec)+" s";
}

//! check if two quantities have the same sign
template <class T> bool same_sign(const T &a,const T &b)
{return (a<=0 and b<=0) or (a>=0 and b>=0);}

//! check it two quantities have opposite sign
template <class T> bool opposite_sign(const T &a,const T &b)
{return !same_sign(a,b);}

//! crashes emitting the message
void internal_crash(int line,const char *file,const char *temp,...);

//! combine arguments in a single string
string combine(const char *format,...);

//! close gently with a message
void close_with_mess(const char *format,...);

//!check if a file exists
int file_exists(string path);

//! check if a directoy exists
int dir_exists(string path);

//! handle signals
void signal_handler(int sig);

//! check that a vector is orderd
template <class T> inline void check_ordered(const initializer_list<T> &vec)
{
  auto prev=vec.begin(),cur=prev+1;
  size_t it=1;
  do
    {
      if(*prev>*cur)
	CRASH("Element %zu has value %s, greater than element %zu, %s",it-1,to_string(*prev).c_str(),it,to_string(*cur).c_str());
      prev=cur++;
      it++;
    }
  while(cur!=vec.end());
  
}

//! return a range of int
class range_t : private array<size_t,3>
{
public:
  //bind
  size_t &start=(*this)[0];
  size_t &each=(*this)[1];
  size_t &end=(*this)[2];
  
  //! default constructor
  range_t() {}
  
  //! init from triplet
  range_t(initializer_list<size_t> list)
  {
    if(list.size()!=3) CRASH("list size %d while expecting 3",list.size());
    copy(list.begin(),list.end(),this->begin());
  }
};

//! convert crashing if not working
inline int to_int(string s)
{
  int out=0;
  try{out=stoi(s);}
  catch(exception &e){CRASH("Exception %s while converting to int string \"%s\"",e.what(),s.c_str());}
  
  return out;
}

DEFINE_HAS_METHOD(size);
#define is_vector has_method_size

DEFINE_HAS_METHOD(ave_err);

DEFINE_HAS_METHOD(is_printable);

#endif
