#include <span>
#include <iostream>
#include <deque>
#include <functional>
#include <algorithm>
#include <memory>
#include <list>
#include <numeric>
#include <random>
#include <set>
#include "simple_string.h"
#include "bubble_sort.h"
#include "insertion_sort.h"

#include "generate_data.h"
#include "time_sort.h"
#include "heap_sort.h"
using namespace std;
static void find_with_array(){
    const int size = 8;
    unique_ptr<int[]> v1 (new int[size]{10, 20, -30, 40, -50, 60, 20, -40});
    unique_ptr<int[]> v2 (new int[size]);

    span s(v1.get(),v1.get()+size);
    copy(s.begin(),s.end(),v2.get());

    auto value = 20;

    auto itr1 = find_if(v1.get(),v1.get()+size, bind(greater<>(),placeholders::_1,value));

    if(itr1!=v1.get()+size)
        cout << *itr1 << " is the first value greater than "
             << value << endl;

    itr1 = find_if_not(v2.get(),v2.get()+size,[value](auto i){
        return i>=value;
    });

    if(itr1!=v2.get()+size)
        cout << *itr1 << " is not greater than or equal to "
             << value << endl;
    value = 40;

    auto itr2 = find_if(s.rbegin(),s.rend(), bind(greater<>(),placeholders::_1,value));
    if (itr2 != s.rend())
        cout << *itr2 << " is the last value greater than "
             << value << endl;
};

class max_odd
{
public:
    bool operator()(int current_max,int x)
    {
        return (x%2) == 1 && x>current_max;
    }
};

template<typename T>
struct abs_value{
    T operator()(T f)
    {
        return std::abs(f);
    }
};

template<typename T>
class print:public unary_function<T,void>
{
public:
    explicit print(ostream &out):os_(out),i_(0){}

    void operator()(const T &x)
    {
        os_ << x << ' ';
        i_++;
    }

    int count()
    {
        return i_;
    }

private:
    ostream &os_;
    int i_;
};

template<typename InputIterator1,typename InputIterator2>
static void find_mismatches(InputIterator1 first1,InputIterator1 last1,
                            InputIterator2 first2,InputIterator2 last2)
{
    std::cout << __FUNCTION__ << "()\n";

    if(distance(first1,last1)== distance(first2,last2))
    {
        if(equal(first1,last1,first2))
            cout << "ranges are equal" << endl;
        else
        {
            auto t1 = first1;
            auto t2 = first2;

            while (t1!=last1)
            {
                auto results = mismatch(t1,last1,t2);
                if(results.first!=last1)
                {
                    std::cout << "mismatching elements: " << *results.first;
                    std::cout << " and " << *results.second << '\n';
                    t1 = ++results.first;
                    t2 = ++results.second;
                } else
                    t1 = last1;
            }
        }
    }
}

template<typename InputIterator1,typename InputIterator2>
static void search_for_subsequence(InputIterator1 first1,InputIterator1 last1,
                                   InputIterator2 first2,InputIterator2 last2)
{
    cout << __FUNCTION__ << "()\n";

    auto itr = search(first1,last1,first2,last2);

    if(itr!=last1)
    {
        cout << "subsequence is present at index " << distance(first1,itr) << endl;
    } else
    {
        cout << "subsequence is not present" << endl;
    }
}

template<typename InputIterator1, typename InputIterator2>
static void find_end_for_subsequence(InputIterator1 first1,InputIterator1 last1,
                                     InputIterator2 firsr2,InputIterator2 last2)
{
    std::cout << __FUNCTION__ << "()\n";

    auto itr = find_end(first1,last1,firsr2,last2);

    if(itr!=last1)
    {
        cout << "last occurrence is at index "
             << distance(first1, itr)
             << " with contents ";
        copy(itr,itr+ distance(firsr2,last2),ostream_iterator<decltype(*last2)>(cout," "));
        cout << endl;
    }
}

