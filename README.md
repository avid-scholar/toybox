toybox
======

toybox is a C++ library i use and write for myself. It is not meant to be consistent, documented, useful or serve whatever particular need you may suppose. It's only purpose is to store code sniplets that i use frequently or tend to rewrite or just adore. It is probable to discover inside something unportable, gotos, and more up to ascii art drawn poems. Consistently there are no restrictions on copying, modyfying, plaggearizing or using it in any kind of project. When using it you are not required to reference me or provide any other explanations.

inside the repository you may find:

1. various obstruction/lock/wait -free data structures and proof-of-concept examples on subject

2. lazily-locked structures (e.g. futex+lockfree crossbreeds)

3. primitive utility classes, freebsd workarounds, compiler workarounds

4. mt debugging/monitoring tools (pthread-based)

5. simple telnet/http client/server classes

6. maybe some lua wrappers

7. whatever may become my interest in future (e.g. linux kernel module planned)


If not specified otherwise target platform is always amd64 linux 2.6.x/3.x.x, compiler is gcc 4.2 or newer gcc (some dependencies on gcc extensions may be present). Most of mentioned is a rewrite of once written in proprietary projects, but there is absolutely no proprietary code here. Moreover i am reluctant to introduce any dependencies including boost and stl. Instead i prefer simpler and feature-scarce code which only does what i need.
