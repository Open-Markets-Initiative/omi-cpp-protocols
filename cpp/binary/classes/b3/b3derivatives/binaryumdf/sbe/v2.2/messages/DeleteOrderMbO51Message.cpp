#include "DeleteOrderMbO51Message.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

DeleteOrderMbO51Message::DeleteOrderMbO51Message(std::uint64_t security_id, const MatchEventIndicator& match_event_indicator, const std::array<std::byte, 1>& offset_9_padding_1, MdEntryType md_entry_type, const std::array<std::byte, 5>& offset_11_padding_5, std::int64_t md_entry_size_quantity, std::uint64_t secondary_order_id, std::optional<std::uint64_t> transact_time, std::optional<std::uint32_t> rpt_seq, std::optional<Decimal> md_corporate_offset_price_optional)
  : security_id_(security_id), match_event_indicator_(match_event_indicator), offset_9_padding_1_(offset_9_padding_1), md_entry_type_(md_entry_type), offset_11_padding_5_(offset_11_padding_5), md_entry_size_quantity_(md_entry_size_quantity), secondary_order_id_(secondary_order_id), transact_time_(transact_time), rpt_seq_(rpt_seq), md_corporate_offset_price_optional_(md_corporate_offset_price_optional) {}

std::uint64_t DeleteOrderMbO51Message::security_id() const { return security_id_; }
void DeleteOrderMbO51Message::set_security_id(std::uint64_t value) { security_id_ = value; }

const MatchEventIndicator& DeleteOrderMbO51Message::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& DeleteOrderMbO51Message::match_event_indicator() { return match_event_indicator_; }
void DeleteOrderMbO51Message::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

const std::array<std::byte, 1>& DeleteOrderMbO51Message::offset_9_padding_1() const { return offset_9_padding_1_; }
std::array<std::byte, 1>& DeleteOrderMbO51Message::offset_9_padding_1() { return offset_9_padding_1_; }
void DeleteOrderMbO51Message::set_offset_9_padding_1(const std::array<std::byte, 1>& value) { offset_9_padding_1_ = value; }

MdEntryType DeleteOrderMbO51Message::md_entry_type() const { return md_entry_type_; }
void DeleteOrderMbO51Message::set_md_entry_type(MdEntryType value) { md_entry_type_ = value; }

const std::array<std::byte, 5>& DeleteOrderMbO51Message::offset_11_padding_5() const { return offset_11_padding_5_; }
std::array<std::byte, 5>& DeleteOrderMbO51Message::offset_11_padding_5() { return offset_11_padding_5_; }
void DeleteOrderMbO51Message::set_offset_11_padding_5(const std::array<std::byte, 5>& value) { offset_11_padding_5_ = value; }

std::int64_t DeleteOrderMbO51Message::md_entry_size_quantity() const { return md_entry_size_quantity_; }
void DeleteOrderMbO51Message::set_md_entry_size_quantity(std::int64_t value) { md_entry_size_quantity_ = value; }

std::uint64_t DeleteOrderMbO51Message::secondary_order_id() const { return secondary_order_id_; }
void DeleteOrderMbO51Message::set_secondary_order_id(std::uint64_t value) { secondary_order_id_ = value; }

std::optional<std::uint64_t> DeleteOrderMbO51Message::transact_time() const { return transact_time_; }
void DeleteOrderMbO51Message::set_transact_time(std::optional<std::uint64_t> value) { transact_time_ = value; }

std::optional<std::uint32_t> DeleteOrderMbO51Message::rpt_seq() const { return rpt_seq_; }
void DeleteOrderMbO51Message::set_rpt_seq(std::optional<std::uint32_t> value) { rpt_seq_ = value; }

std::optional<Decimal> DeleteOrderMbO51Message::md_corporate_offset_price_optional() const { return md_corporate_offset_price_optional_; }
void DeleteOrderMbO51Message::set_md_corporate_offset_price_optional(std::optional<Decimal> value) { md_corporate_offset_price_optional_ = value; }

