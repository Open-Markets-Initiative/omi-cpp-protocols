#include "TickSizeTableEntry.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

TickSizeTableEntry::TickSizeTableEntry(std::chrono::nanoseconds nanoseconds, std::uint32_t order_book_id, std::uint64_t tick_size, std::int32_t price_from, std::int32_t price_to)
  : nanoseconds_(nanoseconds), order_book_id_(order_book_id), tick_size_(tick_size), price_from_(price_from), price_to_(price_to) {}

std::chrono::nanoseconds TickSizeTableEntry::nanoseconds() const { return nanoseconds_; }
void TickSizeTableEntry::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t TickSizeTableEntry::order_book_id() const { return order_book_id_; }
void TickSizeTableEntry::set_order_book_id(std::uint32_t value) { order_book_id_ = value; }

std::uint64_t TickSizeTableEntry::tick_size() const { return tick_size_; }
void TickSizeTableEntry::set_tick_size(std::uint64_t value) { tick_size_ = value; }

std::int32_t TickSizeTableEntry::price_from() const { return price_from_; }
void TickSizeTableEntry::set_price_from(std::int32_t value) { price_from_ = value; }

std::int32_t TickSizeTableEntry::price_to() const { return price_to_; }
void TickSizeTableEntry::set_price_to(std::int32_t value) { price_to_ = value; }

MessageCode TickSizeTableEntry::type() const { return message_type; }

std::string_view TickSizeTableEntry::name() const { return "Tick Size Table Entry"; }

std::size_t TickSizeTableEntry::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TickSizeTableEntry", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    order_book_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    tick_size_ = wire::read_u64_be(data + offset);
    offset += 8;

    price_from_ = wire::read_i32_be(data + offset);
    offset += 4;

    price_to_ = wire::read_i32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t TickSizeTableEntry::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TickSizeTableEntry", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(order_book_id_));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(tick_size_));
    offset += 8;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(price_from_));
    offset += 4;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(price_to_));
    offset += 4;

    return offset;
}

std::size_t TickSizeTableEntry::encoded_size() const {
    return wire_size;
}

void TickSizeTableEntry::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TickSizeTableEntry::clone() const {
    return std::make_unique<TickSizeTableEntry>(*this);
}

void TickSizeTableEntry::print(std::ostream& out) const {
    out << "TickSizeTableEntry{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", order_book_id=";
    out << order_book_id_;
    out << ", tick_size=";
    out << tick_size_;
    out << ", price_from=";
    out << price_from_;
    out << ", price_to=";
    out << price_to_;
    out << '}';
}

bool TickSizeTableEntry::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TickSizeTableEntry*>(&other);
    return that != nullptr && *this == *that;
}

bool TickSizeTableEntry::operator==(const TickSizeTableEntry& other) const {
    return nanoseconds_ == other.nanoseconds_
        && order_book_id_ == other.order_book_id_
        && tick_size_ == other.tick_size_
        && price_from_ == other.price_from_
        && price_to_ == other.price_to_;
}

bool TickSizeTableEntry::operator!=(const TickSizeTableEntry& other) const {
    return !(*this == other);
}

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
