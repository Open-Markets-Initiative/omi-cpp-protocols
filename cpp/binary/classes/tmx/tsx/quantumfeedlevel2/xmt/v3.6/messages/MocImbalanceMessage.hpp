// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/MocImbalanceMessage.hpp
#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/ImbalanceSide.hpp"
#include "../enums/MarketOrderImbalanceSide.hpp"
#include "../messages/Message.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

class Visitor;

// Moc Imbalance Message
class MocImbalanceMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MsgType::MocImbalanceMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 62;

    MocImbalanceMessage() = default;
    MocImbalanceMessage(const std::string& symbol, ImbalanceSide imbalance_side, std::optional<std::uint32_t> imbalance_volume, std::optional<std::chrono::nanoseconds> trading_system_time_stamp, std::optional<Decimal> imbalance_reference_price, std::optional<std::uint32_t> paired_volume, std::optional<std::uint32_t> market_order_imbalance_volume, MarketOrderImbalanceSide market_order_imbalance_side, std::optional<Decimal> near_indicative_closing_price, std::optional<Decimal> far_indicative_closing_price, std::optional<Decimal> price_variation);

    // Symbol: A Unique Alphanumeric Identifier For A Security
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Imbalance Side: Marker To Indicate Which Side Has An Imbalance Volume For Market On
    // Close
    ImbalanceSide imbalance_side() const;
    void set_imbalance_side(ImbalanceSide value);

    // Imbalance Volume: Identifies The Volume Of Shares Of The Imbalance Side For Market On
    // Close
    std::optional<std::uint32_t> imbalance_volume() const;
    void set_imbalance_volume(std::optional<std::uint32_t> value);

    // Trading System Time Stamp: The Time At Which The Event Being Reported Occurred In The
    // Trading Engine
    std::optional<std::chrono::nanoseconds> trading_system_time_stamp() const;
    void set_trading_system_time_stamp(std::optional<std::chrono::nanoseconds> value);

    // Imbalance Reference Price: The Price That Determines If A Given Limit Priced Market On
    // Close Loc Order Can Contribute To The Moc Imbalance All Loc Orders That Are Priced Equal
    // To Or More Aggressively Than This Price Will Contribute To The Moc Imbalance
    std::optional<Decimal> imbalance_reference_price() const;
    void set_imbalance_reference_price(std::optional<Decimal> value);

    // Paired Volume: The Number Of Moc And Loc Shares That Are Able Be Matched At The
    // Reference Price
    std::optional<std::uint32_t> paired_volume() const;
    void set_paired_volume(std::optional<std::uint32_t> value);

    // Market Order Imbalance Volume: Indicates The Share Imbalance When Considering Moc Orders
    // Only Note This Will Not Change From Freeze Period As Moc Orders Are Not Allowed After
    // This Time
    std::optional<std::uint32_t> market_order_imbalance_volume() const;
    void set_market_order_imbalance_volume(std::optional<std::uint32_t> value);

    // Market Order Imbalance Side: Side Buy Or Sell Of The Market Order Imbalance Volume
    MarketOrderImbalanceSide market_order_imbalance_side() const;
    void set_market_order_imbalance_side(MarketOrderImbalanceSide value);

    // Near Indicative Closing Price: The Calculated Closing Price That Will Maximize The
    // Number Of Shares Matched Based On On Close Orders Moc Loc And Visible Continuous Market
    // Orders Effectively This Is The Price At Which The Closing Print Would Occur At The Time
    // Of Publication
    std::optional<Decimal> near_indicative_closing_price() const;
    void set_near_indicative_closing_price(std::optional<Decimal> value);

    // Far Indicative Closing Price: The Calculated Closing Price That Will Maximize The Number
    // Of Shares Matched Based On Closing Interest Only Moc Loc This Calculation Excludes
    // Continuous Market Orders
    std::optional<Decimal> far_indicative_closing_price() const;
    void set_far_indicative_closing_price(std::optional<Decimal> value);

    // Price Variation: This Field Indicates The Absolute Value Of The Percentage Of Deviation
    // Of The Near Indicative Closing Price From The Reference Price
    std::optional<Decimal> price_variation() const;
    void set_price_variation(std::optional<Decimal> value);

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

    bool operator==(const MocImbalanceMessage& other) const;
    bool operator!=(const MocImbalanceMessage& other) const;

  private:
    std::string symbol_{};
    ImbalanceSide imbalance_side_{};
    std::optional<std::uint32_t> imbalance_volume_{};
    std::optional<std::chrono::nanoseconds> trading_system_time_stamp_{};
    std::optional<Decimal> imbalance_reference_price_{};
    std::optional<std::uint32_t> paired_volume_{};
    std::optional<std::uint32_t> market_order_imbalance_volume_{};
    MarketOrderImbalanceSide market_order_imbalance_side_{};
    std::optional<Decimal> near_indicative_closing_price_{};
    std::optional<Decimal> far_indicative_closing_price_{};
    std::optional<Decimal> price_variation_{};
};

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
