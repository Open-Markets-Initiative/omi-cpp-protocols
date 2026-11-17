// B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.1: groups/CrossSidesGroup.cpp
#include "CrossSidesGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

CrossSidesGroup::CrossSidesGroup(Side side, const std::array<std::byte, 1>& offset_1_padding_1, std::optional<std::uint32_t> account, std::optional<std::uint32_t> entering_firm_optional, std::uint64_t cl_ord_id)
  : side_(side), offset_1_padding_1_(offset_1_padding_1), account_(account), entering_firm_optional_(entering_firm_optional), cl_ord_id_(cl_ord_id) {}

Side CrossSidesGroup::side() const { return side_; }
void CrossSidesGroup::set_side(Side value) { side_ = value; }

const std::array<std::byte, 1>& CrossSidesGroup::offset_1_padding_1() const { return offset_1_padding_1_; }
std::array<std::byte, 1>& CrossSidesGroup::offset_1_padding_1() { return offset_1_padding_1_; }
void CrossSidesGroup::set_offset_1_padding_1(const std::array<std::byte, 1>& value) { offset_1_padding_1_ = value; }

std::optional<std::uint32_t> CrossSidesGroup::account() const { return account_; }
void CrossSidesGroup::set_account(std::optional<std::uint32_t> value) { account_ = value; }

std::optional<std::uint32_t> CrossSidesGroup::entering_firm_optional() const { return entering_firm_optional_; }
void CrossSidesGroup::set_entering_firm_optional(std::optional<std::uint32_t> value) { entering_firm_optional_ = value; }

std::uint64_t CrossSidesGroup::cl_ord_id() const { return cl_ord_id_; }
void CrossSidesGroup::set_cl_ord_id(std::uint64_t value) { cl_ord_id_ = value; }

std::size_t CrossSidesGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("CrossSidesGroup", wire_size, length);

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, offset_1_padding_1_.data(), 1);
    offset += 1;

    account_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    entering_firm_optional_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    cl_ord_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    return offset;
}

std::size_t CrossSidesGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CrossSidesGroup", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_bytes(data + offset, offset_1_padding_1_.data(), 1);
    offset += 1;

    wire::write_u32_le(data + offset, account_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_u32_le(data + offset, entering_firm_optional_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(cl_ord_id_));
    offset += 8;

    return offset;
}

std::size_t CrossSidesGroup::encoded_size() const {
    return wire_size;
}

void CrossSidesGroup::print(std::ostream& out) const {
    out << "CrossSidesGroup{";
    out << "side=";
    out << side_;
    out << ", offset_1_padding_1=";
    print::hex(out, offset_1_padding_1_.data(), offset_1_padding_1_.size());
    out << ", account=";
    print::optional(out, account_);
    out << ", entering_firm_optional=";
    print::optional(out, entering_firm_optional_);
    out << ", cl_ord_id=";
    out << cl_ord_id_;
    out << '}';
}

bool CrossSidesGroup::operator==(const CrossSidesGroup& other) const {
    return side_ == other.side_
        && offset_1_padding_1_ == other.offset_1_padding_1_
        && account_ == other.account_
        && entering_firm_optional_ == other.entering_firm_optional_
        && cl_ord_id_ == other.cl_ord_id_;
}

bool CrossSidesGroup::operator!=(const CrossSidesGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const CrossSidesGroup& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
