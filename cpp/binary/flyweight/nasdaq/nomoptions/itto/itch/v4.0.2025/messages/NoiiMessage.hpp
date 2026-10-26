#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Day.hpp"
#include "../enums/AuctionType.hpp"
#include "../enums/ImbalanceDirection.hpp"
#include "../common/Decimal.hpp"
#include "../enums/CustomerFirmIndicator.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// For the NASDAQ Opening Auction, NASDAQ will begin the dissemination of NOII messages for a
// put or a call option five minutes prior to the start of opening process event and two
// minutes prior to the halt resumption (reopening) process event.
class NoiiMessage {
  public:
    static constexpr const char* name = "NoiiMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit NoiiMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every NoiiMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 34;
    static constexpr std::size_t fixed_size = 34;
    std::size_t encoded_size() const { return 34; }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(0)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(2)))); }
    std::int64_t timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp().count())); }

    std::uint32_t auction_id() const { return wire::read_u32_be(at(8)); }

    AuctionType auction_type() const { return static_cast<AuctionType>(wire::read_char(at(12))); }

    std::uint32_t paired_contracts() const { return wire::read_u32_be(at(13)); }

    ImbalanceDirection imbalance_direction() const { return static_cast<ImbalanceDirection>(wire::read_char(at(17))); }

    std::uint32_t option_id() const { return wire::read_u32_be(at(18)); }

    Decimal imbalance_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(22))), -4); }

    std::uint32_t imbalance_volume() const { return wire::read_u32_be(at(26)); }

    CustomerFirmIndicator customer_firm_indicator() const { return static_cast<CustomerFirmIndicator>(wire::read_char(at(30))); }

    std::span<const std::byte, 3> reserved_3() const { return bytes_.subspan(31).template first<3>(); }

    void print(std::ostream& out) const {
        out << "NoiiMessage{";
        out << "tracking_number=";
        out << tracking_number();
        out << ", timestamp=";
        calendar::print(out, timestamp().count(), 1, "America/New_York");
        out << ", auction_id=";
        out << auction_id();
        out << ", auction_type=";
        out << auction_type();
        out << ", paired_contracts=";
        out << paired_contracts();
        out << ", imbalance_direction=";
        out << imbalance_direction();
        out << ", option_id=";
        out << option_id();
        out << ", imbalance_price=";
        out << imbalance_price();
        out << ", imbalance_volume=";
        out << imbalance_volume();
        out << ", customer_firm_indicator=";
        out << customer_firm_indicator();
        out << ", reserved_3=";
        print::hex(out, reserved_3().data(), reserved_3().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const NoiiMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
