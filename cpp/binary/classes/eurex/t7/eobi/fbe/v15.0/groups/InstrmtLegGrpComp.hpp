#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

#include "../common/Decimal.hpp"
#include "../enums/LegSecurityType.hpp"
#include "../enums/LegSide.hpp"
#include "../enums/RelatedPriceType.hpp"
#include "../enums/TradingStyle.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

// Instrmt Leg Grp Comp
class InstrmtLegGrpComp {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 40;

    InstrmtLegGrpComp() = default;
    InstrmtLegGrpComp(std::optional<std::int32_t> leg_symbol, const std::array<std::byte, 4>& pad4, std::optional<std::int64_t> leg_security_id, std::optional<Decimal> leg_price, std::optional<std::int32_t> leg_ratio_qty, std::optional<LegSecurityType> leg_security_type, std::optional<LegSide> leg_side, std::optional<RelatedPriceType> related_price_type, std::optional<TradingStyle> trading_style, std::optional<Decimal> related_price);

    // Leg Symbol:
    std::optional<std::int32_t> leg_symbol() const;
    void set_leg_symbol(std::optional<std::int32_t> value);

    // Pad4:
    const std::array<std::byte, 4>& pad4() const;
    std::array<std::byte, 4>& pad4();
    void set_pad4(const std::array<std::byte, 4>& value);

    // Leg Security Id:
    std::optional<std::int64_t> leg_security_id() const;
    void set_leg_security_id(std::optional<std::int64_t> value);

    // Leg Price:
    std::optional<Decimal> leg_price() const;
    void set_leg_price(std::optional<Decimal> value);

    // Leg Ratio Qty:
    std::optional<std::int32_t> leg_ratio_qty() const;
    void set_leg_ratio_qty(std::optional<std::int32_t> value);

    // Leg Security Type:
    std::optional<LegSecurityType> leg_security_type() const;
    void set_leg_security_type(std::optional<LegSecurityType> value);

    // Leg Side:
    std::optional<LegSide> leg_side() const;
    void set_leg_side(std::optional<LegSide> value);

    // Related Price Type:
    std::optional<RelatedPriceType> related_price_type() const;
    void set_related_price_type(std::optional<RelatedPriceType> value);

    // Trading Style:
    std::optional<TradingStyle> trading_style() const;
    void set_trading_style(std::optional<TradingStyle> value);

    // Related Price:
    std::optional<Decimal> related_price() const;
    void set_related_price(std::optional<Decimal> value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const InstrmtLegGrpComp& other) const;
    bool operator!=(const InstrmtLegGrpComp& other) const;

  private:
    std::optional<std::int32_t> leg_symbol_{};
    std::array<std::byte, 4> pad4_{};
    std::optional<std::int64_t> leg_security_id_{};
    std::optional<Decimal> leg_price_{};
    std::optional<std::int32_t> leg_ratio_qty_{};
    std::optional<LegSecurityType> leg_security_type_{};
    std::optional<LegSide> leg_side_{};
    std::optional<RelatedPriceType> related_price_type_{};
    std::optional<TradingStyle> trading_style_{};
    std::optional<Decimal> related_price_{};
};

std::ostream& operator<<(std::ostream& out, const InstrmtLegGrpComp& value);

} // namespace eurex::t7::eobi::fbe::v15_0
