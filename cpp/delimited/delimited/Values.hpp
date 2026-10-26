#pragma once

#include <array>
#include <charconv>
#include <chrono>
#include <cstdint>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "Encoding.hpp"

// The values a delimited line's fields are read into, as a row of its record type holds them, and
// how a row prints them. Text is a view of the line it was read from, valid while the line is.
namespace scaled::delimited::values {

// a field every line states: its value
template <typename T>
struct Required {
    T data{};

    void set(const T value) {
        data = value;
    }

    void reset() {
        data = T{};
    }

    bool has_value() const {
        return true;
    }

    const T& value() const {
        return data;
    }
};

// a field a line may leave empty: its value, none where it is empty
template <typename T>
struct Optional {
    std::optional<T> data;

    void set(const T value) {
        data = value;
    }

    void reset() {
        data.reset();
    }

    bool has_value() const {
        return data.has_value();
    }

    const T& value() const {
        return *data;
    }
};

// text every line states in a single byte encoding (Latin-1, Windows-1252): held decoded to UTF-8
template <encoding::Encoding Encoded>
struct RequiredText {
    std::string data;

    void set(const std::string_view bytes) {
        data.clear();
        encoding::decode(data, bytes, Encoded);
    }

    void reset() {
        data.clear();
    }

    bool has_value() const {
        return true;
    }

    const std::string& value() const {
        return data;
    }
};

// text a line may leave empty, in a single byte encoding: held decoded to UTF-8, none where it is empty
template <encoding::Encoding Encoded>
struct OptionalText {
    std::optional<std::string> data;

    void set(const std::string_view bytes) {
        data.emplace();
        encoding::decode(*data, bytes, Encoded);
    }

    void reset() {
        data.reset();
    }

    bool has_value() const {
        return data.has_value();
    }

    const std::string& value() const {
        return *data;
    }
};

// text, quoted
inline void text(std::ostream& out, const std::string_view value) {
    out << '"' << value << '"';
}

// an integer
inline void integer(std::ostream& out, const std::int64_t value) {
    out << value;
}

// a decimal's integer of its places, as the decimal it is: 1234500 of 4 places is 123.4500
inline void decimal(std::ostream& out, const std::int64_t value, const int places) {
    std::array<char, 24> digits{};
    auto magnitude = static_cast<std::uint64_t>(value);
    if (value < 0) {
        out << '-';
        magnitude = 0 - magnitude;
    }
    const auto result = std::to_chars(digits.data(), digits.data() + digits.size(), magnitude);
    const std::string_view written{ digits.data(), static_cast<std::size_t>(result.ptr - digits.data()) };
    const auto size = static_cast<int>(written.size());
    if (size <= places) {
        out << "0.";
        for (int zero = size; zero < places; ++zero) {
            out << '0';
        }
        out << written;
        return;
    }
    out << written.substr(0, static_cast<std::size_t>(size - places));
    if (places > 0) {
        out << '.' << written.substr(static_cast<std::size_t>(size - places));
    }
}

// a month or a day of a date, two digits
inline void two(std::ostream& out, const unsigned value) {
    if (value < 10) {
        out << '0';
    }
    out << value;
}

// a date, days since 1970-01-01, as yyyy-mm-dd
inline void date(std::ostream& out, const std::int32_t days) {
    const std::chrono::year_month_day day{ std::chrono::sys_days{ std::chrono::days{ days } } };
    out << static_cast<int>(day.year()) << '-';
    two(out, static_cast<unsigned>(day.month()));
    out << '-';
    two(out, static_cast<unsigned>(day.day()));
}

// a field's value through a printer, or null where the line left it empty
template <typename Value, typename Printer>
void print(std::ostream& out, const Value& field, Printer&& printer) {
    if (!field.has_value()) {
        out << "null";
        return;
    }
    printer(out, field.value());
}

}