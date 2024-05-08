# 建立欧洲奥地利某气象站降雨量气象模型的实验

| 目录      | 用途                       |
| :-------- | :------------------------- |
| gene_algo | 遗传算法求解的模型         |
| latex     | 论文书写                   |
| src       | 研究其它多种模型的求解效果 |
| ppt       | 汇报PPT |

## 作品简介
本文针对局部地区的降雨量与其它气象相关的因素进行了数学模型
的建立和求解的通用算法的设计，运用线性回归，障碍计数，时间序
列和神经网络等模型分别进行了尝试，最终发现决策树取得了较好的结果.

根据气象预测的要求，定义正确为与真实数据相差的绝对值小于$10$mm.我们
首先针对与降水量关联度最大的水平面气压和气温等条件，运用线性回归模型拟合真实数据，完成
了该简单模型的求解，取得了正确率$53 \%$和绝对平均误差$11$mm的良好的预测效果，在这里
同时使用了最小二乘法进行拟合，均能够取得很好的效果.在此时还尝试了障碍计数模型来应对未
降雨的情况，但尝试后发现准确率极低，只有$6\%$左右，整理数据后分析得到数据的趋势具有连
续变量的特征，趋势上大致更加符合回归模型这一类.

随后扩大研究的范围，添加了云层覆盖，湿度，风速为新的自变量，由于此时线
性回归在多个自变量的的相互影响下适应性较差，转变模型，运用了神经网络回归模型进行拟合，在仅
使用$5$个神经层，共$200$多个神经元的情况下取得了绝对平均误差仅
为$8$\si{\milli\meter}的优异结果 .同时，我们也展开了遗传算法训练网络的尝试，在有$4$层,分别
为$5,20,20,1$个神经元的网络中，发现每个个体网络无论输入，输出值均为$26mm$上下，
同时，各个个体逐渐趋同演化，丧失了物种多样性,经过$100$代后，每个个体的适
应度已相同，很难进化，最后无奈放弃此方法，猜测是遗传算法并不适合此种情况神经
网络的训练，但依旧提供了一种解决问题的新思路.

在数据具有明显季节性质，且相邻的日期可能相互影响的情况下，我们也
对时间序列模型进行了一定的尝试和研究，最后得到的效果也不如神经网
络回归模型，原因可能是相互影响因素已经体现在了自变量中.经过进一步
的分析，尽管数据间并非存在明显的非线性关系，但是由于数据具有取值
范围相对局限的特点，我们尝试了决策树模型，最终得到了满意
的结果，绝对平均误差降到了$2.6$mm，正确率飙升到$90\%$左右.尝试和分
析过后，最后认为该决策树模型更加准确.

该模型具有预测率较高，和可以轻易扩展到新的自变量的优点.生成该模型
的方法可以轻易地被用于生成任何局部降雨模型，非常简单易行.在考虑到气
象的周期性而忽略人为影响的情况下，本模型具有较为准确的预测能力.
同时，实际上，降雨量的影响因素更加复杂，采用该模型时可以增加自变量
的数量，进一步提高模型的准确度，具有一定的现实指导意义
