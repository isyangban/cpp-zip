#include<iostream>
#include<vector>
#include<tuple>
#include<string>
#include<utility>
using namespace std;

// pretty-print a tuple (from http://stackoverflow.com/a/6245777/273767)
template<class Ch, class Tr, class Tuple, std::size_t... Is>
void print_tuple_impl(std::basic_ostream<Ch,Tr>& os,
                      const Tuple & t,
                      std::index_sequence<Is...>)
{
    using swallow = int[]; // guaranties left to right order
    (void)swallow{0, (void(os << (Is == 0? "" : ", ") << std::get<Is>(t)), 0)...};
}
 
template<class Ch, class Tr, class... Args>
decltype(auto) operator<<(std::basic_ostream<Ch, Tr>& os,
                          const std::tuple<Args...>& t)
{
    os << "(";
    print_tuple_impl(os, t, std::index_sequence_for<Args...>{});
    return os << ")";
}


template<typename E, typename Tuple, size_t... I>
auto combine(E e, Tuple t, index_sequence<I...>)
{
    return make_tuple(e, get<I>(t)...);
}

template<typename C>
auto zip(C first)  
{
    vector<tuple<typename C::value_type>> result;
    for (auto& e : first) {
        result.push_back(make_tuple(e));
    }
    return result;
}

template<typename C, typename... Args>
auto zip(C first, Args... args) 
{
    vector<tuple<typename C::value_type, typename Args::value_type...>> result;
    auto iter = first.begin();
    auto rhs = zip(args...);
    auto iter2 = rhs.begin();
    while (iter != first.end() && iter2 != rhs.end()) {
        auto e1 = *iter;
        auto e2 = *iter2;
        auto seq = make_index_sequence<tuple_size<decltype(e2)>::value>();
        auto t = combine(e1, e2, seq);
        iter++;
        iter2++;
        result.push_back(t);
    }
    return result;
}


int main() 
{
    vector<int> a = {1, 2, 3, 4, 5};
    string b = "hello";
    vector<double> c = {0.5, 3.14, 1.414, 12.0, 1.0};
    auto zipped = zip(a, b, c);

    for (auto& t : zipped) 
        cout << t << ", ";
    cout << endl;

    return 0;
}
