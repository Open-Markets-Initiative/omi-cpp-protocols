#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// NewOrderSingleMessage
class CustodianInfo {
  public:
    static constexpr const char* name = "CustodianInfo";

    // the bytes it reads, which it does not own: they must outlive it
    explicit CustodianInfo(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every CustodianInfo has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 12;
    static constexpr std::size_t fixed_size = 12;
    std::size_t encoded_size() const { return 12; }

    std::uint32_t custodian() const { return wire::read_u32_le(at(0)); }

    std::uint32_t custody_account() const { return wire::read_u32_le(at(4)); }

    std::uint32_t custody_allocation_type() const { return wire::read_u32_le(at(8)); }

    void print(std::ostream& out) const {
        out << "CustodianInfo{";
        out << "custodian=";
        out << custodian();
        out << ", custody_account=";
        out << custody_account();
        out << ", custody_allocation_type=";
        out << custody_allocation_type();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const CustodianInfo& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
