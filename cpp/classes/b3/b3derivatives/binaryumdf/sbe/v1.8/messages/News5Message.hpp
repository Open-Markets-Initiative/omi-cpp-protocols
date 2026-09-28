#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../bitfields/MatchEventIndicator.hpp"
#include "../enums/NewsSource.hpp"
#include "../messages/Message.hpp"
#include "../structs/Headline.hpp"
#include "../structs/Text.hpp"
#include "../structs/UrlLink.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

class Visitor;

// News_5Message
class News5Message : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::News5Message;

    News5Message() = default;
    News5Message(std::optional<std::uint64_t> security_id_optional, const MatchEventIndicator& match_event_indicator, NewsSource news_source, const std::string& language_code, std::uint16_t part_count, std::uint16_t part_number, std::optional<std::uint64_t> news_id, std::optional<std::chrono::nanoseconds> orig_time, std::uint32_t total_text_length, const Headline& headline, const Text& text, const UrlLink& url_link);

    // Security Id Optional: Security Id as defined by B3. For the Security Id list, see the
    // Security Definition message in the market data feed
    std::optional<std::uint64_t> security_id_optional() const;
    void set_security_id_optional(std::optional<std::uint64_t> value);

    // Match Event Indicator: MatchEventIndicator bit set
    const MatchEventIndicator& match_event_indicator() const;
    MatchEventIndicator& match_event_indicator();
    void set_match_event_indicator(const MatchEventIndicator& value);

    // News Source: newsSource
    NewsSource news_source() const;
    void set_news_source(NewsSource value);

    // Language Code: languageCode
    const std::string& language_code() const;
    std::string& language_code();
    void set_language_code(const std::string& value);

    // Part Count: partCount
    std::uint16_t part_count() const;
    void set_part_count(std::uint16_t value);

    // Part Number: partNumber
    std::uint16_t part_number() const;
    void set_part_number(std::uint16_t value);

    // News Id: newsID
    std::optional<std::uint64_t> news_id() const;
    void set_news_id(std::optional<std::uint64_t> value);

    // Orig Time: origTime
    std::optional<std::chrono::nanoseconds> orig_time() const;
    void set_orig_time(std::optional<std::chrono::nanoseconds> value);

    // Total Text Length: totalTextLength
    std::uint32_t total_text_length() const;
    void set_total_text_length(std::uint32_t value);

    // Headline: headline data struct
    const Headline& headline() const;
    Headline& headline();
    void set_headline(const Headline& value);

    // Text: text data struct
    const Text& text() const;
    Text& text();
    void set_text(const Text& value);

    // Url Link: uRLLink data struct
    const UrlLink& url_link() const;
    UrlLink& url_link();
    void set_url_link(const UrlLink& value);

    // Message
    MessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(Visitor& visitor) const override;
    std::unique_ptr<Message> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Message& other) const override;

    bool operator==(const News5Message& other) const;
    bool operator!=(const News5Message& other) const;

  private:
    std::optional<std::uint64_t> security_id_optional_{};
    MatchEventIndicator match_event_indicator_{};
    NewsSource news_source_{};
    std::string language_code_{};
    std::uint16_t part_count_{};
    std::uint16_t part_number_{};
    std::optional<std::uint64_t> news_id_{};
    std::optional<std::chrono::nanoseconds> orig_time_{};
    std::uint32_t total_text_length_{};
    Headline headline_{};
    Text text_{};
    UrlLink url_link_{};
};

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
