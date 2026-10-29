#include "NewOrderCrossMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

NewOrderCrossMessage::NewOrderCrossMessage(const InboundBusinessHeader& inbound_business_header, const std::array<std::byte, 2>& offset_18_padding_2, std::uint64_t crossid, const std::string& sender_location, const std::string& entering_trader, const std::string& executing_trader_optional, std::uint64_t security_id, std::uint64_t order_qty, Decimal price, std::optional<CrossedIndicator> crossed_indicator, std::optional<CrossType> cross_type, std::optional<CrossPrioritization> cross_prioritization, std::optional<std::uint64_t> max_sweep_qty, const CrossSidesGroups& cross_sides_groups, const DeskId& desk_id, const Memo& memo)
  : inbound_business_header_(inbound_business_header), offset_18_padding_2_(offset_18_padding_2), crossid_(crossid), sender_location_(sender_location), entering_trader_(entering_trader), executing_trader_optional_(executing_trader_optional), security_id_(security_id), order_qty_(order_qty), price_(price), crossed_indicator_(crossed_indicator), cross_type_(cross_type), cross_prioritization_(cross_prioritization), max_sweep_qty_(max_sweep_qty), cross_sides_groups_(cross_sides_groups), desk_id_(desk_id), memo_(memo) {}

const InboundBusinessHeader& NewOrderCrossMessage::inbound_business_header() const { return inbound_business_header_; }
InboundBusinessHeader& NewOrderCrossMessage::inbound_business_header() { return inbound_business_header_; }
void NewOrderCrossMessage::set_inbound_business_header(const InboundBusinessHeader& value) { inbound_business_header_ = value; }

const std::array<std::byte, 2>& NewOrderCrossMessage::offset_18_padding_2() const { return offset_18_padding_2_; }
std::array<std::byte, 2>& NewOrderCrossMessage::offset_18_padding_2() { return offset_18_padding_2_; }
void NewOrderCrossMessage::set_offset_18_padding_2(const std::array<std::byte, 2>& value) { offset_18_padding_2_ = value; }

std::uint64_t NewOrderCrossMessage::crossid() const { return crossid_; }
void NewOrderCrossMessage::set_crossid(std::uint64_t value) { crossid_ = value; }

const std::string& NewOrderCrossMessage::sender_location() const { return sender_location_; }
std::string& NewOrderCrossMessage::sender_location() { return sender_location_; }
void NewOrderCrossMessage::set_sender_location(const std::string& value) { sender_location_ = value; }

const std::string& NewOrderCrossMessage::entering_trader() const { return entering_trader_; }
std::string& NewOrderCrossMessage::entering_trader() { return entering_trader_; }
void NewOrderCrossMessage::set_entering_trader(const std::string& value) { entering_trader_ = value; }

const std::string& NewOrderCrossMessage::executing_trader_optional() const { return executing_trader_optional_; }
std::string& NewOrderCrossMessage::executing_trader_optional() { return executing_trader_optional_; }
void NewOrderCrossMessage::set_executing_trader_optional(const std::string& value) { executing_trader_optional_ = value; }

std::uint64_t NewOrderCrossMessage::security_id() const { return security_id_; }
void NewOrderCrossMessage::set_security_id(std::uint64_t value) { security_id_ = value; }

std::uint64_t NewOrderCrossMessage::order_qty() const { return order_qty_; }
void NewOrderCrossMessage::set_order_qty(std::uint64_t value) { order_qty_ = value; }

Decimal NewOrderCrossMessage::price() const { return price_; }
void NewOrderCrossMessage::set_price(Decimal value) { price_ = value; }

std::optional<CrossedIndicator> NewOrderCrossMessage::crossed_indicator() const { return crossed_indicator_; }
void NewOrderCrossMessage::set_crossed_indicator(std::optional<CrossedIndicator> value) { crossed_indicator_ = value; }

std::optional<CrossType> NewOrderCrossMessage::cross_type() const { return cross_type_; }
void NewOrderCrossMessage::set_cross_type(std::optional<CrossType> value) { cross_type_ = value; }

std::optional<CrossPrioritization> NewOrderCrossMessage::cross_prioritization() const { return cross_prioritization_; }
void NewOrderCrossMessage::set_cross_prioritization(std::optional<CrossPrioritization> value) { cross_prioritization_ = value; }

std::optional<std::uint64_t> NewOrderCrossMessage::max_sweep_qty() const { return max_sweep_qty_; }
void NewOrderCrossMessage::set_max_sweep_qty(std::optional<std::uint64_t> value) { max_sweep_qty_ = value; }

const CrossSidesGroups& NewOrderCrossMessage::cross_sides_groups() const { return cross_sides_groups_; }
CrossSidesGroups& NewOrderCrossMessage::cross_sides_groups() { return cross_sides_groups_; }
void NewOrderCrossMessage::set_cross_sides_groups(const CrossSidesGroups& value) { cross_sides_groups_ = value; }

const DeskId& NewOrderCrossMessage::desk_id() const { return desk_id_; }
DeskId& NewOrderCrossMessage::desk_id() { return desk_id_; }
void NewOrderCrossMessage::set_desk_id(const DeskId& value) { desk_id_ = value; }

const Memo& NewOrderCrossMessage::memo() const { return memo_; }
Memo& NewOrderCrossMessage::memo() { return memo_; }
void NewOrderCrossMessage::set_memo(const Memo& value) { memo_ = value; }

MessageCode NewOrderCrossMessage::type() const { return message_type; }

std::string_view NewOrderCrossMessage::name() const { return "New Order Cross Message"; }

