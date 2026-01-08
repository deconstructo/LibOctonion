
This is a simple, easy to use octonion library, written in C.

My design goal has been to make this library easy to use rather
than high performance - so you'll note that I pass octonions
by value rather than by reference.

Another goal is to make this a standalone library, thus I do
not make use of things like CQRlib that would make things like
multiplication and exponential functions easier to write and
likely more performant.

I will write a second version of this library that does things
"the right way". But for now, I'm going to stay with the
less performant approach.


Now: Why an Octonion library?

- I couldn't find something in C that already did the job
- I thought that it'd be a fun way to learn the maths
- While I highly doubt it, someone else might find it useful
- I need octonions for the next step in my SIOD-TR journey.

License:  GPL3.

Have fun, but make sure that you use protection.

Consent is a continuous thing. Tan() is not.

And most importantly, do not 1/0.

--- 
(c) Chris "Scáth" Ó Luanaigh, 2026

