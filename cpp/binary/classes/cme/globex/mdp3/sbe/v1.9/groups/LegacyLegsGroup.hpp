#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

#include "../common/Decimal.hpp"
#include "../enums/LegSide.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

// Number of Leg entries
class LegacyLegsGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 18;

    LegacyLegsGroup() = default;
    LegacyLegsGroup(std::int32_t leg_security_id, LegSide leg_side, std::int8_t leg_ratio_qty, std::optional<Decimal> leg_price, std::optional<Decimal> leg_option_delta);

    // Leg Security Id: Leg Security ID
    std::int32_t leg_security_id() const;
    void set_leg_security_id(std::int32_t value);

    // Leg Side: Leg side
    LegSide leg_side() const;
    void set_leg_side(LegSide value);

    // Leg Ratio Qty: Leg ratio of quantity for this individual leg relative to the entire
    // multi-leg instrument
    std::int8_t leg_ratio_qty() const;
    void set_leg_ratio_qty(std::int8_t value);

    // Leg Price: Price for the future leg of a UDS Covered instrument
    std::optional<Decimal> leg_price() const;
    void set_leg_price(std::optional<Decimal> value);

    // Leg Option Delta: Delta used to calculate the quantity of futures used to cover the
    // option or option strategy
    std::optional<Decimal> leg_option_delta() const;
    void set_leg_option_delta(std::optional<Decimal> value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const LegacyLegsGroup& other) const;
    bool operator!=(const LegacyLegsGroup& other) const;

  private:
    std::int32_t leg_security_id_{};
    LegSide leg_side_{};
    std::int8_t leg_ratio_qty_{};
    std::optional<Decimal> leg_price_{};
    std::optional<Decimal> leg_option_delta_{};
};

std::ostream& operator<<(std::ostream& out, const LegacyLegsGroup& value);

} // namespace cme::globex::mdp3::sbe::v1_9
