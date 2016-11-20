<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2 Final//EN">
<HTML><HEAD><TITLE>V6/usr/source/s2/wc.c</TITLE></HEAD>
<BODY BGCOLOR="#ffffff"><H1>V6/usr/source/s2/wc.c</H1>
<form action="/cgi-bin/unixtree.cgi" method="POST">
<input type=hidden name=f value=V6/usr/source/s2/wc.c>
Find at most <select name="num">
<option value="5">5</option>
<option value="10">10</option>
<option value="20">20</option>
<option value="50">50</option>
<option value="100">100</option>
<option value="500">500</option></select>
related files. <input type="submit" value="Search"><br>
<input type="checkbox" name="incl" value="1">
including files from this version of Unix.
</form><hr>
<pre>
/* wc line and word count */

int	buf[259];
int wordct[2];
int twordct[2];
int linect[2];
int tlinect[2];

main(argc,argv)
char **argv;
{
	int i, token;
	register char *p1, *p2;
	register int c;

	i = 1;
	do {
		if(argc&lt;=1) buf[0] = 0;
		else if(fopen(argv[i],buf)&lt;0) {
			diag(argv[i]);
			diag(": cannot open\n");
			continue;
		}
		p1 = 0;
		p2 = 0;
		linect[0] = linect[1] = 0;
		wordct[0] = wordct[1] = 0;
		token = 0;
		for(;;) {
			if(p1 &gt;= p2) {
				p1 = &amp;buf[1];
				c = read(buf[0], p1, 512);
				if(c &lt;= 0)
					break;
				p2 = p1+c;
			}
			c = 0;
			c =| *p1++;
			if(' '&lt;c&amp;&amp;c&lt;0177) {
				if(!token++) {
					if(++wordct[1]==0)
						wordct[0]++;
				}
			} else {
				if(c=='\n') {
					if(++linect[1]==0)
						linect[0]++;
				}
				else if(c!=' '&amp;&amp;c!='\t')
					continue;
				token = 0;
			}
		}
		printf("%7s ",locv(linect[0],linect[1]));
		printf("%7s ",locv(wordct[0],wordct[1]));
		printf("%s\n", argc&lt;=1?"":argv[i]);
		close(buf[0]);
		ladd(tlinect, tlinect, linect);
		ladd(twordct, twordct, wordct);
	} while(++i&lt;argc);
	if(argc &gt; 2) {
		printf("%7s ",locv(tlinect[0],tlinect[1]));
		printf("%7s ",locv(twordct[0],twordct[1]));
		printf("total\n");
	}
}

diag(s)
char *s;
{
	while(*s)
		write(2,s++,1);
}











