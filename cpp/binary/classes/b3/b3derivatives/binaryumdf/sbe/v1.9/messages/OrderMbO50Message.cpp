#include "OrderMbO50Message.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

OrderMbO50Message::OrderMbO50Message(std::uint64_t security_id, const MatchEventIndicator& match_event_indicator, MdUpdateAction md_update_action, MdEntryType md_entry_type, const std::array<std::byte, 1>& offset_11_padding_1, std::optional<Decimal> md_corporate_offset_price_optional, std::int64_t md_entry_size_quantity, std::uint32_t md_entry_position_no, std::optional<std::uint32_t> entering_firm, std::optional<std::chrono::nanoseconds> md_insert_timestamp, std::uint64_t secondary_order_id, std::optional<std::uint32_t> rpt_seq, std::optional<std::chrono::nanoseconds> md_entry_timestamp)
  : security_id_(security_id), match_event_indicator_(match_event_indicator), md_update_action_(md_update_action), md_entry_type_(md_entry_type), offset_11_padding_1_(offset_11_padding_1), md_corporate_offset_price_optional_(md_corporate_offset_price_optional), md_entry_size_quantity_(md_entry_size_quantity), md_entry_position_no_(md_entry_position_no), entering_firm_(entering_firm), md_insert_timestamp_(md_insert_timestamp), secondary_order_id_(secondary_order_id), rpt_seq_(rpt_seq), md_entry_timestamp_(md_entry_timestamp) {}

std::uint64_t OrderMbO50Message::security_id() const { return security_id_; }
void OrderMbO50Message::set_security_id(std::uint64_t value) { security_id_ = value; }

const MatchEventIndicator& OrderMbO50Message::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& OrderMbO50Message::match_event_indicator() { return match_event_indicator_; }
void OrderMbO50Message::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

MdUpdateAction OrderMbO50Message::md_update_action() const { return md_update_action_; }
void OrderMbO50Message::set_md_update_action(MdUpdateAction value) { md_update_action_ = value; }

MdEntryType OrderMbO50Message::md_entry_type() const { return md_entry_type_; }
void OrderMbO50Message::set_md_entry_type(MdEntryType value) { md_entry_type_ = value; }

const std::array<std::byte, 1>& OrderMbO50Message::offset_11_padding_1() const { return offset_11_padding_1_; }
std::array<std::byte, 1>& OrderMbO50Message::offset_11_padding_1() { return offset_11_padding_1_; }
void OrderMbO50Message::set_offset_11_padding_1(const std::array<std::byte, 1>& value) { offset_11_padding_1_ = value; }

std::optional<Decimal> OrderMbO50Message::md_corporate_offset_price_optional() const { return md_corporate_offset_price_optional_; }
void OrderMbO50Message::set_md_corporate_offset_price_optional(std::optional<Decimal> value) { md_corporate_offset_price_optional_ = value; }

std::int64_t OrderMbO50Message::md_entry_size_quantity() const { return md_entry_size_quantity_; }
void OrderMbO50Message::set_md_entry_size_quantity(std::int64_t value) { md_entry_size_quantity_ = value; }

std::uint32_t OrderMbO50Message::md_entry_position_no() const { return md_entry_position_no_; }
void OrderMbO50Message::set_md_entry_position_no(std::uint32_t value) { md_entry_position_no_ = value; }

std::optional<std::uint32_t> OrderMbO50Message::entering_firm() const { return entering_firm_; }
void OrderMbO50Message::set_entering_firm(std::optional<std::uint32_t> value) { entering_firm_ = value; }

std::optional<std::chrono::nanoseconds> OrderMbO50Message::md_insert_timestamp() const { return md_insert_timestamp_; }
void OrderMbO50Message::set_md_insert_timestamp(std::optional<std::chrono::nanoseconds> value) { md_insert_timestamp_ = value; }

std::uint64_t OrderMbO50Message::secondary_order_id() const { return secondary_order_id_; }
void OrderMbO50Message::set_secondary_order_id(std::uint64_t value) { secondary_order_id_ = value; }

std::optional<std::uint32_t> OrderMbO50Message::rpt_seq() const { return rpt_seq_; }
void OrderMbO50Message::set_rpt_seq(std::optional<std::uint32_t> value) { rpt_seq_ = value; }

