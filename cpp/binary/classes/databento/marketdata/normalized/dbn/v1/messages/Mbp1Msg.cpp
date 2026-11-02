#include "Mbp1Msg.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

Mbp1Msg::Mbp1Msg(std::optional<Decimal> price, std::uint32_t size, Action action, Side side, const Flags& flags, std::uint8_t depth, std::optional<std::chrono::nanoseconds> ts_recv, std::int32_t ts_in_delta, std::uint32_t sequence, const BidAskPair& bid_ask_pair)
  : price_(price), size_(size), action_(action), side_(side), flags_(flags), depth_(depth), ts_recv_(ts_recv), ts_in_delta_(ts_in_delta), sequence_(sequence), bid_ask_pair_(bid_ask_pair) {}

std::optional<Decimal> Mbp1Msg::price() const { return price_; }
void Mbp1Msg::set_price(std::optional<Decimal> value) { price_ = value; }

std::uint32_t Mbp1Msg::size() const { return size_; }
void Mbp1Msg::set_size(std::uint32_t value) { size_ = value; }

Action Mbp1Msg::action() const { return action_; }
void Mbp1Msg::set_action(Action value) { action_ = value; }

Side Mbp1Msg::side() const { return side_; }
void Mbp1Msg::set_side(Side value) { side_ = value; }

const Flags& Mbp1Msg::flags() const { return flags_; }
Flags& Mbp1Msg::flags() { return flags_; }
void Mbp1Msg::set_flags(const Flags& value) { flags_ = value; }

std::uint8_t Mbp1Msg::depth() const { return depth_; }
void Mbp1Msg::set_depth(std::uint8_t value) { depth_ = value; }

std::optional<std::chrono::nanoseconds> Mbp1Msg::ts_recv() const { return ts_recv_; }
void Mbp1Msg::set_ts_recv(std::optional<std::chrono::nanoseconds> value) { ts_recv_ = value; }

std::int32_t Mbp1Msg::ts_in_delta() const { return ts_in_delta_; }
void Mbp1Msg::set_ts_in_delta(std::int32_t value) { ts_in_delta_ = value; }

std::uint32_t Mbp1Msg::sequence() const { return sequence_; }
void Mbp1Msg::set_sequence(std::uint32_t value) { sequence_ = value; }

const BidAskPair& Mbp1Msg::bid_ask_pair() const { return bid_ask_pair_; }
BidAskPair& Mbp1Msg::bid_ask_pair() { return bid_ask_pair_; }
void Mbp1Msg::set_bid_ask_pair(const BidAskPair& value) { bid_ask_pair_ = value; }

MessageCode Mbp1Msg::type() const { return message_type; }

std::string_view Mbp1Msg::name() const { return "Mbp 1 Msg"; }

std::size_t Mbp1Msg::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("Mbp1Msg", wire_size, length);

    price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    size_ = wire::read_u32_le(data + offset);
    offset += 4;

    action_ = static_cast<Action>(wire::read_char(data + offset));
    offset += 1;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    offset += flags_.decode(data + offset, length - offset);

    depth_ = wire::read_u8(data + offset);
    offset += 1;

    ts_recv_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    ts_in_delta_ = wire::read_i32_le(data + offset);
    offset += 4;

    sequence_ = wire::read_u32_le(data + offset);
    offset += 4;

    offset += bid_ask_pair_.decode(data + offset, length - offset);

    return offset;
}

std::size_t Mbp1Msg::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("Mbp1Msg", wire_size, capacity);

    wire::write_i64_le(data + offset, price_ ? static_cast<std::int64_t>(price_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(size_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(action_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    offset += flags_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(depth_));
    offset += 1;

    wire::write_u64_le(data + offset, ts_recv_ ? static_cast<std::uint64_t>(ts_recv_->count()) : static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(ts_in_delta_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(sequence_));
    offset += 4;

    offset += bid_ask_pair_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t Mbp1Msg::encoded_size() const {
    return wire_size;
}

void Mbp1Msg::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> Mbp1Msg::clone() const {
    return std::make_unique<Mbp1Msg>(*this);
}

void Mbp1Msg::print(std::ostream& out) const {
    out << "Mbp1Msg{";
    out << "price=";
    print::optional(out, price_);
    out << ", size=";
    out << size_;
    out << ", action=";
    out << action_;
    out << ", side=";
    out << side_;
    out << ", flags=";
    flags_.print(out);
    out << ", depth=";
    out << static_cast<int>(depth_);
    out << ", ts_recv=";
    print::optional_duration(out, ts_recv_);
    out << ", ts_in_delta=";
    out << ts_in_delta_;
    out << ", sequence=";
    out << sequence_;
    out << ", bid_ask_pair=";
    bid_ask_pair_.print(out);
    out << '}';
}

bool Mbp1Msg::equals(const Message& other) const {
    const auto* that = dynamic_cast<const Mbp1Msg*>(&other);
    return that != nullptr && *this == *that;
}

bool Mbp1Msg::operator==(const Mbp1Msg& other) const {
    return price_ == other.price_
        && size_ == other.size_
        && action_ == other.action_
        && side_ == other.side_
        && flags_ == other.flags_
        && depth_ == other.depth_
        && ts_recv_ == other.ts_recv_
        && ts_in_delta_ == other.ts_in_delta_
        && sequence_ == other.sequence_
        && bid_ask_pair_ == other.bid_ask_pair_;
}

bool Mbp1Msg::operator!=(const Mbp1Msg& other) const {
    return !(*this == other);
}

} // namespace databento::marketdata::normalized::dbn::v1
