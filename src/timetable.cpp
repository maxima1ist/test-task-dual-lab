#include "timetable.h"

namespace timetable {

    //TimeFormatException
    const char* TimeFormatException::what() const noexcept {
        return MASSAGE.c_str();
    }
    //TimeFormatException

    //Time
    Time::Time() noexcept: hour(0), minute(0) {}

    bool Time::operator==(const Time& other) const noexcept {
        return hour == other.hour && minute == other.minute;
    }

    bool Time::operator<(const Time& other) const noexcept {
        if (hour == other.hour) {
            return minute < other.minute;
        } else {
            return hour < other.hour;
        }
    }

    bool Time::operator>(const Time& other) const noexcept {
        if (hour == other.hour) {
            return minute > other.minute;
        } else {
            return hour > other.hour;
        }
    }

    bool Time::operator<=(const Time& other) const noexcept {
        return !(*this > other);
    }

    bool Time::operator>=(const Time& other) const noexcept {
        return !(*this < other);
    }

    string Time::digitToTimeStr(int16_t digit) {
        if (digit < 0 || digit >= 100) {
            throw TimeFormatException();
        }
        return digit < 10 ? "0" + std::to_string(digit) : std::to_string(digit);
    }

    istream& operator>>(istream& in, Time& t) {
        in >> t.hour;
        in.ignore();
        in >> t.minute;
        if (t.hour < 0 || t.hour >= 24 || t.minute < 0 || t.minute >= 60) {
            throw TimeFormatException();
        }
        return in;
    }

    ostream& operator<<(ostream& out, const Time& t) {
        out << Time::digitToTimeStr(t.hour) << ':' << Time::digitToTimeStr(t.minute);
        return out;
    }
    //Time

    //TransportService
    TransportService::TransportService() noexcept: start(), finish() {}
    TransportService::TransportService(const Time& start, const Time& finish) noexcept: start(start), finish(finish) {}

    bool TransportService::operator<(const TransportService& other) const noexcept {
        if (start == other.start) {
            return finish < other.finish;
        } else {
            return start < other.start;
        }
    }

    bool TransportService::isTheSameRange(const TransportService& other) const noexcept {
        return start == other.start && finish == other.finish;
    }

    bool TransportService::isInsideOfRange(const TransportService& other) const noexcept {
        return start <= other.start && other.finish <= finish;
    }

    istream& operator>>(istream& in, TransportService& transportService) {
        in >> transportService.start >> transportService.finish;
        return in;
    }

    ostream& operator<<(ostream& out, const TransportService& transportService) {
        out << transportService.start << ' ' << transportService.finish;
        return out;
    }
    //TransportService

} //timetable