#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <cstdarg>
#include <cassert>
#include <thread>
#include <map>
#include <typeinfo>
#include <cctype>
#include <cstring>
#include <numeric>
#include <bitset>
#include <valarray>
#include <cmath>
#include <iterator>
#include <set>
#include <unordered_map> //无序
#include <fstream>
#include <stack>
#include <queue>
#include <functional>
#include <span>
#include "semaphore.h"
#include "min.h"
#define MOVE std::move
#define PASS_BY_VALUE 1
#include "simple_string.h"
#include "pair.cpp"
#include "container.cpp"
#include "memblock.cpp"
#include "point.cpp"

using namespace std;

#define MIN(i,j) (((i)<(j)) ? (i):(j))
template<typename T>
T adder(T v)
{
    cout << "(" <<__PRETTY_FUNCTION__ <<")\n";
    return v;
}

template<typename T,typename ... Args>
T adder(T first,Args... args)
{
    cout << __PRETTY_FUNCTION__ <<"\n";
    return first + adder(args...);
}

template<typename T,typename ...>
T adder_(T cnt,...)
{
    T res = 0;
    va_list ptr;
    va_start(ptr,cnt);
    for(;cnt>0;cnt--)
        res += va_arg(ptr,T);
    va_end(ptr);
    return res;
//    cout << __PRETTY_FUNCTION__ <<"\n";
//    return first + adder(args...);
}

const long long factorial_20 = 2432902008176640000LL;

long long factorial(const long long val,const long long sum=1)
{
    if(val > 1)
        return factorial(val-1,sum*val);
    else
        return sum;
}

constexpr long long
cfactorial(const long long in,const long long sum=1)
{
    if(in>1)
    {
        return cfactorial(in-1,sum*in);
    } else
        return sum;
}

enum {compileTimeGeneratedValue = cfactorial(20)};
static_assert(compileTimeGeneratedValue == factorial_20,"error");

template<long long LLn,long long LSum = 1>
struct Factorial:Factorial<LLn -1,LLn *LSum>
{};

template <long long LSum>
struct Factorial<1,LSum>
{
    enum {value=LSum};
};

const long long fact = Factorial<20>::value;

static_assert(fact == factorial_20,"error");

static void play_pingpong(size_t max_iterations,const std::string &string_to_print,
                          semaphore &my_semaphore,semaphore &other_semphore);

static const int num_threads = 2;

static const size_t max_iterations = 4;

template <typename T,typename U>
ostream &operator<<(std::ostream &out,const pair<T,U>&p)
{
    out << "[" << p.first <<", "<<p.second <<"]";
    return out;
}

template<template<typename ,typename ...>class container,typename valueType,typename ...Args>
void print_container(ostream &os,const container<valueType,Args...>&objs)
{
    os << __PRETTY_FUNCTION__ << '\n';
    for(auto const &obj:objs)
        os << obj << ' ';
    os << '\n';
}

template<typename input_iterator>
void print_iterator(ostream &os,input_iterator start,input_iterator end)
{
    os << __PRETTY_FUNCTION__ << '\n';
    while (start != end)
        os << *start++<<' ';
    os << '\n';
}

template <typename T>
T add(T a,T b)
{
    return a+b;
}

template <typename R,typename T,typename U>
R max(T a,U b)
{
    return a>b? a:b;
}

template <typename T>
void f(T x,T y)
{
    cout << "Template" << endl;
}

void f(int w,int z)
{
    cout << "Non-template" <<endl;
}

template <> class container<char *>
{
public:
    explicit container(char *arg):element(arg){

    }
    char *uppercase();

private:
    char *element;
};

char * container<char *>::uppercase() {
    for (int i=0;element[i] != '\0';++i)
        if(islower(element[i]))
            element[i] = toupper(element[i]);
    return element;
}

class Foo
{
public:
    explicit Foo(int i):i_(i)
    {

    }

    Foo operator++()
    {
        cout << "Foo::operator++" << endl;
        return Foo(++i_);
    }

    explicit operator int () const {return i_;}

private:
    int i_;
};

ostream &operator<<(ostream &os ,const Foo &foo)
{
    return os << int(foo);
}

template<> class container<Foo>
{
public:
    explicit container(Foo arg):element(arg)
    {

    }

    Foo increase()
    {
        cout << "container<Foo>::increase()" << endl;
        return ++element;
    }

private:
    Foo element;
};

template<typename T>
struct class_A
{
    explicit class_A(T *p): p_(p)
    {
        cout << typeid(p).name() <<endl;
    }
    T *p_;

    void f(T *t) const
    {
        cout << typeid(t).name() << endl;
    }
};

struct class_B
{
    template<typename T>
    void mf(T *t)
    {
        cout << typeid(t).name() << endl;
    }
};

template <typename T>
struct class_C
{
    template<typename U>
    void mf(U u,T *t)
    {
        cout << typeid(u).name() << endl;
        cout << typeid(t).name() << endl;
    }

    void f(T *t)
    {
        cout << typeid(t).name() << endl;
    }
};

template <typename T,typename U>
struct example_class
{
    example_class()
    {
        std::cout << "example_class <T, U>\n";
    }
};

template <typename T>
struct example_class<T,T>
{
    example_class () { std::cout << "example_class<T, T>\n"; }
};

template <typename T>
struct example_class<T,int>
{
    example_class () { std::cout << "example_class<T, int>\n"; }
};

template <typename T, typename U>
struct example_class<T *,U *>
{
    example_class () { std::cout << "example_class<T*, U*>\n"; }
};

template <typename T, template<typename ...>class container = deque>
class stack
{
public:
    void push(const T &t)
    {
        s.push_back(t);
    }
    void pop()
    {
        s.pop_back();
    }
    T top()
    {
        return s.back();
    }

private:
    container<T> s;
};

template<typename T,int V>
T add_const_n(const T &n)
{
    return n+V;
}

template <typename T>
void print_data_type(const T &a)
{
    cout << typeid(a).name() << endl;
}

template <typename T>
struct example_class_
{
    example_class_() = default;
    T result(T t){return t;}
    void add(const T &t)
    {}
};

template void print_data_type<int>(const int &);
template void print_data_type<double>(const double &);

//template example_class_<int>::example_class_();
//
//template struct example_class_<double>;
//
//template example_class_<string>::example_class_();
//template void example_class_<string>::add(const string &);
//template string example_class_<string>::result(string);

template <typename T>
void print(const deque<T> &d)
{
    cout << "The number of items in the deque:" << d.size() << endl;

    for(typename deque<T>::const_iterator iter = d.cbegin();iter != d.cend();iter++)
    {
        cout << *iter << " ";
    }
    cout << endl << endl;
}

template<typename T, template<typename ...>class sequential_container = vector>
struct sequential_container_wrapper
{
    template<typename ... Args>
    explicit sequential_container_wrapper(Args &&...args):container_(forward<Args>(args)...)
    {
    }
    sequential_container<T> container_;
};

template<typename T, template<typename ...>class container>
ostream &operator<<(std::ostream &os,sequential_container_wrapper<T,container> vw)
{
    os << __PRETTY_FUNCTION__ << '\n';

    for(const auto &e:vw.container_)
        os << e << ' ';
    return os;
}

namespace my_copy{
        template<typename InputIterator,typename OutputIterator>
        OutputIterator copy(InputIterator first,InputIterator last,OutputIterator result)
        {
            for(;first!=last;++first,++result)
            {
                *result = *first;
            }
            return result;
        }
    }

static void print_const(const vector<int> &v)
{
    for(vector<int>::const_iterator it=v.cbegin();it!=v.cend();it++)
    {
        cout << *it <<' ';
    }
}

static void replace_builtin_array()
{
    int a[] = {10, 20, 10, 20, 10, 30, 40, 50, 60, 70};

    cout << "before replacing, a: ";
    for (auto i : a)
        cout << i << " ";
    cout << endl;

    replace(begin(a), end(a),10,40);

    cout << "after replacing, a: ";

    for (auto i : a)
        cout << i << " ";
    cout << endl;
}

static void replace_vector()
{
    vector<int> v{10, 20, 10, 20, 10, 30, 40, 50, 60, 70};

    cout << "before replacing, v: ";
    for (auto i : v)
        cout << i << " ";
    cout << endl;

    // replacing 10 with 42
    replace(v.begin(), v.end(), 10, 42);

    // printing vector elements
    cout << "after replacing, v: ";

    for (auto i : v)
        cout << i << " ";
    cout << endl;
}

void demonstrate_pointer_arithmetic()
{
    const char *a[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};

    copy(begin(a), end(a),ostream_iterator<const char *>(cout," "));
    cout << endl;

    auto p = begin(a);
    p+=5;

    p[1]="z";
//    *(p+1) = "z";
    p-=5;

    copy(begin(a), end(a),ostream_iterator<const char *>(cout," "));
    cout << endl;

}