std::size_t NewOrderCrossMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += inbound_business_header_.decode(data + offset, length - offset);

    wire::require("NewOrderCrossMessage", offset + 2, length);
    wire::read_bytes(data + offset, offset_18_padding_2_.data(), 2);
    offset += 2;

    wire::require("NewOrderCrossMessage", offset + 8, length);
    crossid_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("NewOrderCrossMessage", offset + 10, length);
    sender_location_ = wire::read_text(data + offset, 10, '\0');
    offset += 10;

    wire::require("NewOrderCrossMessage", offset + 5, length);
    entering_trader_ = wire::read_text(data + offset, 5, '\0');
    offset += 5;

    wire::require("NewOrderCrossMessage", offset + 5, length);
    executing_trader_optional_ = wire::read_text(data + offset, 5, '\0');
    offset += 5;

    wire::require("NewOrderCrossMessage", offset + 8, length);
    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("NewOrderCrossMessage", offset + 8, length);
    order_qty_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("NewOrderCrossMessage", offset + 8, length);
    price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    wire::require("NewOrderCrossMessage", offset + 2, length);
    crossed_indicator_ = wire::nullable_enum<CrossedIndicator>(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0ULL));
    offset += 2;

    wire::require("NewOrderCrossMessage", offset + 1, length);
    cross_type_ = wire::nullable_enum<CrossType>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::require("NewOrderCrossMessage", offset + 1, length);
    cross_prioritization_ = wire::nullable_enum<CrossPrioritization>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::require("NewOrderCrossMessage", offset + 8, length);
    max_sweep_qty_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    offset += cross_sides_groups_.decode(data + offset, length - offset);

    offset += desk_id_.decode(data + offset, length - offset);

    offset += memo_.decode(data + offset, length - offset);

    return offset;
}

std::size_t NewOrderCrossMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("NewOrderCrossMessage", encoded_size(), capacity);

    offset += inbound_business_header_.encode(data + offset, capacity - offset);

    wire::write_bytes(data + offset, offset_18_padding_2_.data(), 2);
    offset += 2;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(crossid_));
    offset += 8;

    wire::write_text(data + offset, 10, '\0', sender_location_);
    offset += 10;

    wire::write_text(data + offset, 5, '\0', entering_trader_);
    offset += 5;

    wire::write_text(data + offset, 5, '\0', executing_trader_optional_);
    offset += 5;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_qty_));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(price_.mantissa()));
    offset += 8;

    wire::write_u16_le(data + offset, crossed_indicator_ ? static_cast<std::uint16_t>(*crossed_indicator_) : static_cast<std::uint16_t>(0ULL));
    offset += 2;

    wire::write_u8(data + offset, cross_type_ ? static_cast<std::uint8_t>(*cross_type_) : static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::write_u8(data + offset, cross_prioritization_ ? static_cast<std::uint8_t>(*cross_prioritization_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::write_u64_le(data + offset, max_sweep_qty_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    offset += cross_sides_groups_.encode(data + offset, capacity - offset);

    offset += desk_id_.encode(data + offset, capacity - offset);

    offset += memo_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t NewOrderCrossMessage::encoded_size() const {
    return inbound_business_header_.encoded_size() + 2 + 8 + 10 + 5 + 5 + 8 + 8 + 8 + 2 + 1 + 1 + 8 + cross_sides_groups_.encoded_size() + desk_id_.encoded_size() + memo_.encoded_size();
}

void NewOrderCrossMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> NewOrderCrossMessage::clone() const {
    return std::make_unique<NewOrderCrossMessage>(*this);
}

void NewOrderCrossMessage::print(std::ostream& out) const {
    out << "NewOrderCrossMessage{";
    out << "inbound_business_header=";
    inbound_business_header_.print(out);
    out << ", offset_18_padding_2=";
    print::hex(out, offset_18_padding_2_.data(), offset_18_padding_2_.size());
    out << ", crossid=";
    out << crossid_;
    out << ", sender_location=";
    print::text(out, sender_location_);
    out << ", entering_trader=";
    print::text(out, entering_trader_);
    out << ", executing_trader_optional=";
    print::text(out, executing_trader_optional_);
    out << ", security_id=";
    out << security_id_;
    out << ", order_qty=";
    out << order_qty_;
    out << ", price=";
    out << price_;
    out << ", crossed_indicator=";
    print::optional(out, crossed_indicator_);
    out << ", cross_type=";
    print::optional(out, cross_type_);
    out << ", cross_prioritization=";
    print::optional(out, cross_prioritization_);
    out << ", max_sweep_qty=";
    print::optional(out, max_sweep_qty_);
    out << ", cross_sides_groups=";
    cross_sides_groups_.print(out);
    out << ", desk_id=";
    desk_id_.print(out);
    out << ", memo=";
    memo_.print(out);
    out << '}';
}

bool NewOrderCrossMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const NewOrderCrossMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool NewOrderCrossMessage::operator==(const NewOrderCrossMessage& other) const {
    return inbound_business_header_ == other.inbound_business_header_
        && offset_18_padding_2_ == other.offset_18_padding_2_
        && crossid_ == other.crossid_
        && sender_location_ == other.sender_location_
        && entering_trader_ == other.entering_trader_
        && executing_trader_optional_ == other.executing_trader_optional_
        && security_id_ == other.security_id_
        && order_qty_ == other.order_qty_
        && price_ == other.price_
        && crossed_indicator_ == other.crossed_indicator_
        && cross_type_ == other.cross_type_
        && cross_prioritization_ == other.cross_prioritization_
        && max_sweep_qty_ == other.max_sweep_qty_
        && cross_sides_groups_ == other.cross_sides_groups_
        && desk_id_ == other.desk_id_
        && memo_ == other.memo_;
}

bool NewOrderCrossMessage::operator!=(const NewOrderCrossMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
