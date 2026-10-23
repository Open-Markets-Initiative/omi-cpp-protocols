#include "NoiiMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

NoiiMessage::NoiiMessage(std::chrono::nanoseconds timestamp, std::uint16_t tracking_number, std::uint64_t paired_quantity, std::uint64_t imbalance_quantity, ImbalanceDirection imbalance_direction, std::uint32_t order_book, Decimal equilibrium_price, CrossType cross_type, Decimal best_bid_price, std::uint64_t best_bid_quantity, Decimal best_ask_price, std::uint64_t best_ask_quantity)
  : timestamp_(timestamp), tracking_number_(tracking_number), paired_quantity_(paired_quantity), imbalance_quantity_(imbalance_quantity), imbalance_direction_(imbalance_direction), order_book_(order_book), equilibrium_price_(equilibrium_price), cross_type_(cross_type), best_bid_price_(best_bid_price), best_bid_quantity_(best_bid_quantity), best_ask_price_(best_ask_price), best_ask_quantity_(best_ask_quantity) {}

std::chrono::nanoseconds NoiiMessage::timestamp() const { return timestamp_; }
void NoiiMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint16_t NoiiMessage::tracking_number() const { return tracking_number_; }
void NoiiMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::uint64_t NoiiMessage::paired_quantity() const { return paired_quantity_; }
void NoiiMessage::set_paired_quantity(std::uint64_t value) { paired_quantity_ = value; }

std::uint64_t NoiiMessage::imbalance_quantity() const { return imbalance_quantity_; }
void NoiiMessage::set_imbalance_quantity(std::uint64_t value) { imbalance_quantity_ = value; }

ImbalanceDirection NoiiMessage::imbalance_direction() const { return imbalance_direction_; }
void NoiiMessage::set_imbalance_direction(ImbalanceDirection value) { imbalance_direction_ = value; }

std::uint32_t NoiiMessage::order_book() const { return order_book_; }
void NoiiMessage::set_order_book(std::uint32_t value) { order_book_ = value; }

Decimal NoiiMessage::equilibrium_price() const { return equilibrium_price_; }
void NoiiMessage::set_equilibrium_price(Decimal value) { equilibrium_price_ = value; }

CrossType NoiiMessage::cross_type() const { return cross_type_; }
void NoiiMessage::set_cross_type(CrossType value) { cross_type_ = value; }

Decimal NoiiMessage::best_bid_price() const { return best_bid_price_; }
void NoiiMessage::set_best_bid_price(Decimal value) { best_bid_price_ = value; }

std::uint64_t NoiiMessage::best_bid_quantity() const { return best_bid_quantity_; }
void NoiiMessage::set_best_bid_quantity(std::uint64_t value) { best_bid_quantity_ = value; }

Decimal NoiiMessage::best_ask_price() const { return best_ask_price_; }
void NoiiMessage::set_best_ask_price(Decimal value) { best_ask_price_ = value; }

std::uint64_t NoiiMessage::best_ask_quantity() const { return best_ask_quantity_; }
void NoiiMessage::set_best_ask_quantity(std::uint64_t value) { best_ask_quantity_ = value; }

MessageCode NoiiMessage::type() const { return message_type; }

std::string_view NoiiMessage::name() const { return "Noii Message"; }

std::size_t NoiiMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("NoiiMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(data + offset)));
    offset += 8;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    paired_quantity_ = wire::read_u64_be(data + offset);
    offset += 8;

    imbalance_quantity_ = wire::read_u64_be(data + offset);
    offset += 8;

    imbalance_direction_ = static_cast<ImbalanceDirection>(wire::read_char(data + offset));
    offset += 1;

    order_book_ = wire::read_u32_be(data + offset);
    offset += 4;

    equilibrium_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    cross_type_ = static_cast<CrossType>(wire::read_char(data + offset));
    offset += 1;

    best_bid_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    best_bid_quantity_ = wire::read_u64_be(data + offset);
    offset += 8;

    best_ask_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    best_ask_quantity_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t NoiiMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("NoiiMessage", wire_size, capacity);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(paired_quantity_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(imbalance_quantity_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(imbalance_direction_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(order_book_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(equilibrium_price_.mantissa()));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(cross_type_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(best_bid_price_.mantissa()));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(best_bid_quantity_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(best_ask_price_.mantissa()));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(best_ask_quantity_));
    offset += 8;

    return offset;
}

std::size_t NoiiMessage::encoded_size() const {
    return wire_size;
}

void NoiiMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> NoiiMessage::clone() const {
    return std::make_unique<NoiiMessage>(*this);
}

void NoiiMessage::print(std::ostream& out) const {
    out << "NoiiMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", paired_quantity=";
    out << paired_quantity_;
    out << ", imbalance_quantity=";
    out << imbalance_quantity_;
    out << ", imbalance_direction=";
    out << imbalance_direction_;
    out << ", order_book=";
    out << order_book_;
    out << ", equilibrium_price=";
    out << equilibrium_price_;
    out << ", cross_type=";
    out << cross_type_;
    out << ", best_bid_price=";
    out << best_bid_price_;
    out << ", best_bid_quantity=";
    out << best_bid_quantity_;
    out << ", best_ask_price=";
    out << best_ask_price_;
    out << ", best_ask_quantity=";
    out << best_ask_quantity_;
    out << '}';
}

bool NoiiMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const NoiiMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool NoiiMessage::operator==(const NoiiMessage& other) const {
    return timestamp_ == other.timestamp_
        && tracking_number_ == other.tracking_number_
        && paired_quantity_ == other.paired_quantity_
        && imbalance_quantity_ == other.imbalance_quantity_
        && imbalance_direction_ == other.imbalance_direction_
        && order_book_ == other.order_book_
        && equilibrium_price_ == other.equilibrium_price_
        && cross_type_ == other.cross_type_
        && best_bid_price_ == other.best_bid_price_
        && best_bid_quantity_ == other.best_bid_quantity_
        && best_ask_price_ == other.best_ask_price_
        && best_ask_quantity_ == other.best_ask_quantity_;
}

bool NoiiMessage::operator!=(const NoiiMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
