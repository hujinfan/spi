�ϴ����뵽GitHub��

0.git init (��һ��ִ�м���)
1.git add -A
2.git commit -m "v1, the origin code for i2c."
3.git tag v1
4.git remote add origin https://github.com/hujinfan/spi.git ����һ��ִ�м��ɣ�
5.git push -u origin master
6.git push origin --tags

�汾2 
1.git add -A
2.git commit -m "v2, add gpio_spi.c and oled.c"
3.git tag v2
4.git push origin master
5.git push origin --tags

�汾3
1.git add -A
2.git commit -m "v3, modify the error,the text can be displayed on oled"
3.git tag v3
4.git push origin master
5.git push origin --tags

�汾4
1.git add -A
2.git commit -m "v4, read ID"
3.git tag v4
4.git push origin master
5.git push origin --tags

�汾5
1.git add -A
2.git commit -m "v5, erase��program and read flash"
3.git tag v5
4.git push origin master
5.git push origin --tags