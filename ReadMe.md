# Omi C++ Protocols

Generated C++ binary-protocol parsers, one directory tree per generation format under
`cpp/`:

- `cpp/advanced/` — packed structs, types, messages and dispatch (the Advanced parser)
- `cpp/modern/` — the Modern parser
- `cpp/classes/` — the Classes library: owning classes that decode once and encode back
- `cpp/flyweight/` — the Flyweight library: views over the bytes, read in place without casts
- `cpp/tmp/` — the Tmp header: one per protocol, types and packed messages, each field asked for by its type

Every parser is compile-verified: `checks/` holds one translation unit per protocol and
format that includes the aggregating headers, and `CMakeLists.txt` compiles them all —
so a clean build fires the generated layout `static_assert`s across every protocol.

```sh
cmake -S . -B build && cmake --build build
```

## Programs

`executables/` holds the programs, one directory per protocol under each. They read the
parsers published under `cpp/` by a repository-root-relative include, so a protocol's parser
exists in exactly one place. Each program reads through one format:

- `executables/dump/` — prints every message as its class and fields, through Classes
- `executables/extractor/` — samples a capture down to one packet per message type, through Modern
- `executables/statistics/` — counts packets and messages by type, through Advanced where the
  protocol has a transport sequence and Modern where it does not
- `executables/verify/` — holds every packet to the rules it was framed by and requires it to
  encode back to its own bytes, through Classes; exits non-zero on any failure

The pcap reader they all share is `executables/pcap/`.

```sh
./build/dump_<protocol> capture.pcap
./build/extractor_<protocol> capture.pcap output-directory
./build/statistics_<protocol> -i capture.pcap
./build/verify_<protocol> capture.pcap
```

## Tests

`tests/` holds a test per protocol and format (26 of them), each written against the
surface that format's program uses, plus one run of each program on its protocol's first
declared capture (45 of them):

- `tests/modern/` walks every payload with the Modern iterator and requires the declared
  message — what extractor reads through
- `tests/advanced/` walks every segment with the session layer's `process_segment` and
  requires the declared message to be dispatched — what statistics reads through
- `tests/classes/` decodes every datagram into the `Packet`, requires the declared message
  through the `Visitor`, and requires each datagram to encode back to its own bytes — what
  dump reads through
- the program runs require dump to print the message's class, statistics to count it,
  extractor to write a sample, and verify to pass the whole capture

Every build compiles them, so a test that does not build fails the build like anything under
`checks/`. Running them reads the captures each protocol declares, which takes a packet
corpus checkout:

```sh
cmake -S . -B build -DOMI_PACKETS_DIR=/path/to/packets
cmake --build build --parallel && ctest --test-dir build
```

## Organizations

> [B3][B3.Directory] · [Iex][Iex.Directory] · [Jpx][Jpx.Directory] · [Nasdaq][Nasdaq.Directory]

## Exchanges

> [B3Derivatives][B3Derivatives.Exchange] · [IexEquities][IexEquities.Exchange] · [NsmEquities][NsmEquities.Exchange] · [TseEquities][TseEquities.Exchange]

[B3.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/B3 "Brasil, Bolsa, Balcão"
[Iex.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Iex "Investors Exchange"
[Jpx.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Jpx "Japan Exchange Group"
[Nasdaq.Directory]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Nasdaq "National Association of Securities Dealers Automated Quotations (Nasdaq)"
[B3Derivatives.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/B3/Protocols/B3Derivatives "B3 Derivatives"
[IexEquities.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Iex/Protocols/IexEquities "IEX Equities"
[NsmEquities.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Nasdaq/Protocols/NsmEquities "Nasdaq Stock Market"
[TseEquities.Exchange]: https://github.com/Open-Markets-Initiative/Open-Markets-Initiative/tree/main/Organizations/Jpx/Protocols/TseEquities "Tokyo Stock Exchange Equities"
