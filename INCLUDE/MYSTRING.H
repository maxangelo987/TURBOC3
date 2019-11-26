//@ author Shubham Jain
#ifndef MYSTRING_H
#define MYSTRING_H

#include<string.h>
#include<base.h>

class String;

class _string
{int k,l;
 char * s;
 _string(){}
 _string(char *st)
 {cout<<"inside _string(char *st) constructor\n";
  k=1;
  l=strlen(st);
  s=st;
 }
 friend String;
public:
 ~_string()
 {cout<<"inside _string destructor with k ="<<k<<endl;
  if(is1(k,15))
  delete s;
 }
 friend ostream& operator <<(ostream &o,String &st);
};

class String
{_string * _str;
 void remove()
 {_str->k--;
  if((_str->k&(~(1<<15)))==0)
  delete _str;
 }
public :
 String()
 {cout<<"inside  String() constructor\n";
  _str=new _string("");
 }
 String(char *st)
 { cout<<"inside  String(char *st) constructor\n";
  _str=new _string(st);
 }
 String(String &st)
 {  cout<<"inside  String(String &st) constructor\n";
   _str=st._str;
   _str->k++;
 }
 ~String()
 { cout<<"inside  String destructor with k ="<<_str->k<<endl;
   remove();
 }
 String & operator =(char *st)
 {if(is1(_str->k,15))
  delete _str->s;
  _str->s=st;
  _str->l=strlen(st);
  set0(_str->k,15);
  return *this;
 }
 String & operator =(String &st)
 {remove();
  _str=st._str;
  _str->k++;
  return *this;
 }
 String clone()
 {String a;
  a._str->k=(1<<15)+1;
  a._str->l=_str->l;
  a._str->s=new char[_str->l+1];
  a._str->s[0]=0;
  strcat(a._str->s,_str->s);
  return a;
 }
 String operator +(String &st)
 {String a;
  a._str->k=(1<<15)+1;
  a._str->l=_str->l+st._str->l;
  a._str->s=new char[_str->l+st._str->l+1];
  a._str->s[0]=0;
  strcat(a._str->s,_str->s);
  strcat(a._str->s,st._str->s);
  return a;
 }
 friend ostream& operator <<(ostream &o,String &st);
};

ostream& operator <<(ostream &o,String &st)
{o<<st._str->s;
 return o;
}
#endif