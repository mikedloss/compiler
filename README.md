compiler
========

this is a simple compiler that compiles one language into another.

created as a group project.

language grammar:
<br />
`1. <program> -> BEGIN <statement list> END`<br />
`2. <statement list> -> <statement> {<statement list>}`<br />
`3. <statement> -> ID := <expression>;`<br />
`4. <statement> -> READ ( <id list> );`<br />
`5. <statement> -> WRITE ( <expr list> );`<br />
`6. <id list> -> ID {, ID}`<br />
`7. <expr list> -> <expression> {, <expression>}`<br />
`8. <expression> -> <primary> {<add op> <primary>}`<br />
`9. <primary> -> ( <expression> )`<br />
`10. <primary> -> ID`<br />
`11. <primary> -> INTLITERAL`<br />
`12. <add op> -> PLUSOP`<br />
`13. <add op> -> MINUSOP`<br />
`14. <system goal> -> <program> SCANEOF`


here is the language:<br />
`(SEQUENCE TOKEN)`<br />
`begin BEGIN`<br />
`end END`<br />
`read READ`<br />
`write WRITE`<br />
`variable ID`<br />
`integer INTLITERAL`<br />
`( LPAREN`<br />
`) RPAREN`<br />
`; SEMICOLON`<br />
`, COMMA`<br />
`:= ASSIGNOP`<br />
`+ PLUSOP`<br />
`- MINUSOP`<br />
`eof SCANEOF`<br />
`lexical error ERROR`<br />
