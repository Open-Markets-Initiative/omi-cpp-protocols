// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: messages/MocImbalanceMessage.hpp
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
#include "../messages/Message.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

class Visitor;

// Moc Imbalance Message
class MocImbalanceMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MsgType::MocImbalanceMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 30;

    MocImbalanceMessage() = default;
    MocImbalanceMessage(const std::string& symbol, ImbalanceSide imbalance_side, std::optional<std::uint32_t> imbalance_volume, std::optional<std::chrono::microseconds> trading_system_time_stamp, std::optional<Decimal> imbalance_reference_price);

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
    std::optional<std::chrono::microseconds> trading_system_time_stamp() const;
    void set_trading_system_time_stamp(std::optional<std::chrono::microseconds> value);

    // Imbalance Reference Price: The Price That Determines If A Given Limit Priced Market On
    // Close Loc Order Can Contribute To The Moc Imbalance All Loc Orders That Are Priced Equal
    // To Or More Aggressively Than This Price Will Contribute To The Moc Imbalance
    std::optional<Decimal> imbalance_reference_price() const;
    void set_imbalance_reference_price(std::optional<Decimal> value);

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
    std::optional<std::chrono::microseconds> trading_system_time_stamp_{};
    std::optional<Decimal> imbalance_reference_price_{};
};

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
