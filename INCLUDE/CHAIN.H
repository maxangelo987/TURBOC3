//@ author Shubham Jain
#ifndef CHAIN_H
#define CHAIN_H

template<class T>
class elem;

template<class T>
class elem
{T e;
 elem<T> *p;
 friend chain<T>;
}

template<class T>
class chain
{elem<T> *s;
 int no;
 elem<T>*& to(int);
public:
 chain()                      //default constructor
 {no=0;
 }

 chain(int);                  //cunstructor to make given length of chain

 chain(chain<T> &);           /*cunstructor
				it cunstruct chain by removing given chain*/

 T & operator[](int);         //returns a reference of element at given index

 chain<T> out(int,int);       /*remove & returns elements after given index
				  syntax: out(index_no,no_of_elements)   */

 void add(int,int);           /*adds given no of elements after given index
				  syntax  out(index_no,no_of_elements)   */

 void add(int,chain<T> &);    //add a chain after given index

 chain<T> clone(int,int);     /*retuns a duplicated chain of given interval
				by given index and length                */

 ~chain();                    //decunstructor of chain

 int length();                //returns the length of chain

 chain<T> out_s(int);         //take out chain of no of elements from start

 void add_s(int);             // adds no of elements at start

 chain<T> out_l(int);         //take out chain of no of elements from last

 void add_l(int);             //adds no of elements at last

 chain<T> clone();            //returns a duplicated chain

 void push_s(T &);            //pushes an element at start

 void push_l(T &);            //pushes an element at last

 T& pop_s();                  //take out first element

 T& pop_l();                  //take out last element

 void operator =(chain<T> &);  //initiate given chain to this chain

 void swap(int,int);          //swap two elements at given index(s)

};

/*Definitions of function members of class chain<T>
*/

template<class T> elem<T>*&  chain<T>:: to(int i)
{elem<T> **a;
 a=&s;
 if(i>0)
 {i=(i-1)%no+1;
  for(int n=0;n<i;n++)
  a=&((*a)->p);
 }
 return *a;
}
template<class T> chain<T> :: chain(int i)
{ for(int n=0;n<i;n++)
   to(n)=new elem<T>;
 to(i)=s;
 no=i;
}
template<class T> chain<T> :: chain(chain<T>&c)
{add(0,c);
}

template<class T> T& chain<T> :: operator[](int i)
{ return to(i)->e;
}
template<class T> chain<T> chain<T> ::  out(int i,int j)
{chain<T> c;
 if((i+j)>no)j=no-i;
 c.s=to(i);
 to(i)=to(i+j);
 c.no=j;
 c.to(j)=c.s;
 no-=j;
 return c;
}
template<class T> void chain<T> :: add(int i,int j)
{chain<T> c(j);
 c.to(j)=to(i);
 to(i)=c.s;
 no+=j;
 c.no=0;
}
template<class T> void chain<T>::add(int i,chain<T> & c)
{c.to(c.no)=to(i);
 to(i)=c.s;
 no+=c.no;
 c.no=0;
}
template<class T> chain<T> chain<T>:: clone(int i,int j)
{chain<T> c(j);
 for(int n=0;n<j;n++)
  c[n]=(*this)[i+n];
 return c;
}
template<class T> void chain<T>:: operator=(chain<T>& c)
{out(0,no);
 s=c.s;
 no=c.no;
 c.no=0;
}
template<class T> void chain<T>:: swap(int i,int j)
{if(i>j){int q=i;i=j;j=q;}
 chain c;
 c=out(j,1);add(i+1,c);c.pop_s();
 c=out(i,1);add(j,c);
}
template<class T>  chain<T> :: ~chain()
{elem<T> **a=&s,**b;
 for(int n=0;n<no;n++)
 {b=&((*a)->p);
  delete *a;
  a=b;
 }
}
template<class T>  int chain<T>:: length(){return no;}
template<class T>  chain<T> chain<T>:: out_s(int i){return out(0,i);}
template<class T>  void chain<T>:: add_s(int i){add(0,i);}
template<class T>  chain<T> chain<T>:: out_l(int i){return out(no-i,i);}
template<class T>  void chain<T>:: add_l(int i){add(no,i);}
template<class T>  chain<T> chain<T>:: clone(){return clone(0,no);}
template<class T>  void chain<T>:: push_s(T &t){add_s(1);to(0)->e=t;}
template<class T>  void chain<T>:: push_l(T &t){add_l(1);to(no)->e=t;}
template<class T>  T& chain<T>:: pop_s(){T &t=to(0)->e;out_s(1);return t;}
template<class T>  T& chain<T>:: pop_l(){T &t=to(no)->e;out_l(1);return t;}

#endif










