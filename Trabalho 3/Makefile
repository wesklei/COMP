all:
	flex expr.l
	bison expr.y -v
	gcc expr.c expr.tab.c -o expr
clean:
	-rm expr.output expr.tab.c lex.yy.c expr

