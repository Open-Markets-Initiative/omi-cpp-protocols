#include "AddOrderExpandedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

AddOrderExpandedMessage::AddOrderExpandedMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, SideIndicator side_indicator, std::uint32_t quantity_long, const std::string& expanded_symbol, Decimal price_long, const AddFlags& add_flags, const std::string& participant_id, CustomerIndicator customer_indicator, const std::string& client_id, const std::array<std::byte, 5>& reserved_5)
  : time_offset_(time_offset), order_id_(order_id), side_indicator_(side_indicator), quantity_long_(quantity_long), expanded_symbol_(expanded_symbol), price_long_(price_long), add_flags_(add_flags), participant_id_(participant_id), customer_indicator_(customer_indicator), client_id_(client_id), reserved_5_(reserved_5) {}

std::chrono::nanoseconds AddOrderExpandedMessage::time_offset() const { return time_offset_; }
void AddOrderExpandedMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

std::uint64_t AddOrderExpandedMessage::order_id() const { return order_id_; }
void AddOrderExpandedMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

SideIndicator AddOrderExpandedMessage::side_indicator() const { return side_indicator_; }
void AddOrderExpandedMessage::set_side_indicator(SideIndicator value) { side_indicator_ = value; }

std::uint32_t AddOrderExpandedMessage::quantity_long() const { return quantity_long_; }
void AddOrderExpandedMessage::set_quantity_long(std::uint32_t value) { quantity_long_ = value; }

const std::string& AddOrderExpandedMessage::expanded_symbol() const { return expanded_symbol_; }
std::string& AddOrderExpandedMessage::expanded_symbol() { return expanded_symbol_; }
void AddOrderExpandedMessage::set_expanded_symbol(const std::string& value) { expanded_symbol_ = value; }

Decimal AddOrderExpandedMessage::price_long() const { return price_long_; }
void AddOrderExpandedMessage::set_price_long(Decimal value) { price_long_ = value; }

const AddFlags& AddOrderExpandedMessage::add_flags() const { return add_flags_; }
AddFlags& AddOrderExpandedMessage::add_flags() { return add_flags_; }
void AddOrderExpandedMessage::set_add_flags(const AddFlags& value) { add_flags_ = value; }

const std::string& AddOrderExpandedMessage::participant_id() const { return participant_id_; }
std::string& AddOrderExpandedMessage::participant_id() { return participant_id_; }
void AddOrderExpandedMessage::set_participant_id(const std::string& value) { participant_id_ = value; }

CustomerIndicator AddOrderExpandedMessage::customer_indicator() const { return customer_indicator_; }
void AddOrderExpandedMessage::set_customer_indicator(CustomerIndicator value) { customer_indicator_ = value; }

const std::string& AddOrderExpandedMessage::client_id() const { return client_id_; }
std::string& AddOrderExpandedMessage::client_id() { return client_id_; }
void AddOrderExpandedMessage::set_client_id(const std::string& value) { client_id_ = value; }

const std::array<std::byte, 5>& AddOrderExpandedMessage::reserved_5() const { return reserved_5_; }
std::array<std::byte, 5>& AddOrderExpandedMessage::reserved_5() { return reserved_5_; }
void AddOrderExpandedMessage::set_reserved_5(const std::array<std::byte, 5>& value) { reserved_5_ = value; }

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

    quantity_long_ = wire::read_u32_le(data + offset);
    offset += 4;

    expanded_symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    price_long_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -4);
    offset += 8;

    offset += add_flags_.decode(data + offset, length - offset);

    participant_id_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    customer_indicator_ = static_cast<CustomerIndicator>(wire::read_char(data + offset));
    offset += 1;

    client_id_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    wire::read_bytes(data + offset, reserved_5_.data(), 5);
    offset += 5;

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

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(quantity_long_));
    offset += 4;

    wire::write_text(data + offset, 8, ' ', expanded_symbol_);
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(price_long_.mantissa()));
    offset += 8;

    offset += add_flags_.encode(data + offset, capacity - offset);

    wire::write_text(data + offset, 4, ' ', participant_id_);
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(customer_indicator_));
    offset += 1;

    wire::write_text(data + offset, 4, ' ', client_id_);
    offset += 4;

    wire::write_bytes(data + offset, reserved_5_.data(), 5);
    offset += 5;

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
    out << ", quantity_long=";
    out << quantity_long_;
    out << ", expanded_symbol=";
    print::text(out, expanded_symbol_);
    out << ", price_long=";
    out << price_long_;
    out << ", add_flags=";
    add_flags_.print(out);
    out << ", participant_id=";
    print::text(out, participant_id_);
    out << ", customer_indicator=";
    out << customer_indicator_;
    out << ", client_id=";
    print::text(out, client_id_);
    out << ", reserved_5=";
    print::hex(out, reserved_5_.data(), reserved_5_.size());
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
        && quantity_long_ == other.quantity_long_
        && expanded_symbol_ == other.expanded_symbol_
        && price_long_ == other.price_long_
        && add_flags_ == other.add_flags_
        && participant_id_ == other.participant_id_
        && customer_indicator_ == other.customer_indicator_
        && client_id_ == other.client_id_
        && reserved_5_ == other.reserved_5_;
}

bool AddOrderExpandedMessage::operator!=(const AddOrderExpandedMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
