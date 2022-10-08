#include <iostream>
#include <vector>

// A function is a named group of statements that can be invoked
// from other parts of the program or from the function itself
// in the case of recursive function
int ask() { return 43; }

typedef decltype(ask)* funtion_ptr;

class convertible_to_funtion_ptr {
public:
    operator funtion_ptr() const
    {
        return ask;
    }
};

int main_1(int argc, char** argv)
{
    auto ask_ptr = &ask;

    std::cout << ask_ptr() << '\n';

    auto& ask_ref = ask;
    std::cout << ask_ref << '\n';

    convertible_to_funtion_ptr ask_wrapper;
    std::cout << ask_wrapper() << '\n';
}

class older_than {
public:
    older_than(int limit)
        : m_limit { limit }
    {
    }
    template <typename T>
    bool operator()(T&& object) const
    {
        return std::forward<T>(object).age() > m_limit;
    }

private:
    int m_limit;
};

void nop_function(std::vector<int> people)
{
    std::vector<int> females;
    std::copy_if(begin(people), end(people),
        std::back_inserter(females), [](const auto& person) {
            return person < 10;
        });
}

class error_test_t {
public:
    error_test_t(bool error = true)
        : m_error { error }
    {
    }

    error_test_t operator==(bool test) const
    {
        return error_test_t(test ? m_error : !m_error);
    }

    error_test_t operator!() const
    {
        return error_test_t(!m_error);
    }

    template <typename T>
    bool operator()(T&& value) const
    {
        return m_error == (bool)std::forward<T>(value).error();
    }

private:
    bool m_error;
};