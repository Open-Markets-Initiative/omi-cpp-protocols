#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"

namespace siac::cqs::output::cta::v2_10_a {

// National Best Bid And Offer Short Appendage
class NationalBestBidAndOfferShortAppendage {
  public:
    static constexpr const char* name = "NationalBestBidAndOfferShortAppendage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit NationalBestBidAndOfferShortAppendage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every NationalBestBidAndOfferShortAppendage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 10;
    static constexpr std::size_t fixed_size = 10;
    std::size_t encoded_size() const { return 10; }

    char best_bid_participant_id() const { return wire::read_char(at(0)); }

    Decimal best_bid_price_short() const { return Decimal(static_cast<std::int64_t>(wire::read_u16_be(at(1))), -2); }

    std::uint16_t best_bid_size_short() const { return wire::read_u16_be(at(3)); }

    char best_offer_participant_id() const { return wire::read_char(at(5)); }

    Decimal best_offer_price_short() const { return Decimal(static_cast<std::int64_t>(wire::read_u16_be(at(6))), -2); }

    std::uint16_t best_offer_size_short() const { return wire::read_u16_be(at(8)); }

    void print(std::ostream& out) const {
        out << "NationalBestBidAndOfferShortAppendage{";
        out << "best_bid_participant_id=";
        print::character(out, best_bid_participant_id());
        out << ", best_bid_price_short=";
        out << best_bid_price_short();
        out << ", best_bid_size_short=";
        out << best_bid_size_short();
        out << ", best_offer_participant_id=";
        print::character(out, best_offer_participant_id());
        out << ", best_offer_price_short=";
        out << best_offer_price_short();
        out << ", best_offer_size_short=";
        out << best_offer_size_short();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const NationalBestBidAndOfferShortAppendage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cqs::output::cta::v2_10_a
