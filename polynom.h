//
// Created by derev on 19.07.2022.
//

#ifndef LETO_ZADACHKI_OT_KUZNETSOVA_POLYNOM_H
#define LETO_ZADACHKI_OT_KUZNETSOVA_POLYNOM_H

#include <iostream>
#include <vector>
#include <cmath>
#include <map>


template<typename T>
class Polynom_coef {
private:
    std::vector<T> coef_;
public:
    Polynom_coef(std::initializer_list<T> in_list) {
        coef_.reserve(in_list.size());
        int i = 0;
        for (auto &it: in_list) coef_.push_back(it);
    }

    Polynom_coef(const int &size) {
        coef_.reserve(size);
    }

    Polynom_coef() {};

    int size() const {
        return coef_.size();
    }

    bool operator==(const Polynom_coef<T> &pol) {
        if (coef_.size() != pol.size()) return false;
        for (int i = 0; i < coef_.size(); i++) {
            if (coef_[i] != pol.coef_[i]) return false;
        }
        return true;
    }


    Polynom_coef<T> operator+(const Polynom_coef<T> &pol) const {
        Polynom_coef<T> sum;
        if (coef_.size() >= pol.size()) sum = *this;
        else sum = pol;
        for (int i = 0; i < std::min(pol.size(), static_cast<int>(coef_.size())); i++) {
            sum.coef_[i] = coef_[i] + pol.coef_[i];
        }
        return sum;
    }

    Polynom_coef<T> operator-(const Polynom_coef<T> &pol) const {
        Polynom_coef<T> sum;
        if (coef_.size() >= pol.size()) sum = this;
        else {
            sum = pol;
            for (int i = coef_.size(); i < pol.size(); i++) sum.coef_[i] *= -1;
        }

        for (int i = 0; i < std::min(pol.size(), coef_.size()); i++) {
            sum.coef_[i] = coef_[i] - pol.coef_[i];
        }

        return sum;
    }

    Polynom_coef<T> &operator+=(const Polynom_coef<T> &pol) {
        if (coef_.size() >= pol.size()) {
            for (int i = 0; i < pol.size(); i++) coef_[i] += pol.coef_[i];
        } else {
            coef_.reserve(pol.size());
            for (int i = 0; i < coef_.size(); i++) coef_[i] += pol.coef_[i];
            for (int i = coef_.size(); i < pol.size(); i++) coef_.push_back(pol.coef_[i]);
        }
        return *this;
    }

    Polynom_coef<T> &operator-=(const Polynom_coef<T> &pol) {
        if (coef_.size() >= pol.size()) {
            for (int i = 0; i < pol.size(); i++) coef_[i] -= pol.coef_[i];
        } else {
            coef_.reserve(pol.size());
            for (int i = 0; i < coef_.size(); i++) coef_[i] -= pol.coef_[i];
            for (int i = coef_.size(); i < pol.size(); i++) coef_.push_back(-pol.coef_[i]);
        }
        return *this;
    }

    Polynom_coef<T> operator*(const Polynom_coef<T> &pol) const {
        Polynom_coef<T> prod(pol.size() + coef_.size() - 2);
        for (int i = 0; i < coef_.size(); i++) {
            for (int j = 0; j < pol.size(); j++) {
                if (i + j >= prod.size()) prod.coef_.push_back(coef_[i] * pol.coef_[j]);
                else prod.coef_[i + j] += coef_[i] * pol.coef_[j];
            }
        }
        return prod;
    }

    Polynom_coef<T> &operator*=(const Polynom_coef<T> &pol) {
        Polynom_coef<T> prod(pol.size() + coef_.size() - 2);
        for (int i = 0; i < coef_.size(); i++) {
            for (int j = 0; j < pol.size(); j++) {
                if (i + j >= prod.size()) prod.coef_.push_back(coef_[i] * pol.coef_[j]);
                else prod.coef_[i + j] += coef_[i] * pol.coef_[j];
            }
        }
        *this = prod;
        return *this;
    }


    Polynom_coef<T> derivative() const {
        Polynom_coef<T> der(coef_.size() - 1);
        for (int i = 0; i < coef_.size() - 1; i++) {
            der.coef_.push_back(coef_[i + 1] * (i + 1));
        }
        return der;
    }

    Polynom_coef<T> integral() const {
        Polynom_coef<T> integ(coef_.size() + 1);
        integ.coef_.push_back(0);
        for (int i = 0; i < coef_.size(); i++) {
            integ.coef_.push_back(coef_[i] / (i + 1));
        }
        return integ;
    }

    Polynom_coef<T> operator/(const Polynom_coef<T> &divisor) const {

        Polynom_coef<T> dividend = *this;
        Polynom_coef<T> quot(dividend.size() - divisor.size() + 1);
        for (int i = quot.coef_.capacity() - 1; i >= 0; i--) {
            T coef = dividend.coef_[dividend.size() - 1] / divisor.coef_[divisor.size() - 1];
            quot.coef_.push_back(coef);
            int new_size = 0;
            for (int j = 0; j < divisor.size(); j++) {
                dividend.coef_[dividend.size() - j - 1] -= divisor.coef_[divisor.size() - j - 1] * coef;
                if (dividend.coef_[dividend.size() - j - 1] != 0) new_size = std::max(new_size, dividend.size() - j);
            }
            dividend.coef_.resize(new_size);
        }
        for (int i = 0; i < quot.size() / 2; i++) std::swap(quot.coef_[i], quot.coef_[quot.size() - i - 1]);
        return quot;
    }

