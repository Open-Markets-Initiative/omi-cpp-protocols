#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/MarketMakerMode.hpp"
#include "../enums/MarketParticipantState.hpp"
#include "../enums/PrimaryMarketMaker.hpp"
#include "../messages/PacketMessage.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

class PacketMessageVisitor;

// At the start of each trading day, NASDAQ disseminates a spin of market participant position
// messages. Throughout the day, NASDAQ will send out this message only if NASDAQ Operations
// changes the status of a market participant firm in an issue.
class PayloadMarketParticipantPositionMessage : public PacketMessage {
  public:
    // The code that selects this message
    static constexpr PacketMessageCode message_type = MessageType::MarketParticipantPositionMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 17;

    PayloadMarketParticipantPositionMessage() = default;
    PayloadMarketParticipantPositionMessage(std::chrono::nanoseconds nanoseconds, const std::string& mpid, const std::string& stock, PrimaryMarketMaker primary_market_maker, MarketMakerMode market_maker_mode, MarketParticipantState market_participant_state);

    // Nanoseconds: Nanoseconds portion of the timestamp.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Mpid: Denotes the market participant identifier for which the position message is being
    // generated
    const std::string& mpid() const;
    std::string& mpid();
    void set_mpid(const std::string& value);

    // Stock: Denotes the security symbol for the issue in NASDAQ Single Book. Refer to
    // Appendix NASDAQ Single Book stock symbol convention information.
    const std::string& stock() const;
    std::string& stock();
    void set_stock(const std::string& value);

    // Primary Market Maker: Indicates if the market participant firm qualifies as a Primary
    // Market Maker in accordance with NASDAQ marketplace rules
    PrimaryMarketMaker primary_market_maker() const;
    void set_primary_market_maker(PrimaryMarketMaker value);

    // Market Maker Mode: Indicates the quoting participant’s registration status in relation
    // to SEC Rules 101 and 104 of Regulation M
    MarketMakerMode market_maker_mode() const;
    void set_market_maker_mode(MarketMakerMode value);

    // Market Participant State: Indicates the market participant’s current registration status
    // in the issue
    MarketParticipantState market_participant_state() const;
    void set_market_participant_state(MarketParticipantState value);

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

    bool operator==(const PayloadMarketParticipantPositionMessage& other) const;
    bool operator!=(const PayloadMarketParticipantPositionMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::string mpid_{};
    std::string stock_{};
    PrimaryMarketMaker primary_market_maker_{};
    MarketMakerMode market_maker_mode_{};
    MarketParticipantState market_participant_state_{};
};

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
