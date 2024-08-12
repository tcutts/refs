# Refs 7.8.1

Refs was a reference manager program I wrote between 1992 and 1998.  Initially for my own use, and later released as shareware, partly to fund my delays in finishing my PhD, much of which were caused, ironically, by wasting time writing this software.

I am releasing this source code under the MIT licence primarily just for the interest of many of my old customers who might (God forbid) still be running Refs ...

It does still work on Windows 10, which I think is something of a testament to the commitment of Microsoft to the backwards compatibility of Windows; that this program still runs on operating system released two decades after the application was last compiled from source is quite something.

# WARNING

This program was the first application I ever wrote in C++, and by far the biggest program I had ever written up to that point.

**It is an absolute master class in how not to write a piece of software**, and as such I release it partially as an educational tool.  Do not, for the love of God, write software like this.
It breaks almost every single possible rule of clean code.  There are single character variable names everywhere.  No comments where there should comments, and completely self-obvious code with unnecessary comments.
Huge long functions.  Functions and variables with stupid names.

Absolutely no tests whatsoever, unit, integration or anything else.

# DESIGN

Ahaahahaha!  You think this code is *designed*?  Nevertheless, there are a few things I remember about why it is the way it is.

The codebase pre-dates the existence of Microsoft Foundation Classes, so it uses the underlying Win16 and Win32 C APIs.

Very observant people may spot a couple of classes which look and smell a lot like Borland's TCollection class from ObjectWindows, shipped with Turbo Pascal for Windows.  This is not a coincidence.  Refs versions prior to 7.x were 16-bit only and written in Pascal.
The source code for this old version is long lost (I never used version control, at the time), but the initial version 7.0 was a line-by-line (almost) translation from Borland's object oriented Pascal into C++.  The central data structure of the program was a TCollection class,
and so I had to implement a clone of Borland's Pascal TCollection for the rest of the code to work.  This is actually one of the less rubbish parts of the code.

The translation of the Pascal into C++ was my way of learning C++, which I recognised to be a more useful language for my future career.  However, I clearly made mistakes in doing it.  The C++ version of Refs never was quite as stable as the prior Pascal version at been.

The code never worked well under WINE on Linux, because for some reason I used parts of the Windows Multimedia API, I have no idea why.  That may be different these days, if WINE has finally added support for that API.

# THANKS

Thank you to all those people who helped me with Refs over the years, especially to those of you who helped me translate it into non-English languages.

Those of you who bought licences to use it, which helped fund the (successful) end of my PhD studies, and which led to my transition into a scientific IT and HPC support career which I have continued in ever since.

The anonymous hundreds of people on comp.os.windows.programmer and other Usenet newsgroups who helped teach me how to do various things with the Windows API

Borland, for being the company that actually released compilers at a price point that hobbyist programmers like me could buy

The MSDN, for being an amazing repository of information and documentation long before we had StackExchange, GitHub, Google, or Generative AI

The open source community at large and Linux in general, for showing me the light and giving me a career in an operating system a lot easier to program for than Windows was in the early 1990's...
