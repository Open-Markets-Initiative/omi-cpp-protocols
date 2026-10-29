#include "OrderCancelRequestMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

OrderCancelRequestMessage::OrderCancelRequestMessage(const InboundBusinessHeader& inbound_business_header, const std::array<std::byte, 2>& offset_18_padding_2, std::uint64_t clordid, std::uint64_t security_id, std::optional<std::uint64_t> order_id_optional, std::optional<std::uint64_t> origclordid, Side side, std::optional<SingleCancelRestatementReason> single_cancel_restatement_reason, const std::array<std::byte, 2>& offset_54_padding_2, const std::string& sender_location, const std::string& entering_trader, const std::string& executing_trader_optional, const DeskId& desk_id, const Memo& memo)
  : inbound_business_header_(inbound_business_header), offset_18_padding_2_(offset_18_padding_2), clordid_(clordid), security_id_(security_id), order_id_optional_(order_id_optional), origclordid_(origclordid), side_(side), single_cancel_restatement_reason_(single_cancel_restatement_reason), offset_54_padding_2_(offset_54_padding_2), sender_location_(sender_location), entering_trader_(entering_trader), executing_trader_optional_(executing_trader_optional), desk_id_(desk_id), memo_(memo) {}

const InboundBusinessHeader& OrderCancelRequestMessage::inbound_business_header() const { return inbound_business_header_; }
InboundBusinessHeader& OrderCancelRequestMessage::inbound_business_header() { return inbound_business_header_; }
void OrderCancelRequestMessage::set_inbound_business_header(const InboundBusinessHeader& value) { inbound_business_header_ = value; }

const std::array<std::byte, 2>& OrderCancelRequestMessage::offset_18_padding_2() const { return offset_18_padding_2_; }
std::array<std::byte, 2>& OrderCancelRequestMessage::offset_18_padding_2() { return offset_18_padding_2_; }
void OrderCancelRequestMessage::set_offset_18_padding_2(const std::array<std::byte, 2>& value) { offset_18_padding_2_ = value; }

std::uint64_t OrderCancelRequestMessage::clordid() const { return clordid_; }
void OrderCancelRequestMessage::set_clordid(std::uint64_t value) { clordid_ = value; }

std::uint64_t OrderCancelRequestMessage::security_id() const { return security_id_; }
void OrderCancelRequestMessage::set_security_id(std::uint64_t value) { security_id_ = value; }

std::optional<std::uint64_t> OrderCancelRequestMessage::order_id_optional() const { return order_id_optional_; }
void OrderCancelRequestMessage::set_order_id_optional(std::optional<std::uint64_t> value) { order_id_optional_ = value; }

std::optional<std::uint64_t> OrderCancelRequestMessage::origclordid() const { return origclordid_; }
void OrderCancelRequestMessage::set_origclordid(std::optional<std::uint64_t> value) { origclordid_ = value; }

Side OrderCancelRequestMessage::side() const { return side_; }
void OrderCancelRequestMessage::set_side(Side value) { side_ = value; }

std::optional<SingleCancelRestatementReason> OrderCancelRequestMessage::single_cancel_restatement_reason() const { return single_cancel_restatement_reason_; }
void OrderCancelRequestMessage::set_single_cancel_restatement_reason(std::optional<SingleCancelRestatementReason> value) { single_cancel_restatement_reason_ = value; }

const std::array<std::byte, 2>& OrderCancelRequestMessage::offset_54_padding_2() const { return offset_54_padding_2_; }
std::array<std::byte, 2>& OrderCancelRequestMessage::offset_54_padding_2() { return offset_54_padding_2_; }
void OrderCancelRequestMessage::set_offset_54_padding_2(const std::array<std::byte, 2>& value) { offset_54_padding_2_ = value; }

const std::string& OrderCancelRequestMessage::sender_location() const { return sender_location_; }
std::string& OrderCancelRequestMessage::sender_location() { return sender_location_; }
void OrderCancelRequestMessage::set_sender_location(const std::string& value) { sender_location_ = value; }

const std::string& OrderCancelRequestMessage::entering_trader() const { return entering_trader_; }
std::string& OrderCancelRequestMessage::entering_trader() { return entering_trader_; }
void OrderCancelRequestMessage::set_entering_trader(const std::string& value) { entering_trader_ = value; }

const std::string& OrderCancelRequestMessage::executing_trader_optional() const { return executing_trader_optional_; }
std::string& OrderCancelRequestMessage::executing_trader_optional() { return executing_trader_optional_; }
void OrderCancelRequestMessage::set_executing_trader_optional(const std::string& value) { executing_trader_optional_ = value; }

const DeskId& OrderCancelRequestMessage::desk_id() const { return desk_id_; }
DeskId& OrderCancelRequestMessage::desk_id() { return desk_id_; }
void OrderCancelRequestMessage::set_desk_id(const DeskId& value) { desk_id_ = value; }

const Memo& OrderCancelRequestMessage::memo() const { return memo_; }
Memo& OrderCancelRequestMessage::memo() { return memo_; }
void OrderCancelRequestMessage::set_memo(const Memo& value) { memo_ = value; }

MessageCode OrderCancelRequestMessage::type() const { return message_type; }

