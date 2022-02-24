//
// Created by xu on 2022/2/24.
//

#ifndef STL_20_SIMPLE_STRING_H
#define STL_20_SIMPLE_STRING_H

#include <iterator>

class simple_string_iterator;
class simple_string_const_iterator;

class simple_string {
public:
    typedef char value_type;
    typedef simple_string_iterator iterator;
    typedef simple_string_const_iterator const_iterator;

    simple_string();
    simple_string(const char *s);
    simple_string(const simple_string &rhs) noexcept;
    simple_string(simple_string &&rhs) noexcept;

    simple_string &operator=(const simple_string &rhs) noexcept;

    simple_string &operator=(simple_string &&rhs) noexcept;

    void swap(simple_string &rhs) noexcept;

    char &operator[](size_t index);

    const char &operator[](size_t index) const;

    bool operator<(const simple_string &rhs) const;

    size_t length() const;

    explicit operator const char *() const;

    ~simple_string();

    iterator begin();

    const_iterator begin() const;

    const_iterator cbegin() const;

    iterator end();

    const_iterator end() const;

    const_iterator cend() const;

private:
    size_t len_;

    char *str_;

    char *strnew(const char *s);
};

std::ostream &
operator<<(std::ostream &os, const simple_string &string);

class simple_string_iterator:public std::iterator<std::bidirectional_iterator_tag,simple_string>
{
    friend class simple_string;

public:
    char &operator*();
    const char & operator*() const;

    simple_string_iterator &operator++ ();
    simple_string_iterator operator++(int);

    simple_string_iterator &operator-- ();
    simple_string_iterator operator--(int );

    bool operator==(const simple_string_iterator &rhs) const;

    bool operator!=(const simple_string_iterator &lhs) const;

private:

    simple_string_iterator (simple_string &simple_string,size_t pos = 0);

    simple_string & simple_string_;

    mutable size_t pos_;
};

class simple_string_const_iterator:public std::iterator<std::bidirectional_iterator_tag,simple_string>
{
    friend class simple_string;

public:

    const char& operator* () const;

    simple_string_const_iterator & operator++ ();

    simple_string_const_iterator operator++ (int);

    simple_string_const_iterator &operator-- ();

    simple_string_const_iterator operator-- (int);

    bool operator== (const simple_string_const_iterator &rhs) const;

    bool operator!= (const simple_string_const_iterator &lhs) const;

private:
    simple_string_const_iterator (const simple_string &simple_string, size_t pos = 0);

    const simple_string &simple_string_;

    mutable size_t pos_;
};

#endif //STL_20_SIMPLE_STRING_H
