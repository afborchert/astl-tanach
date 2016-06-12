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
from the table with download links.

Any astl-tanach script takes always as first argument such a text,
converts it into an abstract syntax tree (AST, hence the name Astl),
and executes the script. To get an idea how the syntax tree generated
by astl-tanach looks like it helps to use the `tree.ast` utility
in the subdirectory tanach/tools:

```
tree.ast genesis.txt >genesis.tree
```

Here is an excerpt of the resulting `genesis.tree`, showing the
header and the first verse:

```
("book"
   ("comments"
      ("comment"
         xxxx    Unicode/XML Westminster Leningrad Codex [4.20]
      )
      ("comment"
         xxxx
      )
      ("comment"
         xxxx    Produced by the J. Alan Groves Center for Advanced Biblical Research
      )
      ("comment"
         xxxx    2960 Church Road / Glenside, PA 19038-2000 / USA
      )
      ("comment"
         xxxx    
      )
      ("comment"
         xxxx    Editor: Stephen K. Salisbury <Steve@GrovesCenter.org>
      )
      ("comment"
         xxxx    Senior Editor: Kirk E. Lowery <Kirk@GrovesCenter.org>
      )
      ("comment"
         xxxx
      )
      ("comment"
         xxxx    Transcriber: Christopher V. Kimball, West Redding, CT USA
      )
      ("comment"
         xxxx    Transcribed by WLC2XML of 17 Jan 2016 at 10 May 2016 @ 07:08.30. Build number: 25.0.
      )
      ("comment"
         xxxx    Transformed to text by XML2Text.xsl.xml of 2 Jun 2011 at 2016.06.11-16.46, Build number: 25.0. 
      )
      ("comment"
         xxxx    Layout: Full; Content: Accents.
      )
      ("comment"
         xxxx
      )
      ("comment"
         xxxx    Genesis (50 chapters, 1533 verses).
      )
      ("comment"
         xxxx
      )
      ("comment"
         xxxx  Chapter 1   (31 verses)
      )
      ("comment"
         xxxx
      )
   )
   ("verse"
      ("verse_number"
         1
         1
      )
      ("word_sequence_with_sof_pasuq"
         ("word_sequence"
            ("word"
               ("word_segment"
                  ("letter"
                     ("bet")
                     ("accent_sequence"
                        ("vocal_point"
                           ("degesh_or_mapiq")
                        )
                        ("vocal_point"
                           ("sheva")
                        )
                     )
                  )
                  ("letter"
                     ("resh")
                     ("accent_sequence"
                        ("vocal_point"
                           ("tsere")
                        )
                     )
                  )
                  ("letter"
                     ("alef")
                  )
                  ("letter"
                     ("shin")
                     ("accent_sequence"
                        ("vocal_point"
                           ("shin_dot")
                        )
                        ("vocal_point"
                           ("hiriq")
                        )
                        ("trope"
                           ("tipeha")
                        )
                     )
                  )
                  ("letter"
                     ("yod")
                  )
                  ("letter"
                     ("tav")
                  )
               )
            )
            ("word"
               ("word_segment"
                  ("letter"
                     ("bet")
                     ("accent_sequence"
                        ("vocal_point"
                           ("degesh_or_mapiq")
                        )
                        ("vocal_point"
                           ("qamats")
                        )
                     )
                  )
                  ("letter"
                     ("resh")
                     ("accent_sequence"
                        ("vocal_point"
                           ("qamats")
                        )
                        ("trope"
                           ("munah")
                        )
                     )
                  )
                  ("letter"
                     ("alef")
                  )
               )
            )
            ("word"
               ("word_segment"
                  ("letter"
                     ("alef")
                     ("accent_sequence"
                        ("vocal_point"
                           ("hataf_segol")
                        )
                     )
                  )
                  ("letter"
                     ("lamed")
                     ("accent_sequence"
                        ("vocal_point"
                           ("holam")
                        )
                     )
                  )
                  ("letter"
                     ("he")
                     ("accent_sequence"
                        ("vocal_point"
                           ("hiriq")
                        )
                        ("trope"
                           ("etnahta")
                        )
                     )
                  )
                  ("letter"
                     ("yod")
                  )
                  ("letter"
                     ("final_mem")
                  )
               )
            )
            ("word"
               ("word_segment"
                  ("letter"
                     ("alef")
                     ("accent_sequence"
                        ("vocal_point"
                           ("tsere")
                        )
                        ("trope"
                           ("merkha")
                        )
                     )
                  )
                  ("letter"
                     ("tav")
                  )
               )
            )
            ("word"
               ("word_segment"
                  ("letter"
                     ("he")
                     ("accent_sequence"
                        ("vocal_point"
                           ("patah")
                        )
                     )
                  )
                  ("letter"
                     ("shin")
                     ("accent_sequence"
                        ("vocal_point"
                           ("shin_dot")
                        )
                        ("vocal_point"
                           ("degesh_or_mapiq")
                        )
                        ("vocal_point"
                           ("qamats")
                        )
                     )
                  )
                  ("letter"
                     ("mem")
                     ("accent_sequence"
                        ("vocal_point"
                           ("patah")
                        )
                        ("trope"
                           ("tipeha")
                        )
                     )
                  )
                  ("letter"
                     ("yod")
                     ("accent_sequence"
                        ("vocal_point"
                           ("hiriq")
                        )
                     )
                  )
                  ("letter"
                     ("final_mem")
                  )
               )
            )
            ("word"
               ("word_segment"
                  ("letter"
                     ("vav")
                     ("accent_sequence"
                        ("vocal_point"
                           ("sheva")
                        )
                     )
                  )
                  ("letter"
                     ("alef")
                     ("accent_sequence"
                        ("vocal_point"
                           ("tsere")
                        )
                        ("trope"
                           ("merkha")
                        )
                     )
                  )
                  ("letter"
                     ("tav")
                  )
               )
            )
            ("word"
               ("word_segment"
                  ("letter"
                     ("he")
                     ("accent_sequence"
                        ("vocal_point"
                           ("qamats")
                        )
                     )
                  )
                  ("letter"
                     ("alef")
                     ("accent_sequence"
                        ("vocal_point"
                           ("qamats")
                        )
                        ("vocal_point"
                           ("meteg")
                        )
                     )
                  )
                  ("letter"
                     ("resh")
                     ("accent_sequence"
                        ("vocal_point"
                           ("point_segol")
                        )
                     )
                  )
                  ("letter"
                     ("final_tsadi")
                  )
               )
            )
         )
         ("sof_pasuq")
      )
   )
   /* ... */
)
```

