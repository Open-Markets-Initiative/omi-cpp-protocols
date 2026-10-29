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

class CurrencyCode {
  public:
    static constexpr const char* name = "CurrencyCode";

    // the bytes it reads, which it does not own: they must outlive it
    explicit CurrencyCode(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every CurrencyCode has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return currency_code_text_end(); }

    std::uint8_t currency_code_length() const { return wire::read_u8(at(0)); }

    std::size_t currency_code_text_size() const { return wire::count(currency_code_length()); }
    std::string_view currency_code_text() const {
        wire::require("CurrencyCode", 1 + currency_code_text_size(), bytes_.size());
        return view::characters(at(1), currency_code_text_size());
    }

    void print(std::ostream& out) const {
        out << "CurrencyCode{";
        out << "currency_code_length=";
        out << static_cast<int>(currency_code_length());
        out << ", currency_code_text=";
        print::text(out, currency_code_text());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t currency_code_text_end() const { return 1 + currency_code_text_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const CurrencyCode& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
