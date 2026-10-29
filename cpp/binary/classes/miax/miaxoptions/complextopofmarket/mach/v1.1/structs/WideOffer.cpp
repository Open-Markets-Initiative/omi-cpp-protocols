#include "WideOffer.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

WideOffer::WideOffer(Decimal wide_offer_price, std::uint32_t wide_offer_size, const std::array<std::byte, 4>& reserved_4, OfferCondition offer_condition)
  : wide_offer_price_(wide_offer_price), wide_offer_size_(wide_offer_size), reserved_4_(reserved_4), offer_condition_(offer_condition) {}

Decimal WideOffer::wide_offer_price() const { return wide_offer_price_; }
void WideOffer::set_wide_offer_price(Decimal value) { wide_offer_price_ = value; }

std::uint32_t WideOffer::wide_offer_size() const { return wide_offer_size_; }
void WideOffer::set_wide_offer_size(std::uint32_t value) { wide_offer_size_ = value; }

const std::array<std::byte, 4>& WideOffer::reserved_4() const { return reserved_4_; }
std::array<std::byte, 4>& WideOffer::reserved_4() { return reserved_4_; }
void WideOffer::set_reserved_4(const std::array<std::byte, 4>& value) { reserved_4_ = value; }

OfferCondition WideOffer::offer_condition() const { return offer_condition_; }
void WideOffer::set_offer_condition(OfferCondition value) { offer_condition_ = value; }

std::size_t WideOffer::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("WideOffer", wire_size, length);

    wide_offer_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    wide_offer_size_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::read_bytes(data + offset, reserved_4_.data(), 4);
    offset += 4;

    offer_condition_ = static_cast<OfferCondition>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t WideOffer::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("WideOffer", wire_size, capacity);

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(wide_offer_price_.mantissa()));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(wide_offer_size_));
    offset += 4;

    wire::write_bytes(data + offset, reserved_4_.data(), 4);
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(offer_condition_));
    offset += 1;

    return offset;
}

std::size_t WideOffer::encoded_size() const {
    return wire_size;
}

void WideOffer::print(std::ostream& out) const {
    out << "WideOffer{";
    out << "wide_offer_price=";
    out << wide_offer_price_;
    out << ", wide_offer_size=";
    out << wide_offer_size_;
    out << ", reserved_4=";
    print::hex(out, reserved_4_.data(), reserved_4_.size());
    out << ", offer_condition=";
    out << offer_condition_;
    out << '}';
}

bool WideOffer::operator==(const WideOffer& other) const {
    return wide_offer_price_ == other.wide_offer_price_
        && wide_offer_size_ == other.wide_offer_size_
        && reserved_4_ == other.reserved_4_
        && offer_condition_ == other.offer_condition_;
}

bool WideOffer::operator!=(const WideOffer& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const WideOffer& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
