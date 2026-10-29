#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/SecurityResponseType.hpp"
#include "../messages/Message.hpp"
#include "../structs/OutboundBusinessHeader.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

class Visitor;

// SecurityDefinitionResponseMessage
class SecurityDefinitionResponseMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::SecurityDefinitionResponseMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 83;

    SecurityDefinitionResponseMessage() = default;
    SecurityDefinitionResponseMessage(const OutboundBusinessHeader& outbound_business_header, const std::array<std::byte, 2>& offset_18_padding_2, std::uint64_t security_req_id, std::optional<std::uint64_t> security_id_optional, SecurityResponseType security_response_type, const std::string& security_strategy_type, const std::string& symbol, std::uint64_t security_response_id, const std::string& sender_location, const std::string& entering_trader);

    // Outbound Business Header: OutboundBusinessHeader
    const OutboundBusinessHeader& outbound_business_header() const;
    OutboundBusinessHeader& outbound_business_header();
    void set_outbound_business_header(const OutboundBusinessHeader& value);

    // Offset 18 Padding 2: 2 bytes padding
    const std::array<std::byte, 2>& offset_18_padding_2() const;
    std::array<std::byte, 2>& offset_18_padding_2();
    void set_offset_18_padding_2(const std::array<std::byte, 2>& value);

    // Security Req Id: securityReqID
    std::uint64_t security_req_id() const;
    void set_security_req_id(std::uint64_t value);

    // Security Id Optional: securityID
    std::optional<std::uint64_t> security_id_optional() const;
    void set_security_id_optional(std::optional<std::uint64_t> value);

    // Security Response Type: securityResponseType
    SecurityResponseType security_response_type() const;
    void set_security_response_type(SecurityResponseType value);

    // Security Strategy Type: securityStrategyType
    const std::string& security_strategy_type() const;
    std::string& security_strategy_type();
    void set_security_strategy_type(const std::string& value);

    // Symbol: symbol
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Security Response Id: securityResponseID
    std::uint64_t security_response_id() const;
    void set_security_response_id(std::uint64_t value);

    // Sender Location: senderLocation
    const std::string& sender_location() const;
    std::string& sender_location();
    void set_sender_location(const std::string& value);

    // Entering Trader: enteringTrader
    const std::string& entering_trader() const;
    std::string& entering_trader();
    void set_entering_trader(const std::string& value);

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

    bool operator==(const SecurityDefinitionResponseMessage& other) const;
    bool operator!=(const SecurityDefinitionResponseMessage& other) const;

  private:
    OutboundBusinessHeader outbound_business_header_{};
    std::array<std::byte, 2> offset_18_padding_2_{};
    std::uint64_t security_req_id_{};
    std::optional<std::uint64_t> security_id_optional_{};
    SecurityResponseType security_response_type_{};
    std::string security_strategy_type_{};
    std::string symbol_{};
    std::uint64_t security_response_id_{};
    std::string sender_location_{};
    std::string entering_trader_{};
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
