#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

class UnderlyingSymbol {
  public:
    static constexpr const char* name = "UnderlyingSymbol";

    // the bytes it reads, which it does not own: they must outlive it
    explicit UnderlyingSymbol(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every UnderlyingSymbol has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return underlying_symbol_text_end(); }

    std::uint8_t underlying_symbol_length() const { return wire::read_u8(at(0)); }

    std::size_t underlying_symbol_text_size() const { return wire::count(underlying_symbol_length()); }
    std::string_view underlying_symbol_text() const {
        wire::require("UnderlyingSymbol", 1 + underlying_symbol_text_size(), bytes_.size());
        return view::characters(at(1), underlying_symbol_text_size());
    }

    void print(std::ostream& out) const {
        out << "UnderlyingSymbol{";
        out << "underlying_symbol_length=";
        out << static_cast<int>(underlying_symbol_length());
        out << ", underlying_symbol_text=";
        print::text(out, underlying_symbol_text());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t underlying_symbol_text_end() const { return 1 + underlying_symbol_text_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const UnderlyingSymbol& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
