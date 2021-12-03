/**
 * @file Setting.cpp
 * @author Antonin Nepras
 * @brief Implementation of Setting
 * @version 0.1
 * @date 2021-12-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include "Setting.hpp"


std::ostream& operator<< (std::ostream& out, Color rhs) {
    out << (int)rhs.r << " ";
    out << (int)rhs.g << " ";
    out << (int)rhs.b << " ";
    out << (int)rhs.a;

    return out;
}


std::istream& operator>> (std::istream& in, Color& rhs) {
    int tmp;
    in >> tmp;
    rhs.r = tmp;
    in >> tmp;
    rhs.g = tmp;
    in >> tmp;
    rhs.b = tmp;
    in >> tmp;
    rhs.a = tmp;

    return in;
}


Setting_entry::Setting_entry (std::string name) : m_name(name), 
        m_type(NONE_TYPE) {
}


Setting_entry::Setting_entry (std::string name, bool b) : m_name(name),
        m_type(BOOL_TYPE) {
    m_value.b = new bool(b);
}


Setting_entry::Setting_entry (std::string name, int i) : m_name(name),
        m_type(INT_TYPE) {
    m_value.i = new int(i);
}


Setting_entry::Setting_entry (std::string name, double d) : m_name(name),
        m_type(DOUBLE_TYPE) {
    m_value.d = new double(d);
}


Setting_entry::Setting_entry (std::string name, std::string s) : m_name(name),
        m_type(STRING_TYPE) {
    m_value.s = new std::string(s);
}


Setting_entry::Setting_entry (std::string name, Color c) : m_name(name),
        m_type(COLOR_TYPE) {
    m_value.c = new Color(c);
}


Setting_entry::~Setting_entry (void) {
    set_value();
}


Setting_entry::Setting_entry (const Setting_entry& rhs) : m_name(rhs.m_name),
        m_type(rhs.m_type) {
    switch (rhs.m_type.id)
    {
    case ID::BOOL:
        m_value.b = new bool(*rhs.m_value.b);
        break;

    case ID::INT:
        m_value.i = new int(*rhs.m_value.i);
        break;

    case ID::DOUBLE:
        m_value.d = new double(*rhs.m_value.d);
        break;

    case ID::STRING:
        m_value.s = new std::string(*rhs.m_value.s);
        break;
    
    case ID::COLOR:
        m_value.c = new Color(*rhs.m_value.c);
        break;
    
    default:
        break;
    }
}


Setting_entry::Setting_entry (const Setting_entry&& rhs) : m_name(rhs.m_name),
        m_type(rhs.m_type), m_value(rhs.m_value) {
}


Setting_entry& Setting_entry::operator= (const Setting_entry& rhs) {
    m_name = rhs.m_name;
    m_type = rhs.m_type;
    switch (rhs.m_type.id)
    {
    case ID::BOOL:
        m_value.b = new bool(*rhs.m_value.b);
        break;

    case ID::INT:
        m_value.i = new int(*rhs.m_value.i);
        break;

    case ID::DOUBLE:
        m_value.d = new double(*rhs.m_value.d);
        break;

    case ID::STRING:
        m_value.s = new std::string(*rhs.m_value.s);
        break;
    
    case ID::COLOR:
        m_value.c = new Color(*rhs.m_value.c);
        break;
    
    default:
        break;
    }

    return *this;
}



Setting_entry& Setting_entry::operator= (const Setting_entry&& rhs) {
    m_name = rhs.m_name;
    m_type = rhs.m_type;
    m_value = rhs.m_value;

    return *this;
}


std::ostream& operator<< (std::ostream& out, Setting_entry rhs) {
    out << rhs.get_type().name + " ";
    out << rhs.get_name() + " ";
    switch (rhs.get_type().id) 
    {
    case Setting_entry::ID::BOOL:
        out << *rhs.get_value().b;
        break;

    case Setting_entry::ID::INT:
        out << *rhs.get_value().i; 
        break;

    case Setting_entry::ID::DOUBLE:
        out << *rhs.get_value().d; 
        break;

    case Setting_entry::ID::STRING:
        out << *rhs.get_value().s; 
        break;

    case Setting_entry::ID::COLOR:
        out << *rhs.get_value().c; 
        break;
    }
    return out;
}


std::istream& operator>> (std::istream& in, Setting_entry& rhs) {
    std::string type_name;
    std::string name;

    in >> type_name;
    in >> name;
    rhs.set_name(name);

    if (type_name == rhs.NONE_TYPE.name) {
        rhs.set_value();

    } else if (type_name == rhs.BOOL_TYPE.name) {
        bool tmp;
        in >> tmp;
        rhs.set_value(tmp);

    } else if (type_name == rhs.INT_TYPE.name) {
        int tmp;
        in >> tmp;
        rhs.set_value(tmp);

    } else if (type_name == rhs.DOUBLE_TYPE.name) {
        double tmp;
        in >> tmp;
        rhs.set_value(tmp);

    } else if (type_name == rhs.STRING_TYPE.name) {
        std::string tmp;
        in >> tmp;
        rhs.set_value(tmp);

    } else if (type_name == rhs.COLOR_TYPE.name) {
        Color tmp;
        in >> tmp;
        rhs.set_value(tmp);
    }

    return in;
}


std::string Setting_entry::get_name (void) const {
    return m_name;
}


Setting_entry::Value Setting_entry::get_value (void) const {
    return m_value;
}


Setting_entry::Type Setting_entry::get_type (void) const {
    return m_type;
}



void Setting_entry::set_name (std::string name){
    m_name = name;
}


void Setting_entry::free_value () {
    switch (m_type.id)
    {
    case ID::BOOL:
        delete m_value.b;
        break;

    case ID::INT:
        delete m_value.i;
        break;

    case ID::DOUBLE:
        delete m_value.d;
        break;

    case ID::STRING:
        delete m_value.s;
        break;
    
    case ID::COLOR:
        delete m_value.c;
        break;
    
    default:
        break;
    }
}


void Setting_entry::set_value (void) {
    free_value();
    m_value.n = nullptr;
    m_type = NONE_TYPE;
}


void Setting_entry::set_value (bool b) {
    free_value();
    m_value.b = new bool(b);
    m_type = BOOL_TYPE;
}


void Setting_entry::set_value (int i) {
    free_value();
    m_value.i = new int(i);
    m_type = INT_TYPE;
}


void Setting_entry::set_value (double d) {
    free_value();
    m_value.d = new double(d);
    m_type = DOUBLE_TYPE;
}


void Setting_entry::set_value (std::string s) {
    free_value();
    m_value.s = new std::string(s);
    m_type = STRING_TYPE;
}


void Setting_entry::set_value (Color c) {
    free_value();
    m_value.c = new Color(c);
    m_type = COLOR_TYPE;
}


Setting::Setting (std::string filename) {
    std::ifstream filestream(filename);
    if (filestream.bad()) {
        std::cerr << "File error\n";
        return;
    }

    while (!(filestream.eof() || filestream.bad())) {
        Setting_entry tmp;
        filestream >> tmp;

        if (tmp.get_name() != "") {
            add_entry(tmp);
        }
    }

    if (filestream.bad()) {
        remove_all_entries();
        std::cerr << "File error\n";
        return;
    }
    
    filestream.close();
}


Setting::Setting (const std::vector<Setting_entry>& entries) {
    for (auto i : entries) {
        add_entry(i);
    }
}


Setting::~Setting (void) {
    for (auto i : m_entries) {
        free(i);
    }
}


Setting::Setting (const Setting& rhs) {
    for (auto i : rhs.m_entries) {
        add_entry(*i);
    }
}


Setting::Setting (const Setting&& rhs) {
    m_entries = rhs.m_entries;
}


Setting& Setting::operator= (const Setting& rhs) {
    for (auto i : rhs.m_entries) {
        add_entry(*i);
    }

    return *this;
}


Setting& Setting::operator= (const Setting&& rhs) {
    m_entries = rhs.m_entries;

    return *this;
}


std::ostream& operator<< (std::ostream& out, Setting rhs) {
    for (auto i : rhs.m_entries) {
        out << *i << "\n";
    }

    return out;
}


std::vector<Setting_entry*> Setting::get_entries (void) {
    return m_entries;
}


Setting_entry* Setting::get_entry (std::string name) {
    for (auto i : m_entries) {
        if (i->get_name() == name) {
            return i;
        }
    }

    return nullptr;
}


void Setting::add_entry (Setting_entry entry) {
    Setting_entry* e = get_entry(entry.get_name());
    if (e != nullptr) {
        remove_entry(entry.get_name());
    }

    m_entries.push_back(new Setting_entry(entry));
}


void Setting::remove_entry (std::string name) {
    for (size_t i = 0; i < m_entries.size(); i++) {
        if (m_entries[i]->get_name() == name) {
            delete m_entries[i];
            m_entries.erase(m_entries.begin() + i);
        }
    }
}


void Setting::remove_all_entries (void) {
    for (auto i : m_entries) {
        delete i;
    }

    m_entries.clear();
}


void Setting::export_setting (std::string filename) {
    std::ofstream filestream(filename);
    if (filestream.bad()) {
        std::cerr << "File Error \n";
        return;
    }

    for (auto i : m_entries) {
        filestream << *i << "\n";
    }

    if (filestream.bad()) {
        std::cerr << "File Error \n";
        return;
    }

    filestream.close();
}