    friend std::ostream &operator<<(std::ostream &out, const Polynom_coef<T> &pol) {
        for (int i = 0; i < pol.size(); i++) {
            if (pol.coef_[i] >= 0) out << "+";
            out << pol.coef_[i] << "x^" << i;
        }
        return out;
    }

};

template<typename T>
class Sparse_polynom {
private:
    std::map<int, T> coef_;
public:
    Sparse_polynom(std::initializer_list<std::pair<int, T>> in_list) {
        for (auto it: in_list) coef_[it.first] = it.second;
    }

    Sparse_polynom() {};

    int non_zero() const {
        return coef_.size();
    }

    int degree() const {
        return coef_.end()->first;
    }

    void check_for_0() {
        for (auto it = coef_.begin(); it != coef_.end();) {
            if (it->second == 0) it = coef_.erase(it);
            else ++it;
        }
    }

    bool operator==(const Sparse_polynom<T> &pol) const {
        if (coef_.size() != pol.size()) return false;
        auto it1 = coef_.begin();
        auto it2 = pol.coef_.begin();
        for (it1; it1 != coef_.end(); ++it1, ++it2) {
            if (it1->first != it2->first || it1->second != it2->second) return false;
        }
        return true;
    }


    Sparse_polynom<T> operator+(const Sparse_polynom<T> &pol) const {
        Sparse_polynom<T> sum;
        for (auto &it: coef_) sum.coef_[it.first] = it.second;
        for (auto &it: pol.coef_) {
            auto search = sum.coef_.find(it.first);
            if (search == sum.coef_.end()) sum.coef_[it.first] = it.second;
            else sum.coef_[search->first] += it.second;
        }
        sum.check_for_0();
        return sum;
    }

    Sparse_polynom<T> operator-(const Sparse_polynom<T> &pol) const {
        Sparse_polynom<T> sum;
        for (auto &it: coef_) sum.coef_[it.first] = it.second;
        for (auto &it: pol.coef_) {
            auto search = sum.coef_.find(it.first);
            if (search == sum.coef_.end()) sum.coef_[it.first] = -(it.second);
            else sum.coef_[search->first] -= it.second;
        }
        sum.check_for_0();
        return sum;
    }

    Sparse_polynom<T> &operator+=(const Sparse_polynom<T> &pol) {
        for (auto &it: pol.coef_) {
            auto search = coef_.find(it.first);
            if (search == coef_.end()) coef_[it.first] = it.second;
            else coef_[search->first] += it.second;
        }
        check_for_0();
        return *this;
    }

    Sparse_polynom<T> &operator-=(const Sparse_polynom<T> &pol) {
        for (auto &it: pol.coef_) {
            auto search = coef_.find(it.first);
            if (search == coef_.end()) coef_[it.first] = -(it.second);
            else coef_[search->first] -= it.second;
        }
        check_for_0();
        return *this;
    }

    Sparse_polynom<T> operator*(const Sparse_polynom<T> &pol) const {
        Sparse_polynom<T> prod;
        for (auto &it1: coef_) {
            for (auto &it2: pol.coef_) {
                auto search = prod.coef_.find(it1.first + it2.first);
                if (search == prod.coef_.end()) prod.coef_[it1.first + it2.first] = it1.second * it2.second;
                else prod.coef_[search->first] += it1.second * it2.second;
            }
        }
        prod.check_for_0();
        return prod;
    }

    Sparse_polynom<T> &operator*=(const Sparse_polynom<T> &pol) {
        Sparse_polynom<T> prod;
        for (auto &it1: coef_) {
            for (auto &it2: pol.coef_) {
                auto search = prod.coef_.find(it1.first + it2.first);
                if (search == prod.coef_.end()) prod.coef_[it1.first + it2.first] = it1.second * it2.second;
                else prod.coef_[search->first] += it1.second * it2.second;
            }
        }
        prod.check_for_0();
        *this = prod;
        return *this;
    }


    Sparse_polynom<T> derivative() const {
        Sparse_polynom<T> der;
        for (auto &it: coef_) {
            if (it.first > 0) der.coef_[it.first - 1] = it.second * it.first;
        }
        return der;
    }

    Sparse_polynom<T> integral() const {
        Sparse_polynom<T> integ;
        for (auto &it: coef_) {
            integ.coef_[it.first + 1] = it.second / (it.first + 1);
        }
        return integ;
    }


    Sparse_polynom<T> operator/(const Sparse_polynom<T> &divisor) const {

        Sparse_polynom<T> dividend = *this;
        Sparse_polynom<T> quot;
        while ((--dividend.coef_.end())->first >= (--divisor.coef_.end())->first) {
            int i = (--dividend.coef_.end())->first - (--divisor.coef_.end())->first;
            quot.coef_[i] = (--dividend.coef_.end())->second / (--divisor.coef_.end())->second;
            Sparse_polynom<T> inter{{i, quot.coef_[i]}};
            dividend -= (divisor * inter);
            if (dividend.coef_.begin() == dividend.coef_.end()) break;
        }

        return quot;
    }

    friend std::ostream &operator<<(std::ostream &out, const Sparse_polynom<T> &pol) {
        for (auto &it: pol.coef_) {
            if (it.second >= 0) out << "+";
            out << it.second << "x^" << it.first;
        }
        return out;
    }

};


#endif //LETO_ZADACHKI_OT_KUZNETSOVA_POLYNOM_H
