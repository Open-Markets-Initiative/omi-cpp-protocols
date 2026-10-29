#include "PriorDayTradeDateAndTime.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace siac::cts::output::cta::v1_91 {

PriorDayTradeDateAndTime::PriorDayTradeDateAndTime(std::chrono::seconds seconds, std::chrono::nanoseconds nanoseconds)
  : seconds_(seconds), nanoseconds_(nanoseconds) {}

std::chrono::seconds PriorDayTradeDateAndTime::seconds() const { return seconds_; }
void PriorDayTradeDateAndTime::set_seconds(std::chrono::seconds value) { seconds_ = value; }

std::chrono::nanoseconds PriorDayTradeDateAndTime::nanoseconds() const { return nanoseconds_; }
void PriorDayTradeDateAndTime::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::size_t PriorDayTradeDateAndTime::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PriorDayTradeDateAndTime", wire_size, length);

    seconds_ = std::chrono::seconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    return offset;
}

std::size_t PriorDayTradeDateAndTime::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PriorDayTradeDateAndTime", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(seconds_.count()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    return offset;
}

std::size_t PriorDayTradeDateAndTime::encoded_size() const {
    return wire_size;
}

void PriorDayTradeDateAndTime::print(std::ostream& out) const {
    out << "PriorDayTradeDateAndTime{";
    out << "seconds=";
    out << seconds_.count();
    out << ", nanoseconds=";
    out << nanoseconds_.count();
    out << '}';
}

bool PriorDayTradeDateAndTime::operator==(const PriorDayTradeDateAndTime& other) const {
    return seconds_ == other.seconds_
        && nanoseconds_ == other.nanoseconds_;
}

bool PriorDayTradeDateAndTime::operator!=(const PriorDayTradeDateAndTime& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const PriorDayTradeDateAndTime& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v1_91
