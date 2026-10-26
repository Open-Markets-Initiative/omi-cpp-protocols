#pragma once

#include <array>
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

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

class Visitor;

// Informs clients of changes in the status of a specific security or underlying symbol, such
// as Trading Halts, Short Sale Restriction state changes, etc.
class SecurityStatusMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::SecurityStatusMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 42;

    SecurityStatusMessage() = default;
    SecurityStatusMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, SecurityStatus security_status, HaltCondition halt_condition, const std::array<std::byte, 4>& reserved_4, std::uint32_t price_1, std::uint32_t price_2, SsrTriggeringExchangeId ssr_triggering_exchange_id, std::uint32_t ssr_triggering_volume, std::optional<std::uint32_t> time, SsrState ssr_state, MarketState market_state, char session_state);

    // Source Time: The time when this msg was generated in the order book, in seconds since
    // Jan 1, 1970 00:00:00 UTC.
    std::uint32_t source_time() const;
    void set_source_time(std::uint32_t value);

    // Source Time Ns: The nanosecond offset (UTC Time) from the Time Reference message.
    std::uint32_t source_time_ns() const;
    void set_source_time_ns(std::uint32_t value);

    // Symbol Index: The unique ID of this symbol for all products within this market.
    std::uint32_t symbol_index() const;
    void set_symbol_index(std::uint32_t value);

    // Symbol Seq Num: Reserved for future use. Ignore any content.
    std::uint32_t symbol_seq_num() const;
    void set_symbol_seq_num(std::uint32_t value);

    // Security Status: The new status that this security is transitioning to.
    SecurityStatus security_status() const;
    void set_security_status(SecurityStatus value);

    // Halt Condition: Halt condition.
    HaltCondition halt_condition() const;
    void set_halt_condition(HaltCondition value);

    // Reserved 4: Reserved for future use
    const std::array<std::byte, 4>& reserved_4() const;
    std::array<std::byte, 4>& reserved_4();
    void set_reserved_4(const std::array<std::byte, 4>& value);

    // Price 1: Default value is 0. SSR Triggering Trade Price or Indication Low Price
    // depending on Security Status.
    std::uint32_t price_1() const;
    void set_price_1(std::uint32_t value);

    // Price 2: Default value is 0. Indication High Price if securityStatus = G or I.
    std::uint32_t price_2() const;
    void set_price_2(std::uint32_t value);

    // Ssr Triggering Exchange Id: Only populated when securityStatus = A and this security is
    // listed on this exchange. Otherwise defaulted to space (0x20).
    SsrTriggeringExchangeId ssr_triggering_exchange_id() const;
    void set_ssr_triggering_exchange_id(SsrTriggeringExchangeId value);

    // Ssr Triggering Volume: Default value is 0. Only populated when securityStatus = A and
    // this security is listed on this exchange.
    std::uint32_t ssr_triggering_volume() const;
    void set_ssr_triggering_volume(std::uint32_t value);

    // Time: Default value is 0. Format: HHMMSSmmm. SSR Trigger Time if securityStatus = A.
    std::optional<std::uint32_t> time() const;
    void set_time(std::optional<std::uint32_t> value);

    // Ssr State: The current SSR state.
    SsrState ssr_state() const;
    void set_ssr_state(SsrState value);

    // Market State: The current Market State.
    MarketState market_state() const;
    void set_market_state(MarketState value);

    // Session State: Unused. Defaulted to 0x20.
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
    std::uint32_t source_time_{};
    std::uint32_t source_time_ns_{};
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

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
