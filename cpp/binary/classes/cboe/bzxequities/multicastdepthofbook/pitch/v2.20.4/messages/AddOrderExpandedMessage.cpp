#include "AddOrderExpandedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

AddOrderExpandedMessage::AddOrderExpandedMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, SideIndicator side_indicator, std::uint32_t quantity_binary_4, const std::string& symbol_long, Decimal price_binary_long_price_8, const AddFlags& add_flags, const std::string& participant_id)
  : time_offset_(time_offset), order_id_(order_id), side_indicator_(side_indicator), quantity_binary_4_(quantity_binary_4), symbol_long_(symbol_long), price_binary_long_price_8_(price_binary_long_price_8), add_flags_(add_flags), participant_id_(participant_id) {}

std::chrono::nanoseconds AddOrderExpandedMessage::time_offset() const { return time_offset_; }
void AddOrderExpandedMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

std::uint64_t AddOrderExpandedMessage::order_id() const { return order_id_; }
void AddOrderExpandedMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

SideIndicator AddOrderExpandedMessage::side_indicator() const { return side_indicator_; }
void AddOrderExpandedMessage::set_side_indicator(SideIndicator value) { side_indicator_ = value; }

std::uint32_t AddOrderExpandedMessage::quantity_binary_4() const { return quantity_binary_4_; }
void AddOrderExpandedMessage::set_quantity_binary_4(std::uint32_t value) { quantity_binary_4_ = value; }

const std::string& AddOrderExpandedMessage::symbol_long() const { return symbol_long_; }
std::string& AddOrderExpandedMessage::symbol_long() { return symbol_long_; }
void AddOrderExpandedMessage::set_symbol_long(const std::string& value) { symbol_long_ = value; }

Decimal AddOrderExpandedMessage::price_binary_long_price_8() const { return price_binary_long_price_8_; }
void AddOrderExpandedMessage::set_price_binary_long_price_8(Decimal value) { price_binary_long_price_8_ = value; }

const AddFlags& AddOrderExpandedMessage::add_flags() const { return add_flags_; }
AddFlags& AddOrderExpandedMessage::add_flags() { return add_flags_; }
void AddOrderExpandedMessage::set_add_flags(const AddFlags& value) { add_flags_ = value; }

const std::string& AddOrderExpandedMessage::participant_id() const { return participant_id_; }
std::string& AddOrderExpandedMessage::participant_id() { return participant_id_; }
void AddOrderExpandedMessage::set_participant_id(const std::string& value) { participant_id_ = value; }

MessageCode AddOrderExpandedMessage::type() const { return message_type; }

std::string_view AddOrderExpandedMessage::name() const { return "Add Order Expanded Message"; }

std::size_t AddOrderExpandedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AddOrderExpandedMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    side_indicator_ = static_cast<SideIndicator>(wire::read_char(data + offset));
    offset += 1;

    quantity_binary_4_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_long_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    price_binary_long_price_8_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -4);
    offset += 8;

    offset += add_flags_.decode(data + offset, length - offset);

    participant_id_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    return offset;
}

std::size_t AddOrderExpandedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AddOrderExpandedMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(side_indicator_));
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(quantity_binary_4_));
    offset += 4;

    wire::write_text(data + offset, 8, ' ', symbol_long_);
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(price_binary_long_price_8_.mantissa()));
    offset += 8;

    offset += add_flags_.encode(data + offset, capacity - offset);

    wire::write_text(data + offset, 4, ' ', participant_id_);
    offset += 4;

    return offset;
}

std::size_t AddOrderExpandedMessage::encoded_size() const {
    return wire_size;
}

void AddOrderExpandedMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AddOrderExpandedMessage::clone() const {
    return std::make_unique<AddOrderExpandedMessage>(*this);
}

void AddOrderExpandedMessage::print(std::ostream& out) const {
    out << "AddOrderExpandedMessage{";
    out << "time_offset=";
    out << time_offset_.count();
    out << ", order_id=";
    out << order_id_;
    out << ", side_indicator=";
    out << side_indicator_;
    out << ", quantity_binary_4=";
    out << quantity_binary_4_;
    out << ", symbol_long=";
    print::text(out, symbol_long_);
    out << ", price_binary_long_price_8=";
    out << price_binary_long_price_8_;
    out << ", add_flags=";
    add_flags_.print(out);
    out << ", participant_id=";
    print::text(out, participant_id_);
    out << '}';
}

bool AddOrderExpandedMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AddOrderExpandedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AddOrderExpandedMessage::operator==(const AddOrderExpandedMessage& other) const {
    return time_offset_ == other.time_offset_
        && order_id_ == other.order_id_
        && side_indicator_ == other.side_indicator_
        && quantity_binary_4_ == other.quantity_binary_4_
        && symbol_long_ == other.symbol_long_
        && price_binary_long_price_8_ == other.price_binary_long_price_8_
        && add_flags_ == other.add_flags_
        && participant_id_ == other.participant_id_;
}

bool AddOrderExpandedMessage::operator!=(const AddOrderExpandedMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4
