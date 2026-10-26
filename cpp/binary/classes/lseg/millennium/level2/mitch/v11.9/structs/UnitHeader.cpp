#include "UnitHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

UnitHeader::UnitHeader(std::uint16_t length, std::uint8_t message_count, char market_data_group, std::uint32_t sequence_number)
  : length_(length), message_count_(message_count), market_data_group_(market_data_group), sequence_number_(sequence_number) {}

std::uint16_t UnitHeader::length() const { return length_; }
void UnitHeader::set_length(std::uint16_t value) { length_ = value; }

std::uint8_t UnitHeader::message_count() const { return message_count_; }
void UnitHeader::set_message_count(std::uint8_t value) { message_count_ = value; }

char UnitHeader::market_data_group() const { return market_data_group_; }
void UnitHeader::set_market_data_group(char value) { market_data_group_ = value; }

std::uint32_t UnitHeader::sequence_number() const { return sequence_number_; }
void UnitHeader::set_sequence_number(std::uint32_t value) { sequence_number_ = value; }

std::size_t UnitHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UnitHeader", wire_size, length);

    length_ = wire::read_u16_le(data + offset);
    offset += 2;

    message_count_ = wire::read_u8(data + offset);
    offset += 1;

    market_data_group_ = wire::read_char(data + offset);
    offset += 1;

    sequence_number_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t UnitHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UnitHeader", wire_size, capacity);

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(length_));
    offset += 2;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(message_count_));
    offset += 1;

    wire::write_char(data + offset, market_data_group_);
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(sequence_number_));
    offset += 4;

    return offset;
}

std::size_t UnitHeader::encoded_size() const {
    return wire_size;
}

void UnitHeader::print(std::ostream& out) const {
    out << "UnitHeader{";
    out << "length=";
    out << length_;
    out << ", message_count=";
    out << static_cast<int>(message_count_);
    out << ", market_data_group=";
    print::character(out, market_data_group_);
    out << ", sequence_number=";
    out << sequence_number_;
    out << '}';
}

bool UnitHeader::operator==(const UnitHeader& other) const {
    return length_ == other.length_
        && message_count_ == other.message_count_
        && market_data_group_ == other.market_data_group_
        && sequence_number_ == other.sequence_number_;
}

bool UnitHeader::operator!=(const UnitHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const UnitHeader& value) {
    value.print(out);
    return out;
}

} // namespace lseg::millennium::level2::mitch::v11_9
