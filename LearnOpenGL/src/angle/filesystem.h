#pragma once

#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__

#include <string>
#include <map>
#include <stdio.h>
#include <fstream>

class File {
private:
    std::string m_Src;

    static inline std::map<std::string, std::string>& get_path_map() {
        static std::map<std::string, std::string> path_map;
        return path_map;
    }

public:

    /*
    * Add environment path value
    */
    static inline void add_env_path_val(const std::string& _Tag, const std::string& _Path) {
        get_path_map()[_Tag] = _Path;
    }

    File(const std::string& _Tag, const std::string& _Filename);
    File(const std::string& _File);

    inline std::string raw_str() const {
        return m_Src;
    }
};


#endif // !__FILESYSTEM_H__