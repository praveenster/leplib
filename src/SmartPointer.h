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

#ifndef LEPCPPLIB_SMARTPOINTER_H_
#define LEPCPPLIB_SMARTPOINTER_H_

namespace lepcpplib {
  template <class T> class SmartPointer {
  private:
    struct ReferenceCounter {
      ReferenceCounter() 
        : p_(0), count_(0)
      {
      }

      T* p_;
      int count_;
    };

  public:
    SmartPointer(T* p)
      : r_(0)
    {
      ReferenceCounter* r = new ReferenceCounter;
      r->p_ = p;
      AddReference(r);
    }

    SmartPointer()
      : r_(0)
    {
    }

    ~SmartPointer()
    {
      RemoveReference();
    }

    SmartPointer(const SmartPointer<T>& that)
      : r_(0)
    {
      AddReference(that.r_);
    }

    SmartPointer(SmartPointer<T>& that)
      : r_(0)
    {
      AddReference(that.r_);
    }

    T* operator->()
    {
      return ((r_ != 0) ? r_->p_ : 0);
    }

    T& operator*()
    {
      return *(r_->p_);
    }

    bool operator<(const SmartPointer<T>& that) const
    {
      bool result = false;

      if ((this->r_ == 0) && that.r_ != 0) {
        result = true;
      }
      else if ((this->r_ != 0) && that.r_ == 0) {
        result = false;
      }
      else {
        result = (this->r_ < that.r_);
      }

      return result;
    }

    bool operator>(const SmartPointer<T>& that) const
    {
     return !((*this == that) || (*this < that));
    }

    bool operator==(const SmartPointer<T>& that)
    {
      bool result = false;
      if ((r_ != 0) &&  (that.r_ != 0)) {
        result = ((r_->p_) == (that.r_->p_));
      }

      return result;
    }

    bool operator!=(const SmartPointer<T>& that)
    {
      return !(this->operator==(that));
    }

    const SmartPointer<T>& operator=(const SmartPointer<T>& that)
    {
      AddReference(that.r_);
      return *this;
    }

    bool IsNull()
    {
      return ((r_ == 0) || (r_->p_ == 0));
    }

  private:
  void AddReference(ReferenceCounter* r)
  {
    // ignore this in case this is a self reference.
    if (r_ != r) {
      if (r_ != 0) {
        RemoveReference();
      }

      if (r != 0) {
        r_ = r;
        r_->count_++;
      }
    }
  }

  void RemoveReference()
  {
    if (r_ != 0) {
      r_->count_--;
      if (r_->count_ <= 0) {
        r_->count_ = 0;
        delete r_->p_;
        r_->p_ = 0;
        delete r_;
      }

      r_ = 0;
    }
  }

  private:
    ReferenceCounter* r_;
  };
}

#endif // LEPCPPLIB_SMARTPOINTER_H_
