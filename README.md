Program for parsing GPS coordinates in various formats. Output is a simple map in SVG.
Coordinates can be read from files given as the command line parameters. If one of the files does not exist, program ends. If no file is set as the parameter, another option for entering coordinates is standard input.

Supported formats:

ddd:mm:ss.sss[NS] ddd:mm:ss.sss[WE]
<br/>
ddd°mm'ss"[NS] ddd°mm'ss"[WE]
<br/>
ddd.dddddd[NS] ddd.dddddd[WE]


(-)ddd.dddddd, (-)ddd.dddddd
<br/>
(-)ddd° mm.mmmmm, (-)ddd° mm.mmmmm


[NS]ddd:mm:ss.sss [WE]ddd:mm:ss.sss
<br/>
[NS]ddd°mm'ss" [WE]ddd°mm'ss"
<br/>
[NS]ddd.dddddd [WE]ddd.dddddd
