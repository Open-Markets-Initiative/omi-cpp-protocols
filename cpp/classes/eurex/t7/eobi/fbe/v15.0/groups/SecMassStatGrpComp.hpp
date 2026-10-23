#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

#include "../common/Decimal.hpp"
#include "../enums/MarketCondition.hpp"
#include "../enums/SecurityStatus.hpp"
#include "../enums/SecurityTradingEvent.hpp"
#include "../enums/SecurityTradingStatus.hpp"
#include "../enums/SoldOutIndicator.hpp"
#include "../enums/TesSecurityStatus.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

// Sec Mass Stat Grp Comp
class SecMassStatGrpComp {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 32;

    SecMassStatGrpComp() = default;
    SecMassStatGrpComp(std::optional<std::int64_t> security_id, std::optional<Decimal> high_px, std::optional<Decimal> low_px, std::optional<SecurityStatus> security_status, std::optional<SecurityTradingStatus> security_trading_status, std::optional<MarketCondition> market_condition, std::optional<SecurityTradingEvent> security_trading_event, std::optional<SoldOutIndicator> sold_out_indicator, std::optional<TesSecurityStatus> tes_security_status, const std::array<std::byte, 2>& pad2);

    // Security Id: Unique instrument identifier
    std::optional<std::int64_t> security_id() const;
    void set_security_id(std::optional<std::int64_t> value);

    // High Px:
    std::optional<Decimal> high_px() const;
    void set_high_px(std::optional<Decimal> value);

    // Low Px:
    std::optional<Decimal> low_px() const;
    void set_low_px(std::optional<Decimal> value);

    // Security Status:
    std::optional<SecurityStatus> security_status() const;
    void set_security_status(std::optional<SecurityStatus> value);

    // Security Trading Status:
    std::optional<SecurityTradingStatus> security_trading_status() const;
    void set_security_trading_status(std::optional<SecurityTradingStatus> value);

    // Market Condition:
    std::optional<MarketCondition> market_condition() const;
    void set_market_condition(std::optional<MarketCondition> value);

    // Security Trading Event:
    std::optional<SecurityTradingEvent> security_trading_event() const;
    void set_security_trading_event(std::optional<SecurityTradingEvent> value);

    // Sold Out Indicator:
    std::optional<SoldOutIndicator> sold_out_indicator() const;
    void set_sold_out_indicator(std::optional<SoldOutIndicator> value);

    // Tes Security Status:
    std::optional<TesSecurityStatus> tes_security_status() const;
    void set_tes_security_status(std::optional<TesSecurityStatus> value);

    // Pad2:
    const std::array<std::byte, 2>& pad2() const;
    std::array<std::byte, 2>& pad2();
    void set_pad2(const std::array<std::byte, 2>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const SecMassStatGrpComp& other) const;
    bool operator!=(const SecMassStatGrpComp& other) const;

  private:
    std::optional<std::int64_t> security_id_{};
    std::optional<Decimal> high_px_{};
    std::optional<Decimal> low_px_{};
    std::optional<SecurityStatus> security_status_{};
    std::optional<SecurityTradingStatus> security_trading_status_{};
    std::optional<MarketCondition> market_condition_{};
    std::optional<SecurityTradingEvent> security_trading_event_{};
    std::optional<SoldOutIndicator> sold_out_indicator_{};
    std::optional<TesSecurityStatus> tes_security_status_{};
    std::array<std::byte, 2> pad2_{};
};

std::ostream& operator<<(std::ostream& out, const SecMassStatGrpComp& value);

} // namespace eurex::t7::eobi::fbe::v15_0
