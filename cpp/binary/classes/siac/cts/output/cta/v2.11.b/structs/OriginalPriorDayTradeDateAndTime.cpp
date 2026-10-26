#include "OriginalPriorDayTradeDateAndTime.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace siac::cts::output::cta::v2_11_b {

OriginalPriorDayTradeDateAndTime::OriginalPriorDayTradeDateAndTime(std::chrono::seconds seconds, std::chrono::nanoseconds nanoseconds)
  : seconds_(seconds), nanoseconds_(nanoseconds) {}

std::chrono::seconds OriginalPriorDayTradeDateAndTime::seconds() const { return seconds_; }
void OriginalPriorDayTradeDateAndTime::set_seconds(std::chrono::seconds value) { seconds_ = value; }

std::chrono::nanoseconds OriginalPriorDayTradeDateAndTime::nanoseconds() const { return nanoseconds_; }
void OriginalPriorDayTradeDateAndTime::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::size_t OriginalPriorDayTradeDateAndTime::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OriginalPriorDayTradeDateAndTime", wire_size, length);

    seconds_ = std::chrono::seconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    return offset;
}

std::size_t OriginalPriorDayTradeDateAndTime::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OriginalPriorDayTradeDateAndTime", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(seconds_.count()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    return offset;
}

std::size_t OriginalPriorDayTradeDateAndTime::encoded_size() const {
    return wire_size;
}

void OriginalPriorDayTradeDateAndTime::print(std::ostream& out) const {
    out << "OriginalPriorDayTradeDateAndTime{";
    out << "seconds=";
    out << seconds_.count();
    out << ", nanoseconds=";
    out << nanoseconds_.count();
    out << '}';
}

bool OriginalPriorDayTradeDateAndTime::operator==(const OriginalPriorDayTradeDateAndTime& other) const {
    return seconds_ == other.seconds_
        && nanoseconds_ == other.nanoseconds_;
}

bool OriginalPriorDayTradeDateAndTime::operator!=(const OriginalPriorDayTradeDateAndTime& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const OriginalPriorDayTradeDateAndTime& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_11_b
