// Databento.MarketData.Normalized.Dbn.v2: messages/CbboMsg.cpp
#include "CbboMsg.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

CbboMsg::CbboMsg(std::optional<Decimal> price, std::uint32_t size, const std::array<std::byte, 1>& reserved_1, Side side, const Flags& flags, const std::array<std::byte, 1>& second_reserved_1, std::optional<std::chrono::nanoseconds> ts_recv, const std::array<std::byte, 8>& reserved_8, const ConsolidatedBidAskPair& consolidated_bid_ask_pair)
  : price_(price), size_(size), reserved_1_(reserved_1), side_(side), flags_(flags), second_reserved_1_(second_reserved_1), ts_recv_(ts_recv), reserved_8_(reserved_8), consolidated_bid_ask_pair_(consolidated_bid_ask_pair) {}

std::optional<Decimal> CbboMsg::price() const { return price_; }
void CbboMsg::set_price(std::optional<Decimal> value) { price_ = value; }

std::uint32_t CbboMsg::size() const { return size_; }
void CbboMsg::set_size(std::uint32_t value) { size_ = value; }

const std::array<std::byte, 1>& CbboMsg::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& CbboMsg::reserved_1() { return reserved_1_; }
void CbboMsg::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

Side CbboMsg::side() const { return side_; }
void CbboMsg::set_side(Side value) { side_ = value; }

const Flags& CbboMsg::flags() const { return flags_; }
Flags& CbboMsg::flags() { return flags_; }
void CbboMsg::set_flags(const Flags& value) { flags_ = value; }

const std::array<std::byte, 1>& CbboMsg::second_reserved_1() const { return second_reserved_1_; }
std::array<std::byte, 1>& CbboMsg::second_reserved_1() { return second_reserved_1_; }
void CbboMsg::set_second_reserved_1(const std::array<std::byte, 1>& value) { second_reserved_1_ = value; }

std::optional<std::chrono::nanoseconds> CbboMsg::ts_recv() const { return ts_recv_; }
void CbboMsg::set_ts_recv(std::optional<std::chrono::nanoseconds> value) { ts_recv_ = value; }

const std::array<std::byte, 8>& CbboMsg::reserved_8() const { return reserved_8_; }
std::array<std::byte, 8>& CbboMsg::reserved_8() { return reserved_8_; }
void CbboMsg::set_reserved_8(const std::array<std::byte, 8>& value) { reserved_8_ = value; }

const ConsolidatedBidAskPair& CbboMsg::consolidated_bid_ask_pair() const { return consolidated_bid_ask_pair_; }
ConsolidatedBidAskPair& CbboMsg::consolidated_bid_ask_pair() { return consolidated_bid_ask_pair_; }
void CbboMsg::set_consolidated_bid_ask_pair(const ConsolidatedBidAskPair& value) { consolidated_bid_ask_pair_ = value; }

MessageCode CbboMsg::type() const { return message_type; }

std::string_view CbboMsg::name() const { return "Cbbo Msg"; }

std::size_t CbboMsg::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("CbboMsg", wire_size, length);

    price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    size_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::read_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    offset += flags_.decode(data + offset, length - offset);

    wire::read_bytes(data + offset, second_reserved_1_.data(), 1);
    offset += 1;

    ts_recv_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    wire::read_bytes(data + offset, reserved_8_.data(), 8);
    offset += 8;

    offset += consolidated_bid_ask_pair_.decode(data + offset, length - offset);

    return offset;
}

std::size_t CbboMsg::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CbboMsg", wire_size, capacity);

    wire::write_i64_le(data + offset, price_ ? static_cast<std::int64_t>(price_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(size_));
    offset += 4;

    wire::write_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    offset += flags_.encode(data + offset, capacity - offset);

    wire::write_bytes(data + offset, second_reserved_1_.data(), 1);
    offset += 1;

    wire::write_u64_le(data + offset, ts_recv_ ? static_cast<std::uint64_t>(ts_recv_->count()) : static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    wire::write_bytes(data + offset, reserved_8_.data(), 8);
    offset += 8;

    offset += consolidated_bid_ask_pair_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t CbboMsg::encoded_size() const {
    return wire_size;
}

void CbboMsg::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> CbboMsg::clone() const {
    return std::make_unique<CbboMsg>(*this);
}

void CbboMsg::print(std::ostream& out) const {
    out << "CbboMsg{";
    out << "price=";
    print::optional(out, price_);
    out << ", size=";
    out << size_;
    out << ", reserved_1=";
    print::hex(out, reserved_1_.data(), reserved_1_.size());
    out << ", side=";
    out << side_;
    out << ", flags=";
    flags_.print(out);
    out << ", second_reserved_1=";
    print::hex(out, second_reserved_1_.data(), second_reserved_1_.size());
    out << ", ts_recv=";
    print::optional_duration(out, ts_recv_);
    out << ", reserved_8=";
    print::hex(out, reserved_8_.data(), reserved_8_.size());
    out << ", consolidated_bid_ask_pair=";
    consolidated_bid_ask_pair_.print(out);
    out << '}';
}

bool CbboMsg::equals(const Message& other) const {
    const auto* that = dynamic_cast<const CbboMsg*>(&other);
    return that != nullptr && *this == *that;
}

bool CbboMsg::operator==(const CbboMsg& other) const {
    return price_ == other.price_
        && size_ == other.size_
        && reserved_1_ == other.reserved_1_
        && side_ == other.side_
        && flags_ == other.flags_
        && second_reserved_1_ == other.second_reserved_1_
        && ts_recv_ == other.ts_recv_
        && reserved_8_ == other.reserved_8_
        && consolidated_bid_ask_pair_ == other.consolidated_bid_ask_pair_;
}

bool CbboMsg::operator!=(const CbboMsg& other) const {
    return !(*this == other);
}

} // namespace databento::marketdata::normalized::dbn::v2
