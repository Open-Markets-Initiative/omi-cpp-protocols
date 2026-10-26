#include "RelatedSymGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

RelatedSymGroup::RelatedSymGroup(const std::string& symbol, std::int32_t security_id, std::optional<std::int32_t> order_qty, std::int8_t quote_type, std::optional<std::int8_t> side, const std::array<std::byte, 2>& padding_2)
  : symbol_(symbol), security_id_(security_id), order_qty_(order_qty), quote_type_(quote_type), side_(side), padding_2_(padding_2) {}

const std::string& RelatedSymGroup::symbol() const { return symbol_; }
std::string& RelatedSymGroup::symbol() { return symbol_; }
void RelatedSymGroup::set_symbol(const std::string& value) { symbol_ = value; }

std::int32_t RelatedSymGroup::security_id() const { return security_id_; }
void RelatedSymGroup::set_security_id(std::int32_t value) { security_id_ = value; }

std::optional<std::int32_t> RelatedSymGroup::order_qty() const { return order_qty_; }
void RelatedSymGroup::set_order_qty(std::optional<std::int32_t> value) { order_qty_ = value; }

std::int8_t RelatedSymGroup::quote_type() const { return quote_type_; }
void RelatedSymGroup::set_quote_type(std::int8_t value) { quote_type_ = value; }

std::optional<std::int8_t> RelatedSymGroup::side() const { return side_; }
void RelatedSymGroup::set_side(std::optional<std::int8_t> value) { side_ = value; }

const std::array<std::byte, 2>& RelatedSymGroup::padding_2() const { return padding_2_; }
std::array<std::byte, 2>& RelatedSymGroup::padding_2() { return padding_2_; }
void RelatedSymGroup::set_padding_2(const std::array<std::byte, 2>& value) { padding_2_ = value; }

std::size_t RelatedSymGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RelatedSymGroup", wire_size, length);

    symbol_ = wire::read_text(data + offset, 20, '\0');
    offset += 20;

    security_id_ = wire::read_i32_le(data + offset);
    offset += 4;

    order_qty_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(2147483647LL));
    offset += 4;

    quote_type_ = wire::read_i8(data + offset);
    offset += 1;

    side_ = wire::nullable(wire::read_i8(data + offset), static_cast<std::int8_t>(127LL));
    offset += 1;

    wire::read_bytes(data + offset, padding_2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t RelatedSymGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RelatedSymGroup", wire_size, capacity);

    wire::write_text(data + offset, 20, '\0', symbol_);
    offset += 20;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(security_id_));
    offset += 4;

    wire::write_i32_le(data + offset, order_qty_.value_or(static_cast<std::int32_t>(2147483647LL)));
    offset += 4;

    wire::write_i8(data + offset, static_cast<std::int8_t>(quote_type_));
    offset += 1;

    wire::write_i8(data + offset, side_.value_or(static_cast<std::int8_t>(127LL)));
    offset += 1;

    wire::write_bytes(data + offset, padding_2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t RelatedSymGroup::encoded_size() const {
    return wire_size;
}

void RelatedSymGroup::print(std::ostream& out) const {
    out << "RelatedSymGroup{";
    out << "symbol=";
    print::text(out, symbol_);
    out << ", security_id=";
    out << security_id_;
    out << ", order_qty=";
    print::optional(out, order_qty_);
    out << ", quote_type=";
    out << static_cast<int>(quote_type_);
    out << ", side=";
    print::optional(out, side_);
    out << ", padding_2=";
    print::hex(out, padding_2_.data(), padding_2_.size());
    out << '}';
}

bool RelatedSymGroup::operator==(const RelatedSymGroup& other) const {
    return symbol_ == other.symbol_
        && security_id_ == other.security_id_
        && order_qty_ == other.order_qty_
        && quote_type_ == other.quote_type_
        && side_ == other.side_
        && padding_2_ == other.padding_2_;
}

bool RelatedSymGroup::operator!=(const RelatedSymGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const RelatedSymGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_9
