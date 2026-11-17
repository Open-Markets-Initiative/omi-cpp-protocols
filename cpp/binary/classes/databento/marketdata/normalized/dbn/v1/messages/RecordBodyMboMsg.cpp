// Databento.MarketData.Normalized.Dbn.v1: messages/RecordBodyMboMsg.cpp
#include "RecordBodyMboMsg.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

RecordBodyMboMsg::RecordBodyMboMsg(std::uint64_t order_id, std::optional<Decimal> price, std::uint32_t size, const Flags& flags, std::uint8_t channel_id, Action action, Side side, std::optional<std::chrono::nanoseconds> ts_recv, std::int32_t ts_in_delta, std::uint32_t sequence)
  : order_id_(order_id), price_(price), size_(size), flags_(flags), channel_id_(channel_id), action_(action), side_(side), ts_recv_(ts_recv), ts_in_delta_(ts_in_delta), sequence_(sequence) {}

std::uint64_t RecordBodyMboMsg::order_id() const { return order_id_; }
void RecordBodyMboMsg::set_order_id(std::uint64_t value) { order_id_ = value; }

std::optional<Decimal> RecordBodyMboMsg::price() const { return price_; }
void RecordBodyMboMsg::set_price(std::optional<Decimal> value) { price_ = value; }

std::uint32_t RecordBodyMboMsg::size() const { return size_; }
void RecordBodyMboMsg::set_size(std::uint32_t value) { size_ = value; }

const Flags& RecordBodyMboMsg::flags() const { return flags_; }
Flags& RecordBodyMboMsg::flags() { return flags_; }
void RecordBodyMboMsg::set_flags(const Flags& value) { flags_ = value; }

std::uint8_t RecordBodyMboMsg::channel_id() const { return channel_id_; }
void RecordBodyMboMsg::set_channel_id(std::uint8_t value) { channel_id_ = value; }

Action RecordBodyMboMsg::action() const { return action_; }
void RecordBodyMboMsg::set_action(Action value) { action_ = value; }

Side RecordBodyMboMsg::side() const { return side_; }
void RecordBodyMboMsg::set_side(Side value) { side_ = value; }

std::optional<std::chrono::nanoseconds> RecordBodyMboMsg::ts_recv() const { return ts_recv_; }
void RecordBodyMboMsg::set_ts_recv(std::optional<std::chrono::nanoseconds> value) { ts_recv_ = value; }

std::int32_t RecordBodyMboMsg::ts_in_delta() const { return ts_in_delta_; }
void RecordBodyMboMsg::set_ts_in_delta(std::int32_t value) { ts_in_delta_ = value; }

std::uint32_t RecordBodyMboMsg::sequence() const { return sequence_; }
void RecordBodyMboMsg::set_sequence(std::uint32_t value) { sequence_ = value; }

GatewayMessageCode RecordBodyMboMsg::type() const { return message_type; }

std::string_view RecordBodyMboMsg::name() const { return "Mbo Msg"; }

std::size_t RecordBodyMboMsg::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RecordBodyMboMsg", wire_size, length);

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    size_ = wire::read_u32_le(data + offset);
    offset += 4;

    offset += flags_.decode(data + offset, length - offset);

    channel_id_ = wire::read_u8(data + offset);
    offset += 1;

    action_ = static_cast<Action>(wire::read_char(data + offset));
    offset += 1;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    ts_recv_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    ts_in_delta_ = wire::read_i32_le(data + offset);
    offset += 4;

    sequence_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t RecordBodyMboMsg::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RecordBodyMboMsg", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_i64_le(data + offset, price_ ? static_cast<std::int64_t>(price_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(size_));
    offset += 4;

    offset += flags_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(channel_id_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(action_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_u64_le(data + offset, ts_recv_ ? static_cast<std::uint64_t>(ts_recv_->count()) : static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(ts_in_delta_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(sequence_));
    offset += 4;

    return offset;
}

std::size_t RecordBodyMboMsg::encoded_size() const {
    return wire_size;
}

void RecordBodyMboMsg::accept(GatewayMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<GatewayMessage> RecordBodyMboMsg::clone() const {
    return std::make_unique<RecordBodyMboMsg>(*this);
}

void RecordBodyMboMsg::print(std::ostream& out) const {
    out << "RecordBodyMboMsg{";
    out << "order_id=";
    out << order_id_;
    out << ", price=";
    print::optional(out, price_);
    out << ", size=";
    out << size_;
    out << ", flags=";
    flags_.print(out);
    out << ", channel_id=";
    out << static_cast<int>(channel_id_);
    out << ", action=";
    out << action_;
    out << ", side=";
    out << side_;
    out << ", ts_recv=";
    print::optional_duration(out, ts_recv_);
    out << ", ts_in_delta=";
    out << ts_in_delta_;
    out << ", sequence=";
    out << sequence_;
    out << '}';
}

bool RecordBodyMboMsg::equals(const GatewayMessage& other) const {
    const auto* that = dynamic_cast<const RecordBodyMboMsg*>(&other);
    return that != nullptr && *this == *that;
}

bool RecordBodyMboMsg::operator==(const RecordBodyMboMsg& other) const {
    return order_id_ == other.order_id_
        && price_ == other.price_
        && size_ == other.size_
        && flags_ == other.flags_
        && channel_id_ == other.channel_id_
        && action_ == other.action_
        && side_ == other.side_
        && ts_recv_ == other.ts_recv_
        && ts_in_delta_ == other.ts_in_delta_
        && sequence_ == other.sequence_;
}

bool RecordBodyMboMsg::operator!=(const RecordBodyMboMsg& other) const {
    return !(*this == other);
}

} // namespace databento::marketdata::normalized::dbn::v1
