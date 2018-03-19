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

#if 0
template <typename T>
class subtype {
    template <typename R>
    friend auto operator|(R& rng, subtype /*self*/) {
        return rng | view::filter([](const typename R::value_type& v) {
                   return vns::holds_alternative<T>(v);
               }) |
               view::transform([](const typename R::value_type& v) {
                   return vns::get<T>(v);
               });
    }
};

template <typename T, typename U>
auto subtype2 = view::filter([](const T& v) {
                    return vns::holds_alternative<A>(v);
                }) |
                view::transform([](const T& v) { return vns::get<U>(v); });
#endif

int main() {
    std::vector<V> vs{{a}, {b}, {a}};

    // auto as = vs | subtype<A>();
    // // auto as = vs | subtype2<V, A>;

    // for (auto a : as) {
    //     std::cout << a.val;
    // }
    // std::cout << std::endl;

    std::cout << "build: " << platform::compiler << '\n'
              << "dependency: " << platform::link::compiler << '\n';

    std::for_each(vs.begin(), vs.end(),
                    visit([](A i) { std::cout << i.val << std::endl; },
                          [](B i) { std::cout << i.val << std::endl; },
                          [](C i) { std::cout << i.val << std::endl; }));
}
