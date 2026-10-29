#include "AddOrderExpandedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

AddOrderExpandedMessage::AddOrderExpandedMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, SideIndicator side_indicator, std::uint32_t quantity, const std::string& complex_instrument_id_8, Decimal price, const std::array<std::byte, 1>& reserved_1, const std::string& participant_id, CustomerIndicator customer_indicator, const std::string& client_id)
  : time_offset_(time_offset), order_id_(order_id), side_indicator_(side_indicator), quantity_(quantity), complex_instrument_id_8_(complex_instrument_id_8), price_(price), reserved_1_(reserved_1), participant_id_(participant_id), customer_indicator_(customer_indicator), client_id_(client_id) {}

std::chrono::nanoseconds AddOrderExpandedMessage::time_offset() const { return time_offset_; }
void AddOrderExpandedMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

std::uint64_t AddOrderExpandedMessage::order_id() const { return order_id_; }
void AddOrderExpandedMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

SideIndicator AddOrderExpandedMessage::side_indicator() const { return side_indicator_; }
void AddOrderExpandedMessage::set_side_indicator(SideIndicator value) { side_indicator_ = value; }

std::uint32_t AddOrderExpandedMessage::quantity() const { return quantity_; }
void AddOrderExpandedMessage::set_quantity(std::uint32_t value) { quantity_ = value; }

const std::string& AddOrderExpandedMessage::complex_instrument_id_8() const { return complex_instrument_id_8_; }
std::string& AddOrderExpandedMessage::complex_instrument_id_8() { return complex_instrument_id_8_; }
void AddOrderExpandedMessage::set_complex_instrument_id_8(const std::string& value) { complex_instrument_id_8_ = value; }

Decimal AddOrderExpandedMessage::price() const { return price_; }
void AddOrderExpandedMessage::set_price(Decimal value) { price_ = value; }

const std::array<std::byte, 1>& AddOrderExpandedMessage::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& AddOrderExpandedMessage::reserved_1() { return reserved_1_; }
void AddOrderExpandedMessage::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

const std::string& AddOrderExpandedMessage::participant_id() const { return participant_id_; }
std::string& AddOrderExpandedMessage::participant_id() { return participant_id_; }
void AddOrderExpandedMessage::set_participant_id(const std::string& value) { participant_id_ = value; }

CustomerIndicator AddOrderExpandedMessage::customer_indicator() const { return customer_indicator_; }
void AddOrderExpandedMessage::set_customer_indicator(CustomerIndicator value) { customer_indicator_ = value; }

const std::string& AddOrderExpandedMessage::client_id() const { return client_id_; }
std::string& AddOrderExpandedMessage::client_id() { return client_id_; }
void AddOrderExpandedMessage::set_client_id(const std::string& value) { client_id_ = value; }

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

    quantity_ = wire::read_u32_le(data + offset);
    offset += 4;

    complex_instrument_id_8_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    wire::read_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    participant_id_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    customer_indicator_ = static_cast<CustomerIndicator>(wire::read_char(data + offset));
    offset += 1;

    client_id_ = wire::read_text(data + offset, 4, ' ');
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

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(quantity_));
    offset += 4;

    wire::write_text(data + offset, 8, ' ', complex_instrument_id_8_);
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(price_.mantissa()));
    offset += 8;

    wire::write_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    wire::write_text(data + offset, 4, ' ', participant_id_);
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(customer_indicator_));
    offset += 1;

    wire::write_text(data + offset, 4, ' ', client_id_);
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
    out << ", quantity=";
    out << quantity_;
    out << ", complex_instrument_id_8=";
    print::text(out, complex_instrument_id_8_);
    out << ", price=";
    out << price_;
    out << ", reserved_1=";
    print::hex(out, reserved_1_.data(), reserved_1_.size());
    out << ", participant_id=";
    print::text(out, participant_id_);
    out << ", customer_indicator=";
    out << customer_indicator_;
    out << ", client_id=";
    print::text(out, client_id_);
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
        && quantity_ == other.quantity_
        && complex_instrument_id_8_ == other.complex_instrument_id_8_
        && price_ == other.price_
        && reserved_1_ == other.reserved_1_
        && participant_id_ == other.participant_id_
        && customer_indicator_ == other.customer_indicator_
        && client_id_ == other.client_id_;
}

bool AddOrderExpandedMessage::operator!=(const AddOrderExpandedMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::c1options::complex::pitch::v2_1_18
