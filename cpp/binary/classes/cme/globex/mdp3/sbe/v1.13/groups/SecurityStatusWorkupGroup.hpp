#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

#include "../enums/AggressorIndicator.hpp"
#include "../enums/Side.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// Number of OrderID entries
class SecurityStatusWorkupGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 10;

    SecurityStatusWorkupGroup() = default;
    SecurityStatusWorkupGroup(std::uint64_t order_id, Side side, std::optional<AggressorIndicator> aggressor_indicator);

    // Order Id: Unique Order ID
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Side: Side of order
    Side side() const;
    void set_side(Side value);

    // Aggressor Indicator: Aggressor Indicator 1=Aggressor Order 0=Passive Order
    std::optional<AggressorIndicator> aggressor_indicator() const;
    void set_aggressor_indicator(std::optional<AggressorIndicator> value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const SecurityStatusWorkupGroup& other) const;
    bool operator!=(const SecurityStatusWorkupGroup& other) const;

  private:
    std::uint64_t order_id_{};
    Side side_{};
    std::optional<AggressorIndicator> aggressor_indicator_{};
};

std::ostream& operator<<(std::ostream& out, const SecurityStatusWorkupGroup& value);

} // namespace cme::globex::mdp3::sbe::v1_13
