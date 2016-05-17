上传代码到GitHub：

0.git init (第一次执行即可)
1.git add -A
2.git commit -m "v1, the origin code for i2c."
3.git tag v1
4.git remote add origin https://github.com/hujinfan/spi.git （第一次执行即可）
5.git push -u origin master
6.git push origin --tags

版本2 
1.git add -A
2.git commit -m "v2, add gpio_spi.c and oled.c"
3.git tag v2
4.git push origin master
5.git push origin --tags

版本3
1.git add -A
2.git commit -m "v3, modify the error,the text can be displayed on oled"
3.git tag v3
4.git push origin master
5.git push origin --tags

版本4
1.git add -A
2.git commit -m "v4, read ID"
3.git tag v4
4.git push origin master
5.git push origin --tags

版本5
1.git add -A
2.git commit -m "v5, erase、program and read flash"
3.git tag v5
4.git push origin master
5.git push origin --tags