#include "CompactBid.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

CompactBid::CompactBid(Decimal compact_bid_price, std::uint16_t compact_bid_size, const std::array<std::byte, 2>& reserved_2, BidCondition bid_condition)
  : compact_bid_price_(compact_bid_price), compact_bid_size_(compact_bid_size), reserved_2_(reserved_2), bid_condition_(bid_condition) {}

Decimal CompactBid::compact_bid_price() const { return compact_bid_price_; }
void CompactBid::set_compact_bid_price(Decimal value) { compact_bid_price_ = value; }

std::uint16_t CompactBid::compact_bid_size() const { return compact_bid_size_; }
void CompactBid::set_compact_bid_size(std::uint16_t value) { compact_bid_size_ = value; }

const std::array<std::byte, 2>& CompactBid::reserved_2() const { return reserved_2_; }
std::array<std::byte, 2>& CompactBid::reserved_2() { return reserved_2_; }
void CompactBid::set_reserved_2(const std::array<std::byte, 2>& value) { reserved_2_ = value; }

BidCondition CompactBid::bid_condition() const { return bid_condition_; }
void CompactBid::set_bid_condition(BidCondition value) { bid_condition_ = value; }

std::size_t CompactBid::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("CompactBid", wire_size, length);

    compact_bid_price_ = Decimal(static_cast<std::int64_t>(wire::read_i16_le(data + offset)), -2);
    offset += 2;

    compact_bid_size_ = wire::read_u16_le(data + offset);
    offset += 2;

    wire::read_bytes(data + offset, reserved_2_.data(), 2);
    offset += 2;

    bid_condition_ = static_cast<BidCondition>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t CompactBid::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CompactBid", wire_size, capacity);

    wire::write_i16_le(data + offset, static_cast<std::int16_t>(compact_bid_price_.mantissa()));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(compact_bid_size_));
    offset += 2;

    wire::write_bytes(data + offset, reserved_2_.data(), 2);
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(bid_condition_));
    offset += 1;

    return offset;
}

std::size_t CompactBid::encoded_size() const {
    return wire_size;
}

void CompactBid::print(std::ostream& out) const {
    out << "CompactBid{";
    out << "compact_bid_price=";
    out << compact_bid_price_;
    out << ", compact_bid_size=";
    out << compact_bid_size_;
    out << ", reserved_2=";
    print::hex(out, reserved_2_.data(), reserved_2_.size());
    out << ", bid_condition=";
    out << bid_condition_;
    out << '}';
}

bool CompactBid::operator==(const CompactBid& other) const {
    return compact_bid_price_ == other.compact_bid_price_
        && compact_bid_size_ == other.compact_bid_size_
        && reserved_2_ == other.reserved_2_
        && bid_condition_ == other.bid_condition_;
}

bool CompactBid::operator!=(const CompactBid& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const CompactBid& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