template<typename ForwardIterator,typename Size,typename T,typename BinaryPredicate>
static void search_n_for_value(ForwardIterator first,ForwardIterator last,Size size,const T &value,BinaryPredicate pred)
{
    std::cout << __FUNCTION__ << "()\n";

    for(auto tmp = first;tmp!=last;)
    {
        auto itr = search_n(tmp,last,size,value,pred);

        if(itr!=last)
        {
            cout << size << " values of " << value <<  " found at position " << distance(first,itr) << endl;
            tmp = ++itr;
        } else
        {
            if(tmp==first)
                cout << "consecutive values not present" << endl;
            break;
        }
    }
}

template<typename Container,typename Predicate>
static void adjacent_find_for_pred(const Container &container,Predicate pred)
{
    cout << __FUNCTION__ << "()\n";

    for(auto tmp = container.begin();tmp != container.end();)
    {
        auto itr = adjacent_find(tmp,container.end(),pred);

        if(itr!=container.end())
        {
            cout << "2 values of " << (*itr)[0] << " found at position "
            << distance(container.begin(),itr) << endl;
            tmp = ++itr;
        } else
        {
            if(tmp == container.begin())
                cout << "2 consecutive values not present" << endl;
            break;
        }
    }
}

template<class ForwordIt,class T,class Compare = std::less<>>
ForwordIt binary_find(ForwordIt first,ForwordIt last,const T &value,Compare comp={})
{
    first = lower_bound(first,last,value,comp); // 搜索首个不小于 value 的元素 *first>=value
    return first != last && !comp(value,*first)?first:last; // !comp(value,*first) 如果value小于*first 则不相等
}

template <typename InputIterator1, typename InputIterator2>
static void demonstrate_binary_find(InputIterator1 first1,
                                    InputIterator1 last1,
                                    InputIterator2 first2,
                                    InputIterator2 last2)
{
    auto i=0;
    for(auto itr=first1;itr!=last1;itr++)
    {
        cout << '[' << i++ << ']' << *itr << endl;
    }

    for(;first2!=last2;++first2)
    {
        cout << "Searching for " << *first2 << endl;

        auto it = binary_find(first1,last1,*first2);
        if(it != last1)
            cout << "Found " << *it << " at index " << distance(first1,it) << endl;
        else
            cout << *first2 << " not found" << endl;
    }
}
template <typename InputIterator1, typename InputIterator2>
static void demonstrate_binary_search(InputIterator1 first1,
                                      InputIterator1 last1,
                                      InputIterator2 first2,
                                      InputIterator2 last2)
{
    for(;first2!=last2;++first2)
    {
        cout << "Searching for " << *first2 << endl;
        if(binary_search(first1,last1,*first2))
        {
            std::cout << "Found " << *first2 << endl;
        } else
        {
            std::cout << *first2 << " not found" << endl;
        }
    }
}

static simple_string lowercase(simple_string str)
{
    transform(str.cbegin(),str.cend(),str.begin(),
              [](auto c){return isupper(c)? tolower(c):c;});
    return str;
}

bool is_odd(int i)
{
    return (i%2)==1;
}

struct is_even
{
        bool operator()(int i)
        {
            return (i%2)==0;
        }
};

struct twenty:unary_function<int,int>
{
    bool operator()(int x) const
    {
        return x==20;
    }
};

static void set_difference_on_arrays()
{
    int a1[] = {3, 1, 2, 5, 4, 7, 6, 9, 10, 8};
    int a2[] = {4, 2, 8, 12, 6, 10};
    int answer[distance(begin(a1), end(a1))];

    sort(begin(a1),end(a1));
    sort(begin(a2),end(a2));

    cout << "a1 = ";
    copy(begin(a1), end(a1), ostream_iterator<int>(cout," "));
    cout << "\na2 = ";
    copy(begin(a2), end(a2), ostream_iterator<int>(cout," "));

    auto itr = set_difference(begin(a1),end(a1), begin(a2), end(a2), begin(answer));

    cout << "\nThe set difference has " << distance(begin(answer),itr) << " elements with results = ";
    copy(begin(answer),itr,ostream_iterator<int>(cout," "));
    cout << endl;

}

