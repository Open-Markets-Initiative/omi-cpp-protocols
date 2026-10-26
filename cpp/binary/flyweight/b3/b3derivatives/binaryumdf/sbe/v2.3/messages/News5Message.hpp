#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../enums/NewsSource.hpp"
#include "../structs/Headline.hpp"
#include "../structs/Text.hpp"
#include "../structs/UrlLink.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

// News_5Message
class News5Message {
  public:
    static constexpr const char* name = "News5Message";

    // the bytes it reads, which it does not own: they must outlive it
    explicit News5Message(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every News5Message has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 36;
    std::size_t encoded_size() const { return url_link_end(); }

    std::optional<std::uint64_t> security_id_optional() const { return wire::nullable(wire::read_u64_le(at(0)), static_cast<std::uint64_t>(0ULL)); }

    MatchEventIndicator match_event_indicator() const { return MatchEventIndicator{ bytes_.subspan(8) }; }

    NewsSource news_source() const { return static_cast<NewsSource>(wire::read_u8(at(9))); }

    std::string_view language_code() const { return view::text(at(10), 2, '\0'); }

    std::uint16_t part_count() const { return wire::read_u16_le(at(12)); }

    std::uint16_t part_number() const { return wire::read_u16_le(at(14)); }

    std::optional<std::uint64_t> news_id() const { return wire::nullable(wire::read_u64_le(at(16)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::chrono::nanoseconds> orig_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(24)), static_cast<std::uint64_t>(0ULL)); }

    std::uint32_t total_text_length() const { return wire::read_u32_le(at(32)); }

    Headline headline() const { return Headline{ bytes_.subspan(36) }; }

    Text text() const {
        wire::require("News5Message", headline_end() + Text::minimum_size, bytes_.size());
        return Text{ bytes_.subspan(headline_end()) };
    }

    UrlLink url_link() const {
        wire::require("News5Message", text_end() + UrlLink::minimum_size, bytes_.size());
        return UrlLink{ bytes_.subspan(text_end()) };
    }

    void print(std::ostream& out) const {
        out << "News5Message{";
        out << "security_id_optional=";
        print::optional(out, security_id_optional());
        out << ", match_event_indicator=";
        match_event_indicator().print(out);
        out << ", news_source=";
        out << news_source();
        out << ", language_code=";
        print::text(out, language_code());
        out << ", part_count=";
        out << part_count();
        out << ", part_number=";
        out << part_number();
        out << ", news_id=";
        print::optional(out, news_id());
        out << ", orig_time=";
        print::optional_duration(out, orig_time());
        out << ", total_text_length=";
        out << total_text_length();
        out << ", headline=";
        headline().print(out);
        out << ", text=";
        text().print(out);
        out << ", url_link=";
        url_link().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t headline_end() const { return 36 + headline().encoded_size(); }
    std::size_t text_end() const { return headline_end() + text().encoded_size(); }
    std::size_t url_link_end() const { return text_end() + url_link().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const News5Message& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_3
