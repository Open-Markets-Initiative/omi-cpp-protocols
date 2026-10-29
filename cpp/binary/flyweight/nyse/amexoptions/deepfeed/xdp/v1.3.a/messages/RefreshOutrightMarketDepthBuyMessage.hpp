#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/QuoteCondition.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

// The Refresh Market Depth Buy message is sent in the event no Buy Market Depth messages are
// published for the symbol for 2 consecutive minutes.
class RefreshOutrightMarketDepthBuyMessage {
  public:
    static constexpr const char* name = "RefreshOutrightMarketDepthBuyMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RefreshOutrightMarketDepthBuyMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RefreshOutrightMarketDepthBuyMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 44;
    static constexpr std::size_t fixed_size = 44;
    std::size_t encoded_size() const { return 44; }

    std::uint32_t source_time() const { return wire::read_u32_le(at(0)); }

    std::uint32_t source_ns() const { return wire::read_u32_le(at(4)); }

    std::uint32_t series_index() const { return wire::read_u32_le(at(8)); }

    std::uint32_t symbol_seq_num() const { return wire::read_u32_le(at(12)); }

    std::int32_t first_level_price() const { return wire::read_i32_le(at(16)); }

    std::int32_t second_level_price() const { return wire::read_i32_le(at(20)); }

    std::int32_t third_level_price() const { return wire::read_i32_le(at(24)); }

    std::uint16_t first_volume() const { return wire::read_u16_le(at(28)); }

    std::uint16_t second_volume() const { return wire::read_u16_le(at(30)); }

    std::uint16_t third_volume() const { return wire::read_u16_le(at(32)); }

    QuoteCondition quote_condition() const { return static_cast<QuoteCondition>(wire::read_char(at(34))); }

    std::span<const std::byte, 1> reserved_1() const { return bytes_.subspan(35).template first<1>(); }

    std::uint16_t first_level_customer_volume() const { return wire::read_u16_le(at(36)); }

    std::uint16_t second_level_customer_volume() const { return wire::read_u16_le(at(38)); }

    std::uint16_t third_level_customer_volume() const { return wire::read_u16_le(at(40)); }

    std::span<const std::byte, 2> reserved_2() const { return bytes_.subspan(42).template first<2>(); }

    void print(std::ostream& out) const {
        out << "RefreshOutrightMarketDepthBuyMessage{";
        out << "source_time=";
        out << source_time();
        out << ", source_ns=";
        out << source_ns();
        out << ", series_index=";
        out << series_index();
        out << ", symbol_seq_num=";
        out << symbol_seq_num();
        out << ", first_level_price=";
        out << first_level_price();
        out << ", second_level_price=";
        out << second_level_price();
        out << ", third_level_price=";
        out << third_level_price();
        out << ", first_volume=";
        out << first_volume();
        out << ", second_volume=";
        out << second_volume();
        out << ", third_volume=";
        out << third_volume();
        out << ", quote_condition=";
        out << quote_condition();
        out << ", reserved_1=";
        print::hex(out, reserved_1().data(), reserved_1().size());
        out << ", first_level_customer_volume=";
        out << first_level_customer_volume();
        out << ", second_level_customer_volume=";
        out << second_level_customer_volume();
        out << ", third_level_customer_volume=";
        out << third_level_customer_volume();
        out << ", reserved_2=";
        print::hex(out, reserved_2().data(), reserved_2().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RefreshOutrightMarketDepthBuyMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::amexoptions::deepfeed::xdp::v1_3_a
