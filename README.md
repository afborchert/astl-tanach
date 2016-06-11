# astl-tanach
Astl programming language and tools for the Tanach

## Synopsis

This is an implementation of the Astl programming language
for Tanach texts in the form as distributed by tanach.us.
for C. Astl is an easy to learn scripting language that is
specialized on attributed abstract syntax trees.

Included are astl-tanach and astl-tropes. astl-tanach
works directly on the accented plain texts from tanach.us.
Unfortunately, it is too hard to perform a full grammatical
analysis on that level. Instead a tool is provided that
generates an intermediate language that makes it easier
to fully analyse the grammar.

This is still on-going work in an experimental stage.

## Downloading and building

If you want to clone it, you should do this recursively:

```
git clone --recursive https://github.com/afborchert/astl-tanach.git
```

To build it, you need _bison_ 3.x, a recent _g++_ with
C++14 support, GMP, _pcre2_, and _boost_ libraries:

```
(cd astl/astl && make)
(cd tanach/src && make)
(cd tropes/src && make)
```

## Grammatical Analysis

Firstly, you will need to download the books of the Tanach
you are interested in. Take for example the Genesis:

```
wget -O genesis.txt 'http://www.tanach.us/TextServer?Genesis*&content=Accents'
```

You will find the links for other books by going to the index page
at http://www.tanach.us/Tanach.xml, chosing one of the books,
and selecting the link labeled _Accents_ in the _Text_ row
of the download table. Then process it by the first pass using
`gen_tropes.ast` in the subdirectory tanach/tools:

```
gen_tropes.ast genesis.txt >genesis.tropes
```

This takes some time as the Genesis is a long text with 1533 verses.
The result in `genesis.tropes` is a humn-readable file in an
intermediate format which can be processed using the `astl_tropes`
parser. In the subdirectory tropes/tool you will find `gen_wikitab.ast`
that is able to construct a Mediawiki table for an individual verse.
Select, for example, Genesis 1:1 from `genesis.tropes` generated above,
and store it into `genesis-1:1.tropes`:

```
   verse 1:1 {
      tipeha word {
         "‏בְּרֵאשִׁ֖ית‬"
      }
      etnahta clause munah word {
         "‏בָּרָ֣א‬"
      }
      etnahta word {
         "‏אֱלֹהִ֑ים‬"
      }
      tipeha clause merkha word {
         "‏אֵ֥ת‬"
      }
      tipeha word {
         "‏הַשָּׁמַ֖יִם‬"
      }
      siluq clause merkha word {
         "‏וְאֵ֥ת‬"
      }
      siluq word {
         "‏הָאָֽרֶץ‬"
      }
      sof_pasuq "‏׃‬"
   }
```

This file can now be processed by `gen_wikitab.ast`:

```
gen_wikitab.ast genesis-1:1.tropes >genesis-1:1.wiki
```

This is the contents of `genesis-1:1.wiki`:

```
{| class="wikitable" style="background:#FFFFFF; font-size:85%; text-align:center;"
|- bgcolor="#E0E0E0"
| colspan="8"| 1,1
|-
|'''Gesamter Vers'''
| colspan="7"|
<div dir="rtl">בְּרֵאשִׁ֖ית בָּרָ֣א אֱלֹהִ֑ים אֵ֥ת הַשָּׁמַ֖יִם וְאֵ֥ת הָאָֽרֶץ</div>
|-
|'''1. Ebene'''
|colspan="4"|
<div dir="rtl">אֵ֥ת הַשָּׁמַ֖יִם וְאֵ֥ת הָאָֽרֶץ</div><br />Siluk-Segment
|colspan="3"|
<div dir="rtl">בְּרֵאשִׁ֖ית בָּרָ֣א אֱלֹהִ֑ים</div><br />Etnachta-Segment
|-
|'''Worte'''
|<div dir="rtl">הָאָֽרֶץ</div><br />Siluk
|<div dir="rtl">וְאֵ֥ת</div><br />Mercha
|<div dir="rtl">הַשָּׁמַ֖יִם</div><br />Tifcha
|<div dir="rtl">אֵ֥ת</div><br />Mercha
|<div dir="rtl">אֱלֹהִ֑ים</div><br />Etnachta
|<div dir="rtl">בָּרָ֣א</div><br />Munach
|<div dir="rtl">בְּרֵאשִׁ֖ית</div><br />Tifcha
|}
```

Currently, German labels are used. But it is simple to adapt this
to another language. Just copy `tropes/lib/de_names.ast` to
another name, adapt it to your language and import it instead
of `de_names` in `gen_wikitab.ast`.

## Literature

The work would have been impossible without the following works
which helped me to plunge into the fascinating world of the
grammatical structure of the Tanach texts:

 * Joshua R. Jacobson: _Chanting the Hebrew Bible_. The Art of Cantillation.
   The Jewish Publication Society, Philadelpha 2002, ISBN 0-827-0693-1
 * Israel Yeivin: _Introduction to the Tiberian Masorah_. Scholar Press,
   Chico, California, 1980, ISBN 0-89130-373-1.
 * James D. Price: _The Syntax of Masoretic Accents in the Hebrew Bible_.
   Studies in the Bible and Early Christianity, Volume 27. The Edwin
   Mellen Press, Lewiston, New York, 1990. ISBN 0-88946-510-X.
