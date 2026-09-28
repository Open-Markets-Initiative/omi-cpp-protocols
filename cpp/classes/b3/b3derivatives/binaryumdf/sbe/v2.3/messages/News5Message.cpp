#include "News5Message.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

News5Message::News5Message(std::optional<std::uint64_t> security_id_optional, const MatchEventIndicator& match_event_indicator, NewsSource news_source, const std::string& language_code, std::uint16_t part_count, std::uint16_t part_number, std::optional<std::uint64_t> news_id, std::optional<std::chrono::nanoseconds> orig_time, std::uint32_t total_text_length, const Headline& headline, const Text& text, const UrlLink& url_link)
  : security_id_optional_(security_id_optional), match_event_indicator_(match_event_indicator), news_source_(news_source), language_code_(language_code), part_count_(part_count), part_number_(part_number), news_id_(news_id), orig_time_(orig_time), total_text_length_(total_text_length), headline_(headline), text_(text), url_link_(url_link) {}

std::optional<std::uint64_t> News5Message::security_id_optional() const { return security_id_optional_; }
void News5Message::set_security_id_optional(std::optional<std::uint64_t> value) { security_id_optional_ = value; }

const MatchEventIndicator& News5Message::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& News5Message::match_event_indicator() { return match_event_indicator_; }
void News5Message::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

NewsSource News5Message::news_source() const { return news_source_; }
void News5Message::set_news_source(NewsSource value) { news_source_ = value; }

const std::string& News5Message::language_code() const { return language_code_; }
std::string& News5Message::language_code() { return language_code_; }
void News5Message::set_language_code(const std::string& value) { language_code_ = value; }

std::uint16_t News5Message::part_count() const { return part_count_; }
void News5Message::set_part_count(std::uint16_t value) { part_count_ = value; }

std::uint16_t News5Message::part_number() const { return part_number_; }
void News5Message::set_part_number(std::uint16_t value) { part_number_ = value; }

std::optional<std::uint64_t> News5Message::news_id() const { return news_id_; }
void News5Message::set_news_id(std::optional<std::uint64_t> value) { news_id_ = value; }

std::optional<std::chrono::nanoseconds> News5Message::orig_time() const { return orig_time_; }
void News5Message::set_orig_time(std::optional<std::chrono::nanoseconds> value) { orig_time_ = value; }

std::uint32_t News5Message::total_text_length() const { return total_text_length_; }
void News5Message::set_total_text_length(std::uint32_t value) { total_text_length_ = value; }

const Headline& News5Message::headline() const { return headline_; }
Headline& News5Message::headline() { return headline_; }
void News5Message::set_headline(const Headline& value) { headline_ = value; }

const Text& News5Message::text() const { return text_; }
Text& News5Message::text() { return text_; }
void News5Message::set_text(const Text& value) { text_ = value; }

const UrlLink& News5Message::url_link() const { return url_link_; }
UrlLink& News5Message::url_link() { return url_link_; }
void News5Message::set_url_link(const UrlLink& value) { url_link_ = value; }

MessageCode News5Message::type() const { return message_type; }

std::string_view News5Message::name() const { return "News 5 Message"; }

std::size_t News5Message::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("News5Message", offset + 8, length);
    security_id_optional_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    wire::require("News5Message", offset + 1, length);
    news_source_ = static_cast<NewsSource>(wire::read_u8(data + offset));
    offset += 1;

    wire::require("News5Message", offset + 2, length);
    language_code_ = wire::read_text(data + offset, 2, '\0');
    offset += 2;

    wire::require("News5Message", offset + 2, length);
    part_count_ = wire::read_u16_le(data + offset);
    offset += 2;

    wire::require("News5Message", offset + 2, length);
    part_number_ = wire::read_u16_le(data + offset);
    offset += 2;

    wire::require("News5Message", offset + 8, length);
    news_id_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("News5Message", offset + 8, length);
    orig_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("News5Message", offset + 4, length);
    total_text_length_ = wire::read_u32_le(data + offset);
    offset += 4;

    offset += headline_.decode(data + offset, length - offset);

    offset += text_.decode(data + offset, length - offset);

    offset += url_link_.decode(data + offset, length - offset);

    return offset;
}

std::size_t News5Message::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("News5Message", encoded_size(), capacity);

    wire::write_u64_le(data + offset, security_id_optional_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(news_source_));
    offset += 1;

    wire::write_text(data + offset, 2, '\0', language_code_);
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(part_count_));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(part_number_));
    offset += 2;

    wire::write_u64_le(data + offset, news_id_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_u64_le(data + offset, orig_time_ ? static_cast<std::uint64_t>(orig_time_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(total_text_length_));
    offset += 4;

    offset += headline_.encode(data + offset, capacity - offset);

    offset += text_.encode(data + offset, capacity - offset);

    offset += url_link_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t News5Message::encoded_size() const {
    return 8 + match_event_indicator_.encoded_size() + 1 + 2 + 2 + 2 + 8 + 8 + 4 + headline_.encoded_size() + text_.encoded_size() + url_link_.encoded_size();
}

void News5Message::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> News5Message::clone() const {
    return std::make_unique<News5Message>(*this);
}

void News5Message::print(std::ostream& out) const {
    out << "News5Message{";
    out << "security_id_optional=";
    print::optional(out, security_id_optional_);
    out << ", match_event_indicator=";
    match_event_indicator_.print(out);
    out << ", news_source=";
    out << news_source_;
    out << ", language_code=";
    print::text(out, language_code_);
    out << ", part_count=";
    out << part_count_;
    out << ", part_number=";
    out << part_number_;
    out << ", news_id=";
    print::optional(out, news_id_);
    out << ", orig_time=";
    print::optional_duration(out, orig_time_);
    out << ", total_text_length=";
    out << total_text_length_;
    out << ", headline=";
    headline_.print(out);
    out << ", text=";
    text_.print(out);
    out << ", url_link=";
    url_link_.print(out);
    out << '}';
}

bool News5Message::equals(const Message& other) const {
    const auto* that = dynamic_cast<const News5Message*>(&other);
    return that != nullptr && *this == *that;
}

bool News5Message::operator==(const News5Message& other) const {
    return security_id_optional_ == other.security_id_optional_
        && match_event_indicator_ == other.match_event_indicator_
        && news_source_ == other.news_source_
        && language_code_ == other.language_code_
        && part_count_ == other.part_count_
        && part_number_ == other.part_number_
        && news_id_ == other.news_id_
        && orig_time_ == other.orig_time_
        && total_text_length_ == other.total_text_length_
        && headline_ == other.headline_
        && text_ == other.text_
        && url_link_ == other.url_link_;
}

bool News5Message::operator!=(const News5Message& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_3
