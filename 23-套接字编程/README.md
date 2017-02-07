# 套接字编程 CSocket
------

简单的TCP/UDP套接字收发数据,实践发现TCP服务器需要多线程并发实现多用户收，UDP不需要，但两者可直接利用CSocket封装的API进行操作
> * 设计
> * 结构
> * 效果


------
## 效果
![image](https://github.com/luguanxing/Windows-C-Projects/blob/master/23-%E5%A5%97%E6%8E%A5%E5%AD%97%E7%BC%96%E7%A8%8B/pictures/demo1.gif?raw=true)<br>
<br><br><br>
## 结构
![image](https://github.com/luguanxing/Windows-C-Projects/blob/master/23-%E5%A5%97%E6%8E%A5%E5%AD%97%E7%BC%96%E7%A8%8B/pictures/class.jpg?raw=true)<br>
<br><br><br>
## 设计
![image](https://github.com/luguanxing/Windows-C-Projects/blob/master/23-%E5%A5%97%E6%8E%A5%E5%AD%97%E7%BC%96%E7%A8%8B/pictures/demo2.gif?raw=true)<br>
<br><br><br>
![image](https://github.com/luguanxing/Windows-C-Projects/blob/master/23-%E5%A5%97%E6%8E%A5%E5%AD%97%E7%BC%96%E7%A8%8B/pictures/server.jpg?raw=true)<br>
<br><br><br>
![image](https://github.com/luguanxing/Windows-C-Projects/blob/master/23-%E5%A5%97%E6%8E%A5%E5%AD%97%E7%BC%96%E7%A8%8B/pictures/client.jpg?raw=true)<br>




