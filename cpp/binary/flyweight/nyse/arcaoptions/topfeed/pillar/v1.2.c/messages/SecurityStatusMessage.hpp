#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/SecurityStatus.hpp"
#include "../enums/HaltCondition.hpp"
#include "../enums/SsrTriggeringExchangeId.hpp"
#include "../enums/SsrState.hpp"
#include "../enums/MarketState.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// This message informs clients of changes in the status of a specific security, such as
// Trading Halts, Short Sale Restriction state changes, etc.
class SecurityStatusMessage {
  public:
    static constexpr const char* name = "SecurityStatusMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SecurityStatusMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SecurityStatusMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 42;
    static constexpr std::size_t fixed_size = 42;
    std::size_t encoded_size() const { return 42; }

    std::uint32_t source_time() const { return wire::read_u32_le(at(0)); }

    std::uint32_t source_time_ns() const { return wire::read_u32_le(at(4)); }

    std::uint32_t symbol_index() const { return wire::read_u32_le(at(8)); }

    std::uint32_t symbol_seq_num() const { return wire::read_u32_le(at(12)); }

    SecurityStatus security_status() const { return static_cast<SecurityStatus>(wire::read_char(at(16))); }

    HaltCondition halt_condition() const { return static_cast<HaltCondition>(wire::read_char(at(17))); }

    std::span<const std::byte, 4> reserved_4() const { return bytes_.subspan(18).template first<4>(); }

    std::uint32_t price_1() const { return wire::read_u32_le(at(22)); }

    std::uint32_t price_2() const { return wire::read_u32_le(at(26)); }

    SsrTriggeringExchangeId ssr_triggering_exchange_id() const { return static_cast<SsrTriggeringExchangeId>(wire::read_char(at(30))); }

    std::uint32_t ssr_triggering_volume() const { return wire::read_u32_le(at(31)); }

    std::optional<std::uint32_t> time() const { return wire::nullable(wire::read_u32_le(at(35)), static_cast<std::uint32_t>(0ULL)); }

    SsrState ssr_state() const { return static_cast<SsrState>(wire::read_char(at(39))); }

    MarketState market_state() const { return static_cast<MarketState>(wire::read_char(at(40))); }

    std::uint8_t session_state() const { return wire::read_u8(at(41)); }

    void print(std::ostream& out) const {
        out << "SecurityStatusMessage{";
        out << "source_time=";
        out << source_time();
        out << ", source_time_ns=";
        out << source_time_ns();
        out << ", symbol_index=";
        out << symbol_index();
        out << ", symbol_seq_num=";
        out << symbol_seq_num();
        out << ", security_status=";
        out << security_status();
        out << ", halt_condition=";
        out << halt_condition();
        out << ", reserved_4=";
        print::hex(out, reserved_4().data(), reserved_4().size());
        out << ", price_1=";
        out << price_1();
        out << ", price_2=";
        out << price_2();
        out << ", ssr_triggering_exchange_id=";
        out << ssr_triggering_exchange_id();
        out << ", ssr_triggering_volume=";
        out << ssr_triggering_volume();
        out << ", time=";
        print::optional(out, time());
        out << ", ssr_state=";
        out << ssr_state();
        out << ", market_state=";
        out << market_state();
        out << ", session_state=";
        out << static_cast<int>(session_state());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SecurityStatusMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
