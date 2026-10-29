#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../enums/FastMarketIndicator.hpp"
#include "../enums/SecurityStatus.hpp"
#include "../enums/SecurityTradingStatus.hpp"
#include "../groups/MdInstrumentEntryGrp.hpp"
#include "../messages/Message.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

class Visitor;

// Published for each instrument in one snapshot cycle, carrying instrument state information
// and trade statistics.
class InstrumentSummaryMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::InstrumentSummaryMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 408;

    InstrumentSummaryMessage() = default;
    InstrumentSummaryMessage(std::int64_t security_id, std::chrono::nanoseconds last_update_time, std::optional<std::chrono::nanoseconds> trd_reg_ts_execution_time, std::uint32_t tot_no_orders, SecurityStatus security_status, SecurityTradingStatus security_trading_status, FastMarketIndicator fast_market_indicator, std::uint8_t no_md_entries, std::int64_t trade_volume, std::uint32_t no_of_trades, const std::array<std::byte, 4>& pad_4, const std::array<MdInstrumentEntryGrp, 15>& md_instrument_entry_grp);

    // Security Id: Unique instrument identifier.
    std::int64_t security_id() const;
    void set_security_id(std::int64_t value);

    // Last Update Time: Last update time of the corresponding order book.
    std::chrono::nanoseconds last_update_time() const;
    void set_last_update_time(std::chrono::nanoseconds value);

    // Trd Reg Ts Execution Time: Last matching execution timestamp.
    std::optional<std::chrono::nanoseconds> trd_reg_ts_execution_time() const;
    void set_trd_reg_ts_execution_time(std::optional<std::chrono::nanoseconds> value);

    // Tot No Orders: Corresponding number of orders for this instrument.
    std::uint32_t tot_no_orders() const;
    void set_tot_no_orders(std::uint32_t value);

    // Security Status: Instrument status.
    SecurityStatus security_status() const;
    void set_security_status(SecurityStatus value);

    // Security Trading Status: Instrument state status.
    SecurityTradingStatus security_trading_status() const;
    void set_security_trading_status(SecurityTradingStatus value);

    // Fast Market Indicator: Indicates if product is in the state Fast Market.
    FastMarketIndicator fast_market_indicator() const;
    void set_fast_market_indicator(FastMarketIndicator value);

    // No Md Entries: Number of entries in Market Data message for MDEntryGrp.
    std::uint8_t no_md_entries() const;
    void set_no_md_entries(std::uint8_t value);

    // Trade Volume: Cumulative volume of units traded in the day.
    std::int64_t trade_volume() const;
    void set_trade_volume(std::int64_t value);

    // No Of Trades: Total number of trades.
    std::uint32_t no_of_trades() const;
    void set_no_of_trades(std::uint32_t value);

    // Pad 4: not used
    const std::array<std::byte, 4>& pad_4() const;
    std::array<std::byte, 4>& pad_4();
    void set_pad_4(const std::array<std::byte, 4>& value);

    // Md Instrument Entry Grp: Instrument trade statistics repeated NoMDEntries times in the
    // Instrument Summary Message. The group is not cut off by design.
    const std::array<MdInstrumentEntryGrp, 15>& md_instrument_entry_grp() const;
    std::array<MdInstrumentEntryGrp, 15>& md_instrument_entry_grp();
    void set_md_instrument_entry_grp(const std::array<MdInstrumentEntryGrp, 15>& value);

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

    bool operator==(const InstrumentSummaryMessage& other) const;
    bool operator!=(const InstrumentSummaryMessage& other) const;

  private:
    std::int64_t security_id_{};
    std::chrono::nanoseconds last_update_time_{};
    std::optional<std::chrono::nanoseconds> trd_reg_ts_execution_time_{};
    std::uint32_t tot_no_orders_{};
    SecurityStatus security_status_{};
    SecurityTradingStatus security_trading_status_{};
    FastMarketIndicator fast_market_indicator_{};
    std::uint8_t no_md_entries_{};
    std::int64_t trade_volume_{};
    std::uint32_t no_of_trades_{};
    std::array<std::byte, 4> pad_4_{};
    std::array<MdInstrumentEntryGrp, 15> md_instrument_entry_grp_{};
};

} // namespace bse::bseindia::eobi::fbe::v1_4
