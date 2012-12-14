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
    struct RefCounter {
      RefCounter() 
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
      r_ = new RefCounter;
      r_->p_ = p;
      r_->count_++;
    }

    ~SmartPointer()
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

    SmartPointer(SmartPointer<T>& that)
      : r_(0)
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

      r_ = that.r_;
      r_->count_++;
    }

    T* operator->()
    {
      return ((r_ != 0) ? r_->p_ : 0);
    }

    T& operator*()
    {
      return *(r_->p_);
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

      r_ = that.r_;
      r_->count_++;

      return *this;
    }

    bool IsNull()
    {
      return ((r_ == 0) || (r_->p_ == 0));
    }

  private:
    RefCounter* r_;
  };
}

#endif // LEPCPPLIB_SMARTPOINTER_H_
