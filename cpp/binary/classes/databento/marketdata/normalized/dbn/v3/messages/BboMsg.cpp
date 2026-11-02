#include "BboMsg.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

BboMsg::BboMsg(std::optional<Decimal> price, std::uint32_t size, const std::array<std::byte, 1>& reserved_1, Side side, const Flags& flags, const std::array<std::byte, 1>& second_reserved_1, std::optional<std::chrono::nanoseconds> ts_recv, const std::array<std::byte, 4>& reserved_4, std::uint32_t sequence, const BidAskPair& bid_ask_pair)
  : price_(price), size_(size), reserved_1_(reserved_1), side_(side), flags_(flags), second_reserved_1_(second_reserved_1), ts_recv_(ts_recv), reserved_4_(reserved_4), sequence_(sequence), bid_ask_pair_(bid_ask_pair) {}

std::optional<Decimal> BboMsg::price() const { return price_; }
void BboMsg::set_price(std::optional<Decimal> value) { price_ = value; }

std::uint32_t BboMsg::size() const { return size_; }
void BboMsg::set_size(std::uint32_t value) { size_ = value; }

const std::array<std::byte, 1>& BboMsg::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& BboMsg::reserved_1() { return reserved_1_; }
void BboMsg::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

Side BboMsg::side() const { return side_; }
void BboMsg::set_side(Side value) { side_ = value; }

const Flags& BboMsg::flags() const { return flags_; }
Flags& BboMsg::flags() { return flags_; }
void BboMsg::set_flags(const Flags& value) { flags_ = value; }

const std::array<std::byte, 1>& BboMsg::second_reserved_1() const { return second_reserved_1_; }
std::array<std::byte, 1>& BboMsg::second_reserved_1() { return second_reserved_1_; }
void BboMsg::set_second_reserved_1(const std::array<std::byte, 1>& value) { second_reserved_1_ = value; }

std::optional<std::chrono::nanoseconds> BboMsg::ts_recv() const { return ts_recv_; }
void BboMsg::set_ts_recv(std::optional<std::chrono::nanoseconds> value) { ts_recv_ = value; }

const std::array<std::byte, 4>& BboMsg::reserved_4() const { return reserved_4_; }
std::array<std::byte, 4>& BboMsg::reserved_4() { return reserved_4_; }
void BboMsg::set_reserved_4(const std::array<std::byte, 4>& value) { reserved_4_ = value; }

std::uint32_t BboMsg::sequence() const { return sequence_; }
void BboMsg::set_sequence(std::uint32_t value) { sequence_ = value; }

const BidAskPair& BboMsg::bid_ask_pair() const { return bid_ask_pair_; }
BidAskPair& BboMsg::bid_ask_pair() { return bid_ask_pair_; }
void BboMsg::set_bid_ask_pair(const BidAskPair& value) { bid_ask_pair_ = value; }

MessageCode BboMsg::type() const { return message_type; }

std::string_view BboMsg::name() const { return "Bbo Msg"; }

std::size_t BboMsg::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("BboMsg", wire_size, length);

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

    wire::read_bytes(data + offset, reserved_4_.data(), 4);
    offset += 4;

    sequence_ = wire::read_u32_le(data + offset);
    offset += 4;

    offset += bid_ask_pair_.decode(data + offset, length - offset);

    return offset;
}

std::size_t BboMsg::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("BboMsg", wire_size, capacity);

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

    wire::write_bytes(data + offset, reserved_4_.data(), 4);
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(sequence_));
    offset += 4;

    offset += bid_ask_pair_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t BboMsg::encoded_size() const {
    return wire_size;
}

void BboMsg::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> BboMsg::clone() const {
    return std::make_unique<BboMsg>(*this);
}

void BboMsg::print(std::ostream& out) const {
    out << "BboMsg{";
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
    out << ", reserved_4=";
    print::hex(out, reserved_4_.data(), reserved_4_.size());
    out << ", sequence=";
    out << sequence_;
    out << ", bid_ask_pair=";
    bid_ask_pair_.print(out);
    out << '}';
}

bool BboMsg::equals(const Message& other) const {
    const auto* that = dynamic_cast<const BboMsg*>(&other);
    return that != nullptr && *this == *that;
}

bool BboMsg::operator==(const BboMsg& other) const {
    return price_ == other.price_
        && size_ == other.size_
        && reserved_1_ == other.reserved_1_
        && side_ == other.side_
        && flags_ == other.flags_
        && second_reserved_1_ == other.second_reserved_1_
        && ts_recv_ == other.ts_recv_
        && reserved_4_ == other.reserved_4_
        && sequence_ == other.sequence_
        && bid_ask_pair_ == other.bid_ask_pair_;
}

bool BboMsg::operator!=(const BboMsg& other) const {
    return !(*this == other);
}

} // namespace databento::marketdata::normalized::dbn::v3
