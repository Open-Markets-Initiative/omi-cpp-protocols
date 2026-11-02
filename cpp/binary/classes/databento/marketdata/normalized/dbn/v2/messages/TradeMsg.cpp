#include "TradeMsg.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

TradeMsg::TradeMsg(std::optional<Decimal> price, std::uint32_t size, Action action, Side side, const Flags& flags, std::uint8_t depth, std::optional<std::chrono::nanoseconds> ts_recv, std::int32_t ts_in_delta, std::uint32_t sequence)
  : price_(price), size_(size), action_(action), side_(side), flags_(flags), depth_(depth), ts_recv_(ts_recv), ts_in_delta_(ts_in_delta), sequence_(sequence) {}

std::optional<Decimal> TradeMsg::price() const { return price_; }
void TradeMsg::set_price(std::optional<Decimal> value) { price_ = value; }

std::uint32_t TradeMsg::size() const { return size_; }
void TradeMsg::set_size(std::uint32_t value) { size_ = value; }

Action TradeMsg::action() const { return action_; }
void TradeMsg::set_action(Action value) { action_ = value; }

Side TradeMsg::side() const { return side_; }
void TradeMsg::set_side(Side value) { side_ = value; }

const Flags& TradeMsg::flags() const { return flags_; }
Flags& TradeMsg::flags() { return flags_; }
void TradeMsg::set_flags(const Flags& value) { flags_ = value; }

std::uint8_t TradeMsg::depth() const { return depth_; }
void TradeMsg::set_depth(std::uint8_t value) { depth_ = value; }

std::optional<std::chrono::nanoseconds> TradeMsg::ts_recv() const { return ts_recv_; }
void TradeMsg::set_ts_recv(std::optional<std::chrono::nanoseconds> value) { ts_recv_ = value; }

std::int32_t TradeMsg::ts_in_delta() const { return ts_in_delta_; }
void TradeMsg::set_ts_in_delta(std::int32_t value) { ts_in_delta_ = value; }

std::uint32_t TradeMsg::sequence() const { return sequence_; }
void TradeMsg::set_sequence(std::uint32_t value) { sequence_ = value; }

MessageCode TradeMsg::type() const { return message_type; }

std::string_view TradeMsg::name() const { return "Trade Msg"; }

std::size_t TradeMsg::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeMsg", wire_size, length);

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

    return offset;
}

std::size_t TradeMsg::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeMsg", wire_size, capacity);

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

    return offset;
}

std::size_t TradeMsg::encoded_size() const {
    return wire_size;
}

void TradeMsg::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TradeMsg::clone() const {
    return std::make_unique<TradeMsg>(*this);
}

void TradeMsg::print(std::ostream& out) const {
    out << "TradeMsg{";
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
    out << '}';
}

bool TradeMsg::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TradeMsg*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeMsg::operator==(const TradeMsg& other) const {
    return price_ == other.price_
        && size_ == other.size_
        && action_ == other.action_
        && side_ == other.side_
        && flags_ == other.flags_
        && depth_ == other.depth_
        && ts_recv_ == other.ts_recv_
        && ts_in_delta_ == other.ts_in_delta_
        && sequence_ == other.sequence_;
}

bool TradeMsg::operator!=(const TradeMsg& other) const {
    return !(*this == other);
}

} // namespace databento::marketdata::normalized::dbn::v2
