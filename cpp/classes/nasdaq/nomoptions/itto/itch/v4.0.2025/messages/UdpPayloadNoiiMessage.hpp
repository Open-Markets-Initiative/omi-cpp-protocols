#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/AuctionType.hpp"
#include "../enums/CustomerFirmIndicator.hpp"
#include "../enums/ImbalanceDirection.hpp"
#include "../messages/PacketMessage.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

class PacketMessageVisitor;

// For the NASDAQ Opening Auction, NASDAQ will begin the dissemination of NOII messages for a
// put or a call option five minutes prior to the start of opening process event and two
// minutes prior to the halt resumption (reopening) process event.
class UdpPayloadNoiiMessage : public PacketMessage {
  public:
    // The code that selects this message
    static constexpr PacketMessageCode message_type = MessageType::NoiiMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 34;

    UdpPayloadNoiiMessage() = default;
    UdpPayloadNoiiMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint32_t auction_id, AuctionType auction_type, std::uint32_t paired_contracts, ImbalanceDirection imbalance_direction, std::uint32_t option_id, Decimal imbalance_price, std::uint32_t imbalance_volume, CustomerFirmIndicator customer_firm_indicator, const std::array<std::byte, 3>& reserved_3);

    // Tracking Number: Nasdaq Internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Auction Id: Uniquely identifies the Auction for the trading day.
    std::uint32_t auction_id() const;
    void set_auction_id(std::uint32_t value);

    // Auction Type: Type of Auction:
    AuctionType auction_type() const;
    void set_auction_type(AuctionType value);

    // Paired Contracts: The total number of contracts that are eligible to be matched at the
    // Current Reference Price. 0 for Price Improvement (PRISM) Auction.
    std::uint32_t paired_contracts() const;
    void set_paired_contracts(std::uint32_t value);

    // Imbalance Direction: Indicates the market side of the imbalance
    ImbalanceDirection imbalance_direction() const;
    void set_imbalance_direction(ImbalanceDirection value);

    // Option Id: Option ID assigned daily, valid for trading day.
    std::uint32_t option_id() const;
    void set_option_id(std::uint32_t value);

    // Imbalance Price: The imbalance price. 0 for Price Improvement (PRISM) Auction
    Decimal imbalance_price() const;
    void set_imbalance_price(Decimal value);

    // Imbalance Volume: The imbalance volume.
    std::uint32_t imbalance_volume() const;
    void set_imbalance_volume(std::uint32_t value);

    // Customer Firm Indicator: For Order Exposure (AuctionType=I) only. Indicates the order
    // capacity:
    CustomerFirmIndicator customer_firm_indicator() const;
    void set_customer_firm_indicator(CustomerFirmIndicator value);

    // Reserved 3: Reserved for future use
    const std::array<std::byte, 3>& reserved_3() const;
    std::array<std::byte, 3>& reserved_3();
    void set_reserved_3(const std::array<std::byte, 3>& value);

    // PacketMessage
    PacketMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(PacketMessageVisitor& visitor) const override;
    std::unique_ptr<PacketMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const PacketMessage& other) const override;

    bool operator==(const UdpPayloadNoiiMessage& other) const;
    bool operator!=(const UdpPayloadNoiiMessage& other) const;

  private:
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    std::uint32_t auction_id_{};
    AuctionType auction_type_{};
    std::uint32_t paired_contracts_{};
    ImbalanceDirection imbalance_direction_{};
    std::uint32_t option_id_{};
    Decimal imbalance_price_{ 0, -4 };
    std::uint32_t imbalance_volume_{};
    CustomerFirmIndicator customer_firm_indicator_{};
    std::array<std::byte, 3> reserved_3_{};
};

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
