#include "MoiiMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

MoiiMessage::MoiiMessage(std::chrono::nanoseconds timestamp, std::uint16_t tracking_number, std::uint64_t paired_quantity, std::uint32_t order_book, Decimal equilibrium_price, CrossType cross_type, CrossLevel cross_level)
  : timestamp_(timestamp), tracking_number_(tracking_number), paired_quantity_(paired_quantity), order_book_(order_book), equilibrium_price_(equilibrium_price), cross_type_(cross_type), cross_level_(cross_level) {}

std::chrono::nanoseconds MoiiMessage::timestamp() const { return timestamp_; }
void MoiiMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint16_t MoiiMessage::tracking_number() const { return tracking_number_; }
void MoiiMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::uint64_t MoiiMessage::paired_quantity() const { return paired_quantity_; }
void MoiiMessage::set_paired_quantity(std::uint64_t value) { paired_quantity_ = value; }

std::uint32_t MoiiMessage::order_book() const { return order_book_; }
void MoiiMessage::set_order_book(std::uint32_t value) { order_book_ = value; }

Decimal MoiiMessage::equilibrium_price() const { return equilibrium_price_; }
void MoiiMessage::set_equilibrium_price(Decimal value) { equilibrium_price_ = value; }

CrossType MoiiMessage::cross_type() const { return cross_type_; }
void MoiiMessage::set_cross_type(CrossType value) { cross_type_ = value; }

CrossLevel MoiiMessage::cross_level() const { return cross_level_; }
void MoiiMessage::set_cross_level(CrossLevel value) { cross_level_ = value; }

MessageCode MoiiMessage::type() const { return message_type; }

std::string_view MoiiMessage::name() const { return "Moii Message"; }

std::size_t MoiiMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MoiiMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(data + offset)));
    offset += 8;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    paired_quantity_ = wire::read_u64_be(data + offset);
    offset += 8;

    order_book_ = wire::read_u32_be(data + offset);
    offset += 4;

    equilibrium_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    cross_type_ = static_cast<CrossType>(wire::read_char(data + offset));
    offset += 1;

    cross_level_ = static_cast<CrossLevel>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t MoiiMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MoiiMessage", wire_size, capacity);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(paired_quantity_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(order_book_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(equilibrium_price_.mantissa()));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(cross_type_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(cross_level_));
    offset += 1;

    return offset;
}

std::size_t MoiiMessage::encoded_size() const {
    return wire_size;
}

void MoiiMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> MoiiMessage::clone() const {
    return std::make_unique<MoiiMessage>(*this);
}

void MoiiMessage::print(std::ostream& out) const {
    out << "MoiiMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", paired_quantity=";
    out << paired_quantity_;
    out << ", order_book=";
    out << order_book_;
    out << ", equilibrium_price=";
    out << equilibrium_price_;
    out << ", cross_type=";
    out << cross_type_;
    out << ", cross_level=";
    out << cross_level_;
    out << '}';
}

bool MoiiMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const MoiiMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool MoiiMessage::operator==(const MoiiMessage& other) const {
    return timestamp_ == other.timestamp_
        && tracking_number_ == other.tracking_number_
        && paired_quantity_ == other.paired_quantity_
        && order_book_ == other.order_book_
        && equilibrium_price_ == other.equilibrium_price_
        && cross_type_ == other.cross_type_
        && cross_level_ == other.cross_level_;
}

bool MoiiMessage::operator!=(const MoiiMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
