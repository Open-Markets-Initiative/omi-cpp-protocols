#include "EnterOrderMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

EnterOrderMessage::EnterOrderMessage(std::uint32_t order_token, const std::string& client_reference, BuySellIndicator buy_sell_indicator, std::uint32_t quantity, std::uint32_t orderbook_id, const std::string& group, Decimal price, TimeInForce time_in_force, std::uint32_t firm_id, Display display, Capacity capacity, std::uint32_t minimum_quantity, OrderClassification order_classification, CashMarginType cash_margin_type)
  : order_token_(order_token), client_reference_(client_reference), buy_sell_indicator_(buy_sell_indicator), quantity_(quantity), orderbook_id_(orderbook_id), group_(group), price_(price), time_in_force_(time_in_force), firm_id_(firm_id), display_(display), capacity_(capacity), minimum_quantity_(minimum_quantity), order_classification_(order_classification), cash_margin_type_(cash_margin_type) {}

std::uint32_t EnterOrderMessage::order_token() const { return order_token_; }
void EnterOrderMessage::set_order_token(std::uint32_t value) { order_token_ = value; }

const std::string& EnterOrderMessage::client_reference() const { return client_reference_; }
std::string& EnterOrderMessage::client_reference() { return client_reference_; }
void EnterOrderMessage::set_client_reference(const std::string& value) { client_reference_ = value; }

BuySellIndicator EnterOrderMessage::buy_sell_indicator() const { return buy_sell_indicator_; }
void EnterOrderMessage::set_buy_sell_indicator(BuySellIndicator value) { buy_sell_indicator_ = value; }

std::uint32_t EnterOrderMessage::quantity() const { return quantity_; }
void EnterOrderMessage::set_quantity(std::uint32_t value) { quantity_ = value; }

std::uint32_t EnterOrderMessage::orderbook_id() const { return orderbook_id_; }
void EnterOrderMessage::set_orderbook_id(std::uint32_t value) { orderbook_id_ = value; }

const std::string& EnterOrderMessage::group() const { return group_; }
std::string& EnterOrderMessage::group() { return group_; }
void EnterOrderMessage::set_group(const std::string& value) { group_ = value; }

Decimal EnterOrderMessage::price() const { return price_; }
void EnterOrderMessage::set_price(Decimal value) { price_ = value; }

TimeInForce EnterOrderMessage::time_in_force() const { return time_in_force_; }
void EnterOrderMessage::set_time_in_force(TimeInForce value) { time_in_force_ = value; }

std::uint32_t EnterOrderMessage::firm_id() const { return firm_id_; }
void EnterOrderMessage::set_firm_id(std::uint32_t value) { firm_id_ = value; }

Display EnterOrderMessage::display() const { return display_; }
void EnterOrderMessage::set_display(Display value) { display_ = value; }

Capacity EnterOrderMessage::capacity() const { return capacity_; }
void EnterOrderMessage::set_capacity(Capacity value) { capacity_ = value; }

std::uint32_t EnterOrderMessage::minimum_quantity() const { return minimum_quantity_; }
void EnterOrderMessage::set_minimum_quantity(std::uint32_t value) { minimum_quantity_ = value; }

OrderClassification EnterOrderMessage::order_classification() const { return order_classification_; }
void EnterOrderMessage::set_order_classification(OrderClassification value) { order_classification_ = value; }

CashMarginType EnterOrderMessage::cash_margin_type() const { return cash_margin_type_; }
void EnterOrderMessage::set_cash_margin_type(CashMarginType value) { cash_margin_type_ = value; }

UnsequencedMessageCode EnterOrderMessage::type() const { return message_type; }

std::string_view EnterOrderMessage::name() const { return "Enter Order Message"; }

std::size_t EnterOrderMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("EnterOrderMessage", wire_size, length);

    order_token_ = wire::read_u32_be(data + offset);
    offset += 4;

    client_reference_ = wire::read_text(data + offset, 10, ' ');
    offset += 10;

    buy_sell_indicator_ = static_cast<BuySellIndicator>(wire::read_char(data + offset));
    offset += 1;

    quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    orderbook_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    group_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -1);
    offset += 4;

    time_in_force_ = static_cast<TimeInForce>(wire::read_u32_be(data + offset));
    offset += 4;

    firm_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    display_ = static_cast<Display>(wire::read_char(data + offset));
    offset += 1;

    capacity_ = static_cast<Capacity>(wire::read_char(data + offset));
    offset += 1;

    minimum_quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    order_classification_ = static_cast<OrderClassification>(wire::read_char(data + offset));
    offset += 1;

    cash_margin_type_ = static_cast<CashMarginType>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t EnterOrderMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("EnterOrderMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(order_token_));
    offset += 4;

    wire::write_text(data + offset, 10, ' ', client_reference_);
    offset += 10;

    wire::write_char(data + offset, static_cast<char>(buy_sell_indicator_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(quantity_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(orderbook_id_));
    offset += 4;

    wire::write_text(data + offset, 4, ' ', group_);
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(time_in_force_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(firm_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(display_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(capacity_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(minimum_quantity_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(order_classification_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(cash_margin_type_));
    offset += 1;

    return offset;
}

std::size_t EnterOrderMessage::encoded_size() const {
    return wire_size;
}

void EnterOrderMessage::accept(UnsequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<UnsequencedMessage> EnterOrderMessage::clone() const {
    return std::make_unique<EnterOrderMessage>(*this);
}

void EnterOrderMessage::print(std::ostream& out) const {
    out << "EnterOrderMessage{";
    out << "order_token=";
    out << order_token_;
    out << ", client_reference=";
    print::text(out, client_reference_);
    out << ", buy_sell_indicator=";
    out << buy_sell_indicator_;
    out << ", quantity=";
    out << quantity_;
    out << ", orderbook_id=";
    out << orderbook_id_;
    out << ", group=";
    print::text(out, group_);
    out << ", price=";
    out << price_;
    out << ", time_in_force=";
    out << time_in_force_;
    out << ", firm_id=";
    out << firm_id_;
    out << ", display=";
    out << display_;
    out << ", capacity=";
    out << capacity_;
    out << ", minimum_quantity=";
    out << minimum_quantity_;
    out << ", order_classification=";
    out << order_classification_;
    out << ", cash_margin_type=";
    out << cash_margin_type_;
    out << '}';
}

bool EnterOrderMessage::equals(const UnsequencedMessage& other) const {
    const auto* that = dynamic_cast<const EnterOrderMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool EnterOrderMessage::operator==(const EnterOrderMessage& other) const {
    return order_token_ == other.order_token_
        && client_reference_ == other.client_reference_
        && buy_sell_indicator_ == other.buy_sell_indicator_
        && quantity_ == other.quantity_
        && orderbook_id_ == other.orderbook_id_
        && group_ == other.group_
        && price_ == other.price_
        && time_in_force_ == other.time_in_force_
        && firm_id_ == other.firm_id_
        && display_ == other.display_
        && capacity_ == other.capacity_
        && minimum_quantity_ == other.minimum_quantity_
        && order_classification_ == other.order_classification_
        && cash_margin_type_ == other.cash_margin_type_;
}

bool EnterOrderMessage::operator!=(const EnterOrderMessage& other) const {
    return !(*this == other);
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
