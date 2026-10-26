// Iex.IexEquities.Tops.IexTp.v1.56 canonical values, through the Tmp header: every value the Tmp reading hands
// over from each sample, at its address, held to what the model reads.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <span>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "tests/canonical/Canonical.hpp"
#include "cpp/tmp/iex/iexequities/tops/iextp/v1.56/iex_iexequities_tops_iextp_v1_56.hpp"

// Iex IexEquities Tops IexTp 1.56: the reading of its packets, through its Template Meta Programming header
namespace iex::iexequities::tops::iextp::v1_56 {

/////////////////////////////////////////////////////////////////////
// Reading
/////////////////////////////////////////////////////////////////////

namespace tmp {
    // Thrown when the bytes end before what they must hold
    struct short_read : std::runtime_error {
        using std::runtime_error::runtime_error;
    };

    inline void require(std::size_t needed, std::size_t available) {
        if (needed > available) {
            throw short_read(std::to_string(needed) + " bytes needed, " + std::to_string(available) + " available");
        }
    }

    // The bytes left for a member when the members after it take some: refused when fewer remain
    inline std::size_t leaving(std::size_t available, std::size_t taken) {
        require(taken, available);
        return available - taken;
    }

    // Hand the handler a value, when it takes one
    template <typename Handler, typename T>
    constexpr void call(Handler& handler, const T& value) {
        if constexpr (requires { handler(value); }) { handler(value); }
    }

    // A type laid over its bytes, handed to the handler
    template <typename T, typename Handler>
    const T& read(const std::byte* data, std::size_t length, Handler& handler) {
        require(T::size, length);
        const auto& value = *reinterpret_cast<const T*>(data);
        call(handler, value);
        return value;
    }

    // A field as a rule reads it: an enum by the code the wire holds, a field by its value, and a
    // bit - which its bitfield answers as a value - as it is
    template <typename T>
    constexpr auto rule(const T& field) noexcept {
        if constexpr (requires { field.raw(); }) { return field.raw(); }
        else if constexpr (requires { field.value(); }) { return field.value(); }
        else { return field; }
    }

    // A field an optional member may hold, read as its type's zero when the member is absent
    template <typename T>
    struct maybe {
        const T* field;

        constexpr auto value() const noexcept {
            using type = decltype(field->value());
            return field != nullptr ? field->value() : type{};
        }

        constexpr auto raw() const noexcept requires requires(const T& held) { held.raw(); } {
            using type = decltype(field->raw());
            return field != nullptr ? field->raw() : type{};
        }

        // a bit of an optional bitfield, nothing when the bitfield is absent
        template <typename Bit>
        constexpr auto get() const noexcept requires requires(const T& held) { held.template get<Bit>(); } {
            using type = std::remove_cvref_t<decltype(field->template get<Bit>())>;
            return field != nullptr ? type{ field->template get<Bit>() } : type{};
        }
    };

    // A type laid over its bytes without handing it on: a frame's length, read before the frame is
    template <typename T>
    const T& at(const std::byte* data) noexcept {
        return *reinterpret_cast<const T*>(data);
    }

    // A type laid over bytes ahead of the walk, at a place every byte before it fixes, which a rule
    // reads before the walk reaches it: a branch's code in the header its messages begin with
    template <typename T>
    const T& ahead(const std::byte* data, std::size_t length, std::size_t at) {
        require(at + T::size, length);
        return *reinterpret_cast<const T*>(data + at);
    }

    // A type laid over its bytes and handed to the handler; what it returns is the bytes it took
    template <typename T, typename Handler>
    std::size_t take(const std::byte* data, std::size_t length, Handler& handler) {
        read<T>(data, length, handler);
        return T::size;
    }

    // The characters before a terminating zero, which the bytes must hold
    inline std::size_t terminated(const std::byte* data, std::size_t length) {
        for (std::size_t index = 0; index < length; ++index) {
            if (data[index] == std::byte{ 0 }) { return index; }
        }
        throw short_read("no terminator in " + std::to_string(length) + " bytes");
    }

    // The bytes of a frame ending on a terminator, the terminator included; none while the bytes
    // do not hold it yet
    inline std::size_t through(const std::byte* data, std::size_t length, std::byte terminator) noexcept {
        for (std::size_t index = 0; index < length; ++index) {
            if (data[index] == terminator) { return index + 1; }
        }
        return 0;
    }

    // Bytes a branch's code selects no message for, handed to the handler when it takes them
    template <typename Handler>
    void unknown(Handler& handler, const std::byte* data, std::size_t length) {
        if constexpr (requires { handler.unknown(data, length); }) { handler.unknown(data, length); }
    }

    // How many a count or a length states: a number, or digits of text
    template <typename T>
        requires std::is_integral_v<T>
    constexpr std::size_t count(T value) noexcept { return static_cast<std::size_t>(value); }

