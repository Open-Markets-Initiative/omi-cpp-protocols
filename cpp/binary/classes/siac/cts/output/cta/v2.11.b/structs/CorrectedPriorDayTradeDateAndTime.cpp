#include "CorrectedPriorDayTradeDateAndTime.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace siac::cts::output::cta::v2_11_b {

CorrectedPriorDayTradeDateAndTime::CorrectedPriorDayTradeDateAndTime(std::chrono::seconds seconds, std::chrono::nanoseconds nanoseconds)
  : seconds_(seconds), nanoseconds_(nanoseconds) {}

std::chrono::seconds CorrectedPriorDayTradeDateAndTime::seconds() const { return seconds_; }
void CorrectedPriorDayTradeDateAndTime::set_seconds(std::chrono::seconds value) { seconds_ = value; }

std::chrono::nanoseconds CorrectedPriorDayTradeDateAndTime::nanoseconds() const { return nanoseconds_; }
void CorrectedPriorDayTradeDateAndTime::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::size_t CorrectedPriorDayTradeDateAndTime::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("CorrectedPriorDayTradeDateAndTime", wire_size, length);

    seconds_ = std::chrono::seconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    return offset;
}

std::size_t CorrectedPriorDayTradeDateAndTime::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CorrectedPriorDayTradeDateAndTime", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(seconds_.count()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    return offset;
}

std::size_t CorrectedPriorDayTradeDateAndTime::encoded_size() const {
    return wire_size;
}

void CorrectedPriorDayTradeDateAndTime::print(std::ostream& out) const {
    out << "CorrectedPriorDayTradeDateAndTime{";
    out << "seconds=";
    out << seconds_.count();
    out << ", nanoseconds=";
    out << nanoseconds_.count();
    out << '}';
}

bool CorrectedPriorDayTradeDateAndTime::operator==(const CorrectedPriorDayTradeDateAndTime& other) const {
    return seconds_ == other.seconds_
        && nanoseconds_ == other.nanoseconds_;
}

bool CorrectedPriorDayTradeDateAndTime::operator!=(const CorrectedPriorDayTradeDateAndTime& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const CorrectedPriorDayTradeDateAndTime& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_11_b
