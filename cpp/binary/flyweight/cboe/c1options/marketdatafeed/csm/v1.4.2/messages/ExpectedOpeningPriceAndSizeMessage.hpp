#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/Eop.hpp"
#include "../enums/EopType.hpp"
#include "../enums/LegalMarket.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// The EOP message contains expected opening price and size information for a security.
class ExpectedOpeningPriceAndSizeMessage {
  public:
    static constexpr const char* name = "ExpectedOpeningPriceAndSizeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ExpectedOpeningPriceAndSizeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ExpectedOpeningPriceAndSizeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 19;
    static constexpr std::size_t fixed_size = 19;
    std::size_t encoded_size() const { return 19; }

    std::uint32_t class_key() const { return wire::read_u32_be(at(0)); }

    std::uint32_t security_id() const { return wire::read_u32_be(at(4)); }

    Eop eop() const { return Eop{ bytes_.subspan(8) }; }

    std::uint32_t eos() const { return wire::read_u32_be(at(13)); }

    EopType eop_type() const { return static_cast<EopType>(wire::read_u8(at(17))); }

    LegalMarket legal_market() const { return static_cast<LegalMarket>(wire::read_u8(at(18))); }

    void print(std::ostream& out) const {
        out << "ExpectedOpeningPriceAndSizeMessage{";
        out << "class_key=";
        out << class_key();
        out << ", security_id=";
        out << security_id();
        out << ", eop=";
        eop().print(out);
        out << ", eos=";
        out << eos();
        out << ", eop_type=";
        out << eop_type();
        out << ", legal_market=";
        out << legal_market();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ExpectedOpeningPriceAndSizeMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