static void set_difference_on_sets()
{
    set<int> s1{3, 1, 2, 5, 4, 7, 6, 9, 10, 8};
    set<int> s2{4, 2, 8, 12, 6, 10};
    set<int> answer;

    cout << "s1 = ";
    copy(begin(s1), end(s1),ostream_iterator<int>(cout," "));
    cout << "\ns2= ";
    copy(begin(s2), end(s2),
         ostream_iterator<int>(cout," "));

    auto itr = set_difference(begin(s1), end(s1), begin(s2), end(s2), inserter(answer,answer.end()));
    cout << "\nThe set difference has " << distance(begin(answer), end(answer))
         << " elements with results = ";
    copy(answer.begin(), answer.end(),
         ostream_iterator<int>(cout," "));
    cout << endl;
}

struct sum_odd
{
    int operator()(int sum,int y)
    {
        return (y%2)==1 ? sum+y:sum;
    }
};

int main()
{
#if 0
    find_with_array();
#endif

#if 0
    vector<int> v {10, 20, -30, 40, 10, -40, 60, -10};

    auto itr = find(v.begin(),v.end(),10);

    auto num = count(v.begin(),v.end(),*itr);
    cout << "Found " << num << " occurrences of " << *itr << endl;

    num = count_if(v.begin(),v.end(),
                   bind(equal_to<>(), bind(abs_value<int>(),placeholders::_1),*itr));

    cout << "Found " << num << " occurrences of abs(" << *itr << ")" << endl;

    num = count_if(v.begin(),v.end(),[itr](auto i){
        return abs(i)==*itr;
    });

    cout << "Found " << num << " occurrences of abs(" << *itr << ")" << endl;
#endif

#if 0
    array<int,9> stats {10, 25, 9,
                        -30, 41, 11,
                        -40, 67, -10};

    cout << "Looking for max number" << endl;

    auto result = max_element(stats.begin(),stats.end());

    if(result!=stats.end())
        cout << "Max found = " << *result << " in array of size " << stats.size() << endl;

    result = min_element(stats.begin(),stats.end());
    if(result!=stats.end())
        cout << "Min found = " << *result << endl;

    result = max_element(stats.begin(),stats.end(),max_odd());
    cout << "Max odd = " << *result << endl;

    result = min_element(stats.begin(),stats.end(),
                         [](auto x,auto current_min)
                         {return (x%2)==1 && x<current_min;});
    cout << "Min odd = " << *result << endl;
#endif

#if 0
    int a[] = {1, 4, 2, 8, 5, 7};

    print<int> fun = for_each(begin(a), end(a),print<int>(cout));

    cout << endl << fun.count() << " objects printed." << endl;

    auto total = 0;
    for_each(begin(a), end(a),[&total](auto j)
    {
        cout << j << ' ';
        total++;
    });

    cout << endl << total << " objects printed." << endl;

    print<int> p(cout);

    for(auto i:a)
        p(i);

    cout << endl << p.count() << " objects printed." << endl;
#endif

#if 0
    vector<int> v1 {10, 20, 30, 40, 50};
    deque<int> d1(v1.begin(),v1.end());

    find_mismatches(v1.begin(),v1.end(),d1.begin(),d1.end());

    int a[] = {10, 40, 60, 80, 50};
    find_mismatches(v1.begin(), v1.end(), begin(a), end(a));
#endif

#if 0
    vector<string> l1 {"now", "is", "the", "time",
                       "for", "all", "good", "people",
                       "to", "come", "to", "the",
                       "aid", "of", "their", "party"};

    list<string> l2 {"I've", "seen", "all", "good",
                     "people", "turn", "their", "heads",
                     "each", "day", "so", "satisfied",
                     "I'm", "on", "my", "way"};

    string l3[] = {"all", "good", "people"};
    string l4[] = {"to"};

    search_for_subsequence(l1.begin(), l1.end(), begin(l3), end(l3));
    search_for_subsequence(l2.begin(), l2.end(), begin(l3), end(l3));
    find_end_for_subsequence(l1.begin(), l1.end(), begin(l4), end(l4));
#endif

#if 0
    vector<string> l1 {"now", "is", "the", "time",
                        "for", "all", "good", "people",
                       "to", "come", "to", "the",
                       "aid", "of", "their", "party"};

    list<string> l2 {"I've", "ss", "ss", "ss",
                     "people", "turn", "their", "heads",
                     "each", "day", "ss", "ss",
                     "I'm", "on", "my", "way"};

    search_n_for_value(l1.begin(),l1.end(),2,"t",[](const string &s,const string &v){
        return s[0]==v[0];
    });

    search_n_for_value(l2.begin(), l2.end(), 2, "ss",
                       [](const string &s, const string &v) {
                           return s == v;
                       });
#endif

#if 0
    vector<string> l1 {"now", "is", "the", "time",
                       "for", "all", "good", "people",
                       "to", "come", "to", "the",
                       "aid", "of", "their", "party"};

    list<string> l2 {"I've", "seen", "all", "good",
                     "people", "turn", "their", "heads",
                     "each", "day", "so", "satisfied",
                     "I'm", "on", "my", "way"};

    adjacent_find_for_pred(l1,[](const string &s,const string &v)
    {
        return s[0]==v[0];
    });

    adjacent_find_for_pred(l2,
                           [](const string &s, const string &v) {
                               return s[0] == v[0];
                           });
#endif

#if 0
    string a[] = {"now", "is", "the", "time",
                  "for", "all", "good", "people",
                  "to", "come", "to", "the",
                  "aid", "of", "their", "party"};

    string b[] = {"to", "find", "all", "good", "people"};

    sort(begin(a),end(a));

    demonstrate_binary_search(begin(a), end(a), begin(b), end(b));
    demonstrate_binary_find(begin(a), end(a), begin(b), end(b));

//    vector<int> data = {1,2,3,4,5,6};
//
//    for(int i=0;i<8;i++)
//    {
//        auto lower = lower_bound(data.begin(),data.end(),i);
//        cout << i << "<=";
//        if(lower!=data.end())
//            cout << *lower << " at index" << distance(data.begin(),lower) << endl;
//        else
//            cout << "not found" << endl;
//    }
#endif

#if 0
    simple_string s("HELLO");
    cout << s << endl;

    s = lowercase(s);
    cout << s << endl;
#endif

#if 0
    srand(time(nullptr));

    vector<int> v;
    generate_n(back_inserter(v),10,rand);

    vector<int> v2(10,20);
    copy(v.begin(),v.end(),ostream_iterator<int>(cout," "));
    cout << endl;

//    transform(v.begin(),v.end(),v.begin(),[](auto i){return i%20;});

    transform(v.begin(),v.end(),v2.begin(),v.begin(),modulus<>());
    copy(v.begin(),v.end(),ostream_iterator<int>(cout," "));
    cout << endl;

    sort(v.begin(),v.end(),greater<>());
    copy(v.begin(),v.end(),ostream_iterator<int>(cout," "));
    cout << endl;
#endif

#if 0
    vector<int> v1(10),v2(10);

    fill(v1.begin(),v1.end(),1);
    copy(v1.begin(),v1.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    partial_sum(v1.begin(),v1.end(),v1.begin());
    copy(v1.begin(),v1.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    shuffle(v1.begin(),v1.end(),default_random_engine(time(nullptr)));
    copy(v1.begin(),v1.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    fill(v2.begin(),v2.end(),2);
    partial_sum(v2.begin(),v2.end(),v2.begin());
    shuffle(v2.begin(),v2.end(),mt19937(random_device()()));

    copy(v2.begin(),v2.end(),ostream_iterator<int>(cout," "));
    cout << endl;

    transform(v1.begin(),v1.end(),v2.begin(),v2.begin(),plus<>());
    copy(v2.begin(),v2.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
#endif

#if 0
    vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8, 9};

    cout << "v1 originally contains:\n";
    copy (v1.begin (),
          v1.end (),
          ostream_iterator<int> (cout, " "));

    rotate(v1.begin(),v1.begin()+4,v1.end());
    cout << "\nv1 rotated contains:\n";
    copy (v1.begin (),
          v1.end (),
          ostream_iterator<int> (cout, " "));
    cout << endl;

    vector<int> v2;

    rotate_copy(v1.begin(),v1.begin()+5,v1.end(), back_inserter(v2));

    cout << "\nv2 rotated contains:\n";
    copy (v2.begin (),
          v2.end (),
          ostream_iterator<int> (cout, " "));
    cout << endl;
#endif

#if 0
    array<int,10> my_array{1, 2, 3,
                           4, 5, 6,
                           7, 8, 9,
                           10};
    reverse(my_array.begin(),my_array.end());
    cout << "my_array contains: ";

    copy (my_array.begin (),
          my_array.end (),
          ostream_iterator<int> (cout, " "));

    cout << endl;

    string my_palindrome("amanaplanacanalpanama");

    reverse_copy(my_palindrome.begin(),my_palindrome.end(),ostream_iterator<char>(cout));
    cout << endl;
#endif

#if 0
    int a[] = {10, 20, 30, 30, 20, 10, 10, 20};
    cout << "original array contains:";
    copy(begin(a), end(a),ostream_iterator<int>(cout," "));
    cout << endl;

    auto nend = remove(begin(a), end(a),20);
    cout << "range contains:";
    copy (begin(a), nend, ostream_iterator<int> (cout, " "));
    cout << endl;

    cout << "complete array contains:";
    copy(begin(a), end(a),ostream_iterator<int>(cout," "));
    cout << endl;
#endif

#if 0
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    auto pend = remove_if(begin(a), end(a), is_odd);

    cout << "with all odd values removed the range contains:";
    copy (begin(a), pend, ostream_iterator<int> (cout, " "));
    cout << endl;

    pend = remove_if(begin(a),pend,is_even());

    cout << "with all even values removed the range contains:";
    copy (begin(a), pend, ostream_iterator<int> (cout, " "));
    cout << endl;
#endif

#if 0
    int a[] = {10, 20, 30, 30, 20, 10, 10, 20};

    cout << "original array contains:";
    copy (begin(a),
          end(a),
          ostream_iterator<int> (cout, " "));
    cout << endl;

    vector<int> myVect;

    remove_copy(begin(a), end(a), back_inserter(myVect),20);

    cout << "after removing all 20's myVect contains:";
    copy (myVect.begin(),
          myVect.end(),
          ostream_iterator<int> (cout, " "));
    cout << endl;
#endif

#if 0
    int a[] = {10, 20, 30, 30, 20, 10, 10, 20};

    vector<int> myVect;
    cout << "array a[] originally contains:";
    copy (begin(a), end(a), ostream_iterator<int> (cout, " "));
    cout << endl;

    remove_copy_if(begin(a), end(a), back_inserter(myVect),twenty());
    cout << "After removing 20's myVect contains:";
    copy (myVect.begin(), myVect.end(), ostream_iterator<int> (cout, " "));
    cout << endl;

    myVect.resize(0);

    auto nend = remove_copy_if(begin(a), end(a), back_inserter(myVect), not_fn(bind(equal_to<>(),placeholders::_1,10)));
    cout << "After removing every thing that's not a 10 myVect contains:";
    copy (myVect.begin(), myVect.end(), ostream_iterator<int> (cout, " "));
    cout << endl;

    auto nnend = copy_if(begin(a), end(a), begin(a),[](auto i){return i==10;});
    cout << "After copying every thing that's a 10 a[] contains:";
    copy (begin(a), nnend, ostream_iterator<int> (cout, " "));
    cout << endl;
#endif

#if 0
    vector<int> v{10, -20, 11, 20, 10, -30, -47, -50, 63, 70};

    cout << "before replacing, v: ";
    for (auto i : v)
        cout << i << " ";
    cout << endl;

    auto value = 20;

    replace_if(v.begin(),v.end(),[value](auto i){return abs(i)==value;},42);
    cout << "after replacing abs(20) with 42, v: ";

    for (auto i : v)
        cout << i << " ";
    cout << endl;

    vector<int> v2(v.size());

    replace_copy_if(v.begin(),v.end(),v2.begin(),[](auto i){
        return (i%2)==1;
    },0);

    cout << "after replacing odd numbers with 0, v2: ";

    for (auto i : v2)
        cout << i << " ";
    cout << endl;
#endif

#if 0
    vector<int> aVector{10, 3, 7, 15, -5, 120, 42};

    for(auto i:aVector)
        cout << i << ' ';
    cout << endl;

    sort(aVector.begin(),aVector.end());

    for (auto i : aVector)
        cout << i << " ";
    cout << endl;

    sort(aVector.begin(),aVector.end(),greater<>());

    for (auto i : aVector)
        cout << i << " ";
    cout << endl;
#endif

#if 0
    vector<int> v{1, 4, 2, 8, 5, 7};

    copy(v.begin(),v.end(),ostream_iterator<int>(cout," "));

    auto sum = count_if(v.begin(),v.end(), bind(greater<>(),placeholders::_1,5));

    cout << endl << "There are " << sum << " number(s) greater than 5" << endl;

    auto nend = remove_if(v.begin(),v.end(), bind(less<>(),placeholders::_1,4));

    v.erase(nend,v.end());

    cout << "Elements less than 4 removed:" << endl;
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    sort(v.begin(),v.end());
    cout << "Elements sorted:" << endl;
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
#endif

#if 0
    const int biggest = 100000;
    const int size = 10000;

    srand(time(nullptr));
    vector<int> data = generate_data<int>(size,biggest);
    list<int> list_data(data.begin(),data.end());

    time_sort<int>("bubble_sort(vector)", data, bubble_sort);
    time_sort<int>("bubble_sort(list)", list_data, bubble_sort);

    time_sort<int>("insertion_sort(vector)", data, insertion_sort);
    time_sort<int>("sort(vector)", data);
    auto start = std::chrono::high_resolution_clock::now();
    list_data.sort();
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
    std::cout << duration.count() <<" microseconds" << std::endl;
#endif

#if 0
    set_difference_on_arrays();
    set_difference_on_sets();
#endif

#if 0
    int a1[] = { 5, 10, 15, 20, 25};
    int a2[] = {50, 40, 30, 20, 10};
    int results[distance(begin(a1),end(a1))];

    sort(begin(a1),end(a1));
    sort(begin(a2),end(a2));

    auto itr = set_intersection(begin(a1),end(a1),begin(a2),end(a2),begin(results));
    cout << "intersection has " << distance(begin(results), itr)
         << " elements:\n";
    copy (begin(results), itr, ostream_iterator<int> (cout, " "));
    cout << endl;
#endif

#if 0

    int a1[] = { 5, 10, 15, 20, 25};
    int a2[] = {50, 40, 30, 20, 10};
    vector<int> answer;

    sort(begin(a1),end(a1));
    sort (begin(a2), end(a2));

    set_union(begin(a1), end(a1), begin(a2),end(a2), back_inserter(answer));
    cout << "union has " << answer.size() << " elements:\n";

    copy(answer.begin(),
         answer.end(),
         ostream_iterator<int>(cout, " "));
    cout << endl;
#endif

#if 0
    const int biggest = 100000;
    const int size = 200000;

    srand(time(nullptr));

    vector<int> data = generate_data<int>(size,biggest);

    time_sort<int>("heap_sort(vector)", data, heap_sort);
    time_sort<int>("sort(vector)", data, sort);

    vector<int> v{3432,4,3,5,4,5,34};
    make_heap(v.begin(),v.end());
    copy(v.begin(),v.end(),ostream_iterator<decltype(*v.begin())>(cout," "));
    cout << endl;
    sort_heap(v.begin(),v.end());
    copy(v.begin(),v.end(),ostream_iterator<decltype(*v.begin())>(cout," "));
    cout << endl;
#endif

#if 0
    vector<int> v(10,1);

    partial_sum(v.begin(),v.end(),v.begin());
    for (auto i : v)
        cout << i << ' ';
    cout << "\nThe sum of all the odd numbers is "
    << accumulate(v.begin(),v.end(),0,sum_odd()) <<endl;

    cout << accumulate(v.begin(),v.end(),0,[](auto sum,auto y){
        return (y%2==0)?sum+y:sum;
    });
#endif

}

