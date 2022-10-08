#include <functional>
#include <iostream>
#include <type_traits>

template <typename Function, typename SecondArgType>
class partial_application_on_2nd_impl {
public:
    partial_application_on_2nd_impl(Function function, SecondArgType sec_arg)
        : func { function }
        , second_arg { sec_arg }
    {
    }

    template <typename FirstArg>
    auto operator()(FirstArg&& firstArg) const
        -> std::invoke_result_t<Function, FirstArg, SecondArgType>
    {
        return func(std::forward<FirstArg>(firstArg), second_arg);
    }

private:
    Function func;
    SecondArgType second_arg;
};

template <typename Function, typename SecondArgType>
partial_application_on_2nd_impl<Function, SecondArgType>
bind2nd(Function&& function, SecondArgType&& second_arg)
{
    return partial_application_on_2nd_impl<Function, SecondArgType>(
        std::forward<Function>(function), std::forward<SecondArgType>(second_arg));
}

int main()
{
    auto greater_than_42 = bind2nd(std::greater<int>(), 42);

    std::cout << std::boolalpha << greater_than_42(1) << " " << // false
        greater_than_42(50); // true

    return 0;
}