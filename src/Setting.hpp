/**
 * @file Setting.hpp
 * @author Antonin Nepras
 * @brief Definition of Setting
 * @version 0.1
 * @date 2021-12-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef setting_hpp
#define setting_hpp

#include <inttypes.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    friend std::ostream& operator<< (std::ostream& out, Color rhs);
    friend std::ifstream& operator>> (std::ifstream& out, Color& rhs);
};

class Setting_entry {
public:
    union Value {
        void* n;
        bool* b;
        int* i;
        double* d;
        std::string* s;
        Color* c;

        Value () {
            n = nullptr;
        }
    };

    enum class ID {
        NONE,
        BOOL,
        INT, 
        DOUBLE,
        STRING,
        COLOR
    };

    struct Type {
        ID id;
        std::string name;
    };

    const Type NONE_TYPE = {ID::NONE, "none"};
    const Type BOOL_TYPE = {ID::BOOL, "bool"};
    const Type INT_TYPE = {ID::INT, "int"};
    const Type DOUBLE_TYPE = {ID::DOUBLE, "double"};
    const Type STRING_TYPE = {ID::STRING, "string"};
    const Type COLOR_TYPE = {ID::COLOR, "color"};


    Setting_entry (void) = default;
    Setting_entry (std::string name);
    Setting_entry (std::string name, bool b);
    Setting_entry (std::string name, int i);
    Setting_entry (std::string name, double d);
    Setting_entry (std::string name, std::string s);
    Setting_entry (std::string name, Color c);
    ~Setting_entry (void);

    Setting_entry (const Setting_entry& rhs);
    Setting_entry (const Setting_entry&& rhs);


    Setting_entry& operator= (const Setting_entry& rhs);
    Setting_entry& operator= (const Setting_entry&& rhs);


    friend std::ostream& operator<< (std::ostream& out, Setting_entry rhs);
    friend std::istream& operator>> (std::istream& out, Setting_entry& rhs);


    std::string get_name (void) const;
    Value get_value (void) const;
    Type get_type (void) const;


    void set_name (std::string name);
    void set_value (void);
    void set_value (bool b);
    void set_value (int i);
    void set_value (double d);
    void set_value (std::string s);
    void set_value (Color c);


protected:
    std::string m_name = "";
    Value m_value;
    Type m_type = NONE_TYPE;

    void free_value (void);
};



class Setting 
{
public:
    Setting (void) = default;
    Setting (std::string filename);
    Setting (const std::vector<Setting_entry>& entries);
    ~Setting (void);

    Setting (const Setting& rhs);
    Setting (const Setting&& rhs);

    Setting& operator= (const Setting& rhs);
    Setting& operator= (const Setting&& rhs);

    friend std::ostream& operator<< (std::ostream& out, Setting rhs);

    std::vector<Setting_entry*> get_entries (void);

    Setting_entry* get_entry (std::string name);

    void add_entry (Setting_entry entry);

    void remove_entry (std::string name);

    void remove_all_entries (void);

    void export_setting (std::string filename);

protected:
    std::vector<Setting_entry*> m_entries;
};


#endif
