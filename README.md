toybox
======

toybox is a C++ library i use and write for myself. It is not meant to be consistent, documented, useful or serve whatever particular need you may suppose. It's only purpose is to store code sniplets that i use frequently or tend to rewrite or just want to play with. It is probable to discover inside everything e.g. unportable gcc-specifics, goto-heavy code or even ascii-art drawn poems. Consistently there are no restrictions on copying, modyfying, plaggearizing or using it in any kind of project. When using it you are not required to reference me or provide any other explanations.


Language:         mostly C++

Target arch:      amd64

Target os:        Linux 2.6+, 3.0+, FreeBSD 8.2+, 9.0+

Scripts:          bash, perl

Build system:     boost.build (will probably shift to plain make)

Other tools:      graphviz


My main interests are:

1. various obstruction/lock/wait -free data structures and proof-of-concept examples on subject

2. lazily-locked structures (e.g. futex+lockfree crossbreeds)

3. fully async interfaces for e.g. http/telnet, client/server, db (based on asio)

4. set of very efficient basic classes (strings, streams, allocators)

5. embedded languages and their limits (for now lua)


This list will likely be extended by anything which may become my interest in future. A set of crude utilities needed for logging, configs, threading and such will be created as needed. Most of mentioned is a rewrite of once written in proprietary projects, but there is absolutely no proprietary code here. Moreover i am reluctant to introduce any dependencies including boost and stl. When not able to avoid external library i wrap it into minimal interface suited for my needs.
