#include "AddOrderMpidAttributionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

AddOrderMpidAttributionMessage::AddOrderMpidAttributionMessage(std::chrono::nanoseconds timestamp, std::uint16_t tracking_number, std::uint64_t order_reference_number, BuySellIndicator buy_sell_indicator, std::uint32_t quantity, std::uint32_t order_book, Decimal price, const std::string& attribution)
  : timestamp_(timestamp), tracking_number_(tracking_number), order_reference_number_(order_reference_number), buy_sell_indicator_(buy_sell_indicator), quantity_(quantity), order_book_(order_book), price_(price), attribution_(attribution) {}

std::chrono::nanoseconds AddOrderMpidAttributionMessage::timestamp() const { return timestamp_; }
void AddOrderMpidAttributionMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint16_t AddOrderMpidAttributionMessage::tracking_number() const { return tracking_number_; }
void AddOrderMpidAttributionMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::uint64_t AddOrderMpidAttributionMessage::order_reference_number() const { return order_reference_number_; }
void AddOrderMpidAttributionMessage::set_order_reference_number(std::uint64_t value) { order_reference_number_ = value; }

BuySellIndicator AddOrderMpidAttributionMessage::buy_sell_indicator() const { return buy_sell_indicator_; }
void AddOrderMpidAttributionMessage::set_buy_sell_indicator(BuySellIndicator value) { buy_sell_indicator_ = value; }

std::uint32_t AddOrderMpidAttributionMessage::quantity() const { return quantity_; }
void AddOrderMpidAttributionMessage::set_quantity(std::uint32_t value) { quantity_ = value; }

std::uint32_t AddOrderMpidAttributionMessage::order_book() const { return order_book_; }
void AddOrderMpidAttributionMessage::set_order_book(std::uint32_t value) { order_book_ = value; }

Decimal AddOrderMpidAttributionMessage::price() const { return price_; }
void AddOrderMpidAttributionMessage::set_price(Decimal value) { price_ = value; }

const std::string& AddOrderMpidAttributionMessage::attribution() const { return attribution_; }
std::string& AddOrderMpidAttributionMessage::attribution() { return attribution_; }
void AddOrderMpidAttributionMessage::set_attribution(const std::string& value) { attribution_ = value; }

MessageCode AddOrderMpidAttributionMessage::type() const { return message_type; }

std::string_view AddOrderMpidAttributionMessage::name() const { return "Add Order Mpid Attribution Message"; }

std::size_t AddOrderMpidAttributionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AddOrderMpidAttributionMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(data + offset)));
    offset += 8;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    order_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    buy_sell_indicator_ = static_cast<BuySellIndicator>(wire::read_char(data + offset));
    offset += 1;

    quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    order_book_ = wire::read_u32_be(data + offset);
    offset += 4;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    attribution_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    return offset;
}

std::size_t AddOrderMpidAttributionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AddOrderMpidAttributionMessage", wire_size, capacity);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_reference_number_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(buy_sell_indicator_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(quantity_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(order_book_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(price_.mantissa()));
    offset += 4;

    wire::write_text(data + offset, 4, ' ', attribution_);
    offset += 4;

    return offset;
}

std::size_t AddOrderMpidAttributionMessage::encoded_size() const {
    return wire_size;
}

void AddOrderMpidAttributionMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AddOrderMpidAttributionMessage::clone() const {
    return std::make_unique<AddOrderMpidAttributionMessage>(*this);
}

void AddOrderMpidAttributionMessage::print(std::ostream& out) const {
    out << "AddOrderMpidAttributionMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", order_reference_number=";
    out << order_reference_number_;
    out << ", buy_sell_indicator=";
    out << buy_sell_indicator_;
    out << ", quantity=";
    out << quantity_;
    out << ", order_book=";
    out << order_book_;
    out << ", price=";
    out << price_;
    out << ", attribution=";
    print::text(out, attribution_);
    out << '}';
}

bool AddOrderMpidAttributionMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AddOrderMpidAttributionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AddOrderMpidAttributionMessage::operator==(const AddOrderMpidAttributionMessage& other) const {
    return timestamp_ == other.timestamp_
        && tracking_number_ == other.tracking_number_
        && order_reference_number_ == other.order_reference_number_
        && buy_sell_indicator_ == other.buy_sell_indicator_
        && quantity_ == other.quantity_
        && order_book_ == other.order_book_
        && price_ == other.price_
        && attribution_ == other.attribution_;
}

bool AddOrderMpidAttributionMessage::operator!=(const AddOrderMpidAttributionMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
