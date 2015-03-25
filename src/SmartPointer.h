/*
  Copyright (c) 2011 Neevarp Yhtroom

  Permission is hereby granted, free of charge, to any person obtaining
  a copy of this software and associated documentation files (the
  "Software"), to deal in the Software without restriction, including
  without limitation the rights to use, copy, modify, merge, publish,
  distribute, sublicense, and/or sell copies of the Software, and to
  permit persons to whom the Software is furnished to do so, subject to
  the following conditions:

  The above copyright notice and this permission notice shall be
  included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef LEP_SMARTPOINTER_H_
#define LEP_SMARTPOINTER_H_

namespace lep {
  template <class T> class SmartPointer {
  private:
    T* p_;
    int* count_;

  public:
    SmartPointer(T* p)
      : p_(p), count_(0)
    {
      count_ = new int;
      *count_ =  1;
    }

    SmartPointer()
      : p_(0), count_(0)
    {
    }

    ~SmartPointer()
    {
      RemoveReference();
    }

    SmartPointer(const SmartPointer<T>& that)
      : p_(0), count_(0)
    {
      AddReference(that.p_, that.count_);
    }

    SmartPointer(SmartPointer<T>& that)
      : p_(0), count_(0)
    {
      AddReference(that.p_, that.count_);
    }

    T* operator->()
    {
      return p_;
    }

    const T* operator->() const
    {
      return p_;
    }

    T& operator*()
    {
      return *p_;
    }

    const T& operator*() const
    {
      return *p_;
    }

    bool operator<(const SmartPointer<T>& that) const
    {
      bool result = false;

      if ((this->p_ == 0) && that.p_ != 0) {
        result = true;
      }
      else if ((this->p_ != 0) && that.p_ == 0) {
        result = false;
      }
      else {
        result = (this->p_ < that.p_);
      }

      return result;
    }

    bool operator>(const SmartPointer<T>& that) const
    {
     return !((*this == that) || (*this < that));
    }

    bool operator==(const SmartPointer<T>& that)
    {
      return (p_ == that.p_);
    }

    bool operator!=(const SmartPointer<T>& that)
    {
      return !(this->operator==(that));
    }

    const SmartPointer<T>& operator=(const SmartPointer<T>& that)
    {
      AddReference(that.p_, that.count_);
      return *this;
    }

    bool IsNull()
    {
      return (p_ == 0);
    }

  private:
  void AddReference(T*p, int* count)
  {
    // ignore in case it is a self reference.
    if (p_ != p) {
      if (count_ != 0) {
        RemoveReference();
      }

      if (count != 0) {
        p_ = p;
        count_ = count;
        (*count_)++;
      }
    }
  }

  void RemoveReference()
  {
    if (count_ != 0) {
      (*count_)--;
      if (*count_ <= 0) {
        delete p_;
        p_ = 0;
        delete count_;
      }

      count_ = 0;
    }
  }
};
}

#endif // LEP_SMARTPOINTER_H_

