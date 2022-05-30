#include <iostream>
using namespace std;

int main()
{
    variant<int, float> v, w;
v = 12;
int i = get<int>(v);
w = get<int>(v);
w = get<0>(v); // same effect as the previous line
w = v; // same effect as the previous line

get<double>(v); // ill formed
get<3>(v); // ill formed

try {
  get<float>(w); // will throw.
}
catch (bad_variant_access&) {}
}