void demonstrate_random_access_iterators()
{
    deque<string> v2 {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};

    copy(begin(v2), end(v2),ostream_iterator<string>(cout," "));
    cout << endl;

    auto p = begin(v2);
    p+=5;
    p[1] = "z";
    p-=5;
    copy(begin(v2), end(v2),ostream_iterator<string>(cout," "));
    cout << endl;
}

struct print_ {
    void operator()(const map<string, string>::value_type &p)
    {
        cout << p.first << "=" << p.second << endl;
    }
};

//typedef multimap<string,string> names_type;
//typedef names_type :: value_type value_type;
typedef multimap<simple_string,simple_string> names_type;
typedef names_type :: value_type value_type;
struct print__
{
    explicit print__(ostream &out):os(out){
    }
    void operator()(const names_type::value_type &p)
    {
        os << p.first << " belongs to the " << p.second << " family\n";
    }
    ostream &os;
};

ostream &operator<<(ostream &out,const names_type &l)
{
    for_each(l.begin(),l.end(), print__(out));
    return out;
}

ostream &operator<<(ostream &out,const pair<names_type::iterator,names_type::iterator> &p)
{
    for_each(p.first,p.second,print__(out));
    return out;
}

bool cmp(pair<string,int> const &a,pair<string,int> const &b)
{
    return a.second < b.second;
}

template <typename Container>
void insert_into_container(Container &c)
{
    cout << "Original contents of container:\n";
    copy(c.cbegin(),c.cend(),ostream_iterator<int>(cout," "));
    cout << endl;

    auto itr = c.begin();
    itr++;
    itr++;

    insert_iterator<Container> i_itr(c,itr);
    *i_itr++ = 100;
    *i_itr++ = 200;

    cout << "Container after insertion:\n";
    copy(c.cbegin(),
         c.cend(),
         ostream_iterator<int>(cout, " "));
    cout << endl;
}

void print_top(const std::stack<char> &s)
{
    cout << s.top() << endl;
}

void print_front(const queue<string> &q)
{
    cout << q.front() << endl;
}

struct place
{
    unsigned int dist;
    simple_string dest;

    friend ostream &operator<<(ostream &,const place &);

    place(simple_string dt,unsigned int ds):dist(ds),dest(std::move(dt))
    {

    }

    bool operator< (const place &right) const
    {
        return dist < right.dist;
    }

    bool operator> (const place &right) const
    {
        return dist > right.dist;
    }
};

ostream &operator << (ostream &os,const place &p)
{
    /* 因为 operator << 是 Box 的友元，它可以直接访问该类的任何成员 */
    return os << p.dest << " " << p.dist;
}

float Plus(float a,float b) {return a+b;}
float Minus(float a,float b) {return a-b;}
float multiply(float a,float b) {return a*b;}
float divide(float a,float b) {return a/b;}

float switchOpCode(float a,float b,char opCode)
{
    float result;
    switch(opCode)
    {
        case '+':
            result = Plus(a,b);
            break;
        case '-':
            result = Minus(a,b);
            break;
        case '*':
            result = multiply(a,b);
            break;
        case '/':
            result = divide(a,b);
            break;
    }
    return result;
}

float switchFuncPtr(float a,float b,float (*pt2Func)(float ,float ))
{
    return pt2Func(a,b);
}

class example_class__
{
public:
    explicit example_class__(int i=0):i_(i)
    {}

    float aFun(float a,char b,char c)
    {
        return i_+=a+b+c;
    }
    float bFun(float a,char b,char c)
    {
        return i_+=a-b+c;
    }
    float antherFun(float a,char b,char c)const
    {
        return i_ + a -b +c;
    }
    static float aStaticFun(float a,char b,char c)
    {
        return a+b+c;
    }
private:
    int i_;
};

void pass_ptf(float (*pt2Func)(float,char ,char ))
{
    float result = (*pt2Func)(12,'a','b');
    cout << result << endl;
}

static float aFun(float f,char a,char b)
{
    return f+a+b;
}

typedef float(*pt2Func)(float, float);

static pt2Func get_ptf(char opCode)
{
    if(opCode == '+')
        return &Plus;
    else if (opCode=='-')
        return &Minus;
    else
        return nullptr;
}

class simple_function_object{
public:
    int operator()(int i){return i;}
};

class is_even:public unary_function<int,bool>
{
public:
    bool operator()(int i)
    {
        return (result_type) !(i%2);
    }
};

template<typename InputIterator>
static void demonstrate_functors(InputIterator first,InputIterator last)
{
    vector<float> aVect;
    copy(first,last,ostream_iterator<float>(cout," "));
    cout << endl;

    transform(first,last,first, back_inserter(aVect),multiplies<>());
    copy(aVect.begin(),aVect.end(),ostream_iterator<float>(cout," "));
    cout << endl;

    transform(first,last,aVect.begin(),bind(divides<float>(),placeholders::_1,3.0));

    copy(aVect.begin(),aVect.end(),ostream_iterator<float>(cout," "));
    cout << endl;
}

template<typename InputIterator>
static void demonstrate_lambdas(InputIterator first,InputIterator last)
{
    vector<float> aVect;

    copy(first,last,ostream_iterator<float>(cout," "));
    cout << endl;

    transform(first,last,first, back_inserter(aVect),[](auto a,auto b){return a*b;});

    copy(aVect.begin(),aVect.end(),ostream_iterator<float>(cout," "));

    cout << endl;

    transform(first,last,aVect.begin(),[](auto a){return a/3.0;});

    copy (aVect.begin (),
          aVect.end (),
          ostream_iterator<float> (cout, " "));
    cout << endl;

}

template <typename T>
int test(T lambda)
{
    return lambda(2);
}

static void demonstrate_on_string()
{
    string s = "spaces in text";
    cout << s << endl;
    auto new_end = remove_if(begin(s), end(s),bind(equal_to<>(),placeholders::_1,' '));
    cout << s << endl;
    s.erase(new_end,s.end());
    cout << s << endl;
}

static void demonstrate_on_array()
{
    char s[] = "spaces in text";
    cout << s << endl;

//    auto new_end = remove_if(begin(s), end(s),bind(equal_to<>(),placeholders::_1,' '));
    auto new_end = remove_if(begin(s), end(s),[](char c){return c==' ';});
    cout << s << endl;
}

class is_more_than_two{
public:
    bool operator() (int val) {return val>2;}
    };

static void demonstrate_bind1st()
{
    int numbers[] = {10, 20, 40, 30, 50, 20, 10};

    auto n = count_if(begin(numbers),end(numbers), bind1st(equal_to<int>(),10));

    cout << "There are "
         << n
         << " elements that are equal to 10"
         << endl;

    n = count_if(begin(numbers), end(numbers),bind(equal_to<>(),placeholders::_1,10));
    cout << "There are "
         << n
         << " elements that are equal to 10"
         << endl;

    n = count_if(begin(numbers), end(numbers),[](auto i){return i==10;});
    cout << "There are "
         << n
         << " elements that are equal to 10"
         << endl;
}

static void demonstrate_bind2nd()
{
    int numbers[] = {10, 20, 40, 30, 50, 20, 10};

    auto n = count_if(begin(numbers), end(numbers), bind2nd(equal_to<int>(),20));

    cout << "There are "
         << n
         << " elements that are equal to 20"
         << endl;

    n = count_if(begin(numbers), end(numbers), bind(equal_to<int>(),placeholders::_1,20));

    cout << "There are "
         << n
         << " elements that are equal to 20"
         << endl;

    n = count_if (begin(numbers),
                  end(numbers),
                  [](auto i) { return i == 20; });

    cout << "There are "
         << n
         << " elements that are equal to 20"
         << endl;
}

static void contrast_bind1st_bind2nd_and_bind()
{
    auto p1 = bind1st(plus<int>(),10);
    auto p2 = bind2nd(plus<int>(),10);
    auto p3 = bind(plus<int>(),10,placeholders::_1);
    auto p4 = bind(plus<int>(),placeholders::_1,10);

    cout << p1(20) << endl;
    cout << p2(20) << endl;
    cout << p3(20) << endl;
    cout << p4(20) << endl;

    auto m1 = bind1st(minus<int>(),10);
    auto m2 = bind2nd(minus<int>(),10);
    auto m3 = bind(minus<int>(),10,placeholders::_1);
    auto m4 = bind(minus<int>(),placeholders::_1,10);

    cout << m1(20) << endl;
    cout << m2(20) << endl;
    cout << m3(20) << endl;
    cout << m4(20) << endl;

}

template<typename T>
struct is_odd:unary_function<T,bool>
{
    bool operator()(T number)const
    {
        return number % 2!=0;
    }
};

