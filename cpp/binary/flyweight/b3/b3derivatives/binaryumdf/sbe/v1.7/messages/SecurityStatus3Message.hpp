#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../enums/TradingSessionId.hpp"
#include "../enums/SecurityTradingStatus.hpp"
#include "../enums/SecurityTradingEvent.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// SecurityStatus_3Message
class SecurityStatus3Message {
  public:
    static constexpr const char* name = "SecurityStatus3Message";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SecurityStatus3Message(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SecurityStatus3Message has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 36;
    static constexpr std::size_t fixed_size = 36;
    std::size_t encoded_size() const { return 36; }

    std::uint64_t security_id() const { return wire::read_u64_le(at(0)); }

    MatchEventIndicator match_event_indicator() const { return MatchEventIndicator{ bytes_.subspan(8) }; }

    TradingSessionId trading_session_id() const { return static_cast<TradingSessionId>(wire::read_u8(at(9))); }

    SecurityTradingStatus security_trading_status() const { return static_cast<SecurityTradingStatus>(wire::read_u8(at(10))); }

    std::optional<SecurityTradingEvent> security_trading_event() const { return wire::nullable_enum<SecurityTradingEvent>(wire::read_u8(at(11)), static_cast<std::uint8_t>(255ULL)); }

    std::uint16_t trade_date() const { return wire::read_u16_le(at(12)); }

    std::span<const std::byte, 2> offset_14_padding_2() const { return bytes_.subspan(14).template first<2>(); }

    std::optional<std::chrono::nanoseconds> trad_ses_open_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(16)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::uint64_t> transact_time() const { return wire::nullable(wire::read_u64_le(at(24)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::uint32_t> rpt_seq() const { return wire::nullable(wire::read_u32_le(at(32)), static_cast<std::uint32_t>(0ULL)); }

    void print(std::ostream& out) const {
        out << "SecurityStatus3Message{";
        out << "security_id=";
        out << security_id();
        out << ", match_event_indicator=";
        match_event_indicator().print(out);
        out << ", trading_session_id=";
        out << trading_session_id();
        out << ", security_trading_status=";
        out << security_trading_status();
        out << ", security_trading_event=";
        print::optional(out, security_trading_event());
        out << ", trade_date=";
        out << trade_date();
        out << ", offset_14_padding_2=";
        print::hex(out, offset_14_padding_2().data(), offset_14_padding_2().size());
        out << ", trad_ses_open_time=";
        print::optional_duration(out, trad_ses_open_time());
        out << ", transact_time=";
        print::optional(out, transact_time());
        out << ", rpt_seq=";
        print::optional(out, rpt_seq());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SecurityStatus3Message& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_7
