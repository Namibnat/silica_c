# Silica C

A playground to teach myself about how compilers work.


## Background

I work as a python developer, but I've always felt attracted to low-level code
and understanding how machines work.

I've written some things in C before, and played around with assembly, but I've
never taken on something like a compiler before.  I'm not certain I'll ever finish
this, or even get very far.  In recent years, most of my coding has been focused on
things that help me with my own skills in my work, but I miss the pure joy of
doing coding that has no real value in the job market, but that are purely for fun.


## The plan

I want to create this in tiny steps, starting with the smallest portion of a compiler
that I can.  I don't want to create my own language, purely to build some subset of
a c compiler.

The goal is to create some kind of a C compiler, written in C for x86-64 and will be done
on Linux.  I'm working on a Kali machine mostly, but generally I work on Arch for projects
like this.  Why on those machines?  Well, the main reason is that I love pocking around
on Linux machines, but, I also want to work on a machine that I can totally screw up
and not worried.

I plan to 'show my work' in a way, and so I'll keep a file with little test programs
as I work on things.  Normally I wouldn't keep this kind of thing around, but
this project is a hobby and so a few bit of half working stuff, test files
and exploration will stay in the project for me to play with.

The file structure is as follows:
.
├── doodle -> Directory for playing around in.
├── README.md
├── other meta kind of stuff
└── silica_c -> Here I'll build up the compiler.  Probably as a single file to start with.


## Resources I'm using:

1. The book "Compilers, Principles, Techniques, & Tools", Second Edition by Alfred V. Aho
Monica S. Lam, Ravi Seth and Jeffrey D. Ullman.  Aka, "The Dragon Book".  Generally, I don't
expect that I'll read this thing, I just enjoy poking around in it and have read a few chapters
in the past and find it super interesting even though I'm sure that it will get over my head at
some point.

2. "Crafting Interpreters" by Robert Nystrom.  I've read most of this book already, largely
when I used to commute.  Although this book is about making your own language, it's probably
the most accessable book out there.  I think.  Even though this book is not directly what I'm
doing, I suspect that it will be the first book that I'll actually read cover to cover.

3. "The C Programming Language", Second Edition by Brian W. Kernighan and Denis M. Ritchie.  Aka, K&R.
I already know C to a very basic level, but it's been a while.  Another book that I've already
read most of.  I know it's probably not the best place to learn C from.  It is just a joy to read.

4. "x86-64 Assembly Language Programming with Ubuntu" by Ed Jorgensen, Version 1.1.44.  I have only recently
started with this book and my plan is to slowly poke through it so that I get up to scratch
with assembly.  I have been learning some ARM assembly, but I think I'll put that aside while
I work on this project.  Maybe down the line I'll get some minimal compiler working
on a Rasberry Pi or something, but I'll start on Linux.

5. chatGPT.  Of course, these days every dev is working with ChatGPT.  Here is how I see my main
use of it, I'll get a few boilerplate bits if needed, get debugging help, and use it to help
me understand things out of the books I'm working on.  I do not want it to be writing
the code of figuring out the logic for me.  That takes away all the fun, and ends up creating
dangerous code.  I'm working entirely in Vim without any direct AI stuff in my editor.

6. ISO/IEC standards documents, maybe.  Depending on how it goes, I might look at the standards
documentation, but I'm not sure this will ever be a standards compliant compiler.  This is a toy
and will always be, but I might poke around these kinds of docs just for ideas.

7. There is a book by Nora Sandler which isn't out yet called "Writing a C Compiler, Build a Real Programming Language
from Scratch".  I'll take a look at that when it comes out.



## Contributing

This is a personal project, but if you're playing around with it and feel like I've done something
silly, and for some reason you want to point me in the right direction, please feel free.


## Usage

I'll update this when I have something you can play around with.  But, **please be warned** I
don't know what I'm doing, and might be doing all sorts of memory stuff badly, and may break your system.
Only use this code if you know C.  That said, please feel free to download it and play around with it.

