echo '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="content-type" content="text/html; charset=utf-8" />
<link rel="stylesheet" type="text/css" href="../Resources/style.css" />
<title>Replaced with your title-YeLee的个人博客</title>
</head>
<body>

<div id="page">
	<div id="header">
		<a href="http://yelee.github.com" target="_blank"><h1>YeLee的个人博客</h1></a>
		<div class="description">欢迎光临YeLee的个人Blog</div>
	</div>	
	<div id="menulinks">
		<a class="active" href="../index.html" target="_self">主页</a>	
	</div>

	<div id="mainarea">
	<div id="contentarea">
		<h2>Replaced with your title</h2>
		<div class="content">' >$1.html
cat $1 |sed -e 's/^/\t\t\t\<p\>/g' -e "s/$/\<\/p\>/g" >>$1.html
echo '
		</div>
	</div>
	</div>

	<div id="footer">
		<div id="footerleft">文章转载最好提供来处，谢谢。<br/></div>
	</div>
</div>

</body>
</html>
' >>$1.html
cat $1.html|sed "s/Replaced with your title/$1/" >$(date +%Y%m%d).html
rm $1.html