This representation permits simple analysis like finding verses
with particular tropes. Following examples finds all verses in
a particular text with a shalshelet:

```
attribution rules {
   ("shalshelet") in ("verse" ("verse_number" chapter verse) sequence) -> {
      println(chapter, ":", verse, );
   }
}
```

If you run this example for the Genesis text, you will get the
following result:

```
$ find_shalshelet.ast genesis.txt
19:16
24:12
39:8
$ 
```

If you want to extract the text of the verses as well, you've to
extend the script:

```
import text;

attribution rules {
   ("shalshelet") in
	 ("verse" ("verse_number" chapter verse) sequence) as v -> post {
      gen_text(v);
      println(chapter, ":", verse, " ", v.text);
   }
}
```

The function `gen_text` comes from the imported _text_ module which
reconstructs the text string _v.text_ from the subtree. This delivers
the following result:

```
$ find_shalshelet.ast genesis.txt
19:16 וַֽיִּתְמַהְמָ֓הּ׀וַיַּחֲזִ֨קוּהָאֲנָשִׁ֜יםבְּיָד֣וֹוּבְיַד־אִשְׁתּ֗וֹוּבְיַד֙שְׁתֵּ֣יבְנֹתָ֔יובְּחֶמְלַ֥תיְהוָ֖העָלָ֑יווַיֹּצִאֻ֥הוּוַיַּנִּחֻ֖הוּמִח֥וּץלָעִֽיר׃
24:12 וַיֹּאמַ֓ר׀יְהוָ֗האֱלֹהֵי֙אֲדֹנִ֣יאַבְרָהָ֔םהַקְרֵה־נָ֥אלְפָנַ֖יהַיּ֑וֹםוַעֲשֵׂה־חֶ֕סֶדעִ֖םאֲדֹנִ֥יאַבְרָהָֽם׃
39:8 וַיְמָאֵ֓ן׀וַיֹּ֙אמֶר֙אֶל־אֵ֣שֶׁתאֲדֹנָ֔יוהֵ֣ןאֲדֹנִ֔ילֹא־יָדַ֥עאִתִּ֖ימַה־בַּבָּ֑יִתוְכֹ֥לאֲשֶׁר־יֶשׁ־ל֖וֹנָתַ֥ןבְּיָדִֽי׃
$
```

If you are interested in analysing the grammatical structure of a text,
you need to generate an intermediate representation which makes it more
easily to parse. This intermediate file is generated by the
`gen_tropes.ast` tool in the subdirectory tanach/tools:

```
gen_tropes.ast genesis.txt >genesis.tropes
```

This takes some time as the Genesis is a long text with 1533 verses.
The result in `genesis.tropes` is a human-readable file in an
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
