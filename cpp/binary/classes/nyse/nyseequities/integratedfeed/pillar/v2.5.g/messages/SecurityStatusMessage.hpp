#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../enums/HaltCondition.hpp"
#include "../enums/MarketState.hpp"
#include "../enums/SecurityStatus.hpp"
#include "../enums/SsrState.hpp"
#include "../enums/SsrTriggeringExchangeId.hpp"
#include "../messages/Message.hpp"

namespace nyse::nyseequities::integratedfeed::pillar::v2_5_g {

class Visitor;

// This message informs clients of changes in the status of a specific security, such as
// Trading Halts, Short Sale Restriction state changes, etc.
class SecurityStatusMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::SecurityStatusMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 42;

    SecurityStatusMessage() = default;
    SecurityStatusMessage(std::chrono::seconds source_time, std::chrono::nanoseconds source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, SecurityStatus security_status, HaltCondition halt_condition, const std::array<std::byte, 4>& reserved_4, std::uint32_t price_1, std::uint32_t price_2, SsrTriggeringExchangeId ssr_triggering_exchange_id, std::uint32_t ssr_triggering_volume, std::optional<std::uint32_t> time, SsrState ssr_state, MarketState market_state, char session_state);

    // Source Time: The time when this msg was generated in the order book, in secs since
    // 1/1/1970 00:00:00 UTC
    std::chrono::seconds source_time() const;
    void set_source_time(std::chrono::seconds value);

    // Source Time Ns: The nanosecond offset from the Time Reference second.
    std::chrono::nanoseconds source_time_ns() const;
    void set_source_time_ns(std::chrono::nanoseconds value);

    // Symbol Index: The ID of the symbol in the Symbol Index msg
    std::uint32_t symbol_index() const;
    void set_symbol_index(std::uint32_t value);

    // Symbol Seq Num: The sequence number of this message in the set of all messages for this
    // symbol
    std::uint32_t symbol_seq_num() const;
    void set_symbol_seq_num(std::uint32_t value);

    // Security Status: The new status that this security is transitioning to.
    SecurityStatus security_status() const;
    void set_security_status(SecurityStatus value);

    // Halt Condition: The halt or other condition associated with the security status change.
    HaltCondition halt_condition() const;
    void set_halt_condition(HaltCondition value);

    // Reserved 4: Future use. Any field content should be ignored.
    const std::array<std::byte, 4>& reserved_4() const;
    std::array<std::byte, 4>& reserved_4();
    void set_reserved_4(const std::array<std::byte, 4>& value);

    // Price 1: Default value is 0. If securityStatus = A and this security is listed on this
    // exchange, then this field is the SSR Triggering Trade Price. If securityStatus = G or I,
    // then this field is the Indication Low Price.
    std::uint32_t price_1() const;
    void set_price_1(std::uint32_t value);

    // Price 2: Default value is 0. If securityStatus = G or I, then this field is the
    // Indication High Price.
    std::uint32_t price_2() const;
    void set_price_2(std::uint32_t value);

    // Ssr Triggering Exchange Id: This field is only populated when securityStatus = A and
    // this security is listed on this exchange. Otherwise it is defaulted to 0x20.
    SsrTriggeringExchangeId ssr_triggering_exchange_id() const;
    void set_ssr_triggering_exchange_id(SsrTriggeringExchangeId value);

    // Ssr Triggering Volume: Default value is 0. This field is only populated when
    // securityStatus = A and this security is listed on this exchange.
    std::uint32_t ssr_triggering_volume() const;
    void set_ssr_triggering_volume(std::uint32_t value);

    // Time: Default value is 0. Format: HHMMSSmmm (mmm = milliseconds). If securityStatus = A
    // and this security is listed on this exchange, then this field is the SSR Trigger Time.
    std::optional<std::uint32_t> time() const;
    void set_time(std::optional<std::uint32_t> value);

    // Ssr State: The current SSR state, which this msg updates if the Security Status field
    // contains an SSR Code.
    SsrState ssr_state() const;
    void set_ssr_state(SsrState value);

    // Market State: The current Market State, which this msg updates if the Security Status
    // field contains a Market State Code.
    MarketState market_state() const;
    void set_market_state(MarketState value);

    // Session State: Unused. Defaulted to 0x00.
    char session_state() const;
    void set_session_state(char value);

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

    bool operator==(const SecurityStatusMessage& other) const;
    bool operator!=(const SecurityStatusMessage& other) const;

  private:
    std::chrono::seconds source_time_{};
    std::chrono::nanoseconds source_time_ns_{};
    std::uint32_t symbol_index_{};
    std::uint32_t symbol_seq_num_{};
    SecurityStatus security_status_{};
    HaltCondition halt_condition_{};
    std::array<std::byte, 4> reserved_4_{};
    std::uint32_t price_1_{};
    std::uint32_t price_2_{};
    SsrTriggeringExchangeId ssr_triggering_exchange_id_{};
    std::uint32_t ssr_triggering_volume_{};
    std::optional<std::uint32_t> time_{};
    SsrState ssr_state_{};
    MarketState market_state_{};
    char session_state_{};
};

} // namespace nyse::nyseequities::integratedfeed::pillar::v2_5_g
