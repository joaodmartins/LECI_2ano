//
// Tomás Oliveira e Silva, AED, October 2014, September 2015
//
// Generic stack (First In Last Out) implementation based on an array
//

#ifndef _AED_aStack_
#define _AED_aStack_

#include <cassert>

template <typename T>
class aStack
{
  private:
    int max_size; // maximum stack size
    int cur_size; // current stack size
    T *data;      // the stack data (stored in an array)
  public:
    aStack(int n = 100)
    {
      assert(n >= 10 && n <= 1000000);
      max_size = n;
      cur_size = 0;
      data = new T[n];
    }
    ~aStack(void)
    {
      delete[] data;
    }
    void clear(void)
    {
      cur_size = 0;
    }
    int size(void) const
    {
      return cur_size;
    }
    int is_full(void) const
    {
      return (cur_size == max_size) ? 1 : 0;
    }
    int is_empty(void) const
    {
      return (cur_size == 0) ? 1 : 0;
    }
    T top(void) const
    {
      assert(cur_size > 0);
      return data[cur_size - 1];
    }
    void push(T &v)
    {
      assert(cur_size < max_size);
      data[cur_size++] = v;

      //Resize stack
      if(cur_size == max_size){
        T *t_data = data;
        max_size+=100;
        data = new T[max_size];
        memcpy(data, t_data, cur_size*sizeof(T));
      }
    }
    T pop(void)
    {
      assert(cur_size > 0);
      return data[--cur_size];
    }
};

#endif
