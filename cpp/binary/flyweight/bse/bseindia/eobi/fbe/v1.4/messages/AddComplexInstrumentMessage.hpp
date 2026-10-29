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
#include "../enums/ProductComplex.hpp"
#include "../enums/ImpliedMarketIndicator.hpp"
#include "../groups/InstrmtLegGrp.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

// Published whenever a new complex instrument is created intraday or an existing complex
// instrument is modified.
class AddComplexInstrumentMessage {
  public:
    static constexpr const char* name = "AddComplexInstrumentMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AddComplexInstrumentMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AddComplexInstrumentMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 104;
    static constexpr std::size_t fixed_size = 104;
    std::size_t encoded_size() const { return 104; }

    std::int64_t security_id() const { return wire::read_i64_le(at(0)); }

    std::chrono::nanoseconds transact_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(8)))); }

    std::optional<std::int32_t> security_sub_type() const { return wire::nullable(wire::read_i32_le(at(16)), static_cast<std::int32_t>(-2147483648LL)); }

    ProductComplex product_complex() const { return static_cast<ProductComplex>(wire::read_u8(at(20))); }

    ImpliedMarketIndicator implied_market_indicator() const { return static_cast<ImpliedMarketIndicator>(wire::read_u8(at(21))); }

    std::uint8_t no_legs() const { return wire::read_u8(at(22)); }

    std::span<const std::byte, 1> pad_1() const { return bytes_.subspan(23).template first<1>(); }

    view::entries<InstrmtLegGrp> instrmt_leg_grp() const { return view::entries<InstrmtLegGrp>{ bytes_.subspan(24), 5 }; }

    void print(std::ostream& out) const {
        out << "AddComplexInstrumentMessage{";
        out << "security_id=";
        out << security_id();
        out << ", transact_time=";
        out << transact_time().count();
        out << ", security_sub_type=";
        print::optional(out, security_sub_type());
        out << ", product_complex=";
        out << product_complex();
        out << ", implied_market_indicator=";
        out << implied_market_indicator();
        out << ", no_legs=";
        out << static_cast<int>(no_legs());
        out << ", pad_1=";
        print::hex(out, pad_1().data(), pad_1().size());
        out << ", instrmt_leg_grp=";
        print::sequence(out, instrmt_leg_grp());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AddComplexInstrumentMessage& value) {
    value.print(out);
    return out;
}

} // namespace bse::bseindia::eobi::fbe::v1_4
