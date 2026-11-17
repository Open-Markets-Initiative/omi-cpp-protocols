// Databento.MarketData.Normalized.Dbn.v1: structs/GatewayFrame.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/RecordHeader.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

// A DBN record: the common header, the record its rtype selects, and the ts_out trailer when
// the metadata asks for it
class GatewayFrame {
  public:
    static constexpr const char* name = "GatewayFrame";

    // the bytes it reads, which it does not own: they must outlive it
    explicit GatewayFrame(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every GatewayFrame has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 16;
    static constexpr std::size_t fixed_size = 16;
    std::size_t encoded_size() const { return 16; }

    RecordHeader record_header() const { return RecordHeader{ bytes_.subspan(0) }; }

    void print(std::ostream& out) const {
        out << "GatewayFrame{";
        out << "record_header=";
        record_header().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const GatewayFrame& value) {
    value.print(out);
    return out;
}

} // namespace databento::marketdata::normalized::dbn::v1
