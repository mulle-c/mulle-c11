# How to steal mulle-c code

The easiest way to get mulle-c code into your project is to use [mulle-sde](//github.com/mulle-sde/mulle-sde)
and be done.

Stealing the source files and headers, as to incorporate them into your project,
has advantages and disadvantages


### Advantages

* no need to fork the mulle-c repositories, to keep a safe backup, in case mulle-c gets bought by some mega-corporation
* no dependency on mulle-sde
* easier to make it "your own", for example to cull functionality

### Disadvantages

* loss of upgrades, files stale
* less convenient than just using mulle-sde


## HOWTO

> TIP: Check out the new `mulle-sde steal` command, which can perform all these
> steps automatically.
> e.g. `mulle-sde steal "https://github.com/mulle-c/mulle-container.git"`

### Download

All mulle-c libraries, except mulle-c11, are dependent on at least one other
mulle-c library. In order to compile any one of them, you will need to download
the dependency sources as well. You can also find them by doing any
of the following

* use `mulle-sde dependency list`
* inspect the include statements in the `src/reflect` folder headers
* read the README.md of the mulle-c project, the dependencies are usually listed there with links to the repositories


> Retrieving them from their repositories, is something you will have to do
> manually, after all you don't want to use mulle-sde...


So assuming you collected all required mulle-c projects, now comes the time
to steal code.

### Steal

Copy all source and header files, except the "src/reflect" folder, from the
mulle-c projects "src" folder into a convenient place into your project.


### Integrate headers

From the mulle-c library you are really interested in, copy the `include.h`
and `include-private.h` files and the `reflect` folder contents. If there is
no `reflect` folder, then you are done.

That should be it, when you are using a clang or gcc based compiler, that supports
`__had_include`. If your compiler doesn't support this feature, you will have
to edit the files copied from the `reflect` folder. They will contain lines
such as this:

```
# if defined( __has_include) && __has_include("mulle-data.h")
#   include "mulle-data.h"   // mulle-data
# else
#   include <mulle-data/mulle-data.h>   // mulle-data
#endif
```

Change them to:

```
//# if defined( __has_include) && __has_include("mulle-data.h")
#   include "mulle-data.h"   // mulle-data
//# else
//#   include <mulle-data/mulle-data.h>   // mulle-data
//#endif
```

If you are using multiple mulle-c libraries, copy the contents of each
`reflect folder` and manually combine the contents of the `include.h` and
`include-private.h` headers.


### Licensing

The stolen code needs to keep the original BSD-3 style comment header, and
attribution of some form is still required.

