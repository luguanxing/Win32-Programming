# 网页自动刷新
------

做一个程序，能够一边在notepad++记事本上编辑CSS代码一边在网页上看到效果
> * 背景
> * 功能
> * 设计

------

## 背景
本来打算装livereload的，但因智商捉急安装失败
## 功能
让记事本写的代码不用手动保存就能看到效果，边写边看到显示出的效果，实现“所写即所见”
## 设计
自动检测记事本notepad++并保存后自动刷新chrome的<br>
(注：仅在notepad++和chrome同时运行时有效，可同时编辑html,css,javascript代码)<br>
![image](https://github.com/luguanxing/LGX-Projects/blob/master/07-%E7%BD%91%E9%A1%B5%E8%87%AA%E5%8A%A8%E5%88%B7%E6%96%B0%E5%99%A8/refresher.gif)<br>

