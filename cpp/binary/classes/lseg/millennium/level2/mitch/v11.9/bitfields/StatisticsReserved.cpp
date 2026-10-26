#include "StatisticsReserved.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

StatisticsReserved::StatisticsReserved(std::uint8_t raw) : raw_(raw) {}

std::uint8_t StatisticsReserved::unused_8() const { return static_cast<std::uint8_t>((raw_ & static_cast<std::uint8_t>(0xFF)) >> 0); }
void StatisticsReserved::set_unused_8(std::uint8_t value) { raw_ = static_cast<std::uint8_t>((raw_ & ~static_cast<std::uint8_t>(0xFF)) | ((static_cast<std::uint8_t>(value) << 0) & static_cast<std::uint8_t>(0xFF))); }

std::uint8_t StatisticsReserved::raw() const { return raw_; }
void StatisticsReserved::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t StatisticsReserved::decode(const std::byte* data, std::size_t length) {
    wire::require("StatisticsReserved", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t StatisticsReserved::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("StatisticsReserved", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t StatisticsReserved::encoded_size() const {
    return wire_size;
}

void StatisticsReserved::print(std::ostream& out) const {
    out << "StatisticsReserved{";
    out << "unused_8=";
    out << static_cast<unsigned long long>(unused_8());
    out << '}';
}

bool StatisticsReserved::operator==(const StatisticsReserved& other) const {
    return raw_ == other.raw_;
}

bool StatisticsReserved::operator!=(const StatisticsReserved& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const StatisticsReserved& value) {
    value.print(out);
    return out;
}

} // namespace lseg::millennium::level2::mitch::v11_9
