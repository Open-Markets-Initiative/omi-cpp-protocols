#include "ConsolidatedBidAskPair.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

ConsolidatedBidAskPair::ConsolidatedBidAskPair(std::optional<Decimal> bid_px, std::optional<Decimal> ask_px, std::uint32_t bid_sz, std::uint32_t ask_sz, std::uint16_t bid_pb, const std::array<std::byte, 2>& reserved_2, std::uint16_t ask_pb, const std::array<std::byte, 2>& second_reserved_2)
  : bid_px_(bid_px), ask_px_(ask_px), bid_sz_(bid_sz), ask_sz_(ask_sz), bid_pb_(bid_pb), reserved_2_(reserved_2), ask_pb_(ask_pb), second_reserved_2_(second_reserved_2) {}

std::optional<Decimal> ConsolidatedBidAskPair::bid_px() const { return bid_px_; }
void ConsolidatedBidAskPair::set_bid_px(std::optional<Decimal> value) { bid_px_ = value; }

std::optional<Decimal> ConsolidatedBidAskPair::ask_px() const { return ask_px_; }
void ConsolidatedBidAskPair::set_ask_px(std::optional<Decimal> value) { ask_px_ = value; }

std::uint32_t ConsolidatedBidAskPair::bid_sz() const { return bid_sz_; }
void ConsolidatedBidAskPair::set_bid_sz(std::uint32_t value) { bid_sz_ = value; }

std::uint32_t ConsolidatedBidAskPair::ask_sz() const { return ask_sz_; }
void ConsolidatedBidAskPair::set_ask_sz(std::uint32_t value) { ask_sz_ = value; }

std::uint16_t ConsolidatedBidAskPair::bid_pb() const { return bid_pb_; }
void ConsolidatedBidAskPair::set_bid_pb(std::uint16_t value) { bid_pb_ = value; }

const std::array<std::byte, 2>& ConsolidatedBidAskPair::reserved_2() const { return reserved_2_; }
std::array<std::byte, 2>& ConsolidatedBidAskPair::reserved_2() { return reserved_2_; }
void ConsolidatedBidAskPair::set_reserved_2(const std::array<std::byte, 2>& value) { reserved_2_ = value; }

std::uint16_t ConsolidatedBidAskPair::ask_pb() const { return ask_pb_; }
void ConsolidatedBidAskPair::set_ask_pb(std::uint16_t value) { ask_pb_ = value; }

const std::array<std::byte, 2>& ConsolidatedBidAskPair::second_reserved_2() const { return second_reserved_2_; }
std::array<std::byte, 2>& ConsolidatedBidAskPair::second_reserved_2() { return second_reserved_2_; }
void ConsolidatedBidAskPair::set_second_reserved_2(const std::array<std::byte, 2>& value) { second_reserved_2_ = value; }

std::size_t ConsolidatedBidAskPair::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ConsolidatedBidAskPair", wire_size, length);

    bid_px_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    ask_px_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    bid_sz_ = wire::read_u32_le(data + offset);
    offset += 4;

    ask_sz_ = wire::read_u32_le(data + offset);
    offset += 4;

    bid_pb_ = wire::read_u16_le(data + offset);
    offset += 2;

    wire::read_bytes(data + offset, reserved_2_.data(), 2);
    offset += 2;

    ask_pb_ = wire::read_u16_le(data + offset);
    offset += 2;

    wire::read_bytes(data + offset, second_reserved_2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t ConsolidatedBidAskPair::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ConsolidatedBidAskPair", wire_size, capacity);

    wire::write_i64_le(data + offset, bid_px_ ? static_cast<std::int64_t>(bid_px_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, ask_px_ ? static_cast<std::int64_t>(ask_px_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(bid_sz_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(ask_sz_));
    offset += 4;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(bid_pb_));
    offset += 2;

    wire::write_bytes(data + offset, reserved_2_.data(), 2);
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(ask_pb_));
    offset += 2;

    wire::write_bytes(data + offset, second_reserved_2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t ConsolidatedBidAskPair::encoded_size() const {
    return wire_size;
}

void ConsolidatedBidAskPair::print(std::ostream& out) const {
    out << "ConsolidatedBidAskPair{";
    out << "bid_px=";
    print::optional(out, bid_px_);
    out << ", ask_px=";
    print::optional(out, ask_px_);
    out << ", bid_sz=";
    out << bid_sz_;
    out << ", ask_sz=";
    out << ask_sz_;
    out << ", bid_pb=";
    out << bid_pb_;
    out << ", reserved_2=";
    print::hex(out, reserved_2_.data(), reserved_2_.size());
    out << ", ask_pb=";
    out << ask_pb_;
    out << ", second_reserved_2=";
    print::hex(out, second_reserved_2_.data(), second_reserved_2_.size());
    out << '}';
}

bool ConsolidatedBidAskPair::operator==(const ConsolidatedBidAskPair& other) const {
    return bid_px_ == other.bid_px_
        && ask_px_ == other.ask_px_
        && bid_sz_ == other.bid_sz_
        && ask_sz_ == other.ask_sz_
        && bid_pb_ == other.bid_pb_
        && reserved_2_ == other.reserved_2_
        && ask_pb_ == other.ask_pb_
        && second_reserved_2_ == other.second_reserved_2_;
}

bool ConsolidatedBidAskPair::operator!=(const ConsolidatedBidAskPair& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const ConsolidatedBidAskPair& value) {
    value.print(out);
    return out;
}

} // namespace databento::marketdata::normalized::dbn::v3
