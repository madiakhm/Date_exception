#include <iostream>
#include <stdexcept>

class Date
{
private:
    int year, month, day;

    static bool IsLeapYear(int y) {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    static int DaysInMonth(int y, int m) {
        static int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (m == 2 && IsLeapYear(y)) {
            return 29;
        }
        return days[m - 1];
    }

public:
    Date(int y, int m, int d) : year(y), month(m), day(d) {
        Normalize();
    }

    Date(int days) {
        year = 1;
        month = 1;
        day = days;
        Normalize();
    }

    Date& operator+=(int days) {
        day += days;
        Normalize();
        return *this;
    }

    Date& operator-=(int days) {
        day -= days;
        Normalize();
        return *this;
    }

    Date operator+(int days) const {
        Date result(*this);
        result += days;
        return result;
    }

    Date operator-(int days) const {
        Date result(*this);
        result -= days;
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const Date& date) {
        os << date.year << "-" << date.month << "-" << date.day;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Date& date) {
        is >> date.year >> date.month >> date.day;
        date.Normalize();
        return is;
    }

private:
    void Normalize() {
        while (day < 1) {
            if (month == 1) {
                --year;
                month = 12;
            }
            else {
                --month;
            }
            day += DaysInMonth(year, month);
        }
        while (day > DaysInMonth(year, month)) {
            day -= DaysInMonth(year, month);
            if (month == 12) {
                ++year;
                month = 1;
            }
            else {
                ++month;
            }
        }
    }
};

int main()
{
    try
    {
        Date d1(2022, 2, 28);
        std::cout << d1 << std::endl;
        d1 += 3;
        std::cout << d1 << std::endl;
        Date d2(365);
        std::cout << d2 << std::endl;
        d2 -= 365;
        std::cout << d2 << std::endl;
        Date d3(2021, 12, 31);
        std::cout << d3 + 1 << std::endl;
        std::cout << d3 - 1 << std::endl;
        Date d4(0);
        std::cout << "Enter a date in the format yyyy mm dd: ";
        std::cin >> d4;
        std::cout << "You entered: " << d4 << std::endl;
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}