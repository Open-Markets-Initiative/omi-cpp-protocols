#include "CompactOffer.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

CompactOffer::CompactOffer(Decimal compact_offer_price, std::uint16_t compact_offer_size, const std::array<std::byte, 2>& reserved_2, OfferCondition offer_condition)
  : compact_offer_price_(compact_offer_price), compact_offer_size_(compact_offer_size), reserved_2_(reserved_2), offer_condition_(offer_condition) {}

Decimal CompactOffer::compact_offer_price() const { return compact_offer_price_; }
void CompactOffer::set_compact_offer_price(Decimal value) { compact_offer_price_ = value; }

std::uint16_t CompactOffer::compact_offer_size() const { return compact_offer_size_; }
void CompactOffer::set_compact_offer_size(std::uint16_t value) { compact_offer_size_ = value; }

const std::array<std::byte, 2>& CompactOffer::reserved_2() const { return reserved_2_; }
std::array<std::byte, 2>& CompactOffer::reserved_2() { return reserved_2_; }
void CompactOffer::set_reserved_2(const std::array<std::byte, 2>& value) { reserved_2_ = value; }

OfferCondition CompactOffer::offer_condition() const { return offer_condition_; }
void CompactOffer::set_offer_condition(OfferCondition value) { offer_condition_ = value; }

std::size_t CompactOffer::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("CompactOffer", wire_size, length);

    compact_offer_price_ = Decimal(static_cast<std::int64_t>(wire::read_i16_le(data + offset)), -2);
    offset += 2;

    compact_offer_size_ = wire::read_u16_le(data + offset);
    offset += 2;

    wire::read_bytes(data + offset, reserved_2_.data(), 2);
    offset += 2;

    offer_condition_ = static_cast<OfferCondition>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t CompactOffer::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CompactOffer", wire_size, capacity);

    wire::write_i16_le(data + offset, static_cast<std::int16_t>(compact_offer_price_.mantissa()));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(compact_offer_size_));
    offset += 2;

    wire::write_bytes(data + offset, reserved_2_.data(), 2);
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(offer_condition_));
    offset += 1;

    return offset;
}

std::size_t CompactOffer::encoded_size() const {
    return wire_size;
}

void CompactOffer::print(std::ostream& out) const {
    out << "CompactOffer{";
    out << "compact_offer_price=";
    out << compact_offer_price_;
    out << ", compact_offer_size=";
    out << compact_offer_size_;
    out << ", reserved_2=";
    print::hex(out, reserved_2_.data(), reserved_2_.size());
    out << ", offer_condition=";
    out << offer_condition_;
    out << '}';
}

bool CompactOffer::operator==(const CompactOffer& other) const {
    return compact_offer_price_ == other.compact_offer_price_
        && compact_offer_size_ == other.compact_offer_size_
        && reserved_2_ == other.reserved_2_
        && offer_condition_ == other.offer_condition_;
}

bool CompactOffer::operator!=(const CompactOffer& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const CompactOffer& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
