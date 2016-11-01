# 简单HOOKAPI
------

做一个程序(或DLL)实现HOOK自身API，即使用API时不是使用系统的API，而是执行自己定义的API

------

## 设计
Hook自己的OpenProcess函数，使自己无法使用OpenProcess<br>
## 过程
![image](https://github.com/luguanxing/LGX-Projects/blob/master/11-%E7%AE%80%E5%8D%95HOOKAPI/pictures/1.jpg?raw=true)<br>
Hook后<br>
![image](https://github.com/luguanxing/LGX-Projects/blob/master/11-%E7%AE%80%E5%8D%95HOOKAPI/pictures/2.jpg?raw=true)<br>
恢复Hook后<br>
##反思
HOOK自身API可注入到其它程序实现恶意功能，若做成全局钩子效果更佳(如OpenProcess被HOOK导致无法用OD附加自身)
