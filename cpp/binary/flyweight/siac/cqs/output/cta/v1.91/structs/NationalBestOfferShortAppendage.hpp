#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/BestOfferParticipantId.hpp"
#include "../common/Decimal.hpp"

namespace siac::cqs::output::cta::v1_91 {

// National Best Offer Short Appendage
class NationalBestOfferShortAppendage {
  public:
    static constexpr const char* name = "NationalBestOfferShortAppendage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit NationalBestOfferShortAppendage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every NationalBestOfferShortAppendage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 5;
    static constexpr std::size_t fixed_size = 5;
    std::size_t encoded_size() const { return 5; }

    BestOfferParticipantId best_offer_participant_id() const { return static_cast<BestOfferParticipantId>(wire::read_char(at(0))); }

    Decimal best_offer_price_short() const { return Decimal(static_cast<std::int64_t>(wire::read_u16_be(at(1))), -2); }

    std::uint16_t best_offer_size_short() const { return wire::read_u16_be(at(3)); }

    void print(std::ostream& out) const {
        out << "NationalBestOfferShortAppendage{";
        out << "best_offer_participant_id=";
        out << best_offer_participant_id();
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

inline std::ostream& operator<<(std::ostream& out, const NationalBestOfferShortAppendage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cqs::output::cta::v1_91
