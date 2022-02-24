//
// Created by xu on 2022/2/22.
//

#ifndef STL_SIMPLE_STRING_H
#define STL_SIMPLE_STRING_H

class simple_string
{
public:
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

private:
    size_t len_;

    char *str_;

    char *strnew(const char *s);
};

std::ostream &
operator<<(std::ostream &os, const simple_string &string);

#endif //STL_SIMPLE_STRING_H