    inline std::size_t count(char digit) {
        if (digit < '0' || digit > '9') { throw short_read(std::string("'") + digit + "' is not a digit"); }
        return static_cast<std::size_t>(digit - '0');
    }

    inline std::size_t count(std::string_view digits) {
        std::size_t value = 0;
        for (const char digit : digits) {
            if (digit == ' ') { continue; }
            if (digit < '0' || digit > '9') { throw short_read("\"" + std::string(digits) + "\" is not a number"); }
            value = value * 10 + static_cast<std::size_t>(digit - '0');
        }
        return value;
    }
} // namespace tmp

/////////////////////////////////////////////////////////////////////
// Parsing
/////////////////////////////////////////////////////////////////////

// Message Data: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_message_data([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const message_type& message_type_) {
    if (static_cast<bool>(tmp::rule(message_type_) == 'Q')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& quote_update_message_ = tmp::read<quote_update_message>(data + offset, bound - offset, handler); offset += quote_update_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'T')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_report_message_ = tmp::read<trade_report_message>(data + offset, bound - offset, handler); offset += trade_report_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'B')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_break_message_ = tmp::read<trade_break_message>(data + offset, bound - offset, handler); offset += trade_break_message::size;
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    std::size_t bound = length;
    [[maybe_unused]] const auto& message_header_ = tmp::read<message_header>(data + offset, bound - offset, handler); offset += message_header::size;
    bound = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(message_header_.template get<message_length>()))) + 2);
    tmp::require(bound, length);
    offset += parse_message_data(data + offset, bound - offset, handler, message_header_.template get<message_type>());
    return bound;
}

// Messages: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_messages([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const message_count& message_count_) {
    if (static_cast<bool>(tmp::rule(message_count_) == 0)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, heartbeat{});
        return offset;
    }
    {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            std::size_t count = static_cast<std::size_t>(tmp::rule(message_count_));
            while (count-- > 0) {
                offset += parse_message(data + offset, bound - offset, handler);
            }
        }
        return offset;
    }
}

// Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& iextp_header_ = tmp::read<iextp_header>(data + offset, bound - offset, handler); offset += iextp_header::size;
    {
        const std::size_t size = static_cast<std::size_t>(tmp::rule(iextp_header_.template get<payload_length>()));
        tmp::require(offset + size, bound);
        parse_messages(data + offset, size, handler, iextp_header_.template get<message_count>());
        offset += size;
    }
    return offset;
}


} // namespace iex::iexequities::tops::iextp::v1_56

namespace protocol = ::iex::iexequities::tops::iextp::v1_56;

namespace {

// The handler the reading hands each type laid over a datagram's bytes to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;
    std::string entry;

    // a type this test prints no values of
    template <typename T>
    void operator()(const T&) {}

    void operator()(const protocol::iextp_header& header) {
        if constexpr (requires { header.template get<protocol::version>(); }) { values["packet.iextpheader.version"] = canonical::number(header.template get<protocol::version>().value()); }
        if constexpr (requires { header.template get<protocol::message_protocol_id>(); }) { values["packet.iextpheader.messageprotocolid"] = canonical::number(header.template get<protocol::message_protocol_id>().value()); }
        if constexpr (requires { header.template get<protocol::channel_id>(); }) { values["packet.iextpheader.channelid"] = canonical::number(header.template get<protocol::channel_id>().value()); }
        if constexpr (requires { header.template get<protocol::session_id>(); }) { values["packet.iextpheader.sessionid"] = canonical::number(header.template get<protocol::session_id>().value()); }
        if constexpr (requires { header.template get<protocol::payload_length>(); }) { values["packet.iextpheader.payloadlength"] = canonical::number(header.template get<protocol::payload_length>().value()); }
        if constexpr (requires { header.template get<protocol::message_count>(); }) { values["packet.iextpheader.messagecount"] = canonical::number(header.template get<protocol::message_count>().value()); }
        if constexpr (requires { header.template get<protocol::stream_offset>(); }) { values["packet.iextpheader.streamoffset"] = canonical::number(header.template get<protocol::stream_offset>().value()); }
        if constexpr (requires { header.template get<protocol::first_message_sequence_number>(); }) { values["packet.iextpheader.firstmessagesequencenumber"] = canonical::number(header.template get<protocol::first_message_sequence_number>().value()); }
        if constexpr (requires { header.template get<protocol::send_time>(); }) { values["packet.iextpheader.sendtime"] = canonical::number(header.template get<protocol::send_time>().value()); }
    }

