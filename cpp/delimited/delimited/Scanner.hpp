#pragma once

#include <algorithm>
#include <array>
#include <charconv>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <limits>
#include <optional>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

namespace scaled::delimited {

struct Error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

// a line's fields, the record type first: views into the line
using Fields = std::vector<std::string_view>;

// a line split at every delimiter: n delimiters make n + 1 fields, and two
// side by side an empty one between them
inline void split(const std::string_view line, const char delimiter, Fields& fields) {
    fields.clear();
    std::size_t start = 0;
    for (auto at = line.find(delimiter); at != std::string_view::npos; at = line.find(delimiter, start)) {
        fields.push_back(line.substr(start, at - start));
        start = at + 1;
    }
    fields.push_back(line.substr(start));
}

// a line split at every delimiter outside quotes: a field that starts with
// the quote runs to the quote closing it, a doubled quote inside being one
// quote (held in unquoted, which the views of such fields point into). A line
// holding no quote is split plainly
inline void split(const std::string_view line, const char delimiter, const char quote, Fields& fields, std::deque<std::string>& unquoted) {
    if (line.find(quote) == std::string_view::npos) {
        split(line, delimiter, fields);
        return;
    }

    fields.clear();
    unquoted.clear();
    std::size_t at = 0;
    for (;;) {
        if (at < line.size() && line[at] == quote) {
            std::string text;
            bool doubled = false;
            auto next = at + 1;
            for (;;) {
                const auto close = line.find(quote, next);
                if (close == std::string_view::npos) {
                    throw Error{ "a quoted field is not closed" };
                }
                text.append(line.substr(next, close - next));
                if (close + 1 < line.size() && line[close + 1] == quote) {
                    text.push_back(quote);
                    doubled = true;
                    next = close + 2;
                    continue;
                }
                next = close + 1;
                break;
            }

            if (doubled) {
                unquoted.push_back(std::move(text));
                fields.push_back(unquoted.back());
            }
            else {
                fields.push_back(line.substr(at + 1, next - at - 2));
            }

            if (next == line.size()) {
                return;
            }
            if (line[next] != delimiter) {
                throw Error{ "a quoted field is followed by text before its delimiter" };
            }
            at = next + 1;
            continue;
        }

        const auto end = line.find(delimiter, at);
        if (end == std::string_view::npos) {
            fields.push_back(line.substr(at));
            return;
        }
        fields.push_back(line.substr(at, end - at));
        at = end + 1;
    }
}

// a field's name and text, for an error
inline std::string quote(const std::string_view name, const std::string_view text) {
    return std::string{ name } + " '" + std::string{ text } + "'";
}

// a record type's line has as many fields as its layout, the record type
// included; record names the record (its letter, or a csv record's name)
inline void expect(const Fields& fields, const std::size_t count, const std::string_view record) {
    if (fields.size() != count) {
        throw Error{ std::string{ record } + ": the line has " + std::to_string(fields.size()) + " fields, its layout " + std::to_string(count) };
    }
}

// a record type's line whose last fields are optional: as many fields as its
// layout, or fewer down to the minimum, the fields it stops before absent
inline void expect(const Fields& fields, const std::size_t minimum, const std::size_t count, const std::string_view record) {
    if (fields.size() < minimum || fields.size() > count) {
        throw Error{ std::string{ record } + ": the line has " + std::to_string(fields.size()) + " fields, its layout " + std::to_string(count)
            + " (" + std::to_string(minimum) + " up to its optional last fields)" };
    }
}

// a field a line may stop before: its text, empty when the line is shorter
inline std::string_view at(const Fields& fields, const std::size_t position) {
    if (position < fields.size()) {
        return fields[position];
    }
    return {};
}

// a header line a layout variant states, from the model's header records:
// its record's name, the prefix its line starts with, the delimiter its
// fields are split at after the prefix, whether it is split once (a
// name=value pair, the value holding the rest of the line), and each field's
// constant text, its key first (a layout's letter, a property's name)
struct Expected {
    std::string_view name;
    std::string_view prefix;
    char delimiter;
    bool pair;
    std::span<const std::string_view> constants;
};

// how a file's header differs from a variant's: the fields that match (the
// closest variant matches most), and the first difference - the line, the
// position after its prefix, the text the variant expects and the text found
struct Difference {
    std::size_t matched = 0;
    bool differs = false;
    std::string line;
    std::size_t position = 0;
    std::string expected;
    std::string found;
};

// a header line's fields after its prefix, as the header line it is splits them
inline void header_fields(const std::string_view line, const Expected& expected, Fields& fields) {
    const auto text = line.substr(expected.prefix.size());
    if (!expected.pair) {
        split(text, expected.delimiter, fields);
        return;
    }
    fields.clear();
    const auto at = text.find(expected.delimiter);
    if (at == std::string_view::npos) {
        fields.push_back(text);
        return;
    }
    fields.push_back(text.substr(0, at));
    fields.push_back(text.substr(at + 1));
}

// a file's header lines against a variant's header: each line is the header
// line its prefix and key name, its fields each that line's constant, position
// by position; each header line of the variant is stated once, and every one
// of them unless each table states its own (a file may hold only some tables)
template <std::size_t N>
Difference compare(const std::vector<std::string>& lines, const std::array<Expected, N>& header, const bool every) {
    Difference difference;
    const auto differ = [&](const std::string& line, const std::size_t position, const std::string_view expected, const std::string_view found) {
        if (difference.differs) {
            return;
        }
        difference.differs = true;
        difference.line = line;
        difference.position = position;
        difference.expected = expected;
        difference.found = found;
    };

    std::array<bool, N> stated{};
    Fields fields;
    for (const auto& line : lines) {
        bool known = false;
        for (std::size_t index = 0; index < N && !known; ++index) {
            const auto& expected = header[index];
            if (!line.starts_with(expected.prefix)) {
                continue;
            }
            header_fields(line, expected, fields);
            if (fields[0] != expected.constants[0]) {
                continue;
            }

            known = true;
            const auto named = std::string{ expected.prefix } + std::string{ expected.constants[0] };
            if (stated[index]) {
                differ(named, 0, "one line", "a second");
                continue;
            }
            stated[index] = true;

            const auto count = std::max(fields.size(), expected.constants.size());
            for (std::size_t position = 0; position < count; ++position) {
                std::string_view want = "nothing";
                std::string_view got = "nothing";
                if (position < expected.constants.size()) {
                    want = expected.constants[position];
                }
                if (position < fields.size()) {
                    got = fields[position];
                }
                if (position < expected.constants.size() && position < fields.size() && want == got) {
                    ++difference.matched;
                    continue;
                }
                differ(named, position, want, got);
            }
        }
        if (!known) {
            differ(line, 0, "no such header line", line);
        }
    }

    for (std::size_t index = 0; index < N && every; ++index) {
        if (!stated[index]) {
            differ(std::string{ header[index].prefix } + std::string{ header[index].constants[0] }, 0, std::string{ header[index].name }, "no such line");
        }
    }
    return difference;
}

// the variant whose header the file states exactly: refused naming the model,
// and for the closest variant (the most fields matched) its first difference
template <std::size_t N>
std::size_t select(const std::array<Difference, N>& differences, const std::array<std::string_view, N>& variants, const std::string_view model) {
    std::size_t closest = 0;
    for (std::size_t index = 0; index < N; ++index) {
        if (!differences[index].differs) {
            return index;
        }
        if (differences[index].matched > differences[closest].matched) {
            closest = index;
        }
    }

    const auto& difference = differences[closest];
    throw Error{ "its header is no layout of " + std::string{ model } + "; the closest, " + std::string{ variants[closest] }
        + ", differs at " + difference.line + " position " + std::to_string(difference.position)
        + ": expected " + difference.expected + ", found " + difference.found };
}

// an integer's text, exactly: decimal digits, a minus sign first for a signed
// type; refused when the type cannot hold it
template <typename T>
T integer(const std::string_view text, const std::string_view name) {
    T value{};
    const auto end = text.data() + text.size();
    const auto [at, error] = std::from_chars(text.data(), end, value);
    if (error == std::errc::result_out_of_range) {
        throw Error{ quote(name, text) + " overflows its record field" };
    }
    if (error != std::errc{} || at != end) {
        throw Error{ quote(name, text) + " is not an integer" };
    }
    return value;
}

// a decimal's digits scaled by 10^scale, and its sign
struct Scaled {
    std::uint64_t magnitude;
    bool negative;
};

// a decimal's text (-12.345, 8768, .5) scaled by 10^scale, exactly, with no
// floating point. Places beyond the scale are refused unless they are zeros,
// and so is a magnitude above the limit
inline Scaled scaled(const std::string_view text, const int scale, const std::uint64_t limit, const std::string_view name) {
    auto rest = text;
    Scaled value{ 0, false };
    if (!rest.empty() && rest.front() == '-') {
        value.negative = true;
        rest.remove_prefix(1);
    }

    const auto point = rest.find('.');
    const auto whole = rest.substr(0, point);
    std::string_view fraction;
    if (point != std::string_view::npos) {
        fraction = rest.substr(point + 1);
    }
    if (whole.empty() && fraction.empty()) {
        throw Error{ quote(name, text) + " is not a decimal" };
    }

    const auto places = static_cast<std::size_t>(scale);
    while (fraction.size() > places && fraction.back() == '0') {
        fraction.remove_suffix(1);
    }
    if (fraction.size() > places) {
        throw Error{ quote(name, text) + " has " + std::to_string(fraction.size()) + " decimal places, its record field " + std::to_string(scale) };
    }

    const auto digit = [&](const char c) {
        if (c < '0' || c > '9') {
            throw Error{ quote(name, text) + " is not a decimal" };
        }
        const auto next = static_cast<std::uint64_t>(c - '0');
        if (value.magnitude > (limit - next) / 10) {
            throw Error{ quote(name, text) + " overflows its record field" };
        }
        value.magnitude = value.magnitude * 10 + next;
    };
    for (const char c : whole) {
        digit(c);
    }
    for (const char c : fraction) {
        digit(c);
    }
    for (auto place = fraction.size(); place < places; ++place) {
        digit('0');
    }
    return value;
}

// a decimal as a signed integer of 10^-scale; the smallest int64, a field's
// null value, is never a reading
inline std::int64_t decimal(const std::string_view text, const int scale, const std::string_view name) {
    const auto value = scaled(text, scale, static_cast<std::uint64_t>(std::numeric_limits<std::int64_t>::max()), name);
    if (value.negative) {
        return -static_cast<std::int64_t>(value.magnitude);
    }
    return static_cast<std::int64_t>(value.magnitude);
}

// a Unix timestamp's text in its unit, `places` the decimal places from that
// unit down to nanoseconds (seconds 9), as Unix nanoseconds; the largest uint64,
// a field's null value, is never a reading
inline std::uint64_t unix_nanoseconds(const std::string_view text, const int places, const std::string_view name) {
    const auto value = scaled(text, places, std::numeric_limits<std::uint64_t>::max() - 1, name);
    if (value.negative && value.magnitude != 0) {
        throw Error{ quote(name, text) + " is before 1970" };
    }
    return value.magnitude;
}

// a record's clock, a Unix timestamp as signed Unix nanoseconds; empty when its field is
inline std::optional<std::int64_t> clock(const std::string_view text, const int places, const std::string_view name) {
    if (text.empty()) {
        return std::nullopt;
    }
    const auto value = scaled(text, places, static_cast<std::uint64_t>(std::numeric_limits<std::int64_t>::max()), name);
    if (value.negative) {
        return -static_cast<std::int64_t>(value.magnitude);
    }
    return static_cast<std::int64_t>(value.magnitude);
}

// a boolean's text, 0 or 1
inline std::uint8_t boolean(const std::string_view text, const std::string_view name) {
    if (text == "0") {
        return 0;
    }
    if (text == "1") {
        return 1;
    }
    throw Error{ quote(name, text) + " is not 0 or 1" };
}

// digits as a number
inline std::int64_t digits(const std::string_view text, const std::string_view whole, const std::string_view name) {
    std::int64_t value = 0;
    for (const char c : text) {
        if (c < '0' || c > '9') {
            throw Error{ quote(name, whole) + " is not all digits" };
        }
        value = value * 10 + (c - '0');
    }
    return value;
}

// a yyyymmdd date as days since 1970-01-01
inline std::int64_t days(const std::string_view text, const std::string_view name) {
    if (text.size() != 8) {
        throw Error{ quote(name, text) + " is not a yyyymmdd date" };
    }
    const std::chrono::year_month_day date{
        std::chrono::year{ static_cast<int>(digits(text.substr(0, 4), text, name)) },
        std::chrono::month{ static_cast<unsigned>(digits(text.substr(4, 2), text, name)) },
        std::chrono::day{ static_cast<unsigned>(digits(text.substr(6, 2), text, name)) } };
    if (!date.ok()) {
        throw Error{ quote(name, text) + " is not a date" };
    }
    return std::chrono::sys_days{ date }.time_since_epoch().count();
}

// a time of day, HHMMSS then `fraction` digits of a second, its leading zeros
// dropped (72000012 is 07:20:00.012), as nanoseconds after midnight
inline std::int64_t time_of_day(const std::string_view text, const int fraction, const std::string_view name) {
    if (text.empty() || text.size() > static_cast<std::size_t>(6 + fraction)) {
        throw Error{ quote(name, text) + " is not a time of day" };
    }

    std::int64_t unit = 1;
    for (int place = 0; place < fraction; ++place) {
        unit *= 10;
    }

    const auto value = digits(text, text, name);
    auto part = value % unit;
    const auto clock = value / unit;
    const auto seconds = clock % 100;
    const auto minutes = clock / 100 % 100;
    const auto hours = clock / 10'000;
    if (hours > 23 || minutes > 59 || seconds > 59) {
        throw Error{ quote(name, text) + " is not a time of day" };
    }

    for (int place = fraction; place < 9; ++place) {
        part *= 10;
    }
    return ((hours * 60 + minutes) * 60 + seconds) * 1'000'000'000 + part;
}

}