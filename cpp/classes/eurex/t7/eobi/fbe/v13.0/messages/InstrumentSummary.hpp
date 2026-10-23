#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/FastMarketIndicator.hpp"
#include "../enums/MarketCondition.hpp"
#include "../enums/ProductComplex.hpp"
#include "../enums/SecurityStatus.hpp"
#include "../enums/SecurityTradingEvent.hpp"
#include "../enums/SecurityTradingStatus.hpp"
#include "../enums/SoldOutIndicator.hpp"
#include "../enums/TesSecurityStatus.hpp"
#include "../groups/MdInstrumentEntryGrpComp.hpp"
#include "../messages/Message.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

class Visitor;

// Instrument Summary
class InstrumentSummary : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::InstrumentSummary;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 536;

    InstrumentSummary() = default;
    InstrumentSummary(std::optional<std::int64_t> security_id, std::optional<std::chrono::nanoseconds> last_update_time, std::optional<std::chrono::nanoseconds> trd_reg_ts_execution_time, std::optional<std::uint16_t> tot_no_orders, std::optional<SecurityStatus> security_status, std::optional<SecurityTradingStatus> security_trading_status, std::optional<MarketCondition> market_condition, std::optional<FastMarketIndicator> fast_market_indicator, std::optional<SecurityTradingEvent> security_trading_event, std::optional<SoldOutIndicator> sold_out_indicator, std::optional<Decimal> high_px, std::optional<Decimal> low_px, std::optional<ProductComplex> product_complex, std::optional<std::uint8_t> no_md_entries, std::optional<TesSecurityStatus> tes_security_status, const std::array<std::byte, 5>& pad5, const std::array<MdInstrumentEntryGrpComp, 15>& md_instrument_entry_grp_comp);

    // Security Id:
    std::optional<std::int64_t> security_id() const;
    void set_security_id(std::optional<std::int64_t> value);

    // Last Update Time:
    std::optional<std::chrono::nanoseconds> last_update_time() const;
    void set_last_update_time(std::optional<std::chrono::nanoseconds> value);

    // Trd Reg Ts Execution Time:
    std::optional<std::chrono::nanoseconds> trd_reg_ts_execution_time() const;
    void set_trd_reg_ts_execution_time(std::optional<std::chrono::nanoseconds> value);

    // Tot No Orders:
    std::optional<std::uint16_t> tot_no_orders() const;
    void set_tot_no_orders(std::optional<std::uint16_t> value);

    // Security Status:
    std::optional<SecurityStatus> security_status() const;
    void set_security_status(std::optional<SecurityStatus> value);

    // Security Trading Status:
    std::optional<SecurityTradingStatus> security_trading_status() const;
    void set_security_trading_status(std::optional<SecurityTradingStatus> value);

    // Market Condition:
    std::optional<MarketCondition> market_condition() const;
    void set_market_condition(std::optional<MarketCondition> value);

    // Fast Market Indicator:
    std::optional<FastMarketIndicator> fast_market_indicator() const;
    void set_fast_market_indicator(std::optional<FastMarketIndicator> value);

    // Security Trading Event:
    std::optional<SecurityTradingEvent> security_trading_event() const;
    void set_security_trading_event(std::optional<SecurityTradingEvent> value);

    // Sold Out Indicator:
    std::optional<SoldOutIndicator> sold_out_indicator() const;
    void set_sold_out_indicator(std::optional<SoldOutIndicator> value);

    // High Px:
    std::optional<Decimal> high_px() const;
    void set_high_px(std::optional<Decimal> value);

    // Low Px:
    std::optional<Decimal> low_px() const;
    void set_low_px(std::optional<Decimal> value);

    // Product Complex:
    std::optional<ProductComplex> product_complex() const;
    void set_product_complex(std::optional<ProductComplex> value);

    // No Md Entries:
    std::optional<std::uint8_t> no_md_entries() const;
    void set_no_md_entries(std::optional<std::uint8_t> value);

    // Tes Security Status:
    std::optional<TesSecurityStatus> tes_security_status() const;
    void set_tes_security_status(std::optional<TesSecurityStatus> value);

    // Pad5:
    const std::array<std::byte, 5>& pad5() const;
    std::array<std::byte, 5>& pad5();
    void set_pad5(const std::array<std::byte, 5>& value);

    // Md Instrument Entry Grp Comp:
    const std::array<MdInstrumentEntryGrpComp, 15>& md_instrument_entry_grp_comp() const;
    std::array<MdInstrumentEntryGrpComp, 15>& md_instrument_entry_grp_comp();
    void set_md_instrument_entry_grp_comp(const std::array<MdInstrumentEntryGrpComp, 15>& value);

    // Message
    MessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(Visitor& visitor) const override;
    std::unique_ptr<Message> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Message& other) const override;

    bool operator==(const InstrumentSummary& other) const;
    bool operator!=(const InstrumentSummary& other) const;

  private:
    std::optional<std::int64_t> security_id_{};
    std::optional<std::chrono::nanoseconds> last_update_time_{};
    std::optional<std::chrono::nanoseconds> trd_reg_ts_execution_time_{};
    std::optional<std::uint16_t> tot_no_orders_{};
    std::optional<SecurityStatus> security_status_{};
    std::optional<SecurityTradingStatus> security_trading_status_{};
    std::optional<MarketCondition> market_condition_{};
    std::optional<FastMarketIndicator> fast_market_indicator_{};
    std::optional<SecurityTradingEvent> security_trading_event_{};
    std::optional<SoldOutIndicator> sold_out_indicator_{};
    std::optional<Decimal> high_px_{};
    std::optional<Decimal> low_px_{};
    std::optional<ProductComplex> product_complex_{};
    std::optional<std::uint8_t> no_md_entries_{};
    std::optional<TesSecurityStatus> tes_security_status_{};
    std::array<std::byte, 5> pad5_{};
    std::array<MdInstrumentEntryGrpComp, 15> md_instrument_entry_grp_comp_{};
};

} // namespace eurex::t7::eobi::fbe::v13_0
