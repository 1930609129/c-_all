//
// Created by xu on 2022/2/24.
//

#include <iostream>
#include <cstring>
#include "simple_string.h"

using namespace std;

std::ostream &operator<<(std::ostream &os,const simple_string &string)
{
    return os << (const char *)string;
}

simple_string::simple_string():len_(0),str_(nullptr) {
    cout << "simple_string::simple_string()" << endl;
}

simple_string::simple_string(const char *s) :len_(0),str_(strnew(s)){
    cout << "simple_string::simple_string(const char *)" << endl;
}

simple_string::simple_string(const simple_string &rhs) noexcept :len_(0),str_(strnew(rhs.str_)){
    cout << "simple_string::simple_string(const &)" << endl;
}

simple_string::simple_string(simple_string &&rhs) noexcept :len_(rhs.len_),str_(rhs.str_){
    cout << "simple_string::simple_string(simple_string &&)" << endl;
    rhs.str_ = nullptr;
    rhs.len_ = 0;
}

simple_string & simple_string::operator=(const simple_string &rhs) noexcept
{
    cout << "simple_string::operator=(const simple_string &)" << endl;
    if(&rhs != this)
    {
        simple_string(rhs).swap(*this);
    }
    return *this;
}

simple_string & simple_string::operator=(simple_string &&rhs) noexcept {
    cout << "simple_string::operator=(simple_string &&)" << endl;
    if(&rhs != this)
    {
        len_ = rhs.len_;
        delete [] str_;
        str_ = rhs.str_;
        rhs.len_ = 0;
        rhs.str_ = nullptr;
    }
    return *this;
}

void simple_string::swap(simple_string &rhs) noexcept {
    std::swap(len_,rhs.len_);
    std::swap(str_,rhs.str_);
    cout << "simple_string::swap(simple_string &)" << endl;
}

char & simple_string::operator[](size_t index) {
    return str_[index];
}

const char & simple_string::operator[](size_t index) const {
    return str_[index];
}

size_t simple_string::length() const {
    return len_;
}

bool simple_string::operator<(const simple_string &rhs) const {
    return strcmp(str_,rhs.str_)<0;
}

simple_string::operator const char *() const {
    return str_;
}

simple_string::~simple_string() {
    cout << "simple_string::~simple_string";
    delete [] str_;

    if (str_== nullptr)
        cout << "(nullptr)";
    cout << endl;
}

char *simple_string::strnew(const char *s) {
    if(s!= nullptr)
    {
        len_ = strlen(s);
        return strcpy(new char [len_+1],s);
    } else
        return nullptr;
}

typename simple_string::iterator simple_string::begin() {
    cout << "simple_string::begin()" << endl;
    return {*this,0};
}

simple_string::const_iterator simple_string::begin() const{
    cout << "const simple_string::begin()" << endl;
    return simple_string_const_iterator(*this,0);
}

typename simple_string::const_iterator simple_string::cbegin() const {
    cout << "simple_string::cbegin()" << endl;
    return {*this, 0};
}

typename simple_string::iterator simple_string::end() {
    cout << "simple_string::end()" << endl;
    return {*this, len_};
}

simple_string::const_iterator simple_string::end() const{
    cout << "const simple_string::end()" << endl;
    return {*this, len_};
}

simple_string::const_iterator simple_string::cend() const {
    cout << "simple_string::cend()" << endl;
    return {*this, len_};
}

char & simple_string_iterator::operator*() {
    cout << "simple_string_iterator::operator*()" << endl;
    return simple_string_[pos_];
}

const char & simple_string_iterator::operator*() const{
    cout << "simple_string_iterator::operator*()" << endl;
    return simple_string_[pos_];
}

simple_string_iterator & simple_string_iterator::operator++() {
    cout << "simple_string_iterator::operator++" << endl;
    ++pos_;
    return *this;
}

simple_string_iterator simple_string_iterator::operator++(int) {
    cout << "simple_string_iterator::operator++(int)" << endl;
    return {simple_string_,pos_++};
}

simple_string_iterator &simple_string_iterator::operator--() {
    cout << "simple_string_iterator::operator--()" << endl;
    --pos_;
    return *this;
}

simple_string_iterator simple_string_iterator::operator--(int) {
    cout << "simple_string_iterator::operator--(int)" << endl;
    return {simple_string_,pos_--};
}

bool simple_string_iterator::operator==(const simple_string_iterator &rhs) const {
    cout << "simple_string_iterator::operator==" << endl;
    return &simple_string_ == &rhs.simple_string_ && pos_ == rhs.pos_;
}

bool simple_string_iterator::operator!=(const simple_string_iterator &lhs) const {
    cout << "simple_string_iterator::operator!=" << endl;
    return !(*this == lhs);
}

const char & simple_string_const_iterator::operator*() const {
    cout << "simple_string_const_iterator::operator*()" << endl;
    return simple_string_[pos_];
}

simple_string_const_iterator &simple_string_const_iterator::operator++() {
    cout << "simple_string_const_iterator::operator++()" << endl;
    ++pos_;
    return *this;
}

simple_string_const_iterator simple_string_const_iterator::operator++(int) {
    cout << "simple_string_const_iterator::operator++(int)" << endl;
    simple_string_const_iterator old (*this);
    ++(*this);
    return old;
}

simple_string_const_iterator & simple_string_const_iterator::operator--() {
    cout << "simple_string_const_iterator::operator--" << endl;
    --pos_;
    return *this;
}

simple_string_const_iterator simple_string_const_iterator::operator--(int) {
    cout << "simple_string_const_iterator::operator--(int)" << endl;
    return simple_string_const_iterator(simple_string_,pos_--);
}

bool simple_string_const_iterator::operator==(const simple_string_const_iterator &rhs) const {
    cout << "simple_string_const_iterator::operator==()" << endl;
    return &simple_string_ == &rhs.simple_string_ && pos_ == rhs.pos_;
}

bool simple_string_const_iterator::operator!=(const simple_string_const_iterator &lhs) const {
    cout << "simple_string_const_iterator::operator!=()" << endl;
    return !(*this==lhs);
}

simple_string_iterator::simple_string_iterator(simple_string &string, size_t pos)
:simple_string_(string),pos_(pos) {
    cout << "simple_string_iterator::simple_string_iterator()" << endl;
}

simple_string_const_iterator::simple_string_const_iterator(const simple_string &string, size_t pos)
:simple_string_(string),pos_(pos){
    cout << "simple_string_const_iterator::simple_string_const_iterator()" << endl;
}