template<typename T, template<typename ...>class sequential_container>
static void print_results(const sequential_container<T> &container)
{
    copy(container.begin(),container.end(),ostream_iterator<T>(cout," "));
    cout << endl;
}

template<typename InputIterator>
static void print_results_(InputIterator first,InputIterator last)
{
    if(first!=last)
    {
        copy(first,last,ostream_iterator<decltype(*first)>(cout," "));
        cout << endl;
    }
}

struct IntGreaterThanThree : public unary_function<int,bool>
{
    bool operator()(int x) const {return x>3;}
};

class WrapInt
{
public:
    WrapInt():val(0){}

    explicit WrapInt(int x):val (x){}
    void showval()const
    {
        cout << val << ' ';
    }
    [[nodiscard]] bool isPrime() const
    {
        for(int i=2;i<=(val/2);i++)
            if(!(val % i))
                return false;
        return true;
    }
    [[nodiscard]] bool isEven() const
    {
        return !(val%2);
    }
    [[nodiscard]] bool isOdd() const
    {
        return val % 2;
    }
private:
    int val;
};

bool isGreatThanTen(int i)
{
    return i>10;
}

class example__class
{
public:
    explicit example__class(int y):x(y){}

    bool firstFunc(int i) const
    {
        return i>x;
    }

private:
    int x;
};

template <typename InputIterator>
static void _print(InputIterator first,InputIterator last,const string &s)
{
    if (first != last)
    {
        cout << s;
        copy(first,last,ostream_iterator<decltype(*first)>(cout," "));
        cout << endl;
    }
}

template<typename T>
class is_greater_than
{
public:
    explicit is_greater_than(const T &n):value(n){}

    bool operator()(const T &element) const
    {
        return element>value;
    }
private:
    const T &value;
};

static void find_with_deque()
{
    deque<int> values {10, 20, -30, 40, -50, 60, 20, -40};

    auto value = 20;

    auto itr1 = find_if(values.begin(),values.end(),is_greater_than<int>(value));

    if(itr1!=values.end())
        cout << *itr1 << " is the first value greater than " << value << endl;

    value = 40;

    itr1 = find_if_not(values.begin(),values.end(),[value](auto i){return i>=value;});

    if(itr1!=values.end())
        cout << *itr1 << " is not greater than or equal to " << value << endl;
    auto itr2 = find_if(values.rbegin(),values.rend(), bind(greater<>(),placeholders::_1,value));

    if (itr2 != values.rend())
        cout << *itr2 << " is the last value greater than " << value << endl;
}



