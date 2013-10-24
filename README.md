compiler
========

this is a simple compiler that compiles one language into another

language grammar:
1. <program> 6 BEGIN <statement list> END
2. <statement list> 6 <statement> {<statement list>}
3. <statement> 6 ID := <expression>;
4. <statement> 6 READ ( <id list> );
5. <statement> 6 WRITE ( <expr list> );
6. <id list> 6 ID {, ID}
7. <expr list> 6 <expression> {, <expression>}
8. <expression> 6 <primary> {<add op> <primary>}
9. <primary> 6 ( <expression> )
10. <primary> 6 ID
11. <primary> 6 INTLITERAL
12. <add op> 6 PLUSOP
13. <add op> 6 MINUSOP
14. <system goal> 6 <program> SCANEOF

here is the language:
SEQUENCE TOKEN
begin BEGIN
end END
read READ
write WRITE
variable ID
integer INTLITERAL
( LPAREN
) RPAREN
; SEMICOLON
, COMMA
:= ASSIGNOP
+ PLUSOP
- MINUSOP
eof SCANEOF
lexical error ERROR
