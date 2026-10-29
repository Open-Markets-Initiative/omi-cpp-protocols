#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/ClosingOnlyIndicator.hpp"
#include "../enums/MarketId.hpp"
#include "../enums/PriceScaleCode.hpp"
#include "../enums/PutOrCall.hpp"
#include "../enums/SeriesType.hpp"
#include "../messages/Message.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

class Visitor;

// This message is published over the real-time data channels at system startup or in the
// context of a refresh sequence after a Matching Engine or PILLAR Publisher failover.
class OutrightSeriesIndexMappingMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OutrightSeriesIndexMappingMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 51;

    OutrightSeriesIndexMappingMessage() = default;
    OutrightSeriesIndexMappingMessage(std::uint32_t series_index, SeriesType series_type, MarketId market_id, std::uint8_t system_id, const std::string& option_symbol_root, const std::string& underlying_symbol, std::uint32_t underlying_index, PriceScaleCode price_scale_code, std::uint16_t contract_multiplier, const std::string& maturity_date, PutOrCall put_or_call, const std::string& strike_price, ClosingOnlyIndicator closing_only_indicator, const std::array<std::byte, 1>& reserved_1);

    // Series Index: The unique ID of this series for all products within this market
    std::uint32_t series_index() const;
    void set_series_index(std::uint32_t value);

    // Series Type: Identifies series type
    SeriesType series_type() const;
    void set_series_type(SeriesType value);

    // Market Id: ID of the Originating Market
    MarketId market_id() const;
    void set_market_id(MarketId value);

    // System Id: ID of the Originating matching engine server.
    std::uint8_t system_id() const;
    void set_system_id(std::uint8_t value);

    // Option Symbol Root: Root symbol for options in OCC symbology
    const std::string& option_symbol_root() const;
    std::string& option_symbol_root();
    void set_option_symbol_root(const std::string& value);

    // Underlying Symbol: Underlying symbol for options in NYSE symbology
    const std::string& underlying_symbol() const;
    std::string& underlying_symbol();
    void set_underlying_symbol(const std::string& value);

    // Underlying Index: Underlying stock mapping index
    std::uint32_t underlying_index() const;
    void set_underlying_index(std::uint32_t value);

    // Price Scale Code: Specifies placement of the decimal point in price fields for this
    // security.
    PriceScaleCode price_scale_code() const;
    void set_price_scale_code(PriceScaleCode value);

    // Contract Multiplier: Number of Underlying shares per option contract
    std::uint16_t contract_multiplier() const;
    void set_contract_multiplier(std::uint16_t value);

    // Maturity Date: Option maturity date - YYMMDD
    const std::string& maturity_date() const;
    std::string& maturity_date();
    void set_maturity_date(const std::string& value);

    // Put Or Call: Option Type
    PutOrCall put_or_call() const;
    void set_put_or_call(PutOrCall value);

    // Strike Price: Strike price
    const std::string& strike_price() const;
    std::string& strike_price();
    void set_strike_price(const std::string& value);

    // Closing Only Indicator: Closing Only Indicator
    ClosingOnlyIndicator closing_only_indicator() const;
    void set_closing_only_indicator(ClosingOnlyIndicator value);

    // Reserved 1: This field is reserved for future use
    const std::array<std::byte, 1>& reserved_1() const;
    std::array<std::byte, 1>& reserved_1();
    void set_reserved_1(const std::array<std::byte, 1>& value);

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

    bool operator==(const OutrightSeriesIndexMappingMessage& other) const;
    bool operator!=(const OutrightSeriesIndexMappingMessage& other) const;

  private:
    std::uint32_t series_index_{};
    SeriesType series_type_{};
    MarketId market_id_{};
    std::uint8_t system_id_{};
    std::string option_symbol_root_{};
    std::string underlying_symbol_{};
    std::uint32_t underlying_index_{};
    PriceScaleCode price_scale_code_{};
    std::uint16_t contract_multiplier_{};
    std::string maturity_date_{};
    PutOrCall put_or_call_{};
    std::string strike_price_{};
    ClosingOnlyIndicator closing_only_indicator_{};
    std::array<std::byte, 1> reserved_1_{};
};

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
