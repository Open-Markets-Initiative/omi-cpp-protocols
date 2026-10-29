#include "FullOrderExecution.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

FullOrderExecution::FullOrderExecution(std::optional<Side> side, const std::array<std::byte, 7>& pad7, std::optional<Decimal> price, std::optional<std::chrono::nanoseconds> trd_reg_ts_time_priority, std::optional<std::int64_t> security_id, std::optional<std::uint32_t> trd_match_id, std::optional<std::int32_t> last_qty, std::optional<Decimal> last_px)
  : side_(side), pad7_(pad7), price_(price), trd_reg_ts_time_priority_(trd_reg_ts_time_priority), security_id_(security_id), trd_match_id_(trd_match_id), last_qty_(last_qty), last_px_(last_px) {}

std::optional<Side> FullOrderExecution::side() const { return side_; }
void FullOrderExecution::set_side(std::optional<Side> value) { side_ = value; }

const std::array<std::byte, 7>& FullOrderExecution::pad7() const { return pad7_; }
std::array<std::byte, 7>& FullOrderExecution::pad7() { return pad7_; }
void FullOrderExecution::set_pad7(const std::array<std::byte, 7>& value) { pad7_ = value; }

std::optional<Decimal> FullOrderExecution::price() const { return price_; }
void FullOrderExecution::set_price(std::optional<Decimal> value) { price_ = value; }

std::optional<std::chrono::nanoseconds> FullOrderExecution::trd_reg_ts_time_priority() const { return trd_reg_ts_time_priority_; }
void FullOrderExecution::set_trd_reg_ts_time_priority(std::optional<std::chrono::nanoseconds> value) { trd_reg_ts_time_priority_ = value; }

std::optional<std::int64_t> FullOrderExecution::security_id() const { return security_id_; }
void FullOrderExecution::set_security_id(std::optional<std::int64_t> value) { security_id_ = value; }

std::optional<std::uint32_t> FullOrderExecution::trd_match_id() const { return trd_match_id_; }
void FullOrderExecution::set_trd_match_id(std::optional<std::uint32_t> value) { trd_match_id_ = value; }

std::optional<std::int32_t> FullOrderExecution::last_qty() const { return last_qty_; }
void FullOrderExecution::set_last_qty(std::optional<std::int32_t> value) { last_qty_ = value; }

std::optional<Decimal> FullOrderExecution::last_px() const { return last_px_; }
void FullOrderExecution::set_last_px(std::optional<Decimal> value) { last_px_ = value; }

MessageCode FullOrderExecution::type() const { return message_type; }

std::string_view FullOrderExecution::name() const { return "Full Order Execution"; }

std::size_t FullOrderExecution::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("FullOrderExecution", wire_size, length);

    side_ = wire::nullable_enum<Side>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::read_bytes(data + offset, pad7_.data(), 7);
    offset += 7;

    price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -8);
    offset += 8;

    trd_reg_ts_time_priority_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    security_id_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    trd_match_id_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0xFFFFFFFFULL));
    offset += 4;

    last_qty_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(0x80000000LL));
    offset += 4;

    last_px_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -8);
    offset += 8;

    return offset;
}

std::size_t FullOrderExecution::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("FullOrderExecution", wire_size, capacity);

    wire::write_u8(data + offset, side_ ? static_cast<std::uint8_t>(*side_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_bytes(data + offset, pad7_.data(), 7);
    offset += 7;

    wire::write_i64_le(data + offset, price_ ? static_cast<std::int64_t>(price_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_u64_le(data + offset, trd_reg_ts_time_priority_ ? static_cast<std::uint64_t>(trd_reg_ts_time_priority_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_i64_le(data + offset, security_id_.value_or(static_cast<std::int64_t>(0x8000000000000000LL)));
    offset += 8;

    wire::write_u32_le(data + offset, trd_match_id_.value_or(static_cast<std::uint32_t>(0xFFFFFFFFULL)));
    offset += 4;

    wire::write_i32_le(data + offset, last_qty_.value_or(static_cast<std::int32_t>(0x80000000LL)));
    offset += 4;

    wire::write_i64_le(data + offset, last_px_ ? static_cast<std::int64_t>(last_px_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    return offset;
}

std::size_t FullOrderExecution::encoded_size() const {
    return wire_size;
}

void FullOrderExecution::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> FullOrderExecution::clone() const {
    return std::make_unique<FullOrderExecution>(*this);
}

void FullOrderExecution::print(std::ostream& out) const {
    out << "FullOrderExecution{";
    out << "side=";
    print::optional(out, side_);
    out << ", pad7=";
    print::hex(out, pad7_.data(), pad7_.size());
    out << ", price=";
    print::optional(out, price_);
    out << ", trd_reg_ts_time_priority=";
    print::optional_duration(out, trd_reg_ts_time_priority_);
    out << ", security_id=";
    print::optional(out, security_id_);
    out << ", trd_match_id=";
    print::optional(out, trd_match_id_);
    out << ", last_qty=";
    print::optional(out, last_qty_);
    out << ", last_px=";
    print::optional(out, last_px_);
    out << '}';
}

bool FullOrderExecution::equals(const Message& other) const {
    const auto* that = dynamic_cast<const FullOrderExecution*>(&other);
    return that != nullptr && *this == *that;
}

bool FullOrderExecution::operator==(const FullOrderExecution& other) const {
    return side_ == other.side_
        && pad7_ == other.pad7_
        && price_ == other.price_
        && trd_reg_ts_time_priority_ == other.trd_reg_ts_time_priority_
        && security_id_ == other.security_id_
        && trd_match_id_ == other.trd_match_id_
        && last_qty_ == other.last_qty_
        && last_px_ == other.last_px_;
}

bool FullOrderExecution::operator!=(const FullOrderExecution& other) const {
    return !(*this == other);
}

} // namespace eurex::t7::eobi::fbe::v3_0
