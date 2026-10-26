#include "ExpirationBlock.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace siac::opra::output::obi::v6_2 {

ExpirationBlock::ExpirationBlock(ExpirationMonth expiration_month, std::uint8_t expiration_day, std::uint8_t expiration_year)
  : expiration_month_(expiration_month), expiration_day_(expiration_day), expiration_year_(expiration_year) {}

ExpirationMonth ExpirationBlock::expiration_month() const { return expiration_month_; }
void ExpirationBlock::set_expiration_month(ExpirationMonth value) { expiration_month_ = value; }

std::uint8_t ExpirationBlock::expiration_day() const { return expiration_day_; }
void ExpirationBlock::set_expiration_day(std::uint8_t value) { expiration_day_ = value; }

std::uint8_t ExpirationBlock::expiration_year() const { return expiration_year_; }
void ExpirationBlock::set_expiration_year(std::uint8_t value) { expiration_year_ = value; }

std::size_t ExpirationBlock::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ExpirationBlock", wire_size, length);

    expiration_month_ = static_cast<ExpirationMonth>(wire::read_char(data + offset));
    offset += 1;

    expiration_day_ = wire::read_u8(data + offset);
    offset += 1;

    expiration_year_ = wire::read_u8(data + offset);
    offset += 1;

    return offset;
}

std::size_t ExpirationBlock::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ExpirationBlock", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(expiration_month_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(expiration_day_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(expiration_year_));
    offset += 1;

    return offset;
}

std::size_t ExpirationBlock::encoded_size() const {
    return wire_size;
}

void ExpirationBlock::print(std::ostream& out) const {
    out << "ExpirationBlock{";
    out << "expiration_month=";
    out << expiration_month_;
    out << ", expiration_day=";
    out << static_cast<int>(expiration_day_);
    out << ", expiration_year=";
    out << static_cast<int>(expiration_year_);
    out << '}';
}

bool ExpirationBlock::operator==(const ExpirationBlock& other) const {
    return expiration_month_ == other.expiration_month_
        && expiration_day_ == other.expiration_day_
        && expiration_year_ == other.expiration_year_;
}

bool ExpirationBlock::operator!=(const ExpirationBlock& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const ExpirationBlock& value) {
    value.print(out);
    return out;
}

} // namespace siac::opra::output::obi::v6_2
