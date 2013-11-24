Program for parsing GPS coordinates in various formats. Output is a simple map in SVG.
Coordinates can be read from files given as the command line parameters. If one of the files does not exist, program ends. If no file is set as the parameter, another option for entering coordinates is standard input.

Supported formats:

ddd:mm:ss[NS] ddd:mm:ss[WE]
<br/>
ddd:mm.mmmmm[NS] ddd:mm.mmmmm[WE]
<br/>
ddd°mm'ss"[NS] ddd°mm'ss"[WE]
<br/>
ddd°mm.mmmmm'[NS] ddd°mm.mmmmm'[WE]
<br/>
ddd.dddddd[NS] ddd.dddddd[WE]


(-)ddd:mm:ss (-)ddd:mm:ss
<br/>
(-)ddd:mm.mmmmm (-)ddd:mm.mmmmm
<br/>
(-)ddd°mm'ss", (-)ddd°mm'ss"
<br/>
(-)ddd°mm.mmmmm, (-)ddd°mm.mmmmm
<br/>
(-)ddd.dddddd, (-)ddd.dddddd


[NS]ddd:mm:ss.sss [WE]ddd:mm:ss.sss
<br/>
[NS]ddd:mm.mmmmm [WE]ddd:mm.mmmmm
<br/>
[NS]ddd°mm'ss" [WE]ddd°mm'ss"
<br/>
[NS]ddd°mm.mmmmm' [WE]ddd°mm.mmmmm'
<br/>
[NS]ddd.dddddd [WE]ddd.dddddd

Range of input values:
* degrees:
** 180 W (-180) - 180 E (180)
** 90 N (90) - 90 S (-90)

* minutes:
** 0 - 59.99999

* seconds
** 0 - 59


