#include "PriceTickSizeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jnx::jnxequities::pts::itch::v1_6 {

PriceTickSizeMessage::PriceTickSizeMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t price_tick_size_table_id, Decimal price_tick_size, Decimal price_start)
  : nanoseconds_(nanoseconds), price_tick_size_table_id_(price_tick_size_table_id), price_tick_size_(price_tick_size), price_start_(price_start) {}

std::chrono::nanoseconds PriceTickSizeMessage::nanoseconds() const { return nanoseconds_; }
void PriceTickSizeMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t PriceTickSizeMessage::price_tick_size_table_id() const { return price_tick_size_table_id_; }
void PriceTickSizeMessage::set_price_tick_size_table_id(std::uint32_t value) { price_tick_size_table_id_ = value; }

Decimal PriceTickSizeMessage::price_tick_size() const { return price_tick_size_; }
void PriceTickSizeMessage::set_price_tick_size(Decimal value) { price_tick_size_ = value; }

Decimal PriceTickSizeMessage::price_start() const { return price_start_; }
void PriceTickSizeMessage::set_price_start(Decimal value) { price_start_ = value; }

MessageCode PriceTickSizeMessage::type() const { return message_type; }

std::string_view PriceTickSizeMessage::name() const { return "Price Tick Size Message"; }

std::size_t PriceTickSizeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PriceTickSizeMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    price_tick_size_table_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    price_tick_size_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -1);
    offset += 4;

    price_start_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -1);
    offset += 4;

    return offset;
}

std::size_t PriceTickSizeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PriceTickSizeMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(price_tick_size_table_id_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(price_tick_size_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(price_start_.mantissa()));
    offset += 4;

    return offset;
}

std::size_t PriceTickSizeMessage::encoded_size() const {
    return wire_size;
}

void PriceTickSizeMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> PriceTickSizeMessage::clone() const {
    return std::make_unique<PriceTickSizeMessage>(*this);
}

void PriceTickSizeMessage::print(std::ostream& out) const {
    out << "PriceTickSizeMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", price_tick_size_table_id=";
    out << price_tick_size_table_id_;
    out << ", price_tick_size=";
    out << price_tick_size_;
    out << ", price_start=";
    out << price_start_;
    out << '}';
}

bool PriceTickSizeMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const PriceTickSizeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PriceTickSizeMessage::operator==(const PriceTickSizeMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && price_tick_size_table_id_ == other.price_tick_size_table_id_
        && price_tick_size_ == other.price_tick_size_
        && price_start_ == other.price_start_;
}

bool PriceTickSizeMessage::operator!=(const PriceTickSizeMessage& other) const {
    return !(*this == other);
}

} // namespace jnx::jnxequities::pts::itch::v1_6
