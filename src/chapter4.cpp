#include <map>
#include <string>
#include <vector>
// Curring
// The greater funtion an its curried version
bool greater(double first, double second)
{
    return first > second;
}

auto greater_curried(double first)
{
    return [first](double second) {
        return first > second;
    };
}

struct person_t {
    int age;
    std::string firstname, lastname;
    enum output_format_t {
        full_name,
        last_name
    };
};

void print_person(const person_t& person, std::ostream& out, person_t::output_format_t format);

auto print_person_cd(const person_t& person)
{
    return [&](std::ostream& out) {
        return [&](person_t::output_format_t format) {
            print_person(person, out, format);
        };
    };
}

using result_t = int;
using connection_t = int;
using session_t = int;

result_t query(connection_t& connection, session_t& session,
    const std::string& table_name, const std::string& filter);

void to_upper(std::string& string);

void pointer_to_upper(std::string* str)
{
    if (str)
        to_upper(*str);
}

void vector_to_upper(std::vector<std::string>& strs)
{
    for (auto& str : strs) {
        to_upper(str);
    }
}

void map_to_upper(std::map<int, std::string>& strs)
{
    for (auto& pair : strs) {
        to_upper(pair.second);
    }
}

template <typename Function>
auto pointer_lift(Function f)
{
    return [f](auto* item) {
        if (item) {
            f(*item);
        }
    }
}

template <typename Function>
auto collection_lift(Function f)
{
    return [f](auto& items) {
        for (auto& item : items) {
            f(item);
        }
    };
}
