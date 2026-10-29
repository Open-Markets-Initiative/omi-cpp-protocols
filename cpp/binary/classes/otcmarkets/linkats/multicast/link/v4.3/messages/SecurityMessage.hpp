#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../bitfields/SecurityFlags.hpp"
#include "../enums/AssetClass.hpp"
#include "../enums/ReportingStatus.hpp"
#include "../enums/SecurityAction.hpp"
#include "../enums/SecurityStatus.hpp"
#include "../enums/Tier.hpp"
#include "../messages/Message.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

class Visitor;

// The Security Message is included in all the quote channels and provides basic security
// attribute information.
class SecurityMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::SecurityMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 32;

    SecurityMessage() = default;
    SecurityMessage(std::uint32_t channel_seq_num, const std::string& symbol, std::uint64_t last_update_milli, SecurityAction security_action, AssetClass asset_class, std::uint32_t security_id, const SecurityFlags& security_flags, Tier tier, ReportingStatus reporting_status, SecurityStatus security_status);

    // Channel Seq Num: Monotonically increasing message sequence number at the channel level.
    std::uint32_t channel_seq_num() const;
    void set_channel_seq_num(std::uint32_t value);

    // Symbol: Ticker symbol. Fixed income symbols may not have a symbol. For these securities,
    // the security ID or CUSIP (Reference Data Security Message) must be used as an
    // identifier.
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Last Update Milli: Milliseconds from UTC epoch.
    std::uint64_t last_update_milli() const;
    void set_last_update_milli(std::uint64_t value);

    // Security Action: Security action indicator.
    SecurityAction security_action() const;
    void set_security_action(SecurityAction value);

    // Asset Class: Asset class indicator.
    AssetClass asset_class() const;
    void set_asset_class(AssetClass value);

    // Security Id: Unique security ID issued by OTC Markets.
    std::uint32_t security_id() const;
    void set_security_id(std::uint32_t value);

    // Security Flags: Notes security level attributes
    const SecurityFlags& security_flags() const;
    SecurityFlags& security_flags();
    void set_security_flags(const SecurityFlags& value);

    // Tier: The market tier assigned by OTC Markets Group.
    Tier tier() const;
    void set_tier(Tier value);

    // Reporting Status: Reporting status.
    ReportingStatus reporting_status() const;
    void set_reporting_status(ReportingStatus value);

    // Security Status: Security status.
    SecurityStatus security_status() const;
    void set_security_status(SecurityStatus value);

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

    bool operator==(const SecurityMessage& other) const;
    bool operator!=(const SecurityMessage& other) const;

  private:
    std::uint32_t channel_seq_num_{};
    std::string symbol_{};
    std::uint64_t last_update_milli_{};
    SecurityAction security_action_{};
    AssetClass asset_class_{};
    std::uint32_t security_id_{};
    SecurityFlags security_flags_{};
    Tier tier_{};
    ReportingStatus reporting_status_{};
    SecurityStatus security_status_{};
};

} // namespace otcmarkets::linkats::multicast::link::v4_3
