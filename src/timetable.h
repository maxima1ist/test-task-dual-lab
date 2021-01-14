#pragma once

#include <iostream>
#include <string>

using std::istream;
using std::ostream;
using std::string;

namespace timetable {

    class TimeFormatException : public std::exception {
    public:
        const string MASSAGE = "Incorrect time format!";
        const char* what() const noexcept override;
    };

    class Time {
    private:
        int16_t hour, minute;

    public:
        Time() noexcept;
        Time(const Time&) noexcept = default;

        bool operator==(const Time&) const noexcept;
        bool operator<(const Time&) const noexcept;
        bool operator>(const Time&) const noexcept;
        bool operator<=(const Time&) const noexcept;
        bool operator>=(const Time&) const noexcept;

        int16_t getTotalInMinutes() const noexcept;

        static string digitToTimeStr(int16_t);

        friend istream& operator>>(istream&, Time&);
        friend ostream& operator<<(ostream&, const Time&);
    };

    class TransportService {
    private:
        Time start, finish;
        bool inMidnight;

    public:
        const int16_t TOTAL_MINUTES_IN_DAY = 24 * 60;

        TransportService() noexcept;
        explicit TransportService(const Time&, const Time&) noexcept;

        bool operator<(const TransportService&) const noexcept;

        int16_t getDurationInMinutes() const noexcept;

        bool isTheSameRange(const TransportService&) const noexcept;
        bool isInsideOfRange(const TransportService&) const noexcept;

        friend istream& operator>>(istream&, TransportService&);
        friend ostream& operator<<(ostream&, const TransportService&);
    };

} //timetable