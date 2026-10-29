#include "SendTime.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace nyse::nyseequities::bbo::xdp::v2_4_g {

SendTime::SendTime(std::chrono::seconds seconds, std::chrono::nanoseconds nanoseconds)
  : seconds_(seconds), nanoseconds_(nanoseconds) {}

std::chrono::seconds SendTime::seconds() const { return seconds_; }
void SendTime::set_seconds(std::chrono::seconds value) { seconds_ = value; }

std::chrono::nanoseconds SendTime::nanoseconds() const { return nanoseconds_; }
void SendTime::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::size_t SendTime::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SendTime", wire_size, length);

    seconds_ = std::chrono::seconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    return offset;
}

std::size_t SendTime::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SendTime", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(seconds_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    return offset;
}

std::size_t SendTime::encoded_size() const {
    return wire_size;
}

void SendTime::print(std::ostream& out) const {
    out << "SendTime{";
    out << "seconds=";
    out << seconds_.count();
    out << ", nanoseconds=";
    out << nanoseconds_.count();
    out << '}';
}

bool SendTime::operator==(const SendTime& other) const {
    return seconds_ == other.seconds_
        && nanoseconds_ == other.nanoseconds_;
}

bool SendTime::operator!=(const SendTime& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SendTime& value) {
    value.print(out);
    return out;
}

} // namespace nyse::nyseequities::bbo::xdp::v2_4_g
