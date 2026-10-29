#include "WideBid.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

WideBid::WideBid(Decimal wide_bid_price, std::uint32_t wide_bid_size, const std::array<std::byte, 4>& reserved_4, BidCondition bid_condition)
  : wide_bid_price_(wide_bid_price), wide_bid_size_(wide_bid_size), reserved_4_(reserved_4), bid_condition_(bid_condition) {}

Decimal WideBid::wide_bid_price() const { return wide_bid_price_; }
void WideBid::set_wide_bid_price(Decimal value) { wide_bid_price_ = value; }

std::uint32_t WideBid::wide_bid_size() const { return wide_bid_size_; }
void WideBid::set_wide_bid_size(std::uint32_t value) { wide_bid_size_ = value; }

const std::array<std::byte, 4>& WideBid::reserved_4() const { return reserved_4_; }
std::array<std::byte, 4>& WideBid::reserved_4() { return reserved_4_; }
void WideBid::set_reserved_4(const std::array<std::byte, 4>& value) { reserved_4_ = value; }

BidCondition WideBid::bid_condition() const { return bid_condition_; }
void WideBid::set_bid_condition(BidCondition value) { bid_condition_ = value; }

std::size_t WideBid::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("WideBid", wire_size, length);

    wide_bid_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    wide_bid_size_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::read_bytes(data + offset, reserved_4_.data(), 4);
    offset += 4;

    bid_condition_ = static_cast<BidCondition>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t WideBid::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("WideBid", wire_size, capacity);

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(wide_bid_price_.mantissa()));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(wide_bid_size_));
    offset += 4;

    wire::write_bytes(data + offset, reserved_4_.data(), 4);
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(bid_condition_));
    offset += 1;

    return offset;
}

std::size_t WideBid::encoded_size() const {
    return wire_size;
}

void WideBid::print(std::ostream& out) const {
    out << "WideBid{";
    out << "wide_bid_price=";
    out << wide_bid_price_;
    out << ", wide_bid_size=";
    out << wide_bid_size_;
    out << ", reserved_4=";
    print::hex(out, reserved_4_.data(), reserved_4_.size());
    out << ", bid_condition=";
    out << bid_condition_;
    out << '}';
}

bool WideBid::operator==(const WideBid& other) const {
    return wide_bid_price_ == other.wide_bid_price_
        && wide_bid_size_ == other.wide_bid_size_
        && reserved_4_ == other.reserved_4_
        && bid_condition_ == other.bid_condition_;
}

bool WideBid::operator!=(const WideBid& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const WideBid& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
