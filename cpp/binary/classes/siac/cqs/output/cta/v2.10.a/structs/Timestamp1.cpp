#include "Timestamp1.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace siac::cqs::output::cta::v2_10_a {

Timestamp1::Timestamp1(std::chrono::seconds seconds, std::chrono::nanoseconds nanoseconds)
  : seconds_(seconds), nanoseconds_(nanoseconds) {}

std::chrono::seconds Timestamp1::seconds() const { return seconds_; }
void Timestamp1::set_seconds(std::chrono::seconds value) { seconds_ = value; }

std::chrono::nanoseconds Timestamp1::nanoseconds() const { return nanoseconds_; }
void Timestamp1::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::size_t Timestamp1::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("Timestamp1", wire_size, length);

    seconds_ = std::chrono::seconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    return offset;
}

std::size_t Timestamp1::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("Timestamp1", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(seconds_.count()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    return offset;
}

std::size_t Timestamp1::encoded_size() const {
    return wire_size;
}

void Timestamp1::print(std::ostream& out) const {
    out << "Timestamp1{";
    out << "seconds=";
    out << seconds_.count();
    out << ", nanoseconds=";
    out << nanoseconds_.count();
    out << '}';
}

bool Timestamp1::operator==(const Timestamp1& other) const {
    return seconds_ == other.seconds_
        && nanoseconds_ == other.nanoseconds_;
}

bool Timestamp1::operator!=(const Timestamp1& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const Timestamp1& value) {
    value.print(out);
    return out;
}

} // namespace siac::cqs::output::cta::v2_10_a
