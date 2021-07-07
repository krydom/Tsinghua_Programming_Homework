# -*- coding:utf-8 -*-
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle
import numpy as np
import matplotlib.font_manager as fm

f = "HGH_CNKI.TTF"
prop1 = fm.FontProperties(fname=f,size=6)
prop2 = fm.FontProperties(fname=f,size=30)
prop3 = fm.FontProperties(fname=f,size=15)

class BarBrowser(object): 
    def __init__(self, rects):
        self.xy = 0
        self.width = 0
        self.height = 0
        # 鼠标选中矩形

        self.selected = ax.add_artist(
            Rectangle(rects[0].get_xy(),rects[0].get_width(),rects[0].get_height(), 
                    color='g', visible=False),
            )
        self._x = 0
        self._is_drawed = False
        self._is_called = False 
        self._map = {rect.xy[0]:rect.get_height()  for rect in rects}


    def motion(self, event):
        if event.ydata is None: 
            return True

        if self._is_called and self._is_drawed:
            self._is_called = False
            return True

        self.selected.set_height(event.ydata)
        fig.canvas.draw()

        self._map[self.xy[0]] = event.ydata
        self._is_called = False
        

    def _has_picked(self, event): 
        #  判断是否还在同一个bar内操作
        _is_pick = event.artist.xy[0]==self._x
        self._x = event.artist.xy[0]        
        return _is_pick


    def enter_axes(self, event):
        # 选中一个bar,操作    
        if not event.artist:
            return True
        
        self._is_called = True
        self._is_drawed = False
        if self._has_picked(event):
            return True

        # draw
        self.xy = event.artist.xy
        self.width = event.artist.get_width()
        self.height = event.artist.get_height()
        
        self.selected.set_visible(True)
        self.selected.set_xy(self.xy)
        self.selected.set_height(self.height)
        self.selected.set_alpha(0.7)
        
        for i in range(len(province)):
            a = province[i][0]
            b = province[i][1:]
            while True:
                if len(b)==2:
                    province[i]=a+' '+b[1]
                    break
                else:
                    a = a+' '+b[1]
                    b = b[2:]
        
        fig.suptitle(str(province[int(self.xy[0]+0.6)])+' : '+str(self.height),fontproperties=prop2)
        fig.canvas.draw()
        
        
        # end draw
        self._is_drawed = True


if __name__ == '__main__':
    fig = plt.figure(figsize=(10, 8), dpi=100 )
    ax = fig.add_subplot(111)

    # 数据 
    province = ['北京','天津','上海','重庆','河北','山西','辽宁','吉林','黑龙江','江苏','浙江','安徽','福建','江西','山东','河南','湖北','湖南','广东','海南','四川','贵州','云南','陕西','甘肃','青海','台湾','内蒙古','广西','西藏','宁夏','新疆','香港','澳门']
    province_n = province
    wordnum = [339,115,213,143,216,182,146,110,193,244,247,217,194,210,267,184,259,189,289,143,222,174,170,236,162,84,242,126,213,88,61,150,130,48]

    xno = np.arange(len(province))
    
    for i in range(len(province_n)):
        a = province_n[i][0]
        b = province_n[i][1:]
        while True:
            if len(b)==1:
                province_n[i]=a+'\n'+b
                break
            else:
                a = a+'\n'+b[0]
                b = b[1:]
    
    # 绘制柱形图
    rects = ax.bar(xno, wordnum, picker=True)
    plt.xticks(xno, province_n,fontproperties=prop1)    # 设置x轴坐标

    browser = BarBrowser(rects)
    fig.canvas.mpl_connect('pick_event', browser.enter_axes)
    fig.canvas.mpl_connect('button_press_event', browser.motion)
    
    plt.text (10,300,'click the bars to get the details' ,fontsize=10,color = "blue",fontproperties=prop3) 

    plt.show()