std::string_view OrderCancelRequestMessage::name() const { return "Order Cancel Request Message"; }

std::size_t OrderCancelRequestMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += inbound_business_header_.decode(data + offset, length - offset);

    wire::require("OrderCancelRequestMessage", offset + 2, length);
    wire::read_bytes(data + offset, offset_18_padding_2_.data(), 2);
    offset += 2;

    wire::require("OrderCancelRequestMessage", offset + 8, length);
    clordid_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("OrderCancelRequestMessage", offset + 8, length);
    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("OrderCancelRequestMessage", offset + 8, length);
    order_id_optional_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("OrderCancelRequestMessage", offset + 8, length);
    origclordid_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("OrderCancelRequestMessage", offset + 1, length);
    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    wire::require("OrderCancelRequestMessage", offset + 1, length);
    single_cancel_restatement_reason_ = wire::nullable_enum<SingleCancelRestatementReason>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::require("OrderCancelRequestMessage", offset + 2, length);
    wire::read_bytes(data + offset, offset_54_padding_2_.data(), 2);
    offset += 2;

    wire::require("OrderCancelRequestMessage", offset + 10, length);
    sender_location_ = wire::read_text(data + offset, 10, '\0');
    offset += 10;

    wire::require("OrderCancelRequestMessage", offset + 5, length);
    entering_trader_ = wire::read_text(data + offset, 5, '\0');
    offset += 5;

    wire::require("OrderCancelRequestMessage", offset + 5, length);
    executing_trader_optional_ = wire::read_text(data + offset, 5, '\0');
    offset += 5;

    offset += desk_id_.decode(data + offset, length - offset);

    offset += memo_.decode(data + offset, length - offset);

    return offset;
}

std::size_t OrderCancelRequestMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderCancelRequestMessage", encoded_size(), capacity);

    offset += inbound_business_header_.encode(data + offset, capacity - offset);

    wire::write_bytes(data + offset, offset_18_padding_2_.data(), 2);
    offset += 2;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(clordid_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    wire::write_u64_le(data + offset, order_id_optional_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_u64_le(data + offset, origclordid_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_u8(data + offset, single_cancel_restatement_reason_ ? static_cast<std::uint8_t>(*single_cancel_restatement_reason_) : static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::write_bytes(data + offset, offset_54_padding_2_.data(), 2);
    offset += 2;

    wire::write_text(data + offset, 10, '\0', sender_location_);
    offset += 10;

    wire::write_text(data + offset, 5, '\0', entering_trader_);
    offset += 5;

    wire::write_text(data + offset, 5, '\0', executing_trader_optional_);
    offset += 5;

    offset += desk_id_.encode(data + offset, capacity - offset);

    offset += memo_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t OrderCancelRequestMessage::encoded_size() const {
    return inbound_business_header_.encoded_size() + 2 + 8 + 8 + 8 + 8 + 1 + 1 + 2 + 10 + 5 + 5 + desk_id_.encoded_size() + memo_.encoded_size();
}

void OrderCancelRequestMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderCancelRequestMessage::clone() const {
    return std::make_unique<OrderCancelRequestMessage>(*this);
}

void OrderCancelRequestMessage::print(std::ostream& out) const {
    out << "OrderCancelRequestMessage{";
    out << "inbound_business_header=";
    inbound_business_header_.print(out);
    out << ", offset_18_padding_2=";
    print::hex(out, offset_18_padding_2_.data(), offset_18_padding_2_.size());
    out << ", clordid=";
    out << clordid_;
    out << ", security_id=";
    out << security_id_;
    out << ", order_id_optional=";
    print::optional(out, order_id_optional_);
    out << ", origclordid=";
    print::optional(out, origclordid_);
    out << ", side=";
    out << side_;
    out << ", single_cancel_restatement_reason=";
    print::optional(out, single_cancel_restatement_reason_);
    out << ", offset_54_padding_2=";
    print::hex(out, offset_54_padding_2_.data(), offset_54_padding_2_.size());
    out << ", sender_location=";
    print::text(out, sender_location_);
    out << ", entering_trader=";
    print::text(out, entering_trader_);
    out << ", executing_trader_optional=";
    print::text(out, executing_trader_optional_);
    out << ", desk_id=";
    desk_id_.print(out);
    out << ", memo=";
    memo_.print(out);
    out << '}';
}

bool OrderCancelRequestMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderCancelRequestMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderCancelRequestMessage::operator==(const OrderCancelRequestMessage& other) const {
    return inbound_business_header_ == other.inbound_business_header_
        && offset_18_padding_2_ == other.offset_18_padding_2_
        && clordid_ == other.clordid_
        && security_id_ == other.security_id_
        && order_id_optional_ == other.order_id_optional_
        && origclordid_ == other.origclordid_
        && side_ == other.side_
        && single_cancel_restatement_reason_ == other.single_cancel_restatement_reason_
        && offset_54_padding_2_ == other.offset_54_padding_2_
        && sender_location_ == other.sender_location_
        && entering_trader_ == other.entering_trader_
        && executing_trader_optional_ == other.executing_trader_optional_
        && desk_id_ == other.desk_id_
        && memo_ == other.memo_;
}

bool OrderCancelRequestMessage::operator!=(const OrderCancelRequestMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
