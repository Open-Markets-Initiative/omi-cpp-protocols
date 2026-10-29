#include "OrderDetails.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

OrderDetails::OrderDetails(std::chrono::nanoseconds trd_reg_ts_time_priority, std::int64_t display_qty, Side side, const std::array<std::byte, 7>& pad_7, Decimal price)
  : trd_reg_ts_time_priority_(trd_reg_ts_time_priority), display_qty_(display_qty), side_(side), pad_7_(pad_7), price_(price) {}

std::chrono::nanoseconds OrderDetails::trd_reg_ts_time_priority() const { return trd_reg_ts_time_priority_; }
void OrderDetails::set_trd_reg_ts_time_priority(std::chrono::nanoseconds value) { trd_reg_ts_time_priority_ = value; }

std::int64_t OrderDetails::display_qty() const { return display_qty_; }
void OrderDetails::set_display_qty(std::int64_t value) { display_qty_ = value; }

Side OrderDetails::side() const { return side_; }
void OrderDetails::set_side(Side value) { side_ = value; }

const std::array<std::byte, 7>& OrderDetails::pad_7() const { return pad_7_; }
std::array<std::byte, 7>& OrderDetails::pad_7() { return pad_7_; }
void OrderDetails::set_pad_7(const std::array<std::byte, 7>& value) { pad_7_ = value; }

Decimal OrderDetails::price() const { return price_; }
void OrderDetails::set_price(Decimal value) { price_ = value; }

std::size_t OrderDetails::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderDetails", wire_size, length);

    trd_reg_ts_time_priority_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    display_qty_ = wire::read_i64_le(data + offset);
    offset += 8;

    side_ = static_cast<Side>(wire::read_u8(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, pad_7_.data(), 7);
    offset += 7;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -6);
    offset += 8;

    return offset;
}

std::size_t OrderDetails::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderDetails", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(trd_reg_ts_time_priority_.count()));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(display_qty_));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(side_));
    offset += 1;

    wire::write_bytes(data + offset, pad_7_.data(), 7);
    offset += 7;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(price_.mantissa()));
    offset += 8;

    return offset;
}

std::size_t OrderDetails::encoded_size() const {
    return wire_size;
}

void OrderDetails::print(std::ostream& out) const {
    out << "OrderDetails{";
    out << "trd_reg_ts_time_priority=";
    out << trd_reg_ts_time_priority_.count();
    out << ", display_qty=";
    out << display_qty_;
    out << ", side=";
    out << side_;
    out << ", pad_7=";
    print::hex(out, pad_7_.data(), pad_7_.size());
    out << ", price=";
    out << price_;
    out << '}';
}

bool OrderDetails::operator==(const OrderDetails& other) const {
    return trd_reg_ts_time_priority_ == other.trd_reg_ts_time_priority_
        && display_qty_ == other.display_qty_
        && side_ == other.side_
        && pad_7_ == other.pad_7_
        && price_ == other.price_;
}

bool OrderDetails::operator!=(const OrderDetails& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const OrderDetails& value) {
    value.print(out);
    return out;
}

} // namespace bse::bseindia::eobi::fbe::v1_4
