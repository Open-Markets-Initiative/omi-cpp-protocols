#include "BidAskPair.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

BidAskPair::BidAskPair(std::optional<Decimal> bid_px, std::optional<Decimal> ask_px, std::uint32_t bid_sz, std::uint32_t ask_sz, std::uint32_t bid_ct, std::uint32_t ask_ct)
  : bid_px_(bid_px), ask_px_(ask_px), bid_sz_(bid_sz), ask_sz_(ask_sz), bid_ct_(bid_ct), ask_ct_(ask_ct) {}

std::optional<Decimal> BidAskPair::bid_px() const { return bid_px_; }
void BidAskPair::set_bid_px(std::optional<Decimal> value) { bid_px_ = value; }

std::optional<Decimal> BidAskPair::ask_px() const { return ask_px_; }
void BidAskPair::set_ask_px(std::optional<Decimal> value) { ask_px_ = value; }

std::uint32_t BidAskPair::bid_sz() const { return bid_sz_; }
void BidAskPair::set_bid_sz(std::uint32_t value) { bid_sz_ = value; }

std::uint32_t BidAskPair::ask_sz() const { return ask_sz_; }
void BidAskPair::set_ask_sz(std::uint32_t value) { ask_sz_ = value; }

std::uint32_t BidAskPair::bid_ct() const { return bid_ct_; }
void BidAskPair::set_bid_ct(std::uint32_t value) { bid_ct_ = value; }

std::uint32_t BidAskPair::ask_ct() const { return ask_ct_; }
void BidAskPair::set_ask_ct(std::uint32_t value) { ask_ct_ = value; }

std::size_t BidAskPair::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("BidAskPair", wire_size, length);

    bid_px_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    ask_px_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    bid_sz_ = wire::read_u32_le(data + offset);
    offset += 4;

    ask_sz_ = wire::read_u32_le(data + offset);
    offset += 4;

    bid_ct_ = wire::read_u32_le(data + offset);
    offset += 4;

    ask_ct_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t BidAskPair::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("BidAskPair", wire_size, capacity);

    wire::write_i64_le(data + offset, bid_px_ ? static_cast<std::int64_t>(bid_px_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, ask_px_ ? static_cast<std::int64_t>(ask_px_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(bid_sz_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(ask_sz_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(bid_ct_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(ask_ct_));
    offset += 4;

    return offset;
}

std::size_t BidAskPair::encoded_size() const {
    return wire_size;
}

void BidAskPair::print(std::ostream& out) const {
    out << "BidAskPair{";
    out << "bid_px=";
    print::optional(out, bid_px_);
    out << ", ask_px=";
    print::optional(out, ask_px_);
    out << ", bid_sz=";
    out << bid_sz_;
    out << ", ask_sz=";
    out << ask_sz_;
    out << ", bid_ct=";
    out << bid_ct_;
    out << ", ask_ct=";
    out << ask_ct_;
    out << '}';
}

bool BidAskPair::operator==(const BidAskPair& other) const {
    return bid_px_ == other.bid_px_
        && ask_px_ == other.ask_px_
        && bid_sz_ == other.bid_sz_
        && ask_sz_ == other.ask_sz_
        && bid_ct_ == other.bid_ct_
        && ask_ct_ == other.ask_ct_;
}

bool BidAskPair::operator!=(const BidAskPair& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const BidAskPair& value) {
    value.print(out);
    return out;
}

} // namespace databento::marketdata::normalized::dbn::v1
