#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/RfqSide.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

// This message is disseminated for anonymous Request for Quotes (RFQs) from the market
class RequestForQuoteMessage {
  public:
    static constexpr const char* name = "RequestForQuoteMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RequestForQuoteMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RequestForQuoteMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 15;
    static constexpr std::size_t fixed_size = 15;
    std::size_t encoded_size() const { return 15; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint16_t trade_date() const { return wire::read_u16_be(at(4)); }

    std::uint32_t tradeable_instrument_id() const { return wire::read_u32_be(at(6)); }

    RfqSide rfq_side() const { return static_cast<RfqSide>(wire::read_char(at(10))); }

    std::uint32_t quantity() const { return wire::read_u32_be(at(11)); }

    void print(std::ostream& out) const {
        out << "RequestForQuoteMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", trade_date=";
        out << trade_date();
        out << ", tradeable_instrument_id=";
        out << tradeable_instrument_id();
        out << ", rfq_side=";
        out << rfq_side();
        out << ", quantity=";
        out << quantity();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RequestForQuoteMessage& value) {
    value.print(out);
    return out;
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
