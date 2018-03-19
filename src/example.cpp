#include "tobim/visit.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include <range/v3/all.hpp>

#include "platform/platform.hpp"

#if __cpp_lib_variant < 201606 // missing in libstdc++ 7.{1,2}
#include "mpark/variant.hpp"
template <class... T>
using Variant = mpark::variant<T...>;
namespace vns = mpark;
#else
#include <variant>
template <class... T>
using Variant = std::variant<T...>;
namespace vns = std;
#endif

using namespace ranges;

struct A {
    int val = 7;
} a;
struct B {
    char val = 'x';
} b;
struct C {
    char val = 'u';
} c;

using V = Variant<A, B, C>;
using tobim::visit;

int main() {
    std::vector<V> vs{{a}, {b}, {a}};

    std::cout << "compiler_id of current translation: " << platform::compiler << '\n'
              << "compiler_id of link target:         " << platform::link::compiler << '\n';

    std::for_each(vs.begin(), vs.end(),
                  visit([](A i) { std::cout << i.val << std::endl; },
                        [](B i) { std::cout << i.val << std::endl; },
                        [](C i) { std::cout << i.val << std::endl; }));
}
