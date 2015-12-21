# C++ Zip
C++ version of the python built-in function zip

### Usage
``` cpp
vector<int> a = {1, 2, 3, 4, 5};
string b = "hello";
vector<double> c = {0.5, 3.14, 1.414, 12.0, 1.0};
auto zipped = zip(a, b, c);
// zipped type is std::vector<std::tuple<int, const char, double>>
```
