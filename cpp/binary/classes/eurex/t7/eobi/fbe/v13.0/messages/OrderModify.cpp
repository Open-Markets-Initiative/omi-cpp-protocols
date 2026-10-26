#include "OrderModify.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

OrderModify::OrderModify(std::optional<std::chrono::nanoseconds> request_time, std::optional<std::chrono::nanoseconds> trd_reg_ts_prev_time_priority, std::optional<Decimal> prev_price, std::optional<Decimal> prev_display_qty, std::optional<std::int64_t> security_id, const OrderDetailsComp& order_details_comp, std::optional<PrevPriceHhiIndicator> prev_price_hhi_indicator, const std::array<std::byte, 7>& pad7)
  : request_time_(request_time), trd_reg_ts_prev_time_priority_(trd_reg_ts_prev_time_priority), prev_price_(prev_price), prev_display_qty_(prev_display_qty), security_id_(security_id), order_details_comp_(order_details_comp), prev_price_hhi_indicator_(prev_price_hhi_indicator), pad7_(pad7) {}

std::optional<std::chrono::nanoseconds> OrderModify::request_time() const { return request_time_; }
void OrderModify::set_request_time(std::optional<std::chrono::nanoseconds> value) { request_time_ = value; }

std::optional<std::chrono::nanoseconds> OrderModify::trd_reg_ts_prev_time_priority() const { return trd_reg_ts_prev_time_priority_; }
void OrderModify::set_trd_reg_ts_prev_time_priority(std::optional<std::chrono::nanoseconds> value) { trd_reg_ts_prev_time_priority_ = value; }

std::optional<Decimal> OrderModify::prev_price() const { return prev_price_; }
void OrderModify::set_prev_price(std::optional<Decimal> value) { prev_price_ = value; }

std::optional<Decimal> OrderModify::prev_display_qty() const { return prev_display_qty_; }
void OrderModify::set_prev_display_qty(std::optional<Decimal> value) { prev_display_qty_ = value; }

std::optional<std::int64_t> OrderModify::security_id() const { return security_id_; }
void OrderModify::set_security_id(std::optional<std::int64_t> value) { security_id_ = value; }

const OrderDetailsComp& OrderModify::order_details_comp() const { return order_details_comp_; }
OrderDetailsComp& OrderModify::order_details_comp() { return order_details_comp_; }
void OrderModify::set_order_details_comp(const OrderDetailsComp& value) { order_details_comp_ = value; }

std::optional<PrevPriceHhiIndicator> OrderModify::prev_price_hhi_indicator() const { return prev_price_hhi_indicator_; }
void OrderModify::set_prev_price_hhi_indicator(std::optional<PrevPriceHhiIndicator> value) { prev_price_hhi_indicator_ = value; }

const std::array<std::byte, 7>& OrderModify::pad7() const { return pad7_; }
std::array<std::byte, 7>& OrderModify::pad7() { return pad7_; }
void OrderModify::set_pad7(const std::array<std::byte, 7>& value) { pad7_ = value; }

MessageCode OrderModify::type() const { return message_type; }

std::string_view OrderModify::name() const { return "Order Modify"; }

std::size_t OrderModify::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderModify", wire_size, length);

    request_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    trd_reg_ts_prev_time_priority_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    prev_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -8);
    offset += 8;

    prev_display_qty_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -4);
    offset += 8;

    security_id_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    offset += order_details_comp_.decode(data + offset, length - offset);

    prev_price_hhi_indicator_ = wire::nullable_enum<PrevPriceHhiIndicator>(wire::read_i8(data + offset), static_cast<std::int8_t>(0x80LL));
    offset += 1;

    wire::read_bytes(data + offset, pad7_.data(), 7);
    offset += 7;

    return offset;
}

std::size_t OrderModify::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderModify", wire_size, capacity);

    wire::write_u64_le(data + offset, request_time_ ? static_cast<std::uint64_t>(request_time_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_u64_le(data + offset, trd_reg_ts_prev_time_priority_ ? static_cast<std::uint64_t>(trd_reg_ts_prev_time_priority_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_i64_le(data + offset, prev_price_ ? static_cast<std::int64_t>(prev_price_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_i64_le(data + offset, prev_display_qty_ ? static_cast<std::int64_t>(prev_display_qty_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_i64_le(data + offset, security_id_.value_or(static_cast<std::int64_t>(0x8000000000000000LL)));
    offset += 8;

    offset += order_details_comp_.encode(data + offset, capacity - offset);

    wire::write_i8(data + offset, prev_price_hhi_indicator_ ? static_cast<std::int8_t>(*prev_price_hhi_indicator_) : static_cast<std::int8_t>(0x80LL));
    offset += 1;

    wire::write_bytes(data + offset, pad7_.data(), 7);
    offset += 7;

    return offset;
}

std::size_t OrderModify::encoded_size() const {
    return wire_size;
}

void OrderModify::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderModify::clone() const {
    return std::make_unique<OrderModify>(*this);
}

void OrderModify::print(std::ostream& out) const {
    out << "OrderModify{";
    out << "request_time=";
    print::optional_duration(out, request_time_);
    out << ", trd_reg_ts_prev_time_priority=";
    print::optional_duration(out, trd_reg_ts_prev_time_priority_);
    out << ", prev_price=";
    print::optional(out, prev_price_);
    out << ", prev_display_qty=";
    print::optional(out, prev_display_qty_);
    out << ", security_id=";
    print::optional(out, security_id_);
    out << ", order_details_comp=";
    order_details_comp_.print(out);
    out << ", prev_price_hhi_indicator=";
    print::optional(out, prev_price_hhi_indicator_);
    out << ", pad7=";
    print::hex(out, pad7_.data(), pad7_.size());
    out << '}';
}

bool OrderModify::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderModify*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderModify::operator==(const OrderModify& other) const {
    return request_time_ == other.request_time_
        && trd_reg_ts_prev_time_priority_ == other.trd_reg_ts_prev_time_priority_
        && prev_price_ == other.prev_price_
        && prev_display_qty_ == other.prev_display_qty_
        && security_id_ == other.security_id_
        && order_details_comp_ == other.order_details_comp_
        && prev_price_hhi_indicator_ == other.prev_price_hhi_indicator_
        && pad7_ == other.pad7_;
}

bool OrderModify::operator!=(const OrderModify& other) const {
    return !(*this == other);
}

} // namespace eurex::t7::eobi::fbe::v13_0
