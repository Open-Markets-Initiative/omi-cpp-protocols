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

class Symbol {
  public:
    static constexpr const char* name = "Symbol";

    // the bytes it reads, which it does not own: they must outlive it
    explicit Symbol(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every Symbol has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return symbol_text_end(); }

    std::uint8_t symbol_length() const { return wire::read_u8(at(0)); }

    std::size_t symbol_text_size() const { return wire::count(symbol_length()); }
    std::string_view symbol_text() const {
        wire::require("Symbol", 1 + symbol_text_size(), bytes_.size());
        return view::characters(at(1), symbol_text_size());
    }

    void print(std::ostream& out) const {
        out << "Symbol{";
        out << "symbol_length=";
        out << static_cast<int>(symbol_length());
        out << ", symbol_text=";
        print::text(out, symbol_text());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t symbol_text_end() const { return 1 + symbol_text_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const Symbol& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
