#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/SecurityStatus.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

// The Series Status message is used to inform the subscribers of changes in symbol status of
// an outright symbol.
class OutrightSeriesStatusMessage {
  public:
    static constexpr const char* name = "OutrightSeriesStatusMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OutrightSeriesStatusMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OutrightSeriesStatusMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 20;
    static constexpr std::size_t fixed_size = 20;
    std::size_t encoded_size() const { return 20; }

    std::uint32_t source_time() const { return wire::read_u32_le(at(0)); }

    std::uint32_t source_time_ns() const { return wire::read_u32_le(at(4)); }

    std::uint32_t series_index() const { return wire::read_u32_le(at(8)); }

    std::uint32_t symbol_seq_num() const { return wire::read_u32_le(at(12)); }

    SecurityStatus security_status() const { return static_cast<SecurityStatus>(wire::read_char(at(16))); }

    char halt_condition() const { return wire::read_char(at(17)); }

    std::span<const std::byte, 2> reserved_2() const { return bytes_.subspan(18).template first<2>(); }

    void print(std::ostream& out) const {
        out << "OutrightSeriesStatusMessage{";
        out << "source_time=";
        out << source_time();
        out << ", source_time_ns=";
        out << source_time_ns();
        out << ", series_index=";
        out << series_index();
        out << ", symbol_seq_num=";
        out << symbol_seq_num();
        out << ", security_status=";
        out << security_status();
        out << ", halt_condition=";
        print::character(out, halt_condition());
        out << ", reserved_2=";
        print::hex(out, reserved_2().data(), reserved_2().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OutrightSeriesStatusMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::amexoptions::deepfeed::xdp::v1_3_a
