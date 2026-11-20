// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: groups/CopLimit.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

#include "../common/Decimal.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// Cop Limit
class CopLimit {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 18;

    CopLimit() = default;
    CopLimit(std::optional<std::uint16_t> broker_number, std::optional<std::uint64_t> order_id, std::optional<Decimal> price);

    // Broker Number: An Exchange Assigned Public Number Uniquely Identifying A Partici Pating
    // Organization
    std::optional<std::uint16_t> broker_number() const;
    void set_broker_number(std::optional<std::uint16_t> value);

    // Order Id: Public Numeric Identifier Assigned To An Order By The Trading System
    std::optional<std::uint64_t> order_id() const;
    void set_order_id(std::optional<std::uint64_t> value);

    // Price: The Price In A Valid Currency
    std::optional<Decimal> price() const;
    void set_price(std::optional<Decimal> value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const CopLimit& other) const;
    bool operator!=(const CopLimit& other) const;

  private:
    std::optional<std::uint16_t> broker_number_{};
    std::optional<std::uint64_t> order_id_{};
    std::optional<Decimal> price_{};
};

std::ostream& operator<<(std::ostream& out, const CopLimit& value);

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
