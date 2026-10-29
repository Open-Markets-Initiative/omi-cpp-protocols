#include "CustodianInfo.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

CustodianInfo::CustodianInfo(std::uint32_t custodian, std::uint32_t custody_account, std::uint32_t custody_allocation_type)
  : custodian_(custodian), custody_account_(custody_account), custody_allocation_type_(custody_allocation_type) {}

std::uint32_t CustodianInfo::custodian() const { return custodian_; }
void CustodianInfo::set_custodian(std::uint32_t value) { custodian_ = value; }

std::uint32_t CustodianInfo::custody_account() const { return custody_account_; }
void CustodianInfo::set_custody_account(std::uint32_t value) { custody_account_ = value; }

std::uint32_t CustodianInfo::custody_allocation_type() const { return custody_allocation_type_; }
void CustodianInfo::set_custody_allocation_type(std::uint32_t value) { custody_allocation_type_ = value; }

std::size_t CustodianInfo::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("CustodianInfo", wire_size, length);

    custodian_ = wire::read_u32_le(data + offset);
    offset += 4;

    custody_account_ = wire::read_u32_le(data + offset);
    offset += 4;

    custody_allocation_type_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t CustodianInfo::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CustodianInfo", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(custodian_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(custody_account_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(custody_allocation_type_));
    offset += 4;

    return offset;
}

std::size_t CustodianInfo::encoded_size() const {
    return wire_size;
}

void CustodianInfo::print(std::ostream& out) const {
    out << "CustodianInfo{";
    out << "custodian=";
    out << custodian_;
    out << ", custody_account=";
    out << custody_account_;
    out << ", custody_allocation_type=";
    out << custody_allocation_type_;
    out << '}';
}

bool CustodianInfo::operator==(const CustodianInfo& other) const {
    return custodian_ == other.custodian_
        && custody_account_ == other.custody_account_
        && custody_allocation_type_ == other.custody_allocation_type_;
}

bool CustodianInfo::operator!=(const CustodianInfo& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const CustodianInfo& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
