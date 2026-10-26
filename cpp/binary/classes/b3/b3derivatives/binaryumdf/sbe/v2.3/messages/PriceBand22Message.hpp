#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../bitfields/MatchEventIndicator.hpp"
#include "../common/Decimal.hpp"
#include "../enums/PriceBandMidpointPriceType.hpp"
#include "../enums/PriceBandType.hpp"
#include "../enums/PriceLimitType.hpp"
#include "../messages/Message.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

class Visitor;

// PriceBand_22Message
class PriceBand22Message : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::PriceBand22Message;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 48;

    PriceBand22Message() = default;
    PriceBand22Message(std::uint64_t security_id, const MatchEventIndicator& match_event_indicator, std::optional<PriceBandType> price_band_type, std::optional<PriceLimitType> price_limit_type, std::optional<PriceBandMidpointPriceType> price_band_midpoint_price_type, std::optional<Decimal> low_limit_price, std::optional<Decimal> high_limit_price, std::optional<Decimal> trading_reference_price, std::optional<std::chrono::nanoseconds> md_entry_timestamp, std::optional<std::uint32_t> rpt_seq);

    // Security Id: securityID
    std::uint64_t security_id() const;
    void set_security_id(std::uint64_t value);

    // Match Event Indicator: MatchEventIndicator bit set
    const MatchEventIndicator& match_event_indicator() const;
    MatchEventIndicator& match_event_indicator();
    void set_match_event_indicator(const MatchEventIndicator& value);

    // Price Band Type: priceBandType
    std::optional<PriceBandType> price_band_type() const;
    void set_price_band_type(std::optional<PriceBandType> value);

    // Price Limit Type: priceLimitType
    std::optional<PriceLimitType> price_limit_type() const;
    void set_price_limit_type(std::optional<PriceLimitType> value);

    // Price Band Midpoint Price Type: priceBandMidpointPriceType
    std::optional<PriceBandMidpointPriceType> price_band_midpoint_price_type() const;
    void set_price_band_midpoint_price_type(std::optional<PriceBandMidpointPriceType> value);

    // Low Limit Price: lowLimitPrice
    std::optional<Decimal> low_limit_price() const;
    void set_low_limit_price(std::optional<Decimal> value);

    // High Limit Price: highLimitPrice
    std::optional<Decimal> high_limit_price() const;
    void set_high_limit_price(std::optional<Decimal> value);

    // Trading Reference Price: tradingReferencePrice
    std::optional<Decimal> trading_reference_price() const;
    void set_trading_reference_price(std::optional<Decimal> value);

    // Md Entry Timestamp: mDEntryTimestamp
    std::optional<std::chrono::nanoseconds> md_entry_timestamp() const;
    void set_md_entry_timestamp(std::optional<std::chrono::nanoseconds> value);

    // Rpt Seq: rptSeq
    std::optional<std::uint32_t> rpt_seq() const;
    void set_rpt_seq(std::optional<std::uint32_t> value);

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

    bool operator==(const PriceBand22Message& other) const;
    bool operator!=(const PriceBand22Message& other) const;

  private:
    std::uint64_t security_id_{};
    MatchEventIndicator match_event_indicator_{};
    std::optional<PriceBandType> price_band_type_{};
    std::optional<PriceLimitType> price_limit_type_{};
    std::optional<PriceBandMidpointPriceType> price_band_midpoint_price_type_{};
    std::optional<Decimal> low_limit_price_{};
    std::optional<Decimal> high_limit_price_{};
    std::optional<Decimal> trading_reference_price_{};
    std::optional<std::chrono::nanoseconds> md_entry_timestamp_{};
    std::optional<std::uint32_t> rpt_seq_{};
};

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_3
