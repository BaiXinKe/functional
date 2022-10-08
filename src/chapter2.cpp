#include <numeric>
#include <string>
#include <vector>

double average_score(const std::vector<int>& scores)
{
    int sum {};
    for (int score : scores) {
        sum += score;
    }
    return sum / (double)scores.size();
}

// version 2
double average_score_2(const std::vector<int>& scores)
{
    return std::accumulate(cbegin(scores), cend(scores), 0) / (double)scores.size();
}

// product
double scores_product(const std::vector<int>& scores)
{
    return std::accumulate(cbegin(scores), cend(scores), 1, std::multiplies<int>());
}

// Counting newline characters with std::accumulate
int f(int previouds_count, char c)
{
    return (c != '\n') ? previouds_count : previouds_count + 1;
}

int count_lines(const std::string& s)
{
    return std::accumulate(cbegin(s), cend(s), 0, f);
}

// string trim
std::string trim_left(std::string s)
{
    s.erase(begin(s), std::find_if_not(begin(s), end(s), std::isspace<char>));
    return s;
}

std::string trim_right(std::string s)
{
    s.erase(std::find_if_not(rbegin(s), rend(s), std::isspace<char>).base(), s.end());
    return s;
}

std::string trim(std::string s)
{
    return trim_left(trim_right(std::move(s)));
}

// partition and stable_partition

// Createing a funtion that you cloud call multiple times would be useful
template <typename FilterFunction>
std::vector<std::string>
names_of(const std::vector<int>& people, FilterFunction filter)
{
    std::vector<std::string> result;

    for (const auto& person : people) {
        if (filter(person)) {
            result.push_back(name(person));
        }
    }
    return result;
}

// process a non-empty vector recursively by first processing it head
// and then processing its tail.
template <typename FilterFunction>
std::vector<std::string>
names_for_2(const std::vector<int>& people, FilterFunction filter)
{
    if (people.empty()) {
        return {};
    }
    const auto head = people.front();
    const auto processed_tail = names_for_2(tail(people), filter);
    if (filter(head)) {
        return prepend(name(head), processed_tail);
    } else {
        return processed_tail;
    }
}

// effective
template <typename FilterFunction, typename Iterator>
std::vector<std::string>
names_for_3(Iterator people_begin, Iterator people_end, FilterFunction filter)
{
    if (people_begin == people_end)
        return {};
    const auto& head = *people_begin;
    const auto processed_tail = names_for_3(people_begin + 1, people_end, filter);

    if (filter(head)) {
        return prepend(name(head), processed_tail);
    }
    return processed_tail;
}

// tail-recursive implementation
template <typename FilterFunction, typename Iterator>
std::vector<std::string>
names_for_helper(
    Iterator people_begin,
    Iterator people_end,
    FilterFunction filter,
    std::vector<std::string> previously_collected)
{
    if (people_begin == people_begin) {
        return previously_collected;
    }

    const auto head = *people_begin;
    if (filter(head)) {
        previously_collected.push_back(name(head));
    }

    return names_for_helper(people_begin + 1, people_end, filter, std::move(previously_collected));
}

// compiler that support tail-call optimization (TCO) will be able to convert the recursive function to
// a simple loop and make it as efficient;
template <typename FilterFunction, typename Iterator>
std::vector<std::string> names_for_tail(
    Iterator people_begin, Iterator people_end, FilterFunction filter)
{
    return names_for_helper(people_begin, people_end, filter, {});
}