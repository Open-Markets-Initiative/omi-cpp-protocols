#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/MarketMakerMode.hpp"
#include "../enums/MarketParticipantState.hpp"
#include "../enums/PrimaryMarketMaker.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

class Visitor;

// Nasdaq will send out this message only if Nasdaq Operations changes the status of a market
// participant firm in an issue
class MarketParticipantPositionMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::MarketParticipantPositionMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 25;

    MarketParticipantPositionMessage() = default;
    MarketParticipantPositionMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, const std::string& mpid, const std::string& stock, PrimaryMarketMaker primary_market_maker, MarketMakerMode market_maker_mode, MarketParticipantState market_participant_state);

    // Stock Locate: Locate Code uniquely assigned to the security symbol for the day
    std::uint16_t stock_locate() const;
    void set_stock_locate(std::uint16_t value);

    // Tracking Number: Nasdaq internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Mpid: Denotes the market participant identifier for which the position message is being
    // generated
    const std::string& mpid() const;
    std::string& mpid();
    void set_mpid(const std::string& value);

    // Stock: Denotes the security symbol for the issue in the NASDAQ execution system.
    const std::string& stock() const;
    std::string& stock();
    void set_stock(const std::string& value);

    // Primary Market Maker: Indicates if the market participant firm qualifies as a Primary
    // Market Maker in accordance with NASDAQ marketplace rules
    PrimaryMarketMaker primary_market_maker() const;
    void set_primary_market_maker(PrimaryMarketMaker value);

    // Market Maker Mode: Indicates the quoting participant's registration status in relation
    // to SEC Rules 101 and 104 of Regulation M
    MarketMakerMode market_maker_mode() const;
    void set_market_maker_mode(MarketMakerMode value);

    // Market Participant State: Indicates the market participant's current registration status
    // in the issue
    MarketParticipantState market_participant_state() const;
    void set_market_participant_state(MarketParticipantState value);

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

    bool operator==(const MarketParticipantPositionMessage& other) const;
    bool operator!=(const MarketParticipantPositionMessage& other) const;

  private:
    std::uint16_t stock_locate_{};
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    std::string mpid_{};
    std::string stock_{};
    PrimaryMarketMaker primary_market_maker_{};
    MarketMakerMode market_maker_mode_{};
    MarketParticipantState market_participant_state_{};
};

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
