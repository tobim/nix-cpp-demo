#ifndef TOBIM__VISIT_HPP
#define TOBIM__VISIT_HPP

#include <utility>

namespace tobim {

namespace detail {

template <class V>
class visit_helper {
   public:
    visit_helper(const V& v) : v_(v) {}
    visit_helper(V&& v) : v_(std::move(v)) {}

    template <class T>
    void operator()(const T& t) const {
        visit(v_, t);
    }

   private:
    const V& v_;
};

template <class V>
visit_helper<V> visit_help(V&& v) {
    return visit_helper<V>(v);
}

}  // namespace detail

#if __cpp_variadic_using < 201611
namespace detail {

template <typename... Lambdas>
struct lambda_visitor;

template <typename Lambda1, typename... Lambdas>
struct lambda_visitor<Lambda1, Lambdas...> : public lambda_visitor<Lambdas...>,
                                             public Lambda1 {
    using Lambda1::operator();
    using lambda_visitor<Lambdas...>::operator();

    lambda_visitor(Lambda1 l1, Lambdas... lambdas)
        : lambda_visitor<Lambdas...>(lambdas...), Lambda1(l1) {}
};

template <typename Lambda1>
struct lambda_visitor<Lambda1> : public Lambda1 {
    using Lambda1::operator();

    lambda_visitor(Lambda1 l1) : Lambda1(l1) {}
};

}  // namespace detail

template <class... Fs>
constexpr detail::lambda_visitor<typename std::decay<Fs>::type...> compose(
    Fs&&... fs) {
    using visitor_type =
        detail::lambda_visitor<typename std::decay<Fs>::type...>;
    return visitor_type(std::forward<Fs>(fs)...);
};

template <class... Fs>
detail::visit_helper<detail::lambda_visitor<
    typename std::decay<Fs>::type...>> constexpr visit(Fs&&... fs) {
    return detail::visit_help(compose(std::forward<Fs>(fs)...));
}
#else
template <class... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};
template <class... Ts>
overloaded(Ts...)->overloaded<Ts...>;

template <class... Fs>
detail::visit_helper<
    overloaded<typename std::decay<Fs>::type...>> constexpr visit(Fs&&... fs) {
    return detail::visit_help(overloaded{std::forward<Fs>(fs)...});
}
#endif

}  // namespace tobim

#endif  // TOBIM__VISIT_HPP
