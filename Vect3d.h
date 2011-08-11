#ifndef VECT3D_H
#define VECT3D_H

#if defined(_MSC_VER)
	#include <type_traits>
#else
	#include <bits/cpp_type_traits.h>
#endif
//#include <g++-3/std/cpp_type_traits.h>
#include <sstream>
//#include "defs.h"

#define SQR(x) ((x)*(x))
using namespace std;
//class ostream;

template <typename T>
class Vect3d
{
   public:
      Vect3d (T xc=0, T yc=0, T zc=0) : x (xc), y (yc), z (zc) { } 
      template<typename U> Vect3d(const Vect3d<U>&);

      T xcomp () const;
      T ycomp () const;
      T zcomp () const;
      void setX(T x);
      void setY(T y);
      void setZ(T z);
      void set(T X, T Y, T Z);

      template<typename U> T distsq(const Vect3d<U>&);

      template<typename U> Vect3d<T>& operator=(const Vect3d<U>&);
      template<typename U> Vect3d<T>& operator+=(const Vect3d<U>&);
      template<typename U> Vect3d<T>& operator-=(const Vect3d<U>&);
      template<typename U> Vect3d<T>& operator^=(const Vect3d<U>&);
      template<typename U> Vect3d<T>& operator*=(const U&);
      template<typename U> Vect3d<T>& operator/=(const U&);

   private:
      T x,y,z;
};

template <class T> inline T
Vect3d<T>::xcomp() const
{
   return x;
}

template <class T> inline T
Vect3d<T>::ycomp() const
{
   return y;
}

template <class T> inline T
Vect3d<T>::zcomp() const
{
   return z;
}


template <class T> 
template<typename U>
   inline 
Vect3d<T>::Vect3d(const Vect3d<U>& __v)
   : x(__v.x()), y(__v.y(),__v.z()) { }


   template<typename T>
   template<typename U>
   Vect3d<T>&
Vect3d<T>::operator*=(const U& __t)
{
   x *= __t;
   y *= __t;
   z *= __t;
   return *this;
}

template<typename T>
template<typename U>
   Vect3d<T>&
Vect3d<T>::operator/=(const U& __t)
{
   x /= __t;
   y /= __t;
   z /= __t;
   return *this;
}

template<typename T>
template<typename U>
   Vect3d<T>&
Vect3d<T>::operator=(const Vect3d<U>& __r)
{
   x = __r.xcomp();
   y = __r.ycomp();
   z = __r.zcomp();
   return *this;
}

template<typename T>
template<typename U>
   Vect3d<T>&
Vect3d<T>::operator+=(const Vect3d<U>& __r)
{
   x += __r.xcomp();
   y += __r.ycomp();
   z += __r.zcomp();
   return *this;
}


template<typename T>
template<typename U>

T Vect3d<T>::distsq(const Vect3d<U>& __r)
{
   return (SQR(x-__r.xcomp()) + SQR(y-__r.ycomp()) + SQR(z-__r.zcomp()));
}


template<typename T>
template<typename U>
   Vect3d<T>&
Vect3d<T>::operator-=(const Vect3d<U>& __r)
{
   x -= __r.xcomp();
   y -= __r.ycomp();
   z -= __r.zcomp();
   return *this;
}

   template<typename T>
inline void Vect3d<T>::setX(T X)
{
   x = X;
}

   template<typename T>
inline void Vect3d<T>::setY(T Y)
{
   y = Y;
}
   template<typename T>
inline void Vect3d<T>::setZ(T Z)
{
   z = Z;
}

   template<typename T>
inline void Vect3d<T>::set(T X, T Y, T Z)
{
   x = X;
   y = Y;
   z = Z;
}


template<typename T>
template<typename U>
   Vect3d<T>&
Vect3d<T>::operator^=(const Vect3d<U>& __r)
{
   x = y*__r.zcomp() - z* __r.ycomp();
   y = z*__r.xcomp() - x* __r.zcomp();
   z =  x*__r.ycomp() - y* __r.xcomp();
   return *this;
}

// Operators:
template<typename T>
   inline Vect3d<T>
operator+(const Vect3d<T>& __x, const Vect3d<T>& __y)
{ return Vect3d<T> (__x) += __y; }

template<typename T>
   inline Vect3d<T>
operator-(const Vect3d<T>& __x, const Vect3d<T>& __y)
{ return Vect3d<T> (__x) -= __y; }

template<typename T>
   inline Vect3d<T>
operator*(const Vect3d<T>& __x, const T& __y)
{ return Vect3d<T> (__x) *= __y; }

template<typename T>
   inline Vect3d<T>
operator*(const T& __x, const Vect3d<T>& __y)
{ return Vect3d<T> (__y) *= __x; }

template<typename T>
   inline Vect3d<T>
operator^(const Vect3d<T>& u, const Vect3d<T>& v)
{ 
   return Vect3d<T>
      (u.ycomp()*v.zcomp()- u.zcomp()*v.ycomp(), 
       u.zcomp()*v.xcomp()- u.xcomp()*v.zcomp(), 
       u.xcomp()*v.ycomp()- u.ycomp()*v.xcomp()); 
}

template<typename T>
   inline Vect3d<T>
operator/(const Vect3d<T>& __x, const T& __y)
{ return Vect3d<T> (__x) /= __y; }

template<typename T>
   inline bool
operator==(const Vect3d<T>& u, const Vect3d<T>& v)
{ return u.xcomp() == v.xcomp() && u.ycomp() == v.ycomp() && u.zcomp() == v.zcomp();}

#if 1
template<typename _Tp, typename _CharT, class _Traits>
   basic_ostream<_CharT, _Traits>&
operator<<(basic_ostream<_CharT, _Traits>& __os, const Vect3d<_Tp>& __v)
{
   basic_ostringstream<_CharT, _Traits> __s;
   __s.flags(__os.flags());
   __s.imbue(__os.getloc());
   __s.precision(__os.precision());
   __s << '[' << __v.xcomp() << "," << __v.ycomp() <<  "," << __v.zcomp() <<   ']';
   return __os << __s.str();
}
#else
template <class FLOAT> ostream&
operator << (ostream& os, const Vect3d<FLOAT>& v)
{
     return os << '(' << v.xcomp()  << ',' << v.ycomp() << ',' << v.zcomp() << ')';
}
#endif


template<typename T>
   inline T
operator*(const Vect3d<T>& u, const Vect3d<T>& v)
{return (u.xcomp()*v.xcomp() +u.ycomp()*v.ycomp() +u.zcomp()*v.zcomp());}


typedef Vect3d<float> vect_f;
typedef Vect3d<double> vect_d;
typedef Vect3d<int> vect_i;

static Vect3d<float> x_hat = Vect3d<float>(1.0,0.0,0.0);
static Vect3d<float> y_hat = Vect3d<float>(0.0,1.0,0.0);
static Vect3d<double> z_hat = Vect3d<double>(0.0,0.0,1.0);
static Vect3d<float> i_hat = Vect3d<float>(1.0,0.0,0.0);
static Vect3d<float> j_hat = Vect3d<float>(0.0,1.0,0.0);
static Vect3d<float> k_hat = Vect3d<float>(0.0,0.0,1.0);


#endif//VECT3D_H
