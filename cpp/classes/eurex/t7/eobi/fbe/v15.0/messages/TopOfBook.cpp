#include "TopOfBook.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

TopOfBook::TopOfBook(std::optional<std::chrono::nanoseconds> transact_time, std::optional<std::int64_t> security_id, std::optional<Decimal> bid_px, std::optional<Decimal> offer_px, std::optional<Decimal> bid_size, std::optional<Decimal> offer_size, std::optional<std::uint16_t> number_of_buy_orders, std::optional<std::uint16_t> number_of_sell_orders, const std::array<std::byte, 4>& pad4)
  : transact_time_(transact_time), security_id_(security_id), bid_px_(bid_px), offer_px_(offer_px), bid_size_(bid_size), offer_size_(offer_size), number_of_buy_orders_(number_of_buy_orders), number_of_sell_orders_(number_of_sell_orders), pad4_(pad4) {}

std::optional<std::chrono::nanoseconds> TopOfBook::transact_time() const { return transact_time_; }
void TopOfBook::set_transact_time(std::optional<std::chrono::nanoseconds> value) { transact_time_ = value; }

std::optional<std::int64_t> TopOfBook::security_id() const { return security_id_; }
void TopOfBook::set_security_id(std::optional<std::int64_t> value) { security_id_ = value; }

std::optional<Decimal> TopOfBook::bid_px() const { return bid_px_; }
void TopOfBook::set_bid_px(std::optional<Decimal> value) { bid_px_ = value; }

std::optional<Decimal> TopOfBook::offer_px() const { return offer_px_; }
void TopOfBook::set_offer_px(std::optional<Decimal> value) { offer_px_ = value; }

std::optional<Decimal> TopOfBook::bid_size() const { return bid_size_; }
void TopOfBook::set_bid_size(std::optional<Decimal> value) { bid_size_ = value; }

std::optional<Decimal> TopOfBook::offer_size() const { return offer_size_; }
void TopOfBook::set_offer_size(std::optional<Decimal> value) { offer_size_ = value; }

std::optional<std::uint16_t> TopOfBook::number_of_buy_orders() const { return number_of_buy_orders_; }
void TopOfBook::set_number_of_buy_orders(std::optional<std::uint16_t> value) { number_of_buy_orders_ = value; }

std::optional<std::uint16_t> TopOfBook::number_of_sell_orders() const { return number_of_sell_orders_; }
void TopOfBook::set_number_of_sell_orders(std::optional<std::uint16_t> value) { number_of_sell_orders_ = value; }

const std::array<std::byte, 4>& TopOfBook::pad4() const { return pad4_; }
std::array<std::byte, 4>& TopOfBook::pad4() { return pad4_; }
void TopOfBook::set_pad4(const std::array<std::byte, 4>& value) { pad4_ = value; }

MessageCode TopOfBook::type() const { return message_type; }

std::string_view TopOfBook::name() const { return "Top Of Book"; }

std::size_t TopOfBook::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TopOfBook", wire_size, length);

    transact_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    security_id_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    bid_px_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -8);
    offset += 8;

    offer_px_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -8);
    offset += 8;

    bid_size_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -4);
    offset += 8;

    offer_size_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -4);
    offset += 8;

    number_of_buy_orders_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0xFFFFULL));
    offset += 2;

    number_of_sell_orders_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0xFFFFULL));
    offset += 2;

    wire::read_bytes(data + offset, pad4_.data(), 4);
    offset += 4;

    return offset;
}

std::size_t TopOfBook::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TopOfBook", wire_size, capacity);

    wire::write_u64_le(data + offset, transact_time_ ? static_cast<std::uint64_t>(transact_time_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_i64_le(data + offset, security_id_.value_or(static_cast<std::int64_t>(0x8000000000000000LL)));
    offset += 8;

    wire::write_i64_le(data + offset, bid_px_ ? static_cast<std::int64_t>(bid_px_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_i64_le(data + offset, offer_px_ ? static_cast<std::int64_t>(offer_px_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_i64_le(data + offset, bid_size_ ? static_cast<std::int64_t>(bid_size_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_i64_le(data + offset, offer_size_ ? static_cast<std::int64_t>(offer_size_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_u16_le(data + offset, number_of_buy_orders_.value_or(static_cast<std::uint16_t>(0xFFFFULL)));
    offset += 2;

    wire::write_u16_le(data + offset, number_of_sell_orders_.value_or(static_cast<std::uint16_t>(0xFFFFULL)));
    offset += 2;

    wire::write_bytes(data + offset, pad4_.data(), 4);
    offset += 4;

    return offset;
}

std::size_t TopOfBook::encoded_size() const {
    return wire_size;
}

void TopOfBook::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TopOfBook::clone() const {
    return std::make_unique<TopOfBook>(*this);
}

void TopOfBook::print(std::ostream& out) const {
    out << "TopOfBook{";
    out << "transact_time=";
    print::optional_duration(out, transact_time_);
    out << ", security_id=";
    print::optional(out, security_id_);
    out << ", bid_px=";
    print::optional(out, bid_px_);
    out << ", offer_px=";
    print::optional(out, offer_px_);
    out << ", bid_size=";
    print::optional(out, bid_size_);
    out << ", offer_size=";
    print::optional(out, offer_size_);
    out << ", number_of_buy_orders=";
    print::optional(out, number_of_buy_orders_);
    out << ", number_of_sell_orders=";
    print::optional(out, number_of_sell_orders_);
    out << ", pad4=";
    print::hex(out, pad4_.data(), pad4_.size());
    out << '}';
}

bool TopOfBook::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TopOfBook*>(&other);
    return that != nullptr && *this == *that;
}

bool TopOfBook::operator==(const TopOfBook& other) const {
    return transact_time_ == other.transact_time_
        && security_id_ == other.security_id_
        && bid_px_ == other.bid_px_
        && offer_px_ == other.offer_px_
        && bid_size_ == other.bid_size_
        && offer_size_ == other.offer_size_
        && number_of_buy_orders_ == other.number_of_buy_orders_
        && number_of_sell_orders_ == other.number_of_sell_orders_
        && pad4_ == other.pad4_;
}

bool TopOfBook::operator!=(const TopOfBook& other) const {
    return !(*this == other);
}

} // namespace eurex::t7::eobi::fbe::v15_0