std::optional<std::chrono::nanoseconds> OrderMbO50Message::md_entry_timestamp() const { return md_entry_timestamp_; }
void OrderMbO50Message::set_md_entry_timestamp(std::optional<std::chrono::nanoseconds> value) { md_entry_timestamp_ = value; }

MessageCode OrderMbO50Message::type() const { return message_type; }

std::string_view OrderMbO50Message::name() const { return "Order Mb O 50 Message"; }

std::size_t OrderMbO50Message::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderMbO50Message", wire_size, length);

    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    md_update_action_ = static_cast<MdUpdateAction>(wire::read_u8(data + offset));
    offset += 1;

    md_entry_type_ = static_cast<MdEntryType>(wire::read_char(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, offset_11_padding_1_.data(), 1);
    offset += 1;

    md_corporate_offset_price_optional_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4);
    offset += 8;

    md_entry_size_quantity_ = wire::read_i64_le(data + offset);
    offset += 8;

    md_entry_position_no_ = wire::read_u32_le(data + offset);
    offset += 4;

    entering_firm_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    md_insert_timestamp_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    secondary_order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    rpt_seq_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    md_entry_timestamp_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    return offset;
}

std::size_t OrderMbO50Message::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderMbO50Message", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(md_update_action_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(md_entry_type_));
    offset += 1;

    wire::write_bytes(data + offset, offset_11_padding_1_.data(), 1);
    offset += 1;

    wire::write_i64_le(data + offset, md_corporate_offset_price_optional_ ? static_cast<std::int64_t>(md_corporate_offset_price_optional_->mantissa()) : static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(md_entry_size_quantity_));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(md_entry_position_no_));
    offset += 4;

    wire::write_u32_le(data + offset, entering_firm_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_u64_le(data + offset, md_insert_timestamp_ ? static_cast<std::uint64_t>(md_insert_timestamp_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(secondary_order_id_));
    offset += 8;

    wire::write_u32_le(data + offset, rpt_seq_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_u64_le(data + offset, md_entry_timestamp_ ? static_cast<std::uint64_t>(md_entry_timestamp_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    return offset;
}

std::size_t OrderMbO50Message::encoded_size() const {
    return wire_size;
}

void OrderMbO50Message::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderMbO50Message::clone() const {
    return std::make_unique<OrderMbO50Message>(*this);
}

void OrderMbO50Message::print(std::ostream& out) const {
    out << "OrderMbO50Message{";
    out << "security_id=";
    out << security_id_;
    out << ", match_event_indicator=";
    match_event_indicator_.print(out);
    out << ", md_update_action=";
    out << md_update_action_;
    out << ", md_entry_type=";
    out << md_entry_type_;
    out << ", offset_11_padding_1=";
    print::hex(out, offset_11_padding_1_.data(), offset_11_padding_1_.size());
    out << ", md_corporate_offset_price_optional=";
    print::optional(out, md_corporate_offset_price_optional_);
    out << ", md_entry_size_quantity=";
    out << md_entry_size_quantity_;
    out << ", md_entry_position_no=";
    out << md_entry_position_no_;
    out << ", entering_firm=";
    print::optional(out, entering_firm_);
    out << ", md_insert_timestamp=";
    print::optional_duration(out, md_insert_timestamp_);
    out << ", secondary_order_id=";
    out << secondary_order_id_;
    out << ", rpt_seq=";
    print::optional(out, rpt_seq_);
    out << ", md_entry_timestamp=";
    print::optional_duration(out, md_entry_timestamp_);
    out << '}';
}

bool OrderMbO50Message::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderMbO50Message*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderMbO50Message::operator==(const OrderMbO50Message& other) const {
    return security_id_ == other.security_id_
        && match_event_indicator_ == other.match_event_indicator_
        && md_update_action_ == other.md_update_action_
        && md_entry_type_ == other.md_entry_type_
        && offset_11_padding_1_ == other.offset_11_padding_1_
        && md_corporate_offset_price_optional_ == other.md_corporate_offset_price_optional_
        && md_entry_size_quantity_ == other.md_entry_size_quantity_
        && md_entry_position_no_ == other.md_entry_position_no_
        && entering_firm_ == other.entering_firm_
        && md_insert_timestamp_ == other.md_insert_timestamp_
        && secondary_order_id_ == other.secondary_order_id_
        && rpt_seq_ == other.rpt_seq_
        && md_entry_timestamp_ == other.md_entry_timestamp_;
}

bool OrderMbO50Message::operator!=(const OrderMbO50Message& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_9
