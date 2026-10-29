#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// NewOrderSingleMessage
class CustodianInfo {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 12;

    CustodianInfo() = default;
    CustodianInfo(std::uint32_t custodian, std::uint32_t custody_account, std::uint32_t custody_allocation_type);

    // Custodian: custodian
    std::uint32_t custodian() const;
    void set_custodian(std::uint32_t value);

    // Custody Account: custodyAccount
    std::uint32_t custody_account() const;
    void set_custody_account(std::uint32_t value);

    // Custody Allocation Type: custodyAllocationType
    std::uint32_t custody_allocation_type() const;
    void set_custody_allocation_type(std::uint32_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const CustodianInfo& other) const;
    bool operator!=(const CustodianInfo& other) const;

  private:
    std::uint32_t custodian_{};
    std::uint32_t custody_account_{};
    std::uint32_t custody_allocation_type_{};
};

std::ostream& operator<<(std::ostream& out, const CustodianInfo& value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
