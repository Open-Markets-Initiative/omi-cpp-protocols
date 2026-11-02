#include "Mbp10MsgBidAskPair.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

Mbp10MsgBidAskPair::Mbp10MsgBidAskPair(std::optional<Decimal> bid_px, std::optional<Decimal> ask_px, std::uint32_t bid_sz, std::uint32_t ask_sz, std::uint32_t bid_ct, std::uint32_t ask_ct)
  : bid_px_(bid_px), ask_px_(ask_px), bid_sz_(bid_sz), ask_sz_(ask_sz), bid_ct_(bid_ct), ask_ct_(ask_ct) {}

std::optional<Decimal> Mbp10MsgBidAskPair::bid_px() const { return bid_px_; }
void Mbp10MsgBidAskPair::set_bid_px(std::optional<Decimal> value) { bid_px_ = value; }

std::optional<Decimal> Mbp10MsgBidAskPair::ask_px() const { return ask_px_; }
void Mbp10MsgBidAskPair::set_ask_px(std::optional<Decimal> value) { ask_px_ = value; }

std::uint32_t Mbp10MsgBidAskPair::bid_sz() const { return bid_sz_; }
void Mbp10MsgBidAskPair::set_bid_sz(std::uint32_t value) { bid_sz_ = value; }

std::uint32_t Mbp10MsgBidAskPair::ask_sz() const { return ask_sz_; }
void Mbp10MsgBidAskPair::set_ask_sz(std::uint32_t value) { ask_sz_ = value; }

std::uint32_t Mbp10MsgBidAskPair::bid_ct() const { return bid_ct_; }
void Mbp10MsgBidAskPair::set_bid_ct(std::uint32_t value) { bid_ct_ = value; }

std::uint32_t Mbp10MsgBidAskPair::ask_ct() const { return ask_ct_; }
void Mbp10MsgBidAskPair::set_ask_ct(std::uint32_t value) { ask_ct_ = value; }

std::size_t Mbp10MsgBidAskPair::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("Mbp10MsgBidAskPair", wire_size, length);

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

std::size_t Mbp10MsgBidAskPair::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("Mbp10MsgBidAskPair", wire_size, capacity);

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

std::size_t Mbp10MsgBidAskPair::encoded_size() const {
    return wire_size;
}

void Mbp10MsgBidAskPair::print(std::ostream& out) const {
    out << "Mbp10MsgBidAskPair{";
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

bool Mbp10MsgBidAskPair::operator==(const Mbp10MsgBidAskPair& other) const {
    return bid_px_ == other.bid_px_
        && ask_px_ == other.ask_px_
        && bid_sz_ == other.bid_sz_
        && ask_sz_ == other.ask_sz_
        && bid_ct_ == other.bid_ct_
        && ask_ct_ == other.ask_ct_;
}

bool Mbp10MsgBidAskPair::operator!=(const Mbp10MsgBidAskPair& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const Mbp10MsgBidAskPair& value) {
    value.print(out);
    return out;
}

} // namespace databento::marketdata::normalized::dbn::v1
