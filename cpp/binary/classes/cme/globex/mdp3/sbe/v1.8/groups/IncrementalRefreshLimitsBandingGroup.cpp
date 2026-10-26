#include "IncrementalRefreshLimitsBandingGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

IncrementalRefreshLimitsBandingGroup::IncrementalRefreshLimitsBandingGroup(std::optional<Decimal> high_limit_price, std::optional<Decimal> low_limit_price, std::optional<Decimal> max_price_variation, std::int32_t security_id, std::uint32_t rpt_seq)
  : high_limit_price_(high_limit_price), low_limit_price_(low_limit_price), max_price_variation_(max_price_variation), security_id_(security_id), rpt_seq_(rpt_seq) {}

std::optional<Decimal> IncrementalRefreshLimitsBandingGroup::high_limit_price() const { return high_limit_price_; }
void IncrementalRefreshLimitsBandingGroup::set_high_limit_price(std::optional<Decimal> value) { high_limit_price_ = value; }

std::optional<Decimal> IncrementalRefreshLimitsBandingGroup::low_limit_price() const { return low_limit_price_; }
void IncrementalRefreshLimitsBandingGroup::set_low_limit_price(std::optional<Decimal> value) { low_limit_price_ = value; }

std::optional<Decimal> IncrementalRefreshLimitsBandingGroup::max_price_variation() const { return max_price_variation_; }
void IncrementalRefreshLimitsBandingGroup::set_max_price_variation(std::optional<Decimal> value) { max_price_variation_ = value; }

std::int32_t IncrementalRefreshLimitsBandingGroup::security_id() const { return security_id_; }
void IncrementalRefreshLimitsBandingGroup::set_security_id(std::int32_t value) { security_id_ = value; }

std::uint32_t IncrementalRefreshLimitsBandingGroup::rpt_seq() const { return rpt_seq_; }
void IncrementalRefreshLimitsBandingGroup::set_rpt_seq(std::uint32_t value) { rpt_seq_ = value; }

std::size_t IncrementalRefreshLimitsBandingGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("IncrementalRefreshLimitsBandingGroup", wire_size, length);

    high_limit_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -7);
    offset += 8;

    low_limit_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -7);
    offset += 8;

    max_price_variation_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -7);
    offset += 8;

    security_id_ = wire::read_i32_le(data + offset);
    offset += 4;

    rpt_seq_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t IncrementalRefreshLimitsBandingGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("IncrementalRefreshLimitsBandingGroup", wire_size, capacity);

    wire::write_i64_le(data + offset, high_limit_price_ ? static_cast<std::int64_t>(high_limit_price_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, low_limit_price_ ? static_cast<std::int64_t>(low_limit_price_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, max_price_variation_ ? static_cast<std::int64_t>(max_price_variation_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(security_id_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(rpt_seq_));
    offset += 4;

    return offset;
}

std::size_t IncrementalRefreshLimitsBandingGroup::encoded_size() const {
    return wire_size;
}

void IncrementalRefreshLimitsBandingGroup::print(std::ostream& out) const {
    out << "IncrementalRefreshLimitsBandingGroup{";
    out << "high_limit_price=";
    print::optional(out, high_limit_price_);
    out << ", low_limit_price=";
    print::optional(out, low_limit_price_);
    out << ", max_price_variation=";
    print::optional(out, max_price_variation_);
    out << ", security_id=";
    out << security_id_;
    out << ", rpt_seq=";
    out << rpt_seq_;
    out << '}';
}

bool IncrementalRefreshLimitsBandingGroup::operator==(const IncrementalRefreshLimitsBandingGroup& other) const {
    return high_limit_price_ == other.high_limit_price_
        && low_limit_price_ == other.low_limit_price_
        && max_price_variation_ == other.max_price_variation_
        && security_id_ == other.security_id_
        && rpt_seq_ == other.rpt_seq_;
}

bool IncrementalRefreshLimitsBandingGroup::operator!=(const IncrementalRefreshLimitsBandingGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshLimitsBandingGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_8
