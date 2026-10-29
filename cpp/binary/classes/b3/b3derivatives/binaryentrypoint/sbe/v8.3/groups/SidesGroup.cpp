#include "SidesGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

SidesGroup::SidesGroup(Side side, std::optional<std::uint32_t> account, std::optional<std::uint32_t> trading_sub_account)
  : side_(side), account_(account), trading_sub_account_(trading_sub_account) {}

Side SidesGroup::side() const { return side_; }
void SidesGroup::set_side(Side value) { side_ = value; }

std::optional<std::uint32_t> SidesGroup::account() const { return account_; }
void SidesGroup::set_account(std::optional<std::uint32_t> value) { account_ = value; }

std::optional<std::uint32_t> SidesGroup::trading_sub_account() const { return trading_sub_account_; }
void SidesGroup::set_trading_sub_account(std::optional<std::uint32_t> value) { trading_sub_account_ = value; }

std::size_t SidesGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SidesGroup", wire_size, length);

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    account_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    trading_sub_account_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    return offset;
}

std::size_t SidesGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SidesGroup", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_u32_le(data + offset, account_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_u32_le(data + offset, trading_sub_account_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    return offset;
}

std::size_t SidesGroup::encoded_size() const {
    return wire_size;
}

void SidesGroup::print(std::ostream& out) const {
    out << "SidesGroup{";
    out << "side=";
    out << side_;
    out << ", account=";
    print::optional(out, account_);
    out << ", trading_sub_account=";
    print::optional(out, trading_sub_account_);
    out << '}';
}

bool SidesGroup::operator==(const SidesGroup& other) const {
    return side_ == other.side_
        && account_ == other.account_
        && trading_sub_account_ == other.trading_sub_account_;
}

bool SidesGroup::operator!=(const SidesGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SidesGroup& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
