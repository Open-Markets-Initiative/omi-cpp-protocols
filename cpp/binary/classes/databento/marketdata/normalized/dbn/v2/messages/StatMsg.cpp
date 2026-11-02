#include "StatMsg.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

StatMsg::StatMsg(std::optional<std::chrono::nanoseconds> ts_recv, std::optional<std::chrono::nanoseconds> ts_ref, std::optional<Decimal> price, std::optional<std::int32_t> quantity, std::uint32_t sequence, std::int32_t ts_in_delta, StatType stat_type, std::uint16_t channel, UpdateAction update_action, std::uint8_t stat_flags, const std::array<std::byte, 6>& reserved_6)
  : ts_recv_(ts_recv), ts_ref_(ts_ref), price_(price), quantity_(quantity), sequence_(sequence), ts_in_delta_(ts_in_delta), stat_type_(stat_type), channel_(channel), update_action_(update_action), stat_flags_(stat_flags), reserved_6_(reserved_6) {}

std::optional<std::chrono::nanoseconds> StatMsg::ts_recv() const { return ts_recv_; }
void StatMsg::set_ts_recv(std::optional<std::chrono::nanoseconds> value) { ts_recv_ = value; }

std::optional<std::chrono::nanoseconds> StatMsg::ts_ref() const { return ts_ref_; }
void StatMsg::set_ts_ref(std::optional<std::chrono::nanoseconds> value) { ts_ref_ = value; }

std::optional<Decimal> StatMsg::price() const { return price_; }
void StatMsg::set_price(std::optional<Decimal> value) { price_ = value; }

std::optional<std::int32_t> StatMsg::quantity() const { return quantity_; }
void StatMsg::set_quantity(std::optional<std::int32_t> value) { quantity_ = value; }

std::uint32_t StatMsg::sequence() const { return sequence_; }
void StatMsg::set_sequence(std::uint32_t value) { sequence_ = value; }

std::int32_t StatMsg::ts_in_delta() const { return ts_in_delta_; }
void StatMsg::set_ts_in_delta(std::int32_t value) { ts_in_delta_ = value; }

StatType StatMsg::stat_type() const { return stat_type_; }
void StatMsg::set_stat_type(StatType value) { stat_type_ = value; }

std::uint16_t StatMsg::channel() const { return channel_; }
void StatMsg::set_channel(std::uint16_t value) { channel_ = value; }

UpdateAction StatMsg::update_action() const { return update_action_; }
void StatMsg::set_update_action(UpdateAction value) { update_action_ = value; }

std::uint8_t StatMsg::stat_flags() const { return stat_flags_; }
void StatMsg::set_stat_flags(std::uint8_t value) { stat_flags_ = value; }

const std::array<std::byte, 6>& StatMsg::reserved_6() const { return reserved_6_; }
std::array<std::byte, 6>& StatMsg::reserved_6() { return reserved_6_; }
void StatMsg::set_reserved_6(const std::array<std::byte, 6>& value) { reserved_6_ = value; }

MessageCode StatMsg::type() const { return message_type; }

std::string_view StatMsg::name() const { return "Stat Msg"; }

std::size_t StatMsg::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("StatMsg", wire_size, length);

    ts_recv_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    ts_ref_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    quantity_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(2147483647LL));
    offset += 4;

    sequence_ = wire::read_u32_le(data + offset);
    offset += 4;

    ts_in_delta_ = wire::read_i32_le(data + offset);
    offset += 4;

    stat_type_ = static_cast<StatType>(wire::read_u16_le(data + offset));
    offset += 2;

    channel_ = wire::read_u16_le(data + offset);
    offset += 2;

    update_action_ = static_cast<UpdateAction>(wire::read_u8(data + offset));
    offset += 1;

    stat_flags_ = wire::read_u8(data + offset);
    offset += 1;

    wire::read_bytes(data + offset, reserved_6_.data(), 6);
    offset += 6;

    return offset;
}

std::size_t StatMsg::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("StatMsg", wire_size, capacity);

    wire::write_u64_le(data + offset, ts_recv_ ? static_cast<std::uint64_t>(ts_recv_->count()) : static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    wire::write_u64_le(data + offset, ts_ref_ ? static_cast<std::uint64_t>(ts_ref_->count()) : static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    wire::write_i64_le(data + offset, price_ ? static_cast<std::int64_t>(price_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i32_le(data + offset, quantity_.value_or(static_cast<std::int32_t>(2147483647LL)));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(sequence_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(ts_in_delta_));
    offset += 4;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(stat_type_));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(channel_));
    offset += 2;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(update_action_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(stat_flags_));
    offset += 1;

    wire::write_bytes(data + offset, reserved_6_.data(), 6);
    offset += 6;

    return offset;
}

std::size_t StatMsg::encoded_size() const {
    return wire_size;
}

void StatMsg::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> StatMsg::clone() const {
    return std::make_unique<StatMsg>(*this);
}

void StatMsg::print(std::ostream& out) const {
    out << "StatMsg{";
    out << "ts_recv=";
    print::optional_duration(out, ts_recv_);
    out << ", ts_ref=";
    print::optional_duration(out, ts_ref_);
    out << ", price=";
    print::optional(out, price_);
    out << ", quantity=";
    print::optional(out, quantity_);
    out << ", sequence=";
    out << sequence_;
    out << ", ts_in_delta=";
    out << ts_in_delta_;
    out << ", stat_type=";
    out << stat_type_;
    out << ", channel=";
    out << channel_;
    out << ", update_action=";
    out << update_action_;
    out << ", stat_flags=";
    out << static_cast<int>(stat_flags_);
    out << ", reserved_6=";
    print::hex(out, reserved_6_.data(), reserved_6_.size());
    out << '}';
}

bool StatMsg::equals(const Message& other) const {
    const auto* that = dynamic_cast<const StatMsg*>(&other);
    return that != nullptr && *this == *that;
}

bool StatMsg::operator==(const StatMsg& other) const {
    return ts_recv_ == other.ts_recv_
        && ts_ref_ == other.ts_ref_
        && price_ == other.price_
        && quantity_ == other.quantity_
        && sequence_ == other.sequence_
        && ts_in_delta_ == other.ts_in_delta_
        && stat_type_ == other.stat_type_
        && channel_ == other.channel_
        && update_action_ == other.update_action_
        && stat_flags_ == other.stat_flags_
        && reserved_6_ == other.reserved_6_;
}

bool StatMsg::operator!=(const StatMsg& other) const {
    return !(*this == other);
}

} // namespace databento::marketdata::normalized::dbn::v2