    void operator()(const protocol::message_header& header) {
        entry = "packet.messages.message[" + std::to_string(index++) + "]";
        if constexpr (requires { header.template get<protocol::message_length>(); }) { values[entry + ".messageheader.messagelength"] = canonical::number(header.template get<protocol::message_length>().value()); }
        if constexpr (requires { header.template get<protocol::message_type>(); }) { values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(header.template get<protocol::message_type>().value())); }
    }

    void operator()(const protocol::quote_update_message& message) {
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.quoteupdatemessage";
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".messagedata.quoteupdatemessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::symbol>(); }) { values[entry + ".messagedata.quoteupdatemessage.symbol"] = canonical::text(std::string(message.template get<protocol::symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::bid_size>(); }) { values[entry + ".messagedata.quoteupdatemessage.bidsize"] = canonical::number(message.template get<protocol::bid_size>().value()); }
        if constexpr (requires { message.template get<protocol::bid_price>(); }) { values[entry + ".messagedata.quoteupdatemessage.bidprice"] = canonical::scaled(message.template get<protocol::bid_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::ask_price>(); }) { values[entry + ".messagedata.quoteupdatemessage.askprice"] = canonical::scaled(message.template get<protocol::ask_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::ask_size>(); }) { values[entry + ".messagedata.quoteupdatemessage.asksize"] = canonical::number(message.template get<protocol::ask_size>().value()); }
    }

    void operator()(const protocol::trade_report_message& message) {
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.tradereportmessage";
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".messagedata.tradereportmessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::symbol>(); }) { values[entry + ".messagedata.tradereportmessage.symbol"] = canonical::text(std::string(message.template get<protocol::symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::size_type>(); }) { values[entry + ".messagedata.tradereportmessage.size"] = canonical::number(message.template get<protocol::size_type>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".messagedata.tradereportmessage.price"] = canonical::scaled(message.template get<protocol::price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { values[entry + ".messagedata.tradereportmessage.tradeid"] = canonical::number(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::reserved_4>(); }) { values[entry + ".messagedata.tradereportmessage.reserved4"] = canonical::number(message.template get<protocol::reserved_4>().value()); }
    }

    void operator()(const protocol::trade_break_message& message) {
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.tradebreakmessage";
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".messagedata.tradebreakmessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::symbol>(); }) { values[entry + ".messagedata.tradebreakmessage.symbol"] = canonical::text(std::string(message.template get<protocol::symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::size_type>(); }) { values[entry + ".messagedata.tradebreakmessage.size"] = canonical::number(message.template get<protocol::size_type>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".messagedata.tradebreakmessage.price"] = canonical::scaled(message.template get<protocol::price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { values[entry + ".messagedata.tradebreakmessage.tradeid"] = canonical::number(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::reserved_4>(); }) { values[entry + ".messagedata.tradebreakmessage.reserved4"] = canonical::number(message.template get<protocol::reserved_4>().value()); }
    }
};

// The values the Tmp reading reads from one datagram, by indexed address. A datagram it cannot read
// is a value the model never reads, so it fails rather than passing with nothing compared.
canonical::Listing read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::parse_packet(frame.payload, frame.payload_len, reader);
    } catch (const std::exception& error) {
        reader.values["(does not decode)"] = error.what();
    }

    return reader.values;
}

// Read each datagram of a sample with Tmp and hold it to the model's values
int check(const char* name, const char* capture, const char* expected) {
    const char* packets = std::getenv("OMI_PACKETS_DIR");

    if (packets == nullptr) {
        std::printf("FAIL: OMI_PACKETS_DIR is not set\n");
        return 1;
    }

    const auto model = canonical::load(canonical::root() + "/" + expected);
    std::vector<std::pair<std::string, std::int64_t>> sources;
    sources.emplace_back(std::string{packets} + "/" + capture, 0);

    packet::PcapIterator captures(sources);
    std::size_t datagram = 0;
    int differences = 0;

    while (captures.advance()) {
        const packet::Frame frame(captures.data(), captures.length());

        if (!frame.valid() || !frame.is_udp()) { continue; }

        if (datagram >= model.size()) {
            std::printf("FAIL %s: more datagrams than the model read\n", name);
            return 1;
        }

        differences += canonical::compare(name, datagram, model[datagram], read(frame));
        ++datagram;
    }

    if (datagram != model.size()) {
        std::printf("FAIL %s: %zu datagrams, the model read %zu\n", name, datagram, model.size());
        return 1;
    }

    if (differences == 0) {
        std::printf("ok   %s: %zu datagrams\n", name, datagram);
    }

    return differences == 0 ? 0 : 1;
}

}

int main() {
    std::printf("== Iex.IexEquities.Tops.IexTp.v1.56 (tmp values)\n");
    int failures = 0;
    failures += check("QuoteUpdateMessage", "Iex/IexEquities.Tops.IexTp.v1.56/QuoteUpdateMessage.pcap", "iex/iexequities/tops/iextp/v1.56/QuoteUpdateMessage.values");
    failures += check("TradeReportMessage", "Iex/IexEquities.Tops.IexTp.v1.56/TradeReportMessage.pcap", "iex/iexequities/tops/iextp/v1.56/TradeReportMessage.values");
    return failures == 0 ? 0 : 1;
}