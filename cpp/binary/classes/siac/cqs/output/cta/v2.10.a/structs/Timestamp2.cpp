#include "Timestamp2.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace siac::cqs::output::cta::v2_10_a {

Timestamp2::Timestamp2(std::chrono::seconds seconds, std::chrono::nanoseconds nanoseconds)
  : seconds_(seconds), nanoseconds_(nanoseconds) {}

std::chrono::seconds Timestamp2::seconds() const { return seconds_; }
void Timestamp2::set_seconds(std::chrono::seconds value) { seconds_ = value; }

std::chrono::nanoseconds Timestamp2::nanoseconds() const { return nanoseconds_; }
void Timestamp2::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::size_t Timestamp2::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("Timestamp2", wire_size, length);

    seconds_ = std::chrono::seconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    return offset;
}

std::size_t Timestamp2::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("Timestamp2", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(seconds_.count()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    return offset;
}

std::size_t Timestamp2::encoded_size() const {
    return wire_size;
}

void Timestamp2::print(std::ostream& out) const {
    out << "Timestamp2{";
    out << "seconds=";
    out << seconds_.count();
    out << ", nanoseconds=";
    out << nanoseconds_.count();
    out << '}';
}

bool Timestamp2::operator==(const Timestamp2& other) const {
    return seconds_ == other.seconds_
        && nanoseconds_ == other.nanoseconds_;
}

bool Timestamp2::operator!=(const Timestamp2& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const Timestamp2& value) {
    value.print(out);
    return out;
}

} // namespace siac::cqs::output::cta::v2_10_a
