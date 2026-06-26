#include "filesystem.h"

File::File(const std::string& _Tag, const std::string& _Filename) {
    auto& path_ma = get_path_map();

    if (path_ma.find(_Tag) == path_ma.end()) {
        return;
    }

    std::ifstream file{ path_ma.at(_Tag) + _Filename };

    if (!file.is_open()) {
        __debugbreak();
    }

    std::string line;
    while (std::getline(file, line))
        m_Src.append(line + '\n');

    file.close();
}

File::File(const std::string& _File) {
    std::ifstream file{ _File };

    if (!file.is_open()) {
        __debugbreak();
    }

    std::string line;
    while (std::getline(file, line))
        m_Src.append(line + '\n');

    file.close();
}