int main(int argc,char *argv[]) {

#if 0
    auto sum = adder_(5,1,2,3,4,5);
    cout << "sum = " <<sum <<endl;

    sum = adder(1,2,3,4,5);
    cout << "sum = " <<sum <<endl;

    string s1 = "C++",s2 = " ",s3 = "is",s4 = " ",s5="cool!";
    auto string_sum = adder(s1,s2,s3,s4,s5);
    cout << "string_sum = " << string_sum << endl;
#endif

#if 0
    assert(factorial(20)==factorial_20);

    cout << "factorial(20) = " << factorial_20;
#endif

#if 0
    thread threads[num_threads];
    cout << "Ready...Set...Go!" << endl;

    semaphore ping_semaphore(1);
    semaphore pong_semaphore(0);

    threads[0] = thread(play_pingpong,max_iterations,"Ping!",ref(ping_semaphore),
                        ref(pong_semaphore));
    threads[1] = thread(play_pingpong,max_iterations,"Pong!",ref(pong_semaphore),
                        ref(ping_semaphore));

    for (auto &t:threads)
        t.join();
    std::cout << "Done!" << std::endl;

#endif

#if 0
    vector<float> vf{1.1,2.2,3.3,4.4};
    print_iterator(cout,vf.begin(),vf.end());
    print_container(cout,vf);

    list<char> lc {'a','b','c','d'};
    print_iterator(cout,lc.begin(),lc.end());
    print_container(cout,lc);

    deque<int> id {1,2,3,4};
    print_iterator(cout,id.begin(),id.end());
    print_container(cout,id);

    map<string,int> msi {{"larry",100},{"curly", 90}, {"moe", 110}};
    print_iterator(cout,msi.begin(),msi.end());
    print_container(cout,msi);
#endif

#if 0
    cout << add(56,7) << endl;
    cout << add<long>(4545L,34235L)<<endl;
#endif

#if 0
    auto d = max<double>(5.5,4);
    int i = max<int,char,char>('a','b');

    cout << d << endl;
    cout << i << endl;
#endif

#if 0
    f(1,2);
    f('a','b');
    f(1,'a');
#endif

#if 0
    int a[] = {1,2,3};
    decltype(*a) b = a[0];
    a[0] = 4;
    cout << b; //输出4
#endif

#if 0
    int a[] = {1,2,3};
    remove_reference<decltype(*a)>::type b = a[0]; //remove_reference移除引用
    a[0] = 4;
    cout << b; //输出1
#endif

#if 0
    auto e = min_ex(10,11.3);
    cout << "Minimum of " << typeid(e).name() << ':' << e << endl;

    auto i =  min(3,6,4);
    cout << "Minimum int 3 Parameters: " << i  << std::endl;
#endif

#if 0
    string str = "hello";
    string s = MOVE(str);
    cout << "s:" << s << " str:" << str << endl;
#endif

#if 0
    {
        simple_string s1("hello");
        simple_string s2("world");

        cout << "the max of " << s1 << " and " << s2 << " = ";
        my_pair::pair<simple_string> string_pair(MOVE(s1),MOVE(s2));

        cout << string_pair.max() << endl;

    }
#endif

#if 0
    {
        double d1 = 100.4;
        double d2 = 200.8;

        my_pair::pair<double> d_pair(d1,d2);

        cout << "the max of "
             << d1 << " and "
             << d2 << " = "
             << d_pair.max()
             << endl;
    }
#endif

#if 0
    container<int> myint(7);
    cout << myint.increase() << endl;

    long l;
    class_A<long> a(&l);
    a.f(&l);

    int i;
    double d;
    class_B b;
    b.mf(&i);
    b.mf(&d);

    class_C<int> c;
    class_C<double> cc;

    c.mf(10,&i);
    cc.mf(20.4,&d);
    c.f(&i);
    cc.f(&d);
#endif

#if 0
    container<int> my_int(7);
    container<double> my_double(10.5);

    char lowercase[] = "hello world";
    container<char *> my_charstring(lowercase);

    cout << my_int.increase() << endl;
    cout << my_double.increase() << endl;
    cout << my_charstring.uppercase() << endl;

    container<Foo> my_foo (Foo(10));
    cout << my_foo.increase() << endl;
#endif

#if 0
    example_class<int,double> a;
    example_class<double,double> b;
    example_class<double,int> c;
    example_class<int *,double *> d;
#endif

#if 0
    memblock<int,5> my_ints;
    memblock<double,15> my_floats;

    my_ints.setmem(0,100);
    my_floats.setmem(3,3.23);

    cout << my_ints.getmem(0) << endl;
    cout << my_floats.getmem(3) << endl;

    auto i = add_const_n<int,6>(10);
    cout << "i= "<< i << endl;
#endif

#if 0
    stack<string> a_deque_stack_of_strings;
    stack<int,list> a_list_stack_of_ints;

    a_deque_stack_of_strings.push("hello");
    string s = a_deque_stack_of_strings.top();
    cout << s << endl;
    a_deque_stack_of_strings.pop();

    a_list_stack_of_ints.push(42);
    int i = a_list_stack_of_ints.top();
    cout << i << endl;
    a_list_stack_of_ints.pop();
#endif

#if 0
    int a = 10,b = 20;

    cout<< "min = " << std::min(a++,b++) << endl;
    cout<< "MIN = "<<MIN(a++,b++) <<endl;

    std::cout << "a = " << a << " b = " << b << std::endl;
#endif

#if 0
    example_class_<int> ai;
    example_class_<double> ad;

    print_data_type(ai);
    print_data_type(ad);
#endif

#if 0
    int a[3];
    a[0] = 7;
    a[1] = a[0]+3;
    a[2] = a[0] + a[1];

    for (int i = 0; i < (sizeof(a)/sizeof(a[0])); ++i) {
        cout << a[i] << ' ';
    }
    cout << endl;

    vector<int> v(3);
    v[0] = 7;
    v[1] = v[0] + 3;
    v[2] = v[0] + v[1];

    for(int i=0;i<v.size();++i)
        cout << v[i] << ' ';
    cout << endl;

    v.resize(0);

    for(int i=0;i<7;++i)
        v.push_back(i);

    for(auto i:v)
        cout << i << ' ';
    cout << endl;

#endif

#if 0
    vector<double> aVector;

    aVector.push_back(1.2);
    aVector.push_back(4.5);

    aVector[1] = aVector[0] + 5.0;
    aVector[0] = 2.7;

    for(auto d:aVector)
        cout << d <<endl;
    cout << endl;
#endif

#if 0
    int ar[] = {12, 45, 234, 64, 12, 35, 63, 23, 12, 55};
    vector<int> vec1(begin(ar), end(ar));
    vector<int> vec2 {12, 45, 234, 64, 12, 35, 63, 23, 12, 55};

    for(auto i:vec1)
        cout << i << ' ';
    cout << endl;

    const char *str = "Hello World";
    vector<char> vec3(str,str+strlen(str));
    vector<char> vec4{'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd'};

    for (auto c : vec3)
        cout << c;

    cout << endl;
#endif

#if 0
    vector<vector<int>> myVec2D;
    vector<int> oneVec,twoVec;

    oneVec.push_back(1),oneVec.push_back(2),oneVec.push_back(3);
    twoVec.push_back(4),twoVec.push_back(5),twoVec.push_back(6);

    myVec2D.push_back(oneVec);
    myVec2D.push_back(twoVec);

    cout << endl << "Using Iterator:" << endl;

    for(vector<vector<int>>::iterator iter2D=myVec2D.begin();iter2D!=myVec2D.end();iter2D++)
    {
        for (vector<int>::iterator iter = iter2D->begin();iter != iter2D->end();iter++)
        {
            cout << *iter << endl;
        }
    }

    cout << endl << "Using subscript operators:" << endl;
    for (size_t i=0;i<myVec2D.size();i++)
    {
        for(size_t j=0;j<myVec2D[i].size();j++)
        {
            cout << myVec2D[i][j] << endl;
        }
    }

    cout << endl << "Using range-based for loop:" << endl;

    for(const auto &inner_vec:myVec2D)
    {
        for(auto i:inner_vec)
            cout << i <<endl;
    }
#endif

#if 0
    vector<int> aVector {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    auto total = 0;
    for(auto anIterator = aVector.begin();anIterator != aVector.end();++anIterator)
    {
        total += *anIterator;
    }

    cout << "Total = " << total << endl;
    total = 0;

    for(int anIterator : aVector)
    {
        total += anIterator;
    }

    cout << "Total = " << total << endl;

    cout << "Total = " << accumulate(aVector.begin(), aVector.end(), 0) << endl;
#endif

#if 0
    deque<float> myDeck;

    for(size_t i=0;i<7;i++)
    {
        myDeck.push_front(i*1.1);
        myDeck.push_back(i*1.1);
    }

    for(auto f:myDeck)
        cout << f << ' ';
    cout << endl;
#endif

#if 0
    deque<char> aDeck;

    for(size_t i=0;i<5;i++)
        aDeck.push_back(i+'A');

    cout << "Original sequence: ";
    for (char c: aDeck)
        cout << c <<' ';
    cout << endl;

    deque<char>::iterator it1 = aDeck.begin()+2;
    auto it2 = aDeck.begin() + 3;

    cout << "*it1: "<< *it1 << endl;
    cout << "*it2: "<< *it2 << endl;

    aDeck.insert(it1,'X');
    cout << "Sequence after insert: ";
    for(auto c : aDeck)
        cout << c << " ";
    cout << endl;

    cout << "*it1: "<< *it1 << endl;
    cout << "*it2: "<< *it2 << endl;
#endif

#if 0
    deque<int> aDeck;
    aDeck.push_back(3);
    aDeck.push_front(1);

    aDeck.insert(aDeck.begin()+1,2);
    aDeck[2] = 0;

    print(aDeck);
#endif

#if 0
    deque<char> myFirstDeck,mySecondDeck;

    for(size_t i=0;i<26;i++)
        myFirstDeck.push_back(i+'A');
    for(size_t i=0;i<10;i++)
        mySecondDeck.push_front(i+'0');

    cout << "Size of myFirstDeck and mySecondDeck: ";
    cout << myFirstDeck.size() << " " << mySecondDeck.size() << endl;
    cout << "myFirstDeck: ";

    for(auto i:myFirstDeck)
        cout << i;
    cout << endl << "mySecondDeck: ";
    for(auto i : mySecondDeck)
        cout << i;
    cout << "\n\n";

    myFirstDeck.swap(mySecondDeck);

    cout << "Size of myFirstDeck and mySecondDeck after first swap: ";
    cout << myFirstDeck.size() << " " << mySecondDeck.size() << endl;

    cout << "myFirstDeck after first swap: ";
    for(auto c : myFirstDeck)
        cout << c;
    cout << endl;

    cout << "mySecondDeck after first swap: ";

    for(char i : mySecondDeck)
        cout << i;
    cout << "\n\n";

    swap(myFirstDeck, mySecondDeck);
    deque<char> myFirstDeck,mySecondDeck;

    for(size_t i=0;i<26;i++)
        myFirstDeck.push_back(i+'A');
    for(size_t i=0;i<10;i++)
        mySecondDeck.push_front(i+'0');

    cout << "Size of myFirstDeck and mySecondDeck: ";
    cout << myFirstDeck.size() << " " << mySecondDeck.size() << endl;
    cout << "myFirstDeck: ";

    for(auto i:myFirstDeck)
        cout << i;
    cout << endl << "mySecondDeck: ";
    for(auto i : mySecondDeck)
        cout << i;
    cout << "\n\n";

    myFirstDeck.swap(mySecondDeck);

    cout << "Size of myFirstDeck and mySecondDeck after first swap: ";
    cout << myFirstDeck.size() << " " << mySecondDeck.size() << endl;

    cout << "myFirstDeck after first swap: ";
    for(auto c : myFirstDeck)
        cout << c;
    cout << endl;

    cout << "mySecondDeck after first swap: ";

    for(char i : mySecondDeck)
        cout << i;
    cout << "\n\n";

    swap(myFirstDeck, mySecondDeck);

#endif

#if 0
    list<char> list1;
    list<char> list2;

    for (int i=0;i<10;i++)
    {
        list1.push_back('A'+i);
    }
    for(int i=0;i<10;i++)
        list2.push_front('0'+i);

    cout << "list1 size = " << list1.size() << endl;
    cout << "list2 size = " << list2.size() << endl;
    cout << "Contents: ";

    while (!list1.empty())
    {
        auto p = list1.begin();
        cout << *p;
        list1.pop_front();
    }
    cout << endl;
    while (!list2.empty())
    {
        auto p = list2.end();
        cout << *--p;
        list2.pop_back();
    }
#endif

#if 0
    list<int> my_list;

    my_list.push_back(0);
    my_list.push_front(0);

    my_list.insert(++my_list.begin(),2);
    my_list.insert(--my_list.end(),42);

    my_list.push_back(5);
    my_list.push_back(6);

    for(auto i:my_list)
        cout << i << ' ';
    cout << endl;
#endif

#if 0
    string my_letters = "abcdefghijklmnopqrstuvwxyz";

    auto i = 0;

    for(auto my_letter:my_letters)
        cout << ++i << ' ' << my_letter << endl;

    for(auto i=my_letters.cbegin();i!=my_letters.cend();i++)
    {
        cout << *i << ' ' << endl;
    }
#endif

#if 0
    const char *ptr = "say goodnight, Gracie";

    string str1(ptr);

    string str2("say goodnight, Gracie");
    string str3(str2);

    string str4(str3,4,9);
    string str5 = str3.substr(4,9);

    string::size_type pos = str2.find("Gracie",0);

    if(pos != string::npos)
    {
        str2.erase(pos,6);
        str2.insert(pos,"Irene");
        cout << str2 << endl;
    }
    str2.erase(0,2);
    cout << str2 << endl;

    str3 = str2+ ' '+str4;
    cout << str3 << endl;

    string match = "Ie";
    pos = str2.find_first_of(match,0);
    cout << "Found character " << str2[pos] << " at position " << pos << endl;
#endif

#if 0
    string a("abcd efg");
    string b = "xyz ijk";
    string c;
    cout << a << ' ' << b << endl;
    cout << "String empty: "  << c.empty()    << endl;

    c = a+b;
    cout << c << endl;
    cout << "String length: "   << c.length()<<endl;
    cout << "String size: "     << c.size()     << endl;
    cout << "String capacity: " << c.capacity() << endl;
    cout << "String empty: "    << c.empty()    << endl;

    string d = c;
    cout << d << endl;
    cout << "First character: " << c[0] << endl;

    string f("    Leading and trailing blanks      ");

    cout << "String f:" <<f.append("ZZZ") << endl;
    cout << "String length: " << f.length() << endl;
    string g("abc abc abd abc");
    cout << "String g: " << g << endl;

    cout<<"Replace 12,1,\"xyz\",3: "<<g.replace(12,0,"xyz",3)<<endl;
    cout << g.replace(0,3,"xyz",3) << endl;
    cout << g.replace(4,3,"xyz",3) << endl;
    cout << g.replace(4,3,"ijk",1) << endl;
    string ::size_type pos;
    pos = g.find("abd");
    cout << g.replace(pos,3,"xjz",3)<<endl;

    cout << "Find: " << g.find("xjz",1) << endl;
    cout << (g.find("qes",1)==string::npos) << endl;

    string h("abc abc abd abc");
    cout << "Find_first_not_of \"abc\",0: " << h.find_first_not_of("abc",0)<<endl;
    cout << "Find_first_not_of \" \": "
         << h.find_first_not_of(" ") << endl;
#endif

#if 0
    bitset<16> aFewBits(32);
    cout << "Bits:" << aFewBits << endl;

    aFewBits[0] = true,aFewBits[5]= false;
    aFewBits[10] = true,aFewBits[12] = true;
    cout << "Bits:" << aFewBits << endl;

    aFewBits <<= 2;
    cout << "Bits rotate: "
         << aFewBits   << endl;
    aFewBits.flip();
    cout << "After flipping bits: "
         << aFewBits  << endl;

    if(aFewBits.any())
        cout << "aFewBits has at least 1 bit set.\n";
    cout << "aFewBits has " << aFewBits.count() <<" bits set.\n";

    if(aFewBits[0]==1)
        cout << "bit 1 is on\n";
    if(aFewBits.test(1))
        cout << "bit 1 is on\n";

    cout << "Add 11 to bit 0: " << aFewBits[0]+11 << endl;
#endif

#if 0
    valarray<int> aValuesArray(10);
    int i;

    for(i=0;i<10;i++)
        aValuesArray[i] = i;
    cout << "Original contents: ";
    for(i = 0; i < 10; i++)
        cout << aValuesArray[i] << " ";
    cout << endl;

    aValuesArray = aValuesArray.cshift(3);
    cout << "Shifted contents: ";
    for(i = 0; i < 10; i++)
        cout << aValuesArray[i] << " ";
    cout << endl;

    valarray<bool> aValuesArray2 = aValuesArray < 5;
    cout << "Those elements less than 5: ";
    for(i = 0; i < 10; i++)
        cout << aValuesArray2[i] << " ";
    cout  << endl;

    valarray<double> aValuesArray3(5);
    for(i=0;i<5;i++)
        aValuesArray3[i] = (double) i;
    cout << "Original contents: ";
    for(i = 0; i < 5; i++)
        cout << aValuesArray3[i] << " ";
    cout << endl;

    aValuesArray3 = sqrt(aValuesArray3);
    for(i = 0; i < 5; i++)
        cout << aValuesArray3[i] << " ";
    cout << endl;

    aValuesArray3 = pow(aValuesArray3,2);
    for(i = 0; i < 5; i++)
        cout << aValuesArray3[i] << " ";
    cout << endl;

    aValuesArray3 = aValuesArray3+aValuesArray3;
    cout << "Double the square roots: ";
    for(i = 0; i < 5; i++)
        cout << aValuesArray3[i] << " ";
    cout << endl;

    aValuesArray3 = aValuesArray3 - 10.0;
    cout << "After subtracting 10 from each element:\n";
    for(i = 0; i < 5; i++)
        cout << aValuesArray3[i] << " ";
    cout << endl;
#endif

#if 0
    string A("abc");
    string && Rval = std::move(A);
    string B(Rval);
    cout << A << endl;
    string C(forward<string>(Rval));
    cout << A << endl;
#endif

#if 0
    const char *shapes[] = { "Circle", "Triangle", "Square", "Rectangle"};

    sequential_container_wrapper<string> b1(3,"words");
    sequential_container_wrapper<const char *,deque> b2(begin(shapes), end(shapes));
    sequential_container_wrapper<string> b3(begin(shapes), end(shapes));

    cout << b1 << endl;
    cout << b2 << endl;
    cout << b3 <<endl;
#endif

#if 0
    int a1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const int a1_size = sizeof(a1)/ sizeof(a1[0]);
    int a2[a1_size];

    my_copy::copy(begin(a1), end(a1),a2);

    for(auto i:a2)
        cout << i << ' ';
    cout << endl;

    vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> v2(v1.size());
//    copy(v1.begin(),v1.end(),v2.begin());

    my_copy::copy(v1.begin(),v1.end(),v2.begin());

    for (auto i : v2)
        cout << i << ' ';

    cout << endl;
#endif

#if 0
    vector<int> v{1, 2, 3, 4, 5, 4, 3, 2, 1};

    for(vector<int>::iterator it = v.begin();it!=v.end();it++)
    {
        cout << *it << ' ';
        *it -= 1;
    }

    cout << endl;
    sort(v.begin(),v.end());
    print_const(v);

    cout << endl;
    vector<string> sv{"hello", "world"};

    for(vector<string>::const_iterator itr = sv.cbegin();itr != sv.cend();itr++)
    {
        cout << "(" << itr->size()<<") "<< *itr<<' ';
    }
    cout << endl;

    for(auto &str:sv)
    {
        cout << "(" << str.size() << ") " << str << ' ';
    }
#endif

#if 0
    list<double> dList{10.1, 20.2, 30.3, 40.4, 50.5};

    for(auto d:dList)
        cout << d<<' ';
    cout << endl;

    list<double>::iterator dListIter = dList.begin();
    *dListIter = 100.1;
    for (auto d : dList)
        cout << d << ' ';
    cout << endl;

    list<double>::const_iterator dListConstIter = dList.cbegin();
    list<double>::value_type d = *dListConstIter;
#endif

#if 0
    vector<string> arguments;

    for(int i=1;i<argc;i++)
        arguments.emplace_back(string(argv[i])); //emplace_back 比push_back 高效
    for(vector<string>::iterator j = arguments.begin();j!=arguments.end();j++)
        cout << *j <<endl;
#endif

#if 0
    vector<int> v;
    copy(istream_iterator<int>(cin),istream_iterator<int>(), back_inserter(v));
    for(auto i:v)
        cout << i << endl;
#endif

#if 0
    vector<int> v;

    copy (istream_iterator<int>(cin),
          istream_iterator<int>(),
          back_inserter(v));

    copy(v.cbegin(),v.cend(),ostream_iterator<int>(cout,"\n"));
#endif

#if 0
    replace_builtin_array();
    replace_vector();
#endif

#if 0
    list<int> aList(1,1);
    aList.push_back(2);
    aList.push_front(0);

    list<int>:: iterator first = aList.begin();

    auto last = aList.end();

    while (last--!=first)
        cout << *last << ' ';
#endif

#if 0
    list<simple_string> aList;
    cout << "starting emplace_back() calls" << endl;

    aList.emplace_back("peach");
    aList.emplace_back("apple");
    aList.emplace_back("bananas");

    cout << "starting push_back() calls" << endl;
    aList.push_back("peach");
    aList.push_back("apple");
    aList.push_back("bananas");
    cout << "ending push_back() calls" << endl;

    list<simple_string> blist(aList.size());


    reverse_copy(aList.begin(),aList.end(),blist.begin());

    copy(blist.begin(),blist.end(),ostream_iterator<simple_string>(cout," "));
    cout << endl;

    copy(blist.rbegin(),blist.rend(),ostream_iterator<simple_string>(cout," "));
    cout << endl;
#endif

#if 0
    demonstrate_pointer_arithmetic();
    demonstrate_random_access_iterators();
#endif

#if 0
    point<int,int> my_point(100,200);
    cout << "my_point.x: "
         << my_point.x
         << "\nmy_point.y: "
         << my_point.y
         << endl;

    point<string,string> book_chapter_1("Chapter1",
                                        "Meet the C++ STL");
    cout << "book_chapter_1.x: "
         << book_chapter_1.x
         << "\nbook_chapter_1.y: "
         << book_chapter_1.y
         << endl;

    point<string ,void *> debug("mynum",reinterpret_cast<void *>(0x410928a8));

    cout << "debug.x: "
         << debug.x
         << "\ndebug.y: "
         << debug.y
         << endl;

    int num  = 0x00636261;
    int *pnum = &num;
    char *pstr = reinterpret_cast<char*>(pnum); //重新解释
    cout << pstr << endl;
    cout << hex << *pnum << endl;
    cout << static_cast<void *>(pstr) << endl;
    cout << pnum << endl;

    point<simple_string,simple_string> book_chapter_2(
            MOVE(simple_string("Chapter2")),

            MOVE(simple_string("Meet the C++ STL associative containers")));

    cout << "book_chapter_2.x: "
         << (const char *) book_chapter_2.x
         << "\nbook_chapter_2.y: "
         << (const char *) book_chapter_2.y
         << endl;
#endif

#if 0
    set<int,greater<>> set_of_ints({2, 1, 3, 0, 7});

    cout << set_of_ints.size() << " elements in the set" << endl;

    auto iter = set_of_ints.find(9);

    if(iter==set_of_ints.end())
        cout << "9 not found\n";
    else
        cout << "9 found\n";
    set_of_ints.insert(9);

    cout << set_of_ints.size() << " elements in the set" << endl;

//    iter = find(set_of_ints.begin(),set_of_ints.end(),9);
    iter = set_of_ints.find(9);
    if(iter==set_of_ints.end())
        cout << "9 not found in the set\n"  << endl;
    else
        cout << "9 found it! \n" << endl;

    copy(set_of_ints.begin(),set_of_ints.end(),ostream_iterator<int>(cout," "));
#endif

#if 0
    set<int> myset;
    for(int i=1;i<=5;i++)
        myset.insert(i*10);

    auto ret = myset.insert(20);

    if(!ret.second)
    {
        auto it = ret.first;

        myset.insert(it,25);
        myset.insert(it, 24);
        myset.insert(it, 26);
        myset.insert({5, 10, 15});

        cout << "myset contains:" << endl;
        for(auto i:myset)
            cout << i << ' ';
        cout << endl;
    }
#endif

#if 0
    set<int> firstSet {5, 4, 6, 7, 8, 2, 1, 3};

    const set<int> &secondSet = firstSet;

    list<int> aList(secondSet.begin(),secondSet.end());

    set<int,greater<>> thirdSet(aList.begin(),aList.end());

    set<int> fourthSet;
    fourthSet.swap(firstSet);

    assert(firstSet.empty());

    copy(thirdSet.begin(),thirdSet.end(),ostream_iterator<int>(cout," "));
    cout << endl;

    copy (fourthSet.begin (),
          fourthSet.end (),
          ostream_iterator<int> (cout, " "));
    cout << endl;
#endif

#if 0
    set<int> firstSet;

    firstSet.insert(55);

    if(firstSet.insert(55).second)
        cout << "element was inserted" << endl;
    else
        cout << "element was not reinserted " << endl;
#endif

#if 0
    set<int> firstSet {5, 4, 6, 7, 8, 2, 1, 3};

    copy(firstSet.begin(),firstSet.end(),ostream_iterator<int>(cout," "));

    cout << endl;

    firstSet.erase(4);
    copy(firstSet.begin(),firstSet.end(),ostream_iterator<int>(cout," "));

    cout << endl;

    auto five = firstSet.find(5);
    firstSet.erase(five);

    reverse_copy(firstSet.begin (),
                 firstSet.end (),
                 ostream_iterator<int> (cout, " "));
    cout << endl;

    auto six = firstSet.find(6);
    auto eight = firstSet.find(8);
    firstSet.erase(six,eight);

    copy (firstSet.rbegin (),
          firstSet.rend (),
          ostream_iterator<int> (cout, " "));

    cout << endl;
#endif

#if 0
    multiset<int> a {4, 1, 1, 1, 1, 1, 0, 5, 1, 0};
    multiset<int> b {4, 4, 2, 4, 2, 4, 0, 1, 5, 5};
    multiset<int> c;

    cout << "Set a: ";
    copy(a.begin(),
         a.end(),
         ostream_iterator<int>(cout, " "));
    cout << endl;

    cout << "Set b: ";
    copy(b.begin(),
         b.end(),
         ostream_iterator<int>(cout, " "));
    cout << endl;

    cout << "Union: ";
    set_union(a.begin(),a.end(),b.begin(),b.end(),ostream_iterator<int>(cout, " "));
    cout << endl;

    cout << "Intersection: ";
    set_intersection(a.begin(),a.end(),b.begin(),b.end(),ostream_iterator<int>(cout," "));
    cout << endl;

    set_difference(a.begin(),a.end(),b.begin(),b.end(), inserter(c,c.end()));

    cout << "Set c (difference of set a and set b): ";

    copy(c.cbegin(),
         c.cend(),
         ostream_iterator<int>(cout, " "));
    cout << endl;
#endif

#if 0
    set<string> str{"set","bset","cset"};
    set<string> str2{"set","set2","set3"};

    copy(str.begin(),str.end(),ostream_iterator<string>(cout," "));
    cout << endl;

    set_union(str.begin(),str.end(),str2.begin(),str2.end(), inserter(str,str.end()));

    copy(str.begin(),str.end(),ostream_iterator<string>(cout," "));
    cout << endl;
#endif

#if 0
    vector<string> word_list {
            "now", "is", "the", "time",
            "for", "all", "good", "people",
            "to", "come", "to", "the",
            "aid", "of", "their", "party"
    };

    typedef map<string,int> WORD_MAP;
    WORD_MAP word_map;

    for(auto const &word:word_list)
        ++word_map[word];

    for(pair<string,int> i:word_map)
        cout << i.second << " " << i.first << endl;
//    for (auto const &i : word_map)
//        std::cout << i.second << " " << i.first << std::endl;

    class total_it
    {
    public:
        explicit total_it(int i):i_(i){

        }
        void operator()(const WORD_MAP::value_type &p)
        {
            i_ += p.second;
        }
        int count() const {return i_;}
    private:
        int i_;
    };

    auto total = 0;

    total_it it = for_each(word_map.begin(),word_map.end(),total_it(total));

    total = it.count();

    cout << "total number of words = " << total <<endl;


    total = 0;

    for_each(word_map.begin(),word_map.end(),[&total](const WORD_MAP::value_type &p){total+=p.second;});
    cout << "total number of words = " << total <<endl;
#endif

#if 0
    pair<string,int> pr("heaven",7);
    cout << pr.first << "=" << pr.second << endl;

    unique_ptr<pair<string,int>> prp(new pair<string,int>("yards",9));

    cout << prp->first << "=" << prp->second << endl;

//    unique_ptr<int> pInt(new int(5));
//    unique_ptr<int> pInt2 = move(pInt);
////    只能移动unique_ptr
////    unique_ptr<int> pInt2(pInt);    // 报错
////    unique_ptr<int> pInt3 = pInt;   // 报错
//    //cout << *pInt << endl; // 出错，pInt为空
//    cout << *pInt2 << endl;

    map<string,string> engGerDict;
    engGerDict["shoe"] = "Schuh";
    engGerDict["head"] = "Kopf";

    map<string,string>::value_type vt("yes","ja");
    engGerDict.insert(vt);

    for_each(engGerDict.begin(),engGerDict.end(),print_());

    auto iter = engGerDict.find("yes");
    if(iter!=engGerDict.end())
        engGerDict.erase(iter);


    for_each(engGerDict.begin(),engGerDict.end(),[](const map<string,string>::value_type &p)
    {
        cout << p.first << "=" << p.second << endl;
    });
#endif

#if 0
    names_type names;

    names.insert(value_type("Kim","Smith"));
    names.insert(value_type("Jane", "Smith"));
    names.insert({"Kay", "Smith"});

    names.insert(names.end(),value_type("Kurt", "Jones"));
    names.insert(names.end(),value_type("Mike", "Jones"));
    names.insert(names.end(),value_type("Kim", "Jones"));

    names.insert({value_type ("Sophie", "Mackay"),value_type("Steve", "Mackay"),
                  value_type("Kim", "Mackay") });

    cout << "All the names:" << endl << names << endl;

    pair<names_type::iterator,names_type::iterator> p = names.equal_range("Kim");

    cout << names.count("Kim") << " People called Kim:" << endl << p << endl;

    names.erase(p.first,p.second);

    cout << "All the names:" << endl << names << endl;

    auto iter = names.find("Kurt");

    if(iter==names.end())
        cout << "Kurt not found" << endl;
    else
        cout << "Kurt's last name is " << iter->second << endl;

//    vector<int> v{1,2,3,4,5,6,6};
//    pair<vector<int>::iterator,vector<int>::iterator> result;
//    int new_val = 6;
//    result = equal_range(v.begin(),v.end(),new_val);
//    cout << *result.first << *result.second << endl;
#endif

#if 0
    names_type names;

    cout << "starting insert(&&)" << endl;
    names.insert(value_type("Kim", "Smith"));
    names.insert(value_type("Jane", "Smith"));
    names.insert(value_type("Kay", "Smith"));
    cout << "ending insert(&&)" << endl;

    cout << "starting emplace()" << endl;
    names.emplace("Kurt", "Jones");
    names.emplace("Kim", "Jones");
    names.emplace("John", "Jones");
    cout << "ending emplace()" << endl;

    cout << "starting emplace_hint()" << endl;
    auto iter = names.end();
    names.emplace_hint(iter,"Sophie", "Mackay");
    names.emplace_hint(iter,"Steve", "Mackay");
    names.emplace_hint(iter, "Kim", "Mackay");
    cout << "ending emplace_hint()" << endl;

    cout << "All the names:" << endl << names << endl;
#endif

#if 0
    vector<string> word_list {"now", "is", "the", "time",
                              "for", "all", "good", "people",
                              "to", "come", "to", "the",
                              "aid", "of", "their", "party"};

    typedef unordered_map<string,int> WORD_MAP;
    WORD_MAP word_map;

    for(auto const &word:word_list)
        ++word_map[word];

    for(auto const &i:word_map)
        cout << i.second << ' ' << i.first << endl;


    vector<pair<string,int>> v(word_map.begin(),word_map.end());

    sort(v.begin(),v.end(),greater<>());
    cout << endl;

    for(auto const &i:v)
        cout << i.second << ' ' << i.first << endl;

    cout << endl;

    sort(v.begin(),v.end(), cmp);
    for(auto const &i:v)
        cout << i.second << ' ' << i.first << endl;

    cout << endl;

    auto total = 0;

    for_each(word_map.begin(),word_map.end(),[&total](const WORD_MAP::value_type &p)
    {
        total += p.second;
    });

    cout << "total number of words = " << total << endl;
#endif

#if 0
    vector<int> aVect;
    back_insert_iterator<vector<int>> n (aVect);

    for(int i;cin >> i;*n++=i);

//    copy(istream_iterator<int>(cin),istream_iterator<int>(), back_inserter(aVect));

    copy(aVect.begin(),aVect.end(),ostream_iterator<int>(cout," "));
#endif

#if 0
    vector<int> aVect1{0,1,2,3,4},aVect2;

    cout << "Original contents of aVect1:\n";
    copy(aVect1.begin(),aVect1.end(),ostream_iterator<int>(cout,"\n"));

    back_insert_iterator<vector<int>> itr(aVect1);

    *itr++ = 100;
    *itr++ = 200;

    cout << "aVect1 after insertion:\n";
    copy (aVect1.begin (),
          aVect1.end (),
          ostream_iterator<int> (cout, "\n"));

    cout << "Size of aVect2 before copy: " << aVect2.size() << endl;

    copy(aVect1.begin(),aVect1.end(), back_inserter(aVect2));
    cout << "Size of aVect2 after copy: " << aVect2.size() << endl;

    copy(aVect2.begin(),aVect2.end(),ostream_iterator<int>(cout,"\n"));

    if(equal(aVect1.begin(),aVect1.end(),aVect2.begin()))
        cout << "vectors are equal" << endl;
    else
        cout << "end of the world" << endl;
#endif

#if 0
    list<int> aList1 {0,1,2,3,4},aList2;

    cout << "Original contents of aList:\n";
    copy (aList1.begin (),
          aList1.end (),
          ostream_iterator<int> (cout, "\n"));

    front_insert_iterator<list<int>> itr(aList1);

    *itr++ = 100;
    *itr++ = 200;
    cout << "aList after insertion:\n";
    copy (aList1.begin (),
          aList1.end (),
          ostream_iterator<int> (cout, "\n"));

    cout << "Size of aList2 before copy: " << aList2.size() << endl;

    copy(aList1.begin(),aList1.end(), front_inserter(aList2));

    cout << "Size of aList2 after copy: " << aList2.size() << endl;

    cout << "Contents of aList2 after insertion: \n";
    copy (aList2.begin (),
          aList2.end (),
          ostream_iterator<int> (cout, "\n"));
    if(!equal(aList1.rbegin(),aList1.rend(),aList2.begin()))
        cout << "end of the world" << endl;
    else
        cout << "output is as expected" << endl;
#endif

#if 0
    list<int> aList {0,1,2,3,4};
    vector<int> aVect {0, 1, 2, 3, 4};
    set<int> aSet{0, 1, 2, 3, 4};

    insert_into_container(aVect);
    insert_into_container(aList);
    insert_into_container(aSet);
#endif

#if 0
    deque<int> aDeck  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    cout << "Contents printed backward:\n";

    copy(aDeck.rbegin(),aDeck.rend(),ostream_iterator<int>(cout," "));
    cout << "\nContents printed backwards with reverse iterator adapter:\n";

    reverse_iterator<deque<int>::iterator> rfirst(aDeck.end());
    reverse_iterator<deque<int>::iterator> rlast(aDeck.begin());

    copy (rfirst,
          rlast,
          ostream_iterator<int> (cout, " "));

    cout << "\nContents printed backwards with reverse_copy:\n";
    reverse_copy (aDeck.begin (),
                  aDeck.end (),
                  ostream_iterator<int> (cout, " "));

    cout << endl;
#endif

#if 0
    list<string> my_list;

    copy(istream_iterator<string>(cin),istream_iterator<string>(), inserter(my_list,my_list.end()));

    my_list.sort();

    copy(my_list.begin(),my_list.end(),ostream_iterator<string>(cout,"\n"));
#endif

#if 0
    typedef vector<int> Vector;

    typedef istream_iterator<Vector::value_type> is_iter;
    typedef ostream_iterator<Vector::value_type> os_iter;

    Vector v;

    cout << "Enter a sequence of integers (eof to quit): ";

    copy(is_iter(cin),is_iter(), back_inserter(v));
    copy(v.begin(),v.end()-1,os_iter(cout," + "));

    if(!v.empty())
        cout << v.back() << " = " << accumulate(v.begin(),v.end(),0) << endl;
#endif

#if 0
    ostream_iterator<int> oi(cout," ");
    *oi++ = 6;
    *oi++ = 88;
    cout << endl;

    deque<int> d{3, 4, 7, 8};
    copy(d.begin(),d.end()-1,ostream_iterator<int>(cout," + "));

    cout << *(d.end()-1) << " = " <<accumulate(d.begin(),d.end(),0) << endl;
#endif

#if 0
    const char *fname = tmpnam(nullptr);
    if(!fname)
        return 1;
    ofstream out(fname,ios::out|ios::in|ios::trunc);

    out << "Here is a sample sentence for output.\n"
           "I hope that you like this sentence out there.";
    out.seekp(0);

//    istreambuf_iterator<char> first(out.rdbuf());
//
//    const istreambuf_iterator<char> last;
//    cout << endl;
//
//    while (first!=last)
//        cout << *first++;

    copy(istreambuf_iterator<char>(out.rdbuf()),istreambuf_iterator<char>(),ostream_iterator<char>(cout));

    cout << endl;

    remove(fname);
#endif

#if 0
    std::stack<char> aStack;
    cout << "Pushing 'A', 'B', 'C', and 'D'" << endl;

    aStack.push('A');
    aStack.push('B');
    aStack.push('C');
    aStack.push('D');

    while (!aStack.empty())
    {
        cout << "Popping: ";
        if(aStack.top()=='C')
            aStack.top() = 'Z';
        print_top(aStack);
        aStack.pop();
    }
#endif

#if 0
    queue<string> aCue;
    cout << "Pushing one two three \n";

    aCue.push("one");
    aCue.push("two");
    aCue.push("three");

    while (!aCue.empty())
    {
        cout << "Popping ";

        if(aCue.front()=="two")
            aCue.front() = "boo";

        print_front(aCue);

        aCue.pop();
    }
#endif

#if 0
    priority_queue<place> pque;

    cout << "begin emplace()" << endl;
    pque.emplace("Nashville",21);
    cout << "end emplace()" << endl;

    cout << "begin push(&&)" <<endl;
    pque.push(place("Cool Springs", 3));
    cout << "end push(&&)" << endl;

    cout << "begin push(const &)" << endl;
    place green_hills("Green Hills", 15);
    pque.push(green_hills);
//    place green_hills = {"Green Hills", 15};
    cout << "end push(const &)" << endl;

    while (!pque.empty())
    {
        cout << pque.top() << endl;
        pque.pop();
    }
#endif

#if 0
    cout << "Switch: 2.0 + 5.0 = " << switchOpCode(2.0,5.9,'+') << endl;

    cout << "Switch: 2.0 - 5.0 = " << switchFuncPtr(2.9,34.5,&Minus) << endl;
#endif

#if 0
    float (*pt2Function)(float ,char ,char ) = nullptr;
    float (example_class__::*pt2Member)(float,char ,char) = nullptr;
    float (example_class__::*pt2ConstMember) (float ,char ,char ) const= nullptr;

    pt2ConstMember = &example_class__::antherFun;

    if(argc>1)
        pt2Member = &example_class__::aFun;
    else
        pt2Member = &example_class__::bFun;

    pt2Function = &example_class__::aStaticFun;
    example_class__ instance1(10);

    cout << (instance1.*pt2Member)(12.5,'a','b') << endl;
    cout << (instance1.*pt2ConstMember)(24.5,'c','d') << endl;
    cout << (*pt2Function)(13.2,'e','f') << endl;

    unique_ptr<example_class__> instance2 (new example_class__());

    cout << (instance2.get()->*pt2Member)(12.5,'a','b');
#endif

#if 0
    pass_ptf(&aFun);

    float (*pt2Function)(float,float) = nullptr;

    pt2Function = get_ptf('+');
    cout << (*pt2Function)(2.4,4.3) << endl;

    pt2Function = get_ptf('-');
    cout << (*pt2Function)(2.4,4.3) << endl;
#endif

#if 0
    simple_function_object aFunctor;

    cout << aFunctor(5) << endl;

    cout << aFunctor.operator()(2) << endl;
#endif

#if 0
    vector<int> aVect(19);

    for(int i=1;i<=20;i++)
        aVect[i-1] = i;
    cout << "Sequence: ";
    for(auto i:aVect)
        cout << i << " ";
    cout << endl;

    auto c = count_if(aVect.begin(),aVect.end(),is_even());
    cout << c << " numbers are evenly divisible by 2.";
#endif

#if 0
    set<float> aSet{5.5, 1.1, 3.3, 4.4, 2.2};

    demonstrate_functors(aSet.begin(),aSet.end());
    demonstrate_lambdas(aSet.begin(), aSet.end());

    auto lambda = [](auto a) {return a+2;};
    cout << lambda(2) << "  "<<test(lambda)<<endl;

    test(lambda);

    set<float,greater<>> dSet{5.5, 1.1, 3.3, 4.4, 2.2};
    demonstrate_functors(dSet.begin(), dSet.end());
    demonstrate_lambdas(dSet.begin(), dSet.end());
#endif

#if 0
    demonstrate_on_string();
    demonstrate_on_array();
#endif

#if 0
    vector<int> v{1, 3, 4, 2, 6, 5, 0};

    auto n = count_if(v.begin(),v.end(),is_more_than_two());
    cout << n << endl;

    n = count_if(v.begin(),v.end(), bind2nd(greater<int>(),2));
    cout << n << endl;

    n = count_if(v.begin(),v.end(), bind(greater<>(),placeholders::_1,2));
    cout << n << endl;

    n = count_if(v.begin(),v.end(),[](auto val){return val>2;});
    cout << n << endl;
#endif

#if 0
    demonstrate_bind1st();
    demonstrate_bind2nd();
    contrast_bind1st_bind2nd_and_bind();
#endif

#if 0
    array<double,5> my_array = {10.1, 20.2,
                                30.3, 40.4,
                                50.5};
    const auto factor = 33.3;

    transform(my_array.begin(),my_array.end(),my_array.begin(), bind2nd(multiplies<double>(),factor));
    copy(my_array.begin(),my_array.end(),ostream_iterator<double>(cout," "));
    cout << endl;

    auto value = 1000.2;

    auto n = count_if(my_array.begin(),my_array.end(), bind(greater<>(),placeholders::_1,value));

    cout << "number of elements greater than "
         << value
         << " = "
         << n
         << endl;

    value = 1200.4;

    auto i = find_if(my_array.rbegin(),my_array.rend(),[value](auto f){return f>value;});

    if(i!=my_array.rend())
        cout << "the last element greater than "
             << value
             << " is "
             << *i
             << endl;
#endif

#if 0
    vector<int> vector1{1,2,3,4};
    vector<int> vector2;

    copy_if(vector1.begin(),vector1.end(), back_inserter(vector2), not1(is_odd<int>()));

    print_results(vector2);

    deque<int> deque1;

    remove_copy_if(vector1.begin(),vector1.end(), back_inserter(deque1),not1(is_odd<int>()));

    print_results(deque1);

    deque1.resize(0);

    copy_if(vector1.begin(),vector1.end(), back_inserter(deque1),[](auto number){return number %2 != 0;});
    print_results(deque1);
#endif

#if 0
    vector<int> v{4, 1, 2, 8, 5, 7};

    auto itr = find_if(v.begin(),v.end(),not1(IntGreaterThanThree()));
    print_results_(itr,v.end());

    itr = find_if(v.begin(),v.end(), not1(bind2nd(greater<int>(),3)));
    print_results_(itr,v.end());

    itr = find_if_not(v.begin(),v.end(),[](auto i){return i>3;});
    print_results_(itr,v.end());

    sort(v.begin(),v.end(), not2(less<int>()));
    print_results_(v.begin(), v.end());
#endif

#if 0
    vector<WrapInt> aVect(10);

    WrapInt wi(10);
    wi.isEven();

    for(auto i=0;i<10;i++)
        aVect[i] = WrapInt(i+1);
    cout << "Sequence contains: ";
    for_each(aVect.begin(),aVect.end(), mem_fun_ref(&WrapInt::showval));
    cout << endl;

    auto end_p = remove_if(aVect.begin(),aVect.end(), mem_fun_ref(&WrapInt::isPrime));
    cout << "Sequence after removing primes: ";
    for_each(aVect.begin(),end_p, mem_fun_ref(&WrapInt::showval));
    cout << endl;
    aVect.erase(end_p, aVect.end());

    cout << "aVect.size " << aVect.size() << endl;
    for (auto i = 0; i < 10; i++) {
        aVect[i] = WrapInt(i+1);
    }
    end_p = remove_if(aVect.begin(),aVect.end(), mem_fn(&WrapInt::isEven));
    cout << "Sequence after removing even values: ";

    for_each(aVect.begin(),
             end_p,
             mem_fn(&WrapInt::showval));

    cout << endl;
    aVect.erase(end_p, aVect.end());
    cout << "aVect.size " << aVect.size() << endl;

    for (int i = 0; i < 10; i++)
        aVect[i] = WrapInt(i + 1);

    end_p = remove_if(aVect.begin(),aVect.end(),[](WrapInt &wi){return wi.isOdd();});
    cout << "Sequence after removing odd values: ";
    for_each(aVect.begin(),end_p,[](WrapInt &wi){wi.showval();});
    aVect.erase(end_p, aVect.end());

//
//    vector<string> str;
//
//    cout << endl;
//    str.push_back("one");
//    str.push_back("two2");
//    for(auto i:str)
//        cout << i.length() << endl;
//    vector<int> lengths (str.size());
//    transform(str.begin(),str.end(),lengths.begin(), mem_fun_ref(&string::length));
//    for (auto i:lengths) {
//        cout << i << endl;
//    }
#endif

#if 0
    bool (*ptrToFunc)(int) = &isGreatThanTen;

    if(ptrToFunc(11))
        cout << "ptrToFunc (11) true" << endl;
#endif

#if 0
    bool (example__class::*ptrToMemFunc)(int) const = &example__class::firstFunc;

    example__class array(10);

    if((array.*ptrToMemFunc)(11))
        cout << "the pointer member function is true because 11 is great than 10" << endl;
#endif

#if 0
    vector<const char *>aVect {"One", "Two", "Three", "Four", "Five"};
    _print(aVect.begin(),aVect.end(),"Sequence contains: ");

    auto itr = find_if(aVect.begin(),aVect.end(), not1(bind2nd(ptr_fun(strcmp),"Three")));
    _print(itr,aVect.end(),"Found it: ");

    itr = find_if(aVect.begin(),aVect.end(),[](auto s){return !strcmp(s,"One");});

    _print(itr, aVect.end(), "Found it: ");
#endif

#if 0
    int a[] = {10, 20, -30, 40, -50, 60};

    auto itr1 = find_if(begin(a), end(a), bind(less<>(),placeholders::_1,0));
    if(itr1 != end(a))
        cout << *itr1 << " is first negative" << endl;

    auto itr2 = find_if(rbegin(a), rend(a), bind(less<>(),placeholders::_1,0));
    if(itr2!= rend(a))
        cout << *itr2 << " is last negative" << endl;
#endif

#if 0
    string s = "abcabcdsdabcsds";
    string ::size_type itr = 0;
    while ((itr=s.find("abc",itr))!=UINT64_MAX)
    {
        s.replace(itr,3,"cdd");
    }
    cout << s << endl;
#endif

    find_with_deque();

    return 0;
}

static void play_pingpong(size_t max_iterations,const std::string &string_to_print,
                          semaphore &my_semaphore,semaphore &other_semphore)
{
    for (int loops_done = 1;loops_done <= max_iterations;++loops_done)
    {
        my_semaphore.acquire();
        std::cout << string_to_print << "(" << loops_done << ")" <<std::endl;
        other_semphore.release();
    }
}