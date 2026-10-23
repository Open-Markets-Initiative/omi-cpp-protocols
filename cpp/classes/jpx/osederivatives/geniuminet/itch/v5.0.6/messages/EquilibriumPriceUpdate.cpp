#include "EquilibriumPriceUpdate.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

EquilibriumPriceUpdate::EquilibriumPriceUpdate(std::chrono::nanoseconds nanoseconds, std::uint32_t order_book_id, std::uint64_t available_bid_quantity_at_equilibrium_price, std::uint64_t available_ask_quantity_at_equilibrium_price, std::int32_t equilibrium_price, const std::array<std::byte, 24>& reserved_24)
  : nanoseconds_(nanoseconds), order_book_id_(order_book_id), available_bid_quantity_at_equilibrium_price_(available_bid_quantity_at_equilibrium_price), available_ask_quantity_at_equilibrium_price_(available_ask_quantity_at_equilibrium_price), equilibrium_price_(equilibrium_price), reserved_24_(reserved_24) {}

std::chrono::nanoseconds EquilibriumPriceUpdate::nanoseconds() const { return nanoseconds_; }
void EquilibriumPriceUpdate::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t EquilibriumPriceUpdate::order_book_id() const { return order_book_id_; }
void EquilibriumPriceUpdate::set_order_book_id(std::uint32_t value) { order_book_id_ = value; }

std::uint64_t EquilibriumPriceUpdate::available_bid_quantity_at_equilibrium_price() const { return available_bid_quantity_at_equilibrium_price_; }
void EquilibriumPriceUpdate::set_available_bid_quantity_at_equilibrium_price(std::uint64_t value) { available_bid_quantity_at_equilibrium_price_ = value; }

std::uint64_t EquilibriumPriceUpdate::available_ask_quantity_at_equilibrium_price() const { return available_ask_quantity_at_equilibrium_price_; }
void EquilibriumPriceUpdate::set_available_ask_quantity_at_equilibrium_price(std::uint64_t value) { available_ask_quantity_at_equilibrium_price_ = value; }

std::int32_t EquilibriumPriceUpdate::equilibrium_price() const { return equilibrium_price_; }
void EquilibriumPriceUpdate::set_equilibrium_price(std::int32_t value) { equilibrium_price_ = value; }

const std::array<std::byte, 24>& EquilibriumPriceUpdate::reserved_24() const { return reserved_24_; }
std::array<std::byte, 24>& EquilibriumPriceUpdate::reserved_24() { return reserved_24_; }
void EquilibriumPriceUpdate::set_reserved_24(const std::array<std::byte, 24>& value) { reserved_24_ = value; }

MessageCode EquilibriumPriceUpdate::type() const { return message_type; }

std::string_view EquilibriumPriceUpdate::name() const { return "Equilibrium Price Update"; }

std::size_t EquilibriumPriceUpdate::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("EquilibriumPriceUpdate", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    order_book_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    available_bid_quantity_at_equilibrium_price_ = wire::read_u64_be(data + offset);
    offset += 8;

    available_ask_quantity_at_equilibrium_price_ = wire::read_u64_be(data + offset);
    offset += 8;

    equilibrium_price_ = wire::read_i32_be(data + offset);
    offset += 4;

    wire::read_bytes(data + offset, reserved_24_.data(), 24);
    offset += 24;

    return offset;
}

std::size_t EquilibriumPriceUpdate::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("EquilibriumPriceUpdate", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(order_book_id_));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(available_bid_quantity_at_equilibrium_price_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(available_ask_quantity_at_equilibrium_price_));
    offset += 8;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(equilibrium_price_));
    offset += 4;

    wire::write_bytes(data + offset, reserved_24_.data(), 24);
    offset += 24;

    return offset;
}

std::size_t EquilibriumPriceUpdate::encoded_size() const {
    return wire_size;
}

void EquilibriumPriceUpdate::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> EquilibriumPriceUpdate::clone() const {
    return std::make_unique<EquilibriumPriceUpdate>(*this);
}

void EquilibriumPriceUpdate::print(std::ostream& out) const {
    out << "EquilibriumPriceUpdate{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", order_book_id=";
    out << order_book_id_;
    out << ", available_bid_quantity_at_equilibrium_price=";
    out << available_bid_quantity_at_equilibrium_price_;
    out << ", available_ask_quantity_at_equilibrium_price=";
    out << available_ask_quantity_at_equilibrium_price_;
    out << ", equilibrium_price=";
    out << equilibrium_price_;
    out << ", reserved_24=";
    print::hex(out, reserved_24_.data(), reserved_24_.size());
    out << '}';
}

bool EquilibriumPriceUpdate::equals(const Message& other) const {
    const auto* that = dynamic_cast<const EquilibriumPriceUpdate*>(&other);
    return that != nullptr && *this == *that;
}

bool EquilibriumPriceUpdate::operator==(const EquilibriumPriceUpdate& other) const {
    return nanoseconds_ == other.nanoseconds_
        && order_book_id_ == other.order_book_id_
        && available_bid_quantity_at_equilibrium_price_ == other.available_bid_quantity_at_equilibrium_price_
        && available_ask_quantity_at_equilibrium_price_ == other.available_ask_quantity_at_equilibrium_price_
        && equilibrium_price_ == other.equilibrium_price_
        && reserved_24_ == other.reserved_24_;
}

bool EquilibriumPriceUpdate::operator!=(const EquilibriumPriceUpdate& other) const {
    return !(*this == other);
}

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
