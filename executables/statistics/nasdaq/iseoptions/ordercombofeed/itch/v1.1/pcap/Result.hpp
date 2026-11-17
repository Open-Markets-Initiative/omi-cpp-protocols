// Nasdaq.IseOptions.OrderComboFeed.Itch.v1.1: pcap/Result.hpp
#pragma once

namespace packet {

    enum class result {
        nasdaq_iseoptions_ordercombofeed_itch_v1_1,
        error,
        end_of_file,
        unknown
    };

}