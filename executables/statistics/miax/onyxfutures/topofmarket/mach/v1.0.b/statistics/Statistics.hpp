#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/binary/modern/miax/onyxfutures/topofmarket/mach/v1.0.b/definitions.hpp"

namespace statistics {

// Miax Mach C++ statistics
struct Statistics {

    miax::onyxfutures::topofmarket::mach::v1_0_b::MachMessageIterator mach_message;
    packet::Parser& parser;
    const statistics::Options& options;

    // counters
    uint64_t total_packets = 0;
    uint64_t unknown_packets = 0;
    uint64_t total_messages = 0;
    uint64_t unknown_messages = 0;
    uint64_t heartbeats = 0;

    // message counters
    uint64_t application_message = 0;
    uint64_t simple_instrument_definition_message = 0;
    uint64_t complex_instrument_definition_message = 0;
    uint64_t system_state_message = 0;
    uint64_t instrument_trading_status_notification_message = 0;
    uint64_t best_bid_and_offer_message = 0;
    uint64_t last_sale_message = 0;
    uint64_t trade_cancel_message = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {}

    // process a frame: every tree carrying its transport reads it
    void udp() {
        const auto& frame = parser.frame();

        if (frame.is_udp()) {
            walk_mach_message(frame);
        }
    }

    // walk the Packet tree's datagrams
    void walk_mach_message(const packet::Frame& frame) {
        mach_message.initialize(frame.payload, frame.payload_len);

        while (mach_message.next()) {
            if (mach_message.packet_type == 0 || mach_message.packet_type == 1 || mach_message.packet_type == 2) {
                ++heartbeats;
                continue;
            }

            process_mach_message(mach_message.message, mach_message.packet_type);
        }
    }

    // count a message of the Packet tree
    void process_mach_message(const std::byte* pointer, const std::uint8_t packet_type) {
        switch (packet_type) {
            case 3:
                ++total_messages;
                ++application_message;
                {
                    const auto* sub_header = miax::onyxfutures::topofmarket::mach::v1_0_b::ApplicationMessage::parse(pointer);
                    const std::uint8_t message_type = sub_header->message_type.get();
                    switch (message_type) {
                        case 1:
                            ++simple_instrument_definition_message;
                            break;
                        case 2:
                            ++complex_instrument_definition_message;
                            break;
                        case 3:
                            ++system_state_message;
                            break;
                        case 4:
                            ++instrument_trading_status_notification_message;
                            break;
                        case 15:
                            ++best_bid_and_offer_message;
                            break;
                        case 16:
                            ++last_sale_message;
                            break;
                        case 14:
                            ++trade_cancel_message;
                            break;
                        default:
                            ++unknown_messages;
                            break;
                    }
                }
                break;

            default:
                ++total_messages;
                ++unknown_messages;
                if (options.verbose) {
                    std::cerr << "Unknown packet_type: " << static_cast<int>(packet_type) << std::endl;
                }
                break;
        }
    }

    // report statistics
    void report() {
        std::cout << std::endl;
        std::cout << "Statistics Report" << std::endl;
        std::cout << "=================" << std::endl;
        std::cout << "Total packets:   " << total_packets << std::endl;
        std::cout << "Unknown packets: " << unknown_packets << std::endl;
        std::cout << "Total messages:  " << total_messages << std::endl;
        std::cout << "Unknown types:   " << unknown_messages << std::endl;
        std::cout << "Heartbeats:      " << heartbeats << std::endl;

        std::cout << std::endl;
        std::cout << "Message Counts:" << std::endl;
        std::cout << "--------------" << std::endl;
        std::cout << "  ApplicationMessage (3)                          " << application_message << std::endl;
        std::cout << "  SimpleInstrumentDefinitionMessage (1)           " << simple_instrument_definition_message << std::endl;
        std::cout << "  ComplexInstrumentDefinitionMessage (2)          " << complex_instrument_definition_message << std::endl;
        std::cout << "  SystemStateMessage (3)                          " << system_state_message << std::endl;
        std::cout << "  InstrumentTradingStatusNotificationMessage (4)  " << instrument_trading_status_notification_message << std::endl;
        std::cout << "  BestBidAndOfferMessage (15)                     " << best_bid_and_offer_message << std::endl;
        std::cout << "  LastSaleMessage (16)                            " << last_sale_message << std::endl;
        std::cout << "  TradeCancelMessage (14)                         " << trade_cancel_message << std::endl;
    }
};
}