MessageCode DeleteOrderMbO51Message::type() const { return message_type; }

std::string_view DeleteOrderMbO51Message::name() const { return "Delete Order Mb O 51 Message"; }

std::size_t DeleteOrderMbO51Message::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("DeleteOrderMbO51Message", wire_size, length);

    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    wire::read_bytes(data + offset, offset_9_padding_1_.data(), 1);
    offset += 1;

    md_entry_type_ = static_cast<MdEntryType>(wire::read_char(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, offset_11_padding_5_.data(), 5);
    offset += 5;

    md_entry_size_quantity_ = wire::read_i64_le(data + offset);
    offset += 8;

    secondary_order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    transact_time_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    rpt_seq_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    md_corporate_offset_price_optional_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4);
    offset += 8;

    return offset;
}

std::size_t DeleteOrderMbO51Message::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("DeleteOrderMbO51Message", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    wire::write_bytes(data + offset, offset_9_padding_1_.data(), 1);
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(md_entry_type_));
    offset += 1;

    wire::write_bytes(data + offset, offset_11_padding_5_.data(), 5);
    offset += 5;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(md_entry_size_quantity_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(secondary_order_id_));
    offset += 8;

    wire::write_u64_le(data + offset, transact_time_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_u32_le(data + offset, rpt_seq_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_i64_le(data + offset, md_corporate_offset_price_optional_ ? static_cast<std::int64_t>(md_corporate_offset_price_optional_->mantissa()) : static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    return offset;
}

std::size_t DeleteOrderMbO51Message::encoded_size() const {
    return wire_size;
}

void DeleteOrderMbO51Message::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> DeleteOrderMbO51Message::clone() const {
    return std::make_unique<DeleteOrderMbO51Message>(*this);
}

void DeleteOrderMbO51Message::print(std::ostream& out) const {
    out << "DeleteOrderMbO51Message{";
    out << "security_id=";
    out << security_id_;
    out << ", match_event_indicator=";
    match_event_indicator_.print(out);
    out << ", offset_9_padding_1=";
    print::hex(out, offset_9_padding_1_.data(), offset_9_padding_1_.size());
    out << ", md_entry_type=";
    out << md_entry_type_;
    out << ", offset_11_padding_5=";
    print::hex(out, offset_11_padding_5_.data(), offset_11_padding_5_.size());
    out << ", md_entry_size_quantity=";
    out << md_entry_size_quantity_;
    out << ", secondary_order_id=";
    out << secondary_order_id_;
    out << ", transact_time=";
    print::optional(out, transact_time_);
    out << ", rpt_seq=";
    print::optional(out, rpt_seq_);
    out << ", md_corporate_offset_price_optional=";
    print::optional(out, md_corporate_offset_price_optional_);
    out << '}';
}

bool DeleteOrderMbO51Message::equals(const Message& other) const {
    const auto* that = dynamic_cast<const DeleteOrderMbO51Message*>(&other);
    return that != nullptr && *this == *that;
}

bool DeleteOrderMbO51Message::operator==(const DeleteOrderMbO51Message& other) const {
    return security_id_ == other.security_id_
        && match_event_indicator_ == other.match_event_indicator_
        && offset_9_padding_1_ == other.offset_9_padding_1_
        && md_entry_type_ == other.md_entry_type_
        && offset_11_padding_5_ == other.offset_11_padding_5_
        && md_entry_size_quantity_ == other.md_entry_size_quantity_
        && secondary_order_id_ == other.secondary_order_id_
        && transact_time_ == other.transact_time_
        && rpt_seq_ == other.rpt_seq_
        && md_corporate_offset_price_optional_ == other.md_corporate_offset_price_optional_;
}

bool DeleteOrderMbO51Message::operator!=(const DeleteOrderMbO51Message& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_2
