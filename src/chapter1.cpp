#include <fstream>
#include <ranges>
#include <string>
#include <vector>

/// Origin Version ===============================================
std::vector<int>
count_lines_in_files(const std::vector<std::string>& files)
{
    std::vector<int> results;
    char c = 0;

    for (const auto& file : files) {
        int line_count {};

        std::ifstream in { file };

        while (in.get(c)) {
            if (c == '\n')
                line_count++;
        }

        results.push_back(line_count);
    }

    return results;
}

// Version 2 ===================================================
int count_lines(const std::string& filename)
{
    std::ifstream in { filename };

    return std::count(
        std::istreambuf_iterator<char>(in),
        std::istreambuf_iterator<char>(),
        '\n');
}

std::vector<int>
count_lines_in_files_2(const std::vector<std::string>& files)
{
    std::vector<int> results;
    for (const auto& file : files) {
        results.push_back(count_lines(file));
    }
    return results;
}

// Version 3 ===================================================
std::vector<int>
count_lines_in_files_3(const std::vector<std::string>& files)
{
    std::vector<int> results(files.size());
    std::transform(cbegin(files), cend(files), begin(results), count_lines);
    return results